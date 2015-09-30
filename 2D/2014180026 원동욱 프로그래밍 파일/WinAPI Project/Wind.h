#pragma once

#include"stdafx.h"

class Wind :public Object{
private:
	int MaxWindGage = 1000;
	int MaxBlow = 150;
	double WindGage = 0;											//���� ������;
	bool DrawWind = false;

	int windDirection = 0;											// 0�̸� x 1�̸� ������ -1�̸� ����		//�߰��� ����

public:
	Wind(){};
	~Wind(){};

	virtual void draw();											//�ٶ� ��������Ʈ, ���� ������ ��� //�߰��� �ڵ�;

	void PlusWindGage(double PlusWindGage);								//��������� ���				//�߰��� �ڵ�
	void Blow(Player * PLAYER, POINT MousePoint, const long x, const long y);							//�÷��̾ �ٶ� ����			//�߰��� �ڵ�

	double GetWindGage(){ return WindGage; }							//WindGage	��������				//����׿�


	// ��ǥ���� access�ϱ� ���� �Լ���
	const POINT getWind();
	void putWind(const int x, const int y);

	//void move();				// ���� �̵������� ����°͵� ����������. ~ ������� �����δٰų�.

	//���� ������ �ʿ� ���� �Լ���
	virtual void SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS);
	virtual void MoveTo(const long x, const long y);				//�̵��� x ���� , y ����			//�߰��� �ڵ�
	virtual void Move();											//�̵�							//�߰��� �ڵ�
	virtual	double GetResistanceXpos(){ return resistanceXpos; }	//resistanceXpos ��������		//�߰��� �ڵ�
	virtual	double GetResistanceYpos(){ return resistanceYpos; }	//resistanceXpos ��������		//�߰��� �ڵ�
};