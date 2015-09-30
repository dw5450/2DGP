#pragma once

#include "Object.h"

class Monster :public Object{
private:
	int monsterType;				// ���͵鵵 ���� �������� Ŭ������ ����°� �����Ͱ����� ���� ������ ����͵� �ƴϰŴϿ� ���� �������� �ٸ� �ൿ�� ���� �ʴ´�(�Ƹ���).
								// ����, ���͸��� �ѹ��� �ٿ��� �����ϴ°� �� ����.
public:
	bool skillPaint = true;					//��ų ����Ʈ ���� ����										//�߰��� ����

	Monster();
	Monster(const long x, const long y, const SIZE size, const int type);
	~Monster();

	virtual void draw();

	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS);
	virtual void MoveTo(const long x, const long y);				//�̵��� x ���� , y ����			//�߰��� �ڵ�
	virtual void Move();											//�̵�							//�߰��� �ڵ�
	virtual	double GetResistanceXpos(){ return resistanceXpos; }	//resistanceXpos ��������		//�߰��� �ڵ�
	virtual	double GetResistanceYpos(){ return resistanceYpos; }	//resistanceXpos ��������		//�߰��� �ڵ�

	// ��ǥ���� access�ϱ� ���� �Լ���
	int getMonsterType(){ return monsterType; }						//���� Ÿ�� ��������			//�߰��� �ڵ�
	const POINT getMonster();
	void putMonster(const int x, const int y);

	void move();				// ���� �̵������� ����°͵� ����������. ~ ������� �����δٰų�.
};