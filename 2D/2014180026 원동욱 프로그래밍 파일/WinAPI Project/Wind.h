#pragma once

#include"stdafx.h"

class Wind :public Object{
private:
	int MaxWindGage = 1000;
	int MaxBlow = 150;
	double WindGage = 0;											//윈드 게이지;
	bool DrawWind = false;

	int windDirection = 0;											// 0이면 x 1이면 오른쪽 -1이면 왼쪽		//추가된 변수

public:
	Wind(){};
	~Wind(){};

	virtual void draw();											//바람 스프라이트, 윈드 게이지 출력 //추가된 코드;

	void PlusWindGage(double PlusWindGage);								//윈드게이지 상승				//추가된 코드
	void Blow(Player * PLAYER, POINT MousePoint, const long x, const long y);							//플레이어에 바람 적용			//추가된 코드

	double GetWindGage(){ return WindGage; }							//WindGage	가져오기				//디버그용


	// 좌표값에 access하기 위한 함수들
	const POINT getWind();
	void putWind(const int x, const int y);

	//void move();				// 여러 이동패턴을 만드는것도 괜찮을지도. ~ 모양으로 움직인다거나.

	//윈드 내에선 필요 없는 함수들
	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS);
	virtual void MoveTo(const long x, const long y);				//이동할 x 방향 , y 방향			//추가된 코드
	virtual void Move();											//이동							//추가된 코드
	virtual	double GetResistanceXpos(){ return resistanceXpos; }	//resistanceXpos 가져오기		//추가된 코드
	virtual	double GetResistanceYpos(){ return resistanceYpos; }	//resistanceXpos 가져오기		//추가된 코드
};