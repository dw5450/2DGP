#pragma once

#include "Object.h"
#include "Monster.h"

class Player :public Object{
private:
	int Hp = 1000;
	int Time = 1000;
	bool end = false;
public:
	Player();
	Player(const long x, const long y, const SIZE size);
	~Player();
	
	bool crash(Monster * MonsterPt);			//충돌 체크 (몬스터 포인터)		//변경된 코드
	void crash(Item * ItemPt);								//충돌 체크 (몬스터 포인터)		//변경된 코드
	void crash(HWND hWnd);
	// 충돌하면 y축으로 하강? 바람크기 감소?->다른 물체들(지형물,몬스터)과 충돌에 따라 
	// 바람의 크기가 감소하려면 private멤버로 값을 저장하고있어야할듯. 그러면 조금 바꿔야함
	virtual void draw();

	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS);						//추가된 코드
	virtual void MoveTo(const long x, const long y);				//이동할 x 방향 , y 방향			//추가된 코드
	virtual void Move();											//이동							//추가된 코드

	bool GetEnd(){ return end; }
	virtual long GetResistance();									//저항 가져오기					//추가된 코드
	double GetSpeedXpos(){ return SpeedXpos; }						//MoveToXpos가져오기	,디버그용	
	double GetSpeedYpos(){ return SpeedYpos; }						//MoveToYpos가져오기	,디버그용


	virtual	double GetResistanceXpos(){ return resistanceXpos; }	//resistanceXpos 가져오기		
	virtual	double GetResistanceYpos(){ return resistanceYpos; }	//resistanceXpos 가져오기	
	int GetHp(){ return Hp; }
	int GetTime(){ return Time; }
	void SetTime(int TIME){Time = TIME;  if (Time < 0) end = true; }

	
	
	// 좌표값에 access하기 위한 함수들
	const POINT getPlayer();
	void putPlayer(const int x, const int y);
	
};