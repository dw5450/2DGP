#pragma once

#include <Windows.h>
#include "Math.h"			
//�߰��� ���� 
#define MAXRESISTANCE (long)100.0					// ���� �ִ밪						//�߰��� ������
// �߻� Ŭ����(�������̽�)
class Object{
public:
	POINT cp;
	SIZE ObjectSize;
	RECT ObjectRect;

	double resistanceXpos = MAXRESISTANCE;							//���װ�
	double resistanceYpos = MAXRESISTANCE;							//���װ�
	double SpeedXpos = 0;								//���� X�� ���� ���ǵ�
	double SpeedYpos = 0;								//���� Y�� ���� ���ǵ�

	Object(){};
	virtual ~Object(){};

	POINT GetCp(){ return cp; }
	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS) = 0;		//���װ� ����;					//�߰��� �ڵ�
	virtual void MoveTo(const long x, const long y) = 0;	//�̵��� x ���� , y ����			//�߰��� �ڵ�
	virtual void Move() = 0;								//�̵�							//�߰��� �ڵ�
	virtual	double GetResistanceXpos() = 0;					//resistanceXpos ��������		//�߰��� �ڵ�
	virtual	double GetResistanceYpos() = 0;					//resistanceXpos ��������		//�߰��� �ڵ�

	

	//ũ������ ĳ���Ͱ� ��� ó���ϰ� �ٲ�
	//virtual void crash() = 0;	// ������Ʈ�� �浹������ �÷��̾�� �Ⱦ�������, �ٸ��� ������->���� �ٸ� crash�� ���� -> ������ ������ ���� �����Լ�
	virtual void draw() = 0;			// ��ü�� �׸��ϴ�.
};