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