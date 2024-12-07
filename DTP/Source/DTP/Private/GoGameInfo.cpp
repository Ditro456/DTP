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
    // ���� ���� (x, y ��ǥ�� ��ȿ�ϰ� �� ĭ�̸� ���� ����)
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] != EMPTY)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid move!"));
        return false;
    }

    board[x][y] = player;

    // �ش� ��ġ ���
    float posX = (x - 9 - CENTER_X) * STEP_X;
    float posY = (y - 9 - CENTER_X) * STEP_Y;

    OutPosition = FVector(posY, posX, CENTER_Z);

    return true;
}

bool GoGameInfo::CheckPlaceStone(int x, int y)
{
    // ���� ���� (x, y ��ǥ�� ��ȿ�ϰ� �� ĭ�̸� ���� ����)
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
    // �¸� ���� Ȯ�� (���ӵ� 5���� �� Ȯ��)
    for (int x = 0; x < BOARD_SIZE; ++x) 
    {
        for (int y = 0; y < BOARD_SIZE; ++y) 
        {
            if (board[x][y] == player) 
            {
                if (CheckDirection(x, y, player, 1, 0) || // ����
                    CheckDirection(x, y, player, 0, 1) || // ����
                    CheckDirection(x, y, player, 1, 1) || // �밢��
                    CheckDirection(x, y, player, 1, -1))  // �밢��
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
    // 1. ��� �¸� �� Ž��
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

    // 2. ������ ���� �Ͽ� �̱� �� �ִ� �� ���
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

    // 2.5. ��밡 �����¸� ����(������� ��) ������ �� �ִ� ��ġ ���
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

    // 3. �ڽ��� �����¸� ����(������� ��) ������ �� �ִ� ���
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

    // 4. ��ġ �򰡿� ���� ��� �ĺ� ��ġ ����
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

    // ������ �������� �������� ����
    std::sort(candidates.begin(), candidates.end(), [](auto& a, auto& b) {
        return std::get<0>(a) > std::get<0>(b);
        });

    // 5. �ĺ��� �� Forbidden�� �ƴ� �� Ž��
    for (auto& cand : candidates)
    {
        int score = std::get<0>(cand);
        int cx = std::get<1>(cand);
        int cy = std::get<2>(cand);

        // Forbidden üũ
        if (!IsForbidden(cx, cy))
        {
            return { cx, cy };
        }
    }

    // 6. ��� �����ϸ� �������� �д�
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

    // ������ ����
    board[x][y] = 1;
    bool win = IsFiveInARow(x, y, 1);

    // �ѹ�
    board[x][y] = EMPTY;

    return win;
}

bool GoGameInfo::OpponentCanWinNextMove(int x, int y)
{
    // ���Ⱑ ����ְ�, ��밡 ���⿡ ���� ������ 5�� �ϼ�?
    if (!IsEmptyPosition(x, y)) 
        return false;

    board[x][y] = 2;
    bool oppWin = IsFiveInARow(x, y, 2);
    board[x][y] = EMPTY;

    return oppWin;
}

bool GoGameInfo::OpponentCanForceWin(int x, int y)
{
    // �ش� ��ġ�� ��� ��(2�� ��)�� �������� �д�.
    if (!IsEmptyPosition(x, y))
        return false;

    board[x][y] = 2;

    int winningMoves = 0;

    // ��� ��ĭ�� Ž���ϸ鼭 ��밡 �ٷ� ���� ���� �̱� �� �ִ��� Ȯ��
    for (int xx = 0; xx < BOARD_SIZE; xx++)
    {
        for (int yy = 0; yy < BOARD_SIZE; yy++)
        {
            if (OpponentCanWinNextMove(xx, yy))
            {
                winningMoves++;

                // 2�� �̻��� �¸� ���� ���� ���� �� �ִٸ� �����¸� �������� ����.
                if (winningMoves >= 2)
                {
                    board[x][y] = EMPTY; // �ѹ�
                    return true;
                }
            }
        }
    }

    // �ѹ�
    board[x][y] = EMPTY;
    return false;
}

bool GoGameInfo::CanForceWin(int x, int y)
{
    // �ش� ��ġ�� ��� ��(1�� ��)�� �������� �д�.
    if (!IsEmptyPosition(x, y))
        return false;

    board[x][y] = 1;

    int winningMoves = 0;

    // ��� ��ĭ�� Ž���ϸ鼭 ��밡 �ٷ� ���� ���� �̱� �� �ִ��� Ȯ��
    for (int xx = 0; xx < BOARD_SIZE; xx++)
    {
        for (int yy = 0; yy < BOARD_SIZE; yy++)
        {
            if (CanWinNextMove(xx, yy))
            {
                winningMoves++;

                // 2�� �̻��� �¸� ���� ���� ���� �� �ִٸ� �����¸� �������� ����.
                if (winningMoves >= 2)
                {
                    board[x][y] = EMPTY; // �ѹ�
                    return true;
                }
            }
        }
    }

    // �ѹ�
    board[x][y] = EMPTY;
    return false;
}

int GoGameInfo::EvaluatePosition(int x, int y)
{
    if (!IsEmptyPosition(x, y)) 
        return -999999; // �̹� �������� �־�

    // �߾ӿ� �������� ���� ����
    int center = BOARD_SIZE / 2;
    int distX = abs(x - center);
    int distY = abs(y - center);
    int baseScore = 1000 - (distX + distY) * 10;

    // �ֺ� 8���� �� �� �� ���� ����ġ �ο�
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
    // 4���� ����: ����(1,0), ����(0,1), �밢1(1,1), �밢2(1,-1)
    int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    for (auto& dir : directions) 
    {
        int count = 1;

        // forward direction
        int dx = dir[0], dy = dir[1];

        // ������ Ž��
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

    // ��� ����
    if (IsOverLine(x, y))
    {
        FString pos = FString::Printf(TEXT("> 5 : (%d, %d)"), x, y);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, pos);
        return true;
    }

    board[x][y] = EMPTY;

    return false;
}