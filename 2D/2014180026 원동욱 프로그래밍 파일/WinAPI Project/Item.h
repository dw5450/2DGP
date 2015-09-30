#pragma once

#include "Object.h"

class Item :public Object{
private:
	int itemType;	//
public:
	Item();
	Item(const int x, const int y, const int type);
	~Item();

	virtual void crash();		// 아이템은 충돌했을때 맵에서 삭제하고(어딘가 멀리 날리든가) 스톡이 꽉 차지 않았다면 아이템 스톡(인벤토리)에 등록합니다. 
	virtual void draw();

	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS);
	virtual void MoveTo(const long x, const long y);				//이동할 x 방향 , y 방향			//추가된 코드
	virtual void Move();											//이동							//추가된 코드

	virtual	double GetResistanceXpos(){ return resistanceXpos; }	//resistanceXpos 가져오기
	virtual	double GetResistanceYpos(){ return resistanceYpos; }	//resistanceXpos 가져오기
	// 멤버에 access하기 위한 함수들

	void setItem(const int x, const int y,const int type);			// x좌표와 y좌표, 아이템의 종류를 입력받습니다.
	const POINT getItemPos();						// x,y좌표를 얻어옵니다.
	const int getItemType();
	// 이 아래로는 아이템별 기능입니다.
};