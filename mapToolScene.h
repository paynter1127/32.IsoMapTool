#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define TILE_LAND_MAX 28 //Ÿ�� ���� �ִ� ����
#define TILE_OBJ_MAX 18 //������Ʈ ���� �ִ� ����
#define TILE_ENEMY_MAX 5 //���ʹ� ���� �ִ� ����
#define TILE_BLOCK_MAX 2 //��� ���� �ִ� ����
#define MAXTILESIZE 128 //�ִ� Ÿ�� ����


class mapToolScene : public gameNode
{
private:
	tagMenuUI UI;//�޴�â UI

	RECT rc_clipping;//Ŭ���� ��Ʈ
	RECT rc_clipping_mini;//�̴ϸ� Ŭ���� ��Ʈ
	RECT rc_temp; //�� ��Ʈ
	int tileSize; //Ÿ�� ũ��
	tagTile tile[MAXTILESIZE][MAXTILESIZE];//��ü Ÿ�� ����ü
	POINT pt_tileMark;//��ü Ÿ�� ���� ������
	float pt_tileMark_mini_x;//��ü Ÿ�� ���� ������
	float pt_tileMark_mini_y;//��ü Ÿ�� ���� ������

	//�޴� Ÿ��(��)
	tagTileMenu tileMenu_land[TILE_LAND_MAX];
	//�޴� Ÿ��(������Ʈ)
	tagTileMenu tileMenu_obj[TILE_OBJ_MAX];
	//�޴� Ÿ��(������Ʈ)
	tagTileMenu tileMenu_enemy[TILE_ENEMY_MAX];

	int now;
	

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void drowDiamond(tagTile tile, int i, int j, int iStyle, COLORREF color);
	void drowRect(RECT rc, COLORREF color);
	void drowTileIndex(tagTile tile, int i, int j);

	void userControl();
	void saveMap();
	void loadMap();

	//Ÿ�� �޴� �ʱ�ȭ
	void initMenu_tile();
	void initMenu_obj();
	void initMenu_enemy();

	mapToolScene() {}
	~mapToolScene() {}
};

