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
	
	bool crash(Monster * MonsterPt);			//�浹 üũ (���� ������)		//����� �ڵ�
	void crash(Item * ItemPt);								//�浹 üũ (���� ������)		//����� �ڵ�
	void crash(HWND hWnd);
	// �浹�ϸ� y������ �ϰ�? �ٶ�ũ�� ����?->�ٸ� ��ü��(������,����)�� �浹�� ���� 
	// �ٶ��� ũ�Ⱑ �����Ϸ��� private����� ���� �����ϰ��־���ҵ�. �׷��� ���� �ٲ����
	virtual void draw();

	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS);						//�߰��� �ڵ�
	virtual void MoveTo(const long x, const long y);				//�̵��� x ���� , y ����			//�߰��� �ڵ�
	virtual void Move();											//�̵�							//�߰��� �ڵ�

	bool GetEnd(){ return end; }
	virtual long GetResistance();									//���� ��������					//�߰��� �ڵ�
	double GetSpeedXpos(){ return SpeedXpos; }						//MoveToXpos��������	,����׿�	
	double GetSpeedYpos(){ return SpeedYpos; }						//MoveToYpos��������	,����׿�


	virtual	double GetResistanceXpos(){ return resistanceXpos; }	//resistanceXpos ��������		
	virtual	double GetResistanceYpos(){ return resistanceYpos; }	//resistanceXpos ��������	
	int GetHp(){ return Hp; }
	int GetTime(){ return Time; }
	void SetTime(int TIME){Time = TIME;  if (Time < 0) end = true; }

	
	
	// ��ǥ���� access�ϱ� ���� �Լ���
	const POINT getPlayer();
	void putPlayer(const int x, const int y);
	
};