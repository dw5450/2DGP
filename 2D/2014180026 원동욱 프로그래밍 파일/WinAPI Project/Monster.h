#pragma once

#include "Object.h"

class Monster :public Object{
private:
	int monsterType;				// 몬스터들도 따로 종류별로 클래스로 만드는게 나을것같으나 여러 종류를 만들것도 아니거니와 몬스터 종류마다 다른 행동을 하진 않는다(아마도).
								// 따라서, 몬스터마다 넘버를 붙여서 구분하는게 더 편함.
public:
	bool skillPaint = true;					//스킬 페인트 실행 여부										//추가된 변수

	Monster();
	Monster(const long x, const long y, const SIZE size, const int type);
	~Monster();

	virtual void draw();

	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS);
	virtual void MoveTo(const long x, const long y);				//이동할 x 방향 , y 방향			//추가된 코드
	virtual void Move();											//이동							//추가된 코드
	virtual	double GetResistanceXpos(){ return resistanceXpos; }	//resistanceXpos 가져오기		//추가된 코드
	virtual	double GetResistanceYpos(){ return resistanceYpos; }	//resistanceXpos 가져오기		//추가된 코드

	// 좌표값에 access하기 위한 함수들
	int getMonsterType(){ return monsterType; }						//몬스터 타입 가져오기			//추가된 코드
	const POINT getMonster();
	void putMonster(const int x, const int y);

	void move();				// 여러 이동패턴을 만드는것도 괜찮을지도. ~ 모양으로 움직인다거나.
};