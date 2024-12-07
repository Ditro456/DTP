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

	bool PlaceStone(int x, int y, int player, FVector& OutPosition);	// 오목 알을 두는 메소드
	bool CheckPlaceStone(int x, int y);
	bool CheckDirection(int x, int y, int player, int dx, int dy);		// 대각선으로 5개인지 확인
	bool CheckWin(int player);											// 해당 플레이어가 이겼는지 확인
	
	std::pair<int, int> AIPlaceStone();

private:
	// =============================================================================
	//									AI
	// =============================================================================

	bool IsEmptyPosition(int x, int y);						// x, y에 두면 AI 승리 여부
	bool CanWinNextMove(int x, int y);						// x,y에 myStoneType을 뒀을 때 즉시 승리할 수 있는지 확인
	bool OpponentCanWinNextMove(int x, int y);				// 상대가 다음 턴에 여기에 두면 승리할 수 있는지, 즉 이 자리를 막아야 하는지 체크
	bool OpponentCanForceWin(int x, int y);					// 상대가 강제승리 패턴(이중장목 등) 형성할 수 있는 위치 방어
	bool CanForceWin(int x, int y);							// 자신이 강제승리 패턴(이중장목 등) 형성할 수 있는 경우
	int EvaluatePosition(int x, int y);						// 중앙에 가까울수록 점수가 높고, 주변에 내 돌이 많으면 점수 상승
	bool IsFiveInARow(int startX, int startY, int stone);	// 특정 위치에 특정 돌을 가정했을 때 5목 완성 여부 체크하는 헬퍼 함수

	// =============================================================================
	//								Place Rule
	// =============================================================================

	bool IsDoubleThree(int x, int y);						// 3x3이 나오는지 여부
	bool IsDoubleFour(int x, int y);						// 4x4가 나오는지 여부
	bool IsOpenThree(int x, int y, int dir);				// 3개가 나올 수 있는지 여부
	bool CheckFakeThree(int x, int y, int dir);				// 거짓 금수 체크
	bool IsFour(int x, int y, int dir);						// 4가 나오는지 확인
	int IsOpenFour(int x, int y, int dir);					// 4개가 나올 수 있는지 여부
	bool IsFive(int x, int y, int dir = 15);				// 오목인지 아닌지 확인
	bool IsOverLine(int x, int y, int dir = 15);			// 장목인지 확인 
	int CheckFiveOrOverLine(int x, int y, int dir = 15);	// 오목 장목인지 확인
	int CheckIsFive(int nLine);								// 장목인지 오목인지 확인
	bool IsForbidden(int x, int y);




	std::vector<std::vector<short>> board;
};
