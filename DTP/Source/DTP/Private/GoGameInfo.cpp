// Fill out your copyright notice in the Description page of Project Settings.

#include "GoGameInfo.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

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
    //FString message = FString::Printf(TEXT("Stone placed at 3D position: (%f, %f, %f)"), posX, posY, CENTER_Z);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);

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