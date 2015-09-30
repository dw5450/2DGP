#include "stdafx.h"

#define SIZE 100								// 아이템 오브젝트의 맵상에서의 사이즈. 적당히 조절할것.

Item::Item(){};

Item::Item(const int x, const int y, const int type){
	cp.x = x;	cp.y = y;
	itemType = type;

	ObjectSize.cx = SIZE; ObjectSize.cy = SIZE;			//  0613 내가 임의로 추가함.
};
Item::~Item(){};

void Item::draw(){
	// 테스트용
	MoveToEx(bufferdc, cp.x, cp.y, NULL);
	LineTo(bufferdc, cp.x + SIZE, cp.y + SIZE);
};
void Item::crash(){
	//if (itemStockCounter < 3){		
	//	MoveToEx(hdc, p.x, p.y,NULL);				// 테스트용->스톡에 추가할 부분
	//	LineTo(hdc, p.x + SIZE, p.y + SIZE);
	//}

	Item::~Item();									// 삭제하든가 좌표를 멀리 날리든가.
}
//----------------------------------------------------
const POINT Item::getItemPos(){
	POINT tp;
	tp.x = cp.x;		tp.y = cp.y;

	return tp;
}

void Item::setItem(const int x,const int y, const int type){
	cp.x = x;	cp.y = y;
	itemType = type;

}
const int Item::getItemType(){
	return itemType;
}

//------------------------------------------------------
void Item::SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS){				//저항값 세팅;					

}
void Item::MoveTo(const long x, const long y){			//이동할 x 방향 , y 방향			

}
void Item::Move(){										//이동							

}
//

// 이 아래로는 아이템 별 기능 구현