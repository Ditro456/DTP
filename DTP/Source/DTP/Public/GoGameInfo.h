// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <vector>

// 보드 판 기본 값
constexpr short BOARD_SIZE = 19;
constexpr short EMPTY = 0;
constexpr short PLAYER1 = 1;
constexpr short PLAYER2 = 2;

// 중심 좌표와 이동 간격
constexpr float CENTER_X = 0.0f;
constexpr float CENTER_Y = 0.0f;
constexpr float CENTER_Z = -504.0f;
constexpr float STEP_X = 9.0f;
constexpr float STEP_Y = -9.0f;

class DTP_API GoGameInfo
{
public:
	GoGameInfo(const UClass* whiteStone, const UClass* blackStone);
	~GoGameInfo();

	bool PlaceStone(int x, int y, int player, FVector& OutPosition);
	bool CheckDirection(int x, int y, int player, int dx, int dy);
	bool CheckWin(int player);

private:

	std::vector<std::vector<short>> board;
};
