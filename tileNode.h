#pragma once

//타일 기본 속정 정의
#define TILEWIDTH 64
#define TILEHEIGHT 32


//맵툴에서 사용할 컨트롤들
enum state_CTRL
{
	SAVE, LOAD,
	TERRAIN, OBJECT, ERASER,
};

//타일 분류
enum state_TileSort
{
	SORT_TILE, SORT_OBJ, SORT_ENEMY, SORT_BLOCK
};

//지형
enum state_TERRAIN
{
	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER, TR_END
};

//오브젝트 속성
enum state_OBJECT
{
	NONE,
	BLOCK,
};

//타일구조체
struct tagTile
{
	state_TERRAIN terrain;

	int x, y;
	RECT rc;
	RECT rc_picking;

	float x_mini, y_mini;
	RECT rc_mini;
	image* img;
	image* img_mini;
	state_OBJECT state_obj;
	int floor;
	image* img_floor[4];
	image* img_floor_mini[4];

	image* img_obj;
	image* img_mini_obj;
	image* img_enemy;
	image* img_mini_enemy;
	bool isImg;
	bool isImg_obj;
	bool isImg_enemy;
};


//메뉴창 내 타일 속성(필드 타일로 복사해줄 이미지 외 정보들)
struct tagTileMenu
{
	LPCSTR strKey;
	//RECT rc;

	image* img;
	image* img_mini;
	state_OBJECT state_obj;
};

//메뉴창
struct tagMenuUI
{
	POINT mark;
	RECT rc_bg;
	image* img_bg;
	RECT rc_miniMap;
	RECT rc_miniMap_show;
	RECT rc_save;
	RECT rc_load;
	RECT rc_preview;
	RECT rc_listBG;
	int num_choice;
	RECT rc_choice; //현재 선택 타일이 뭔지 보여주는 GUI
	RECT rc_sortBG;
	RECT rc_tile;
	RECT rc_obj;
	RECT rc_enemy;
	RECT rc_block;
	state_TileSort tileSort;//타일 분류
	
	RECT rc_popUP_BG;
	RECT rc_popUP_yes;
	RECT rc_popUP_no;
	bool isSave;
	bool isLoad;
	
	RECT rc_manual;
	bool isManual;

	tagMenuUI()
	{
		mark.x = 10;
		mark.y = 10;
		rc_bg = RectMake(mark.x, mark.y, 150, 460);
		img_bg = IMAGEMANAGER->addImage("menu_bg", "menu_bg.bmp", 150, 460);
		rc_miniMap = RectMake(rc_bg.left + 5, rc_bg.top + 5, 140, 110);
		rc_miniMap_show = RectMake(rc_bg.left + 36, rc_bg.left + 23, 68, 46);
		rc_save = RectMake(rc_miniMap.left, rc_miniMap.bottom + 4, 68, 30);
		rc_load = RectMake(rc_miniMap.left + 68 + 4, rc_miniMap.bottom + 4, 68, 30);
		rc_preview = RectMake(rc_miniMap.left, rc_save.bottom + 4, 140, 110);
		rc_listBG = RectMake(rc_miniMap.left, rc_preview.bottom + 4, 140, 104);
		num_choice = 0;
		rc_choice = RectMake(rc_preview.left + 2, rc_preview.bottom + 6 + 20 * (num_choice), 136, 20);
		rc_sortBG = RectMake(rc_listBG.left, rc_listBG.bottom + 1, 140, 20);
		rc_tile = RectMake(rc_listBG.left + 1, rc_listBG.bottom + 2, 24, 18);
		rc_obj = RectMake(rc_tile.right + 2, rc_listBG.bottom + 2, 24, 18);
		rc_enemy = RectMake(rc_obj.right + 2, rc_listBG.bottom + 2, 46, 18);
		rc_block = RectMake(rc_enemy.right + 2, rc_listBG.bottom + 2, 38, 18);
		tileSort = SORT_TILE;
		
		rc_popUP_BG = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 300, 160);
		rc_popUP_yes = RectMake(rc_popUP_BG.left + 60, rc_popUP_BG.top + 110, 68, 30);
		rc_popUP_no = RectMake(rc_popUP_BG.right - 60 - 68, rc_popUP_BG.top + 110, 68, 30);
		isSave = false;
		isLoad = false;

		rc_manual = RectMake(560, 460, WINSIZEX - 560, WINSIZEY - 460);
		isManual = false;
	}
};

