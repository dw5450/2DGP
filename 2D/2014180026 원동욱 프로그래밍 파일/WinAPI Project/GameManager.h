#pragma once

#include "stdafx.h"
class GameManager{
private:
	Object** objectArray;
	Item itemStock[3];					// ������ ������ ��������
	int objectCount;
	int ScreenType;

	Player* controlPlayer;

	int stage = 1;
public:
	GameManager();
	~GameManager();
	void startGame();			// �����Ҷ� ��� ������ �ʱ�ȭ�մϴ�.
	void draw(HDC hdc);				// GameManager�� ��ϵ� ��� �׸��� �׸��ϴ�!
	
	void deleteObject();
	void insertObject(Object* a);		// GameManager�� ������Ʈ�� �߰��մϴ�. �ִ� 255��

	void setPlayer(Player*);
	void setPlayerRes(long , long );


	void setStage(int st){ stage = st; load(stage); }
	int getStage(){ return stage; }

	void SetScreenType(int SCREENTYPE){ ScreenType = SCREENTYPE; }
	int GetScreenType(){ return ScreenType; }

	
	void crash();
	// ���Ӿȿ� ���� ��ɱ��� �־�����ô�. ��������(�����Ȳ �ƴ�!!)�� ���̺�/�ε�
	void save();
	void load(int);
};