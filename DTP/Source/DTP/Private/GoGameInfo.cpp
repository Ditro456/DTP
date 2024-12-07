// Fill out your copyright notice in the Description page of Project Settings.

#include "GoGameInfo.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

GoGameInfo::GoGameInfo(const UClass* whiteStone, const UClass* blackStone) : 
    board(BOARD_SIZE, std::vector<short>(BOARD_SIZE, EMPTY))
{
	
}

GoGameInfo::~GoGameInfo()
{
}

bool GoGameInfo::PlaceStone(int x, int y, int player, FVector& OutPosition)
{
    // 돌을 놓기 (x, y 좌표가 유효하고 빈 칸이면 돌을 놓음)
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] != EMPTY)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid move!"));
        return false;
    }

    board[x][y] = player;

    // 해당 위치 출력
    float posX = (x - 9 - CENTER_X) * STEP_X;
    float posY = (y - 9 - CENTER_X) * STEP_Y;

    OutPosition = FVector(posY, posX, CENTER_Z);

    return true;
}

bool GoGameInfo::CheckPlaceStone(int x, int y)
{
    // 돌을 놓기 (x, y 좌표가 유효하고 빈 칸이면 돌을 놓음)
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] != EMPTY)
        return false;
    
    return true;
}

bool GoGameInfo::CheckDirection(int x, int y, int player, int dx, int dy)
{
    int count = 0;

    for (int i = 0; i < 5; ++i) 
    {
        int nx = x + i * dx;
        int ny = y + i * dy;

        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny] == player)
            count++;

        else
            break;
    }

    return count == 5;
}

bool GoGameInfo::CheckWin(int player)
{
    // 승리 조건 확인 (연속된 5개의 돌 확인)
    for (int x = 0; x < BOARD_SIZE; ++x) 
    {
        for (int y = 0; y < BOARD_SIZE; ++y) 
        {
            if (board[x][y] == player) 
            {
                if (CheckDirection(x, y, player, 1, 0) || // 가로
                    CheckDirection(x, y, player, 0, 1) || // 세로
                    CheckDirection(x, y, player, 1, 1) || // 대각선
                    CheckDirection(x, y, player, 1, -1))  // 대각선
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::pair<int, int> GoGameInfo::AIPlaceStone()
{
    // 1. 즉시 승리 수 탐색
    for (int x = 0; x < BOARD_SIZE; x++) 
    {
        for (int y = 0; y < BOARD_SIZE; y++) 
        {
            if (CanWinNextMove(x, y)) 
            {
                if (!IsForbidden(x, y)) 
                    return { x, y };
            }
        }
    }

    // 2. 상대방이 다음 턴에 이길 수 있는 수 방어
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++) 
        {
            if (OpponentCanWinNextMove(x, y)) 
            {
                if (!IsForbidden(x, y))
                    return { x, y };
            }
        }
    }

    // 2.5. 상대가 강제승리 패턴(이중장목 등) 형성할 수 있는 위치 방어
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            if (OpponentCanForceWin(x, y))
            {
                if (!IsForbidden(x, y))
                    return { x, y };
            }
        }
    }

    // 3. 자신이 강제승리 패턴(이중장목 등) 형성할 수 있는 경우
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            if (CanForceWin(x, y))
            {
                if (!IsForbidden(x, y))
                    return { x, y };
            }
        }
    }

    // 4. 가치 평가에 따라 모든 후보 위치 수집
    std::vector<std::tuple<int, int, int>> candidates; // (score, x, y)

    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            if (IsEmptyPosition(x, y))
            {
                int score = EvaluatePosition(x, y);
                candidates.push_back(std::make_tuple(score, x, y));
            }
        }
    }

    // 점수를 기준으로 내림차순 정렬
    std::sort(candidates.begin(), candidates.end(), [](auto& a, auto& b) {
        return std::get<0>(a) > std::get<0>(b);
        });

    // 5. 후보들 중 Forbidden이 아닌 곳 탐색
    for (auto& cand : candidates)
    {
        int score = std::get<0>(cand);
        int cx = std::get<1>(cand);
        int cy = std::get<2>(cand);

        // Forbidden 체크
        if (!IsForbidden(cx, cy))
        {
            return { cx, cy };
        }
    }

    // 6. 모두 실패하면 랜덤으로 둔다
    srand((unsigned)time(NULL));

    for (int i = 0; i < 100; i++) 
    {
        int randX = rand() % BOARD_SIZE;
        int randY = rand() % BOARD_SIZE;

        if (!IsForbidden(randX, randY))
            return { randX, randY };
    }

    return { -1, -1 };
}

bool GoGameInfo::IsEmptyPosition(int x, int y)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) 
        return false;

    return (board[x][y] == EMPTY);
}

bool GoGameInfo::CanWinNextMove(int x, int y)
{
    if (!IsEmptyPosition(x, y)) 
        return false;

    // 가상의 착수
    board[x][y] = 1;
    bool win = IsFiveInARow(x, y, 1);

    // 롤백
    board[x][y] = EMPTY;

    return win;
}

bool GoGameInfo::OpponentCanWinNextMove(int x, int y)
{
    // 여기가 비어있고, 상대가 여기에 돌을 놓으면 5목 완성?
    if (!IsEmptyPosition(x, y)) 
        return false;

    board[x][y] = 2;
    bool oppWin = IsFiveInARow(x, y, 2);
    board[x][y] = EMPTY;

    return oppWin;
}

bool GoGameInfo::OpponentCanForceWin(int x, int y)
{
    // 해당 위치에 상대 돌(2번 돌)을 가상으로 둔다.
    if (!IsEmptyPosition(x, y))
        return false;

    board[x][y] = 2;

    int winningMoves = 0;

    // 모든 빈칸을 탐색하면서 상대가 바로 다음 수에 이길 수 있는지 확인
    for (int xx = 0; xx < BOARD_SIZE; xx++)
    {
        for (int yy = 0; yy < BOARD_SIZE; yy++)
        {
            if (OpponentCanWinNextMove(xx, yy))
            {
                winningMoves++;

                // 2개 이상의 승리 가능 수를 만들 수 있다면 강제승리 패턴으로 본다.
                if (winningMoves >= 2)
                {
                    board[x][y] = EMPTY; // 롤백
                    return true;
                }
            }
        }
    }

    // 롤백
    board[x][y] = EMPTY;
    return false;
}

bool GoGameInfo::CanForceWin(int x, int y)
{
    // 해당 위치에 상대 돌(1번 돌)을 가상으로 둔다.
    if (!IsEmptyPosition(x, y))
        return false;

    board[x][y] = 1;

    int winningMoves = 0;

    // 모든 빈칸을 탐색하면서 상대가 바로 다음 수에 이길 수 있는지 확인
    for (int xx = 0; xx < BOARD_SIZE; xx++)
    {
        for (int yy = 0; yy < BOARD_SIZE; yy++)
        {
            if (CanWinNextMove(xx, yy))
            {
                winningMoves++;

                // 2개 이상의 승리 가능 수를 만들 수 있다면 강제승리 패턴으로 본다.
                if (winningMoves >= 2)
                {
                    board[x][y] = EMPTY; // 롤백
                    return true;
                }
            }
        }
    }

    // 롤백
    board[x][y] = EMPTY;
    return false;
}

int GoGameInfo::EvaluatePosition(int x, int y)
{
    if (!IsEmptyPosition(x, y)) 
        return -999999; // 이미 차있으면 최악

    // 중앙에 가까울수록 점수 높게
    int center = BOARD_SIZE / 2;
    int distX = abs(x - center);
    int distY = abs(y - center);
    int baseScore = 1000 - (distX + distY) * 10;

    // 주변 8방향 내 돌 수 세서 가중치 부여
    int allyCount = 0;
    for (int dx = -1; dx <= 1; dx++) 
    {
        for (int dy = -1; dy <= 1; dy++) 
        {
            if (dx == 0 && dy == 0) 
                continue;
            
            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) 
                continue;

            if (board[nx][ny] == 1) 
                allyCount++;
        }
    }

    return baseScore + allyCount * 50;
}

bool GoGameInfo::IsFiveInARow(int startX, int startY, int stone)
{
    // 4가지 방향: 가로(1,0), 세로(0,1), 대각1(1,1), 대각2(1,-1)
    int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    for (auto& dir : directions) 
    {
        int count = 1;

        // forward direction
        int dx = dir[0], dy = dir[1];

        // 앞으로 탐색
        for (int i = 1; i < 5; i++) 
        {
            int nx = startX + dx * i;
            int ny = startY + dy * i;

            if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) break;
            if (board[nx][ny] == stone) count++;

            else break;
        }

        // backward direction
        for (int i = 1; i < 5; i++) 
        {
            int nx = startX - dx * i;
            int ny = startY - dy * i;

            if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) break;
            if (board[nx][ny] == stone) count++;

            else break;
        }

        if (count >= 5) return true;
    }

    return false;
}

bool GoGameInfo::IsDoubleThree(int x, int y)
{
    if (!CheckPlaceStone(x, y))
        return false;

    else if (IsFive(x, y))
        return false;

    else if (IsOverLine(x, y))
        return false;

    int countThree = 0;

    for (int i = 0; i <= 4; i++)
    {
        if (IsOpenThree(x, y, i))
            countThree += 1;
    }

    return countThree >= 2;
}

bool GoGameInfo::IsDoubleFour(int x, int y)
{
    if (!CheckPlaceStone(x, y))
        return false;

    else if (IsFive(x, y))
        return false;

    else if (IsOverLine(x, y))
        return false;

    int countFour = 0;

    for (int i = 0; i <= 4; i++)
    {
        if (IsOpenFour(x, y, i) == 2)
            countFour += 2;

        else if (IsFour(x, y, i))
            countFour += 1;
    }

    return countFour >= 2;
}

bool GoGameInfo::IsOpenThree(int x, int y, int dir)
{
    if (IsFive(x, y))
        return false;

    else if (IsOverLine(x, y))
        return false;

    board[x][y] = 1;

    if (dir == 1)
    {
        int i = x - 1;

        while (i >= 0) 
        {
            if (board[i][y] == 1)
                i--;

            else if (board[i][y] == EMPTY)
            {
                if (CheckFakeThree(i, y, dir)) 
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        i = x + 1;

        while (i < BOARD_SIZE) 
        {
            if (board[i][y] == 1)
                i++;

            else if (board[i][y] == EMPTY) 
            {
                if (CheckFakeThree(i, y, dir)) 
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }
    }

    else if (dir == 2) 
    {
        int j = y - 1;

        while (j >= 0) 
        {
            if (board[x][j] == 1)
                j--;

            else if (board[x][j] == EMPTY)
            {
                if (CheckFakeThree(x, j, dir))
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        j = y + 1;

        while (j < BOARD_SIZE) 
        {
            if (board[x][j] == 1)
                j++;

            else if (board[x][j] == EMPTY) 
            {
                if (CheckFakeThree(x, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }
    }

    else if (dir == 3)
    {
        int i = x - 1;
        int j = y - 1;

        while (i >= 0 && j >= 0)
        {
            if (board[i][j] == 1) 
            {
                i--;
                j--;
            }

            else if (board[i][j] == EMPTY)
            {
                if (CheckFakeThree(i, j, dir))
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        i = x + 1;
        j = y + 1;

        while (i < BOARD_SIZE && j < BOARD_SIZE) 
        {
            if (board[i][j] == 1)
            {
                i++;
                j++;
            }

            else if (board[i][j] == EMPTY) 
            {
                if (CheckFakeThree(i, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }
    }

    else if (dir == 4) 
    {
        int i = x - 1;
        int j = y + 1;

        while (i >= 0 && j < BOARD_SIZE) 
        {
            if (board[i][j] == 1)
            {
                i--;
                j++;
            }

            else if (board[i][j] == EMPTY)
            {
                if (CheckFakeThree(i, j, dir))
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        i = x + 1;
        j = y - 1;

        while (i < BOARD_SIZE && j >= 0)
        {
            if (board[i][j] == 1)
            {
                i++;
                j--;
            }

            else if (board[i][j] == EMPTY)
            {
                if (CheckFakeThree(i, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }
    }

    board[x][y] = EMPTY;
    return false;
}

bool GoGameInfo::CheckFakeThree(int x, int y, int dir)
{
    return (IsOpenFour(x, y, dir) == 1) && !IsDoubleFour(x, y) && !IsDoubleThree(x, y);
}

bool GoGameInfo::IsFour(int x, int y, int dir)
{
    if (board[x][y] != EMPTY)
        return false;

    else if (IsFive(x, y))
        return false;

    else if (IsOverLine(x, y))
        return false;

    board[x][y] = 1;

    if (dir == 1) 
    {
        int i = x - 1;

        while (i >= 0) 
        {
            if (board[i][y] == 1)
                i--;

            else if (board[i][y] == EMPTY)
            {
                if (IsFive(i, y, dir))
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        i = x + 1;

        while (i < BOARD_SIZE) 
        {
            if (board[i][y] == 1)
                i++;

            else if (board[i][y] == EMPTY) 
            {
                if (IsFive(i, y, dir)) 
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        board[x][y] = EMPTY;
        return false;
    }

    else if (dir == 2) 
    {
        int j = y - 1;

        while (j >= 0) 
        {
            if (board[x][j] == 1)
                j--;

            else if (board[x][j] == EMPTY) 
            {
                if (IsFive(x, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        j = y + 1;

        while (j < BOARD_SIZE) 
        {
            if (board[x][j] == 1)
                j++;

            else if (board[x][j] == EMPTY)
            {
                if (IsFive(x, j, dir))
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        board[x][y] = EMPTY;
        return false;
    }

    else if (dir == 3)
    {
        int i = x - 1;
        int j = y - 1;

        while (i >= 0 && j >= 0) 
        {
            if (board[i][j] == 1)
            {
                i--;
                j--;
            }

            else if (board[i][j] == EMPTY) 
            {
                if (IsFive(i, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        i = x + 1;
        j = y + 1;

        while (i < BOARD_SIZE && j < BOARD_SIZE)
        {
            if (board[i][j] == 1)
            {
                i++;
                j++;
            }

            else if (board[i][j] == EMPTY)
            {
                if (IsFive(i, j, dir))
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        board[x][y] = EMPTY;
        return false;
    }

    else if (dir == 4) 
    {
        int i = x - 1;
        int j = y + 1;

        while (i >= 0 && j < BOARD_SIZE) 
        {
            if (board[i][j] == 1) 
            {
                i--;
                j++;
            }

            else if (board[i][j] == EMPTY)
            {
                if (IsFive(i, j, dir))
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        i = x + 1;
        j = y - 1;

        while (i < BOARD_SIZE && j >= 0)
        {
            if (board[i][j] == 1) 
            {
                i++;
                j--;
            }

            else if (board[i][j] == EMPTY) 
            {
                if (IsFive(i, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return true;
                }

                else
                    break;
            }

            else
                break;
        }

        board[x][y] = EMPTY;
        return false;
    }

    board[x][y] = EMPTY;
    return false;
}

int GoGameInfo::IsOpenFour(int x, int y, int dir)
{
    if (board[x][y] != EMPTY)
        return 0;

    else if (IsFive(x, y))
        return 0;

    else if (IsOverLine(x, y))
        return 0;

    board[x][y] = 1;
    int nLine = 1;

    if (dir == 1) 
    {
        int i = x - 1;

        while (i >= -1) 
        {
            if (board[i][y] == 1) 
            {
                i--;
                nLine++;
            }

            else if (board[i][y] == EMPTY) 
            {
                if (!IsFive(i, y, dir)) 
                {
                    board[x][y] = EMPTY;
                    return 0;
                }

                else
                    break;
            }

            else 
            {
                board[x][y] = EMPTY;
                return 0;
            }
        }

        i = x + 1;

        while (i < BOARD_SIZE)
        {
            if (board[i][y] == 1)
            {
                i++;
                nLine++;
            }

            else if (board[i][y] == EMPTY)
            {
                if (IsFive(i, y, dir)) 
                {
                    board[x][y] = EMPTY;
                    return ((nLine == 4) ? 1 : 2);
                }

                else
                    break;
            }

            else
                break;
        }

        board[x][y] = EMPTY;
        return 0;
    }

    else if (dir == 2) 
    {
        int j = y - 1;

        while (j >= -1)
        {
            if (board[x][j] == 1) 
            {
                j--;
                nLine++;
            }

            else if (board[x][j] == EMPTY)
            {
                if (!IsFive(x, j, dir))
                {
                    board[x][y] = EMPTY;
                    return 0;
                }

                else
                    break;
            }

            else 
            {
                board[x][y] = EMPTY;
                return 0;
            }
        }

        j = y + 1;

        while (j < BOARD_SIZE) 
        {
            if (board[x][j] == 1)
            {
                j++;
                nLine++;
            }

            else if (board[x][j] == EMPTY)
            {
                if (IsFive(x, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return ((nLine == 4) ? 1 : 2);
                }

                else
                    break;
            }

            else
                break;
        }

        board[x][y] = EMPTY;
        return 0;
    }

    else if (dir == 3) 
    {
        int i = x - 1;
        int j = y - 1;

        while (i >= -1 && j >= -1) 
        {
            if (board[i][j] == 1) 
            {
                i--;
                j--;
                nLine++;
            }

            else if (board[i][j] == EMPTY) 
            {
                if (!IsFive(i, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return 0;
                }

                else
                    break;
            }

            else 
            {
                board[x][y] = EMPTY;
                return 0;
            }
        }

        i = x + 1;
        j = y + 1;

        while (i < BOARD_SIZE && j < BOARD_SIZE) 
        {
            if (board[i][j] == 1) 
            {
                i++;
                j++;
                nLine++;
            }

            else if (board[i][j] == EMPTY) 
            {
                if (IsFive(i, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return ((nLine == 4) ? 1 : 2);
                }

                else
                    break;
            }

            else
                break;
        }

        board[x][y] = EMPTY;
        return 0;
    }

    else if (dir == 4) 
    {
        int i = x - 1;
        int j = y + 1;

        while (i >= -1 && j < BOARD_SIZE) 
        {
            if (board[i][j] == 1) 
            {
                i--;
                j++;
                nLine++;
            }

            else if (board[i][j] == EMPTY) 
            {
                if (!IsFive(i, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return 0;
                }

                else
                    break;
            }

            else 
            {
                board[x][y] = EMPTY;
                return 0;
            }

        }

        i = x + 1;
        j = y - 1;

        while (i < BOARD_SIZE && j >= -1) 
        {
            if (board[i][j] == 1) 
            {
                i++;
                j--;
                nLine++;
            }

            else if (board[i][j] == EMPTY) 
            {
                if (IsFive(i, j, dir)) 
                {
                    board[x][y] = EMPTY;
                    return ((nLine == 4) ? 1 : 2);
                }

                else
                    break;
            }

            else
                break;
        }

        board[x][y] = EMPTY;
        return 0;
    }

    board[x][y] = EMPTY;
    return 0;
}

bool GoGameInfo::IsFive(int x, int y, int dir)
{
    return CheckFiveOrOverLine(x, y, dir) == 1;
}

bool GoGameInfo::IsOverLine(int x, int y, int dir)
{
    return CheckFiveOrOverLine(x, y, dir) == 2;
}

int GoGameInfo::CheckFiveOrOverLine(int x, int y, int dir)
{
    int findDir = 0;
    int isOverLine = false;

    if (board[x][y] != EMPTY)
        return 0;

    if (dir == 15)
        findDir = 15;

    else
        findDir = 1 << (dir - 1);

    board[x][y] = 1;
    int nLine = 1;

    if (findDir & 1) 
    {
        nLine = 1;
        int i = x - 1;

        while (i >= 0) 
        {
            if (board[i--][y] == 1)
                nLine++;

            else
                break;
        }

        i = x + 1;

        while (i < BOARD_SIZE) 
        {
            if (board[i++][y] == 1)
                nLine++;

            else
                break;
        }

        const int checkFive = CheckIsFive(nLine);

        if (checkFive == 1)
        {
            board[x][y] = EMPTY;
            return 1;
        }

        else if (checkFive == 2) 
            isOverLine = true;
    }

    if (findDir & 2) 
    {
        nLine = 1;
        int j = y - 1;

        while (j >= 0) 
        {
            if (board[x][j--] == 1)
                nLine++;

            else
                break;
        }

        j = y + 1;

        while (j < BOARD_SIZE) 
        {
            if (board[x][j++] == 1)
                nLine++;

            else
                break;
        }

        const int checkFive = CheckIsFive(nLine);

        if (checkFive == 1) 
        {
            board[x][y] = EMPTY;
            return 1;
        }

        else if (checkFive == 2)
            isOverLine = true;
    }

    if (findDir & 4) 
    {
        nLine = 1;

        int i = x - 1;
        int j = y - 1;

        while (i >= 0 && j >= 0) 
        {
            if (board[i--][j--] == 1)
                nLine++;

            else
                break;
        }

        i = x + 1;
        j = y + 1;

        while (i < BOARD_SIZE && j < BOARD_SIZE) 
        {
            if (board[i++][j++] == 1)
                nLine++;

            else
                break;
        }
        const int checkFive = CheckIsFive(nLine);

        if (checkFive == 1)
        {
            board[x][y] = EMPTY;
            return 1;
        }

        else if (checkFive == 2)
            isOverLine = true;
    }

    if (findDir & 8) 
    {
        nLine = 1;

        int i = x - 1;
        int j = y + 1;

        while (i >= 0 && j < BOARD_SIZE) 
        {
            if (board[i--][j++] == 1)
                nLine++;

            else
                break;
        }

        i = x + 1;
        j = y - 1;

        while (i < BOARD_SIZE && j >= 0) 
        {
            if (board[i++][j--] == 1)
                nLine++;

            else
                break;
        }
        const int checkFive = CheckIsFive(nLine);

        if (checkFive == 1)
        {
            board[x][y] = EMPTY;
            return 1;
        }

        else if (checkFive == 2)
            isOverLine = true;
    }

    board[x][y] = EMPTY;
    return isOverLine ? 2 : 0;
}

int GoGameInfo::CheckIsFive(int nLine)
{
    if (nLine >= 5) 
    {
        if (nLine == 5)
            return 1;

        else
            return 2;
    }

    return 0;
}

bool GoGameInfo::IsForbidden(int x, int y)
{
    if (!CheckPlaceStone(x, y))
    {
        FString pos = FString::Printf(TEXT("No Place : (%d, %d)"), x, y);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, pos);
        return true;
    }

    // 3x3
    if (IsDoubleThree(x, y))
    {
        FString pos = FString::Printf(TEXT("3x3 : (%d, %d)"), x, y);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, pos);
        return true;
    }

    // 4x4
    if (IsDoubleFour(x, y))
    {
        FString pos = FString::Printf(TEXT("4x4 : (%d, %d)"), x, y);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, pos);
        return true;
    }

    // 장목 여부
    if (IsOverLine(x, y))
    {
        FString pos = FString::Printf(TEXT("> 5 : (%d, %d)"), x, y);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, pos);
        return true;
    }

    board[x][y] = EMPTY;

    return false;
}