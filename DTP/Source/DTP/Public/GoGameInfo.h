// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <vector>

// ���� �� �⺻ ��
constexpr short BOARD_SIZE = 19;
constexpr short EMPTY = 0;
constexpr short PLAYER1 = 1;
constexpr short PLAYER2 = 2;

// �߽� ��ǥ�� �̵� ����
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

	bool PlaceStone(int x, int y, int player, FVector& OutPosition);	// ���� ���� �δ� �޼ҵ�
	bool CheckPlaceStone(int x, int y);
	bool CheckDirection(int x, int y, int player, int dx, int dy);		// �밢������ 5������ Ȯ��
	bool CheckWin(int player);											// �ش� �÷��̾ �̰���� Ȯ��
	
	std::pair<int, int> AIPlaceStone();

private:
	// =============================================================================
	//									AI
	// =============================================================================

	bool IsEmptyPosition(int x, int y);						// x, y�� �θ� AI �¸� ����
	bool CanWinNextMove(int x, int y);						// x,y�� myStoneType�� ���� �� ��� �¸��� �� �ִ��� Ȯ��
	bool OpponentCanWinNextMove(int x, int y);				// ��밡 ���� �Ͽ� ���⿡ �θ� �¸��� �� �ִ���, �� �� �ڸ��� ���ƾ� �ϴ��� üũ
	bool OpponentCanForceWin(int x, int y);					// ��밡 �����¸� ����(������� ��) ������ �� �ִ� ��ġ ���
	bool CanForceWin(int x, int y);							// �ڽ��� �����¸� ����(������� ��) ������ �� �ִ� ���
	int EvaluatePosition(int x, int y);						// �߾ӿ� �������� ������ ����, �ֺ��� �� ���� ������ ���� ���
	bool IsFiveInARow(int startX, int startY, int stone);	// Ư�� ��ġ�� Ư�� ���� �������� �� 5�� �ϼ� ���� üũ�ϴ� ���� �Լ�

	// =============================================================================
	//								Place Rule
	// =============================================================================

	bool IsDoubleThree(int x, int y);						// 3x3�� �������� ����
	bool IsDoubleFour(int x, int y);						// 4x4�� �������� ����
	bool IsOpenThree(int x, int y, int dir);				// 3���� ���� �� �ִ��� ����
	bool CheckFakeThree(int x, int y, int dir);				// ���� �ݼ� üũ
	bool IsFour(int x, int y, int dir);						// 4�� �������� Ȯ��
	int IsOpenFour(int x, int y, int dir);					// 4���� ���� �� �ִ��� ����
	bool IsFive(int x, int y, int dir = 15);				// �������� �ƴ��� Ȯ��
	bool IsOverLine(int x, int y, int dir = 15);			// ������� Ȯ�� 
	int CheckFiveOrOverLine(int x, int y, int dir = 15);	// ���� ������� Ȯ��
	int CheckIsFive(int nLine);								// ������� �������� Ȯ��
	bool IsForbidden(int x, int y);




	std::vector<std::vector<short>> board;
};
