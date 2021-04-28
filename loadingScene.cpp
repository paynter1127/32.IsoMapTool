#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	//IMAGEMANAGER->addFrameImage("����", "numSprite.bmp", 360, 42, 10, 1);
	//IMAGEMANAGER->addFrameImage("����22", "����2.bmp", 360, 42, 10, 1, true, RGB(255, 0, 255));
	//i = 0;
	//�ε�
	//SOUNDMANAGER->addSound("256113__nckn__done", "256113__nckn__done.wav", false, false);
	
	

	//isDone = false;

	return S_OK;
}

void loadingScene::release()
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//SOUNDMANAGER->play("��ư");
			//loadPlayer();
			SCENEMANAGER->loadScene("����");
		}
	}
}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
	_loading->render();
	//imageNum("����22", getMemDC(), 744, 529, (_loading->getCurrentGauge() * 100) / _loading->getLoadItem().size(), 26); //�Ϸ�

	//���� �̸� ǥ��
	//if (IMAGEMANAGER->findImage(_loading->getLoadItem()[i]->getImageResource().keyName))
	{
		//textOutFont(getMemDC(), 30, 544, IMAGEMANAGER->findImage(_loading->getLoadItem()[i]->getImageResource().keyName)->getFileName(), 16);
		//if ((_loading->getCurrentGauge() * 100) / _loading->getLoadItem().size() == 99) 
		//{
		//	//SOUNDMANAGER->play("256113__nckn__done");
		//	i++;
		//}
		//else if((_loading->getCurrentGauge() * 100) / _loading->getLoadItem().size() != 100) i++;
		//else
		{
			//�ε�
			//textOutFont(getMemDC(), _ptMouse.x + 10, _ptMouse.y, "Click to", 40, RGB(250, 200, 0));
			//textOutFont(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 42, "Continue", 40, RGB(250, 200, 0));
		}
	}
}

/* < ���⿡ �� ���� ����� �̹��� �̸� �ε� �صδ� ���Դϴ�. >*/
void loadingScene::loadingImage()
{
	_loading->loadImage("���̹���", "���̹���.bmp", 3, 3);
	_loading->loadFrameImage("�����̹���1", "numSprite.bmp", 360, 42, 10, 1);
	_loading->loadFrameImage("����2", "����2.bmp", 360, 42, 10, 1, true, RGB(255, 0, 255));

	//land1 Ÿ�� �ε�
	{
		//Ÿ��
		_loading->loadImage("st51a_01", "mapTool/tile/st51a_01.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_02", "mapTool/tile/st51a_02.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_03", "mapTool/tile/st51a_03.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_04", "mapTool/tile/st51a_04.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_08", "mapTool/tile/st51a_08.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_09", "mapTool/tile/st51a_09.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_10", "mapTool/tile/st51a_10.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_11", "mapTool/tile/st51a_11.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_15", "mapTool/tile/st51a_15.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_16", "mapTool/tile/st51a_16.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_17", "mapTool/tile/st51a_17.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_18", "mapTool/tile/st51a_18.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_22", "mapTool/tile/st51a_22.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_23", "mapTool/tile/st51a_23.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_24", "mapTool/tile/st51a_24.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_25", "mapTool/tile/st51a_25.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_30", "mapTool/tile/st51a_30.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_31", "mapTool/tile/st51a_31.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_32", "mapTool/tile/st51a_32.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_37", "mapTool/tile/st51a_37.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_38", "mapTool/tile/st51a_38.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_39", "mapTool/tile/st51a_39.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_45", "mapTool/tile/st51a_45.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_46", "mapTool/tile/st51a_46.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_52", "mapTool/tile/st51a_52.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_53", "mapTool/tile/st51a_53.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_59", "mapTool/tile/st51a_59.bmp", 64, 32, true, RGB(0, 0, 255));
		_loading->loadImage("st51a_60", "mapTool/tile/st51a_60.bmp", 64, 32, true, RGB(0, 0, 255));

		//�̴ϸ� Ÿ��
		_loading->loadImage("mini_st51a_01", "mapTool/tile/st51a_01.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_02", "mapTool/tile/st51a_02.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_03", "mapTool/tile/st51a_03.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_04", "mapTool/tile/st51a_04.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_08", "mapTool/tile/st51a_08.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_09", "mapTool/tile/st51a_09.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_10", "mapTool/tile/st51a_10.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_11", "mapTool/tile/st51a_11.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_15", "mapTool/tile/st51a_15.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_16", "mapTool/tile/st51a_16.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_17", "mapTool/tile/st51a_17.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_18", "mapTool/tile/st51a_18.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_22", "mapTool/tile/st51a_22.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_23", "mapTool/tile/st51a_23.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_24", "mapTool/tile/st51a_24.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_25", "mapTool/tile/st51a_25.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_30", "mapTool/tile/st51a_30.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_31", "mapTool/tile/st51a_31.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_32", "mapTool/tile/st51a_32.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_37", "mapTool/tile/st51a_37.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_38", "mapTool/tile/st51a_38.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_39", "mapTool/tile/st51a_39.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_45", "mapTool/tile/st51a_45.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_46", "mapTool/tile/st51a_46.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_52", "mapTool/tile/st51a_52.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_53", "mapTool/tile/st51a_53.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_59", "mapTool/tile/st51a_59.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_st51a_60", "mapTool/tile/st51a_60.bmp", 64 / 10, 32 / 10, true, RGB(0, 0, 255));
	}

	//�̵� �Ұ� Ÿ�� ǥ��
	_loading->loadImage("tile_block", "mapTool/tile_block.bmp", 64, 32);
	
	//��ų ���� Ÿ�� ǥ��
	_loading->loadImage("skill_range", "skill/skill_range.bmp", 64, 32, true, RGB(255, 0, 0));
	_loading->loadImage("skill_hitRange", "skill/skill_hitRange.bmp", 64, 32, true, RGB(255, 0, 0));
	


	//������Ʈ Ÿ�� �ε�
	{
		_loading->loadImage("sign_2_04", "mapTool/obj/sign_2_04.bmp", 64, 95, true, RGB(0, 0, 255));
		_loading->loadImage("sign_2_05", "mapTool/obj/sign_2_05.bmp", 64, 95, true, RGB(0, 0, 255));
		_loading->loadImage("sign_2_06", "mapTool/obj/sign_2_06.bmp", 64, 95, true, RGB(0, 0, 255));
		_loading->loadImage("tree.64.138", "mapTool/obj/tree.64.138.bmp", 64, 138, true, RGB(0, 0, 255));
		_loading->loadImage("bush1.64.55", "mapTool/obj/bush1.64.55.bmp", 64, 55, true, RGB(0, 0, 255));
		_loading->loadImage("bush2.64.45", "mapTool/obj/bush2.64.45.bmp", 64, 55, true, RGB(0, 0, 255));
		_loading->loadImage("bush3.64.48", "mapTool/obj/bush3.64.48.bmp", 64, 55, true, RGB(0, 0, 255));
		_loading->loadImage("bush4.64.37", "mapTool/obj/bush4.64.37.bmp", 64, 55, true, RGB(0, 0, 255));
		_loading->loadImage("bush5.64.58", "mapTool/obj/bush5.64.58.bmp", 64, 55, true, RGB(0, 0, 255));
		_loading->loadImage("bush6.64.48", "mapTool/obj/bush6.64.48.bmp", 64, 55, true, RGB(0, 0, 255));
		_loading->loadImage("bush7.64.45", "mapTool/obj/bush7.64.45.bmp", 64, 55, true, RGB(0, 0, 255));
		_loading->loadImage("bush8.64.37", "mapTool/obj/bush8.64.37.bmp", 64, 55, true, RGB(0, 0, 255));
		_loading->loadImage("barrel.64.58", "mapTool/obj/barrel.64.58.bmp", 64, 58, true, RGB(0, 0, 255));
		_loading->loadImage("palmtree1.440.252", "mapTool/obj/palmtree1.440.252.bmp", 440, 252, true, RGB(255, 0, 255));
		_loading->loadImage("palmtree2.344.318", "mapTool/obj/palmtree2.344.318.bmp", 344, 318, true, RGB(255, 0, 255));
		_loading->loadImage("st50a", "mapTool/obj/st50a.bmp", 384, 328, true, RGB(255, 0, 0));
		_loading->loadImage("st50b", "mapTool/obj/st50b.bmp", 384, 328, true, RGB(255, 0, 0));
		_loading->loadImage("st50c", "mapTool/obj/st50c.bmp", 384, 328, true, RGB(255, 0, 0));


		//�̴ϸ� Ÿ��
		_loading->loadImage("mini_sign_2_04", "mapTool/obj/sign_2_04.bmp", 64 / 10, 95 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_sign_2_05", "mapTool/obj/sign_2_05.bmp", 64 / 10, 95 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_sign_2_06", "mapTool/obj/sign_2_06.bmp", 64 / 10, 95 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_tree.64.138", "mapTool/obj/tree.64.138.bmp", 64 / 10, 138 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_bush1.64.55", "mapTool/obj/bush1.64.55.bmp", 64 / 10, 55 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_bush2.64.45", "mapTool/obj/bush2.64.45.bmp", 64 / 10, 55 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_bush3.64.48", "mapTool/obj/bush3.64.48.bmp", 64 / 10, 55 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_bush4.64.37", "mapTool/obj/bush4.64.37.bmp", 64 / 10, 55 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_bush5.64.58", "mapTool/obj/bush5.64.58.bmp", 64 / 10, 55 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_bush6.64.48", "mapTool/obj/bush6.64.48.bmp", 64 / 10, 55 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_bush7.64.45", "mapTool/obj/bush7.64.45.bmp", 64 / 10, 55 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_bush8.64.37", "mapTool/obj/bush8.64.37.bmp", 64 / 10, 55 / 10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_barrel.64.58", "mapTool/obj/barrel.64.58.bmp", 64 / 10, 58 /10, true, RGB(0, 0, 255));
		_loading->loadImage("mini_palmtree1.440.252", "mapTool/obj/palmtree1.440.252.bmp", 440 / 10, 252 / 10, true, RGB(255, 0, 255));
		_loading->loadImage("mini_palmtree2.344.318", "mapTool/obj/palmtree2.344.318.bmp", 344 / 10, 318 / 10, true, RGB(255, 0, 255));
		_loading->loadImage("mini_st50a", "mapTool/obj/st50a.bmp", 384 / 10, 328 / 10, true, RGB(255, 0, 0));
		_loading->loadImage("mini_st50b", "mapTool/obj/st50b.bmp", 384 / 10, 328 / 10, true, RGB(255, 0, 0));
		_loading->loadImage("mini_st50c", "mapTool/obj/st50c.bmp", 384 / 10, 328 / 10, true, RGB(255, 0, 0));
	}

	//���ʹ� Ÿ�� �ε�
	{
		_loading->loadImage("char_15e", "mapTool/enemy/char_15e.bmp", 44, 53, true, RGB(255, 0, 255));
		_loading->loadImage("necro1", "mapTool/enemy/necro1.bmp", 80, 96, true, RGB(255, 0, 255));
		_loading->loadImage("char_33a", "mapTool/enemy/char_33a.bmp", 49, 84, true, RGB(255, 0, 255));
		_loading->loadImage("char_68e", "mapTool/enemy/char_68e.bmp", 66, 92, true, RGB(255, 0, 255));
		

		//�̴ϸ� Ÿ��
		_loading->loadImage("mini_char_15e", "mapTool/enemy/char_15e.bmp", 44 / 10, 53 / 10, true, RGB(255, 0, 255));
		_loading->loadImage("mini_necro1", "mapTool/enemy/necro1.bmp", 80 / 10, 96 / 10, true, RGB(255, 0, 255));
		_loading->loadImage("mini_char_33a", "mapTool/enemy/char_33a.bmp", 49 / 10, 84 / 10, true, RGB(255, 0, 255));
		_loading->loadImage("mini_char_68e", "mapTool/enemy/char_68e.bmp", 66 / 10, 92 / 10, true, RGB(255, 0, 255));
	}



	//����(Ű����)
	_loading->loadImage("keyInfo.1280.350", "mapTool/keyInfo.1280.350.bmp", 1280 / 2.8 , 350 / 2.8);
	
}

/* < ���⿡ �� ���� ����� ���� �̸� �ε� �صδ� ���Դϴ�. >*/
void loadingScene::loadingSound()
{
	SOUNDMANAGER->addSound("������", "������2.mp3", false, false);
	SOUNDMANAGER->addSound("��ư", "��ư.mp3", false, false);
	SOUNDMANAGER->addSound("find", "find.wav", false, false);
	SOUNDMANAGER->addSound("meter", "meter.wav", false, false);
	SOUNDMANAGER->addSound("battle02", "battle02.wav", false, false);
	SOUNDMANAGER->addSound("battle08", "battle08.wav", false, false);
	SOUNDMANAGER->addSound("water", "water.wav", false, false);
	
}
