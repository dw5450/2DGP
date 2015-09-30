#pragma once

#include <Windows.h>
#include "Math.h"			
//추가된 선언 
#define MAXRESISTANCE (long)100.0					// 저항 최대값						//추가된 디파인
// 추상 클래스(인터페이스)
class Object{
public:
	POINT cp;
	SIZE ObjectSize;
	RECT ObjectRect;

	double resistanceXpos = MAXRESISTANCE;							//저항값
	double resistanceYpos = MAXRESISTANCE;							//저항값
	double SpeedXpos = 0;								//다음 X축 방향 스피드
	double SpeedYpos = 0;								//다음 Y축 방향 스피드

	Object(){};
	virtual ~Object(){};

	POINT GetCp(){ return cp; }
	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS) = 0;		//저항값 세팅;					//추가된 코드
	virtual void MoveTo(const long x, const long y) = 0;	//이동할 x 방향 , y 방향			//추가된 코드
	virtual void Move() = 0;								//이동							//추가된 코드
	virtual	double GetResistanceXpos() = 0;					//resistanceXpos 가져오기		//추가된 코드
	virtual	double GetResistanceYpos() = 0;					//resistanceXpos 가져오기		//추가된 코드

	

	//크러쉬를 캐릭터가 모두 처리하게 바꿈
	//virtual void crash() = 0;	// 오브젝트가 충돌했을때 플레이어는 안없어지고, 다른건 없어짐->각자 다른 crash의 구현 -> 다형성 구현을 위해 가상함수
	virtual void draw() = 0;			// 객체를 그립니다.
};