#include "stdafx.h"

#define SIZE 100								// ������ ������Ʈ�� �ʻ󿡼��� ������. ������ �����Ұ�.

Item::Item(){};

Item::Item(const int x, const int y, const int type){
	cp.x = x;	cp.y = y;
	itemType = type;

	ObjectSize.cx = SIZE; ObjectSize.cy = SIZE;			//  0613 ���� ���Ƿ� �߰���.
};
Item::~Item(){};

void Item::draw(){
	// �׽�Ʈ��
	MoveToEx(bufferdc, cp.x, cp.y, NULL);
	LineTo(bufferdc, cp.x + SIZE, cp.y + SIZE);
};
void Item::crash(){
	//if (itemStockCounter < 3){		
	//	MoveToEx(hdc, p.x, p.y,NULL);				// �׽�Ʈ��->���忡 �߰��� �κ�
	//	LineTo(hdc, p.x + SIZE, p.y + SIZE);
	//}

	Item::~Item();									// �����ϵ簡 ��ǥ�� �ָ� �����簡.
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
void Item::SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS){				//���װ� ����;					

}
void Item::MoveTo(const long x, const long y){			//�̵��� x ���� , y ����			

}
void Item::Move(){										//�̵�							

}
//

// �� �Ʒ��δ� ������ �� ��� ����