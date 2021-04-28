#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define TILE_LAND_MAX 28 //타일 종류 최대 갯수
#define TILE_OBJ_MAX 18 //오브젝트 종류 최대 갯수
#define TILE_ENEMY_MAX 5 //에너미 종류 최대 갯수
#define TILE_BLOCK_MAX 2 //블록 종류 최대 갯수
#define MAXTILESIZE 128 //최대 타일 갯수


class mapToolScene : public gameNode
{
private:
	tagMenuUI UI;//메뉴창 UI

	RECT rc_clipping;//클리핑 렉트
	RECT rc_clipping_mini;//미니맵 클리핑 렉트
	RECT rc_temp; //빈 렉트
	int tileSize; //타일 크기
	tagTile tile[MAXTILESIZE][MAXTILESIZE];//전체 타일 구조체
	POINT pt_tileMark;//전체 타일 종속 기준점
	float pt_tileMark_mini_x;//전체 타일 종속 기준점
	float pt_tileMark_mini_y;//전체 타일 종속 기준점

	//메뉴 타일(땅)
	tagTileMenu tileMenu_land[TILE_LAND_MAX];
	//메뉴 타일(오브젝트)
	tagTileMenu tileMenu_obj[TILE_OBJ_MAX];
	//메뉴 타일(오브젝트)
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

	//타일 메뉴 초기화
	void initMenu_tile();
	void initMenu_obj();
	void initMenu_enemy();

	mapToolScene() {}
	~mapToolScene() {}
};

