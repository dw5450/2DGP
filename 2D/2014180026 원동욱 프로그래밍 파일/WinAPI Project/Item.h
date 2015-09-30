#pragma once

#include "Object.h"

class Item :public Object{
private:
	int itemType;	//
public:
	Item();
	Item(const int x, const int y, const int type);
	~Item();

	virtual void crash();		// �������� �浹������ �ʿ��� �����ϰ�(��� �ָ� �����簡) ������ �� ���� �ʾҴٸ� ������ ����(�κ��丮)�� ����մϴ�. 
	virtual void draw();

	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS);
	virtual void MoveTo(const long x, const long y);				//�̵��� x ���� , y ����			//�߰��� �ڵ�
	virtual void Move();											//�̵�							//�߰��� �ڵ�

	virtual	double GetResistanceXpos(){ return resistanceXpos; }	//resistanceXpos ��������
	virtual	double GetResistanceYpos(){ return resistanceYpos; }	//resistanceXpos ��������
	// ����� access�ϱ� ���� �Լ���

	void setItem(const int x, const int y,const int type);			// x��ǥ�� y��ǥ, �������� ������ �Է¹޽��ϴ�.
	const POINT getItemPos();						// x,y��ǥ�� ���ɴϴ�.
	const int getItemType();
	// �� �Ʒ��δ� �����ۺ� ����Դϴ�.
};