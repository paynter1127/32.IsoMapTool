#pragma once
#include "gameNode.h"
//���ΰ��ӿ� �� ������ ��������� ��Ŭ��� ���ֽʼ�
//��� ��Ŭ��� ������ ���ΰ���.cpp �� init �� �� �޴����� �� �߰� ���ֽʼ�
#include "loadingScene.h"
#include "mapToolScene.h"

class mainGame : public gameNode
{
public:


	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

