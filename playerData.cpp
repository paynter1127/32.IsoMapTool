#include "stdafx.h"
#include "playerData.h"

HRESULT playerData::init()
{
	lv_castle = 1;
	lv_tower = 1;
	lv_worrior = 1;
	lv_archer = 1;
	lv_megician = 1;
	lv_hero = 1;
	num_skill1 = 1;
	num_skill2 = 2;
	num_skill3 = 3;
	gold = 10000;
	lv_stage = 0;

	return S_OK;
}

