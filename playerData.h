#pragma once
#include "singletonBase.h"

class playerData : public singletonBase<playerData>
{
public:// < ���� ���� �� > =============================================================
	//������
	int gold;
	//Ÿ�� ����
	int lv_castle;
	int lv_tower;
	//ĳ���� ����
	int lv_worrior;
	int lv_archer;
	int lv_megician;
	int lv_hero;
	//��ų ����
	int num_skill1;
	int num_skill2;
	int num_skill3;
	

	// < �߰� ���� > =============================================================
	//��������
	int lv_stage;


public:// < �Լ� ���� �� > =============================================================
	HRESULT init();


	playerData() {}
	~playerData() {}
};
