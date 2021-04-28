#include "stdafx.h"
#include "mapToolScene.h"



HRESULT mapToolScene::init()
{
	tileSize = 8;// MAXTILESIZE;
	rc_clipping = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 540, 380);
	rc_clipping_mini = RectMake(UI.rc_bg.left + 7, UI.rc_bg.top + 24, 140 - 4, 90 - 4);
	pt_tileMark = { 240 + 160, 100 };
	pt_tileMark_mini_x = 80;
	pt_tileMark_mini_y = 40;
	//맵 타일 초기화
	for (int i = 0; i < MAXTILESIZE; i++)
	{
		for (int j = 0; j < MAXTILESIZE; j++)
		{
			tile[i][j].x = pt_tileMark.x - (i * 64 / 2) + (j * 64 / 2);
			tile[i][j].y = pt_tileMark.y + (i * 32 / 2) + (j * 32 / 2);
			tile[i][j].rc = RectMakeCenter(tile[i][j].x, tile[i][j].y, 64, 32);
			tile[i][j].rc_picking = RectMakeCenter(tile[i][j].x, tile[i][j].y, 64 / 2, 32 / 2);
			tile[i][j].x_mini = pt_tileMark_mini_x - ((i * 64 / 2) * 0.1) + ((j * 64 / 2) * 0.1);
			tile[i][j].y_mini = pt_tileMark_mini_y + ((i * 32 / 2) * 0.1) + ((j * 32 / 2) * 0.1);
			tile[i][j].rc_mini = RectMake(tile[i][j].x_mini, tile[i][j].y_mini, 64 / 10, 32 / 10);
			//tile[i][j].img = IMAGEMANAGER->findImage("빈이미지"); //초기 타일(빈 타일)
			//tile[i][j].img_mini = IMAGEMANAGER->findImage("빈이미지");//22 //초기 타일(미니맵)
			//tile[i][j].isImg = false;
			tile[i][j].img = IMAGEMANAGER->findImage("st51a_22");//22 //초기 타일
			tile[i][j].img_mini = IMAGEMANAGER->findImage("mini_st51a_22");//22 //초기 타일(미니맵)
			tile[i][j].isImg = true;
			
			tile[i][j].state_obj = NONE;
			tile[i][j].floor = 0;
			tile[i][j].img_floor[0] = IMAGEMANAGER->findImage("st51a_37");
			tile[i][j].img_floor[1] = IMAGEMANAGER->findImage("st51a_37");
			tile[i][j].img_floor[2] = IMAGEMANAGER->findImage("st51a_37");
			tile[i][j].img_floor[3] = IMAGEMANAGER->findImage("st51a_37");

			tile[i][j].img_floor_mini[0] = IMAGEMANAGER->findImage("mini_st51a_37");
			tile[i][j].img_floor_mini[1] = IMAGEMANAGER->findImage("mini_st51a_37");
			tile[i][j].img_floor_mini[2] = IMAGEMANAGER->findImage("mini_st51a_37");
			tile[i][j].img_floor_mini[3] = IMAGEMANAGER->findImage("mini_st51a_37");

			tile[i][j].img_obj = IMAGEMANAGER->findImage("빈이미지"); //초기 타일(빈 타일)
			tile[i][j].img_mini_obj = IMAGEMANAGER->findImage("빈이미지"); //초기 타일(빈 타일)
			tile[i][j].img_enemy = IMAGEMANAGER->findImage("빈이미지"); //초기 타일(빈 타일)
			tile[i][j].img_mini_enemy = IMAGEMANAGER->findImage("빈이미지"); //초기 타일(빈 타일)

			tile[i][j].isImg_obj = false;
			tile[i][j].isImg_enemy = false;
		}
	}
	
	this->initMenu_tile();
	this->initMenu_obj();
	this->initMenu_enemy();

	now = 0;
	
	return S_OK;
}

void mapToolScene::release()
{
	
}

void mapToolScene::update()
{
	this->userControl();

	//맵 타일 업데이트
	for (int i = 0; i < tileSize; i++)
	{
		for (int j = 0; j < tileSize; j++)
		{
			tile[i][j].x = pt_tileMark.x - (i * 64 / 2) + (j * 64 / 2);
			tile[i][j].y = pt_tileMark.y + (i * 32 / 2) + (j * 32 / 2);
			tile[i][j].rc = RectMakeCenter(tile[i][j].x, tile[i][j].y, 64, 32);
			tile[i][j].rc_picking = RectMakeCenter(tile[i][j].x, tile[i][j].y, 64 / 2, 32 / 2);
		}
	}

	//미니맵 타일 업데이트
	for (int i = 0; i < tileSize; i++)
	{
		for (int j = 0; j < tileSize; j++)
		{
			tile[i][j].x_mini = pt_tileMark_mini_x - ((i * 64 / 2) * 0.1) + ((j * 64 / 2) * 0.1);
			tile[i][j].y_mini = pt_tileMark_mini_y + ((i * 32 / 2) * 0.1) + ((j * 32 / 2) * 0.1);
			tile[i][j].rc_mini = RectMake(tile[i][j].x_mini, tile[i][j].y_mini, 64 / 10, 32 / 10);
		}
	}
	
}

void mapToolScene::render()
{

	//타일 렌더 + 클리핑 처리 + 오브젝트 렌더
	for (int i = 0; i < tileSize; i++)
	{
		for (int j = 0; j < tileSize; j++)
		{
			if (IntersectRect(&rc_temp, &rc_clipping, &tile[i][j].rc))
			{
				//타일 렌더 높이 구현
				if (tile[i][j].isImg)
					tile[i][j].img->render(getMemDC(), tile[i][j].rc.left, tile[i][j].rc.top - (TILEHEIGHT / 2) * tile[i][j].floor); //타일 이미지 렌더
				for (int k = 0; k < tile[i][j].floor; k++) 
					tile[i][j].img_floor[k]->render(getMemDC(), tile[i][j].rc.left, tile[i][j].rc.top - (TILEHEIGHT / 2) * k);

				//오브젝트 렌더 + 높이 처리
				if (tile[i][j].isImg_obj)
					tile[i][j].img_obj->render(getMemDC(), tile[i][j].rc.left - tile[i][j].img_obj->getWidth() / 2 + 32, tile[i][j].rc.bottom - tile[i][j].img_obj->getHeight() - (TILEHEIGHT / 2) * tile[i][j].floor);

				//에너미 렌더 + 높이 처리
				if (tile[i][j].isImg_enemy)
					tile[i][j].img_enemy->render(getMemDC(), tile[i][j].rc.left - tile[i][j].img_enemy->getWidth() / 2 + 32, tile[i][j].rc.bottom - tile[i][j].img_enemy->getHeight() - (TILEHEIGHT / 2) * tile[i][j].floor);
			}
		}
	}

	// < 치트 > 토글 키
	{
		for (int i = 0; i < tileSize; i++)
		{
			for (int j = 0; j < tileSize; j++)
			{
				if (IntersectRect(&rc_temp, &rc_clipping, &tile[i][j].rc))
				{
					if (KEYMANAGER->isToggleKey(VK_F5)) drowTileIndex(tile[i][j], i, j);//타일 인덱스 렌더
					if (KEYMANAGER->isToggleKey(VK_F6)) FrameRect(getMemDC(), tile[i][j].rc_picking, RGB(255, 0, 255));//픽킹 렉터 렌더
					if (!KEYMANAGER->isToggleKey(VK_F7)) drowDiamond(tile[i][j], i, j, PS_DOT, RGB(255, 255, 0));//아이소 타일 렌더
					if (!KEYMANAGER->isToggleKey(VK_F8)) //이동 가능 지역 체크 렌더
					{
						if (tile[i][j].state_obj == BLOCK) IMAGEMANAGER->findImage("tile_block")->alphaRender(getMemDC(), tile[i][j].rc.left, tile[i][j].rc.top, 80);
					}
				}
			}
		}
		//토글키 사운드 출력
		if (KEYMANAGER->isOnceKeyUp(VK_F5) ||
			KEYMANAGER->isOnceKeyUp(VK_F6) ||
			KEYMANAGER->isOnceKeyUp(VK_F7) ||
			KEYMANAGER->isOnceKeyUp(VK_F8) ||
			KEYMANAGER->isOnceKeyUp(VK_F9))
			SOUNDMANAGER->play("버튼");
	}
	
	//픽킹 GUI
	for (int i = 0; i < tileSize; i++)
	{
		for (int j = 0; j < tileSize; j++)
		{
			if (PtInRect(&tile[i][j].rc_picking, _ptMouse)) drowDiamond(tile[i][j], i, j, PS_SOLID, RGB(255, 0, 0));
		}
	}

	//메뉴창 렌더
	{
		//UI배경 출력
		FrameRect(getMemDC(), UI.rc_bg, RGB(200, 200, 200));
		UI.img_bg->alphaRender(getMemDC(), UI.rc_bg.left, UI.rc_bg.top, 64);
		
		//미니맵 백그라운드 출력
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		FillRect(getMemDC(), &UI.rc_miniMap, brush);
		DeleteObject(brush);

		//미니맵 출력
		for (int i = 0; i < tileSize; i++)
		{
			for (int j = 0; j < tileSize; j++)
			{
				if (IntersectRect(&rc_temp, &rc_clipping_mini, &tile[i][j].rc_mini))
				{
					if (tile[i][j].isImg)
						tile[i][j].img_mini->render(getMemDC(), tile[i][j].rc_mini.left, tile[i][j].rc_mini.top - ((TILEHEIGHT / 2) * 0.1) * tile[i][j].floor); //타일 이미지 렌더
					for (int k = 0; k < tile[i][j].floor; k++)
						tile[i][j].img_floor_mini[k]->render(getMemDC(), tile[i][j].rc_mini.left, tile[i][j].rc_mini.top - ((TILEHEIGHT / 2) * 0.1) * k);

					//오브젝트 렌더 + 높이 처리
					if (tile[i][j].isImg_obj)
						tile[i][j].img_mini_obj->render(getMemDC(), tile[i][j].rc_mini.left - ((tile[i][j].img_obj->getWidth() / 2) / 10) + 32 / 10, tile[i][j].rc_mini.top - (tile[i][j].img_obj->getHeight() / 10) + 3 - ((TILEHEIGHT / 2) * 0.1) * tile[i][j].floor);

					//에너미 렌더 + 높이 처리
					if (tile[i][j].isImg_enemy)
						tile[i][j].img_mini_enemy->render(getMemDC(), tile[i][j].rc_mini.left - ((tile[i][j].img_enemy->getWidth() / 2) / 10) + 32 / 10, tile[i][j].rc_mini.top - (tile[i][j].img_enemy->getHeight() / 10) + 3 - ((TILEHEIGHT / 2) * 0.1) * tile[i][j].floor);
				}
			}
		}

		//맵 사이즈 텍스트 출력
		char str[128];
		sprintf(str, " Map Size : %d x %d", tileSize, tileSize);
		textOutFont(getMemDC(), UI.rc_miniMap.left, UI.rc_miniMap.top, str, 20, RGB(255, 255, 255), "맑은 고딕");
		
		//맵 카메라 출력
		FrameRect(getMemDC(), UI.rc_miniMap_show, RGB(200, 200, 0));
		
		//세이브,로드 버튼 출력
		IMAGEMANAGER->findImage("menu_bg")->alphaRender(getMemDC(), UI.rc_save.left, UI.rc_save.top, 40, 40, UI.rc_save.right - UI.rc_save.left, UI.rc_save.bottom - UI.rc_save.top, 210);
		IMAGEMANAGER->findImage("menu_bg")->alphaRender(getMemDC(), UI.rc_load.left, UI.rc_load.top, 40, 40, UI.rc_load.right - UI.rc_load.left, UI.rc_load.bottom - UI.rc_load.top, 210);
		FrameRect(getMemDC(), UI.rc_save, RGB(0, 20, 0));
		FrameRect(getMemDC(), UI.rc_load, RGB(0, 20, 0));
		textOutFont(getMemDC(), UI.rc_save.left + 10, UI.rc_save.top + 6, "SAVE", 20);
		textOutFont(getMemDC(), UI.rc_load.left + 10, UI.rc_load.top + 6, "LOAD", 20);

		//선택 타일 프리뷰 화면
		SetBkMode(getMemDC(), 0);
		IMAGEMANAGER->findImage("menu_bg")->alphaRender(getMemDC(), UI.rc_preview.left, UI.rc_preview.top, 0, 0, UI.rc_preview.right - UI.rc_preview.left, UI.rc_preview.bottom - UI.rc_preview.top, 160);
		FrameRect(getMemDC(), UI.rc_preview, RGB(0, 0, 0));
		textOutFont(getMemDC(), UI.rc_preview.left, UI.rc_preview.top, "    [ Tile Preview ]", 20, RGB(0, 0, 0), "맑은 고딕");

		//리스트 BG 출력
		IMAGEMANAGER->findImage("menu_bg")->alphaRender(getMemDC(), UI.rc_listBG.left, UI.rc_listBG.top, 0, 0, UI.rc_listBG.right - UI.rc_listBG.left, UI.rc_listBG.bottom - UI.rc_listBG.top, 160);
		FrameRect(getMemDC(), UI.rc_listBG, RGB(0, 0, 0));


		//타일 파일 명 출력
		SetBkMode(getMemDC(), 0);
		if (UI.tileSort == SORT_TILE)
		{
			//타일 프리뷰 화면 출력 
			tileMenu_land[UI.num_choice + now].img->scaleRender(getMemDC(), UI.rc_preview.left, UI.rc_preview.top + 30, 2.2);
			//타일 파일명 선택 표시 렉트 출력
			FrameRect(getMemDC(), UI.rc_choice, RGB(0, 0, 0));
			TextOut(getMemDC(), 20, 280, tileMenu_land[now].strKey, strlen(tileMenu_land[now].strKey));
			TextOut(getMemDC(), 20, 300, tileMenu_land[now + 1].strKey, strlen(tileMenu_land[now + 1].strKey));
			TextOut(getMemDC(), 20, 320, tileMenu_land[now + 2].strKey, strlen(tileMenu_land[now + 2].strKey));
			TextOut(getMemDC(), 20, 340, tileMenu_land[now + 3].strKey, strlen(tileMenu_land[now + 3].strKey));
			TextOut(getMemDC(), 20, 360, tileMenu_land[now + 4].strKey, strlen(tileMenu_land[now + 4].strKey));
		}
		else if (UI.tileSort == SORT_OBJ)
		{
			//타일 프리뷰 화면 출력 UI.rc_preview = RectMake(UI.rc_miniMap.left, UI.rc_save.bottom + 4, 140, 110);
			if(tileMenu_obj[UI.num_choice + now].img->getHeight() > 110) tileMenu_obj[UI.num_choice + now].img_mini->scaleRender(getMemDC(), UI.rc_preview.left + 36, UI.rc_preview.top + 20, (94 / tileMenu_obj[UI.num_choice + now].img_mini->getHeight()));
			else tileMenu_obj[UI.num_choice + now].img->render(getMemDC(), UI.rc_preview.left + 36, UI.rc_preview.top + 20);
			//타일 파일명 선택 표시 렉트 출력
			FrameRect(getMemDC(), UI.rc_choice, RGB(0, 0, 0));
			TextOut(getMemDC(), 20, 280, tileMenu_obj[now].strKey, strlen(tileMenu_obj[now].strKey));
			TextOut(getMemDC(), 20, 300, tileMenu_obj[now + 1].strKey, strlen(tileMenu_obj[now + 1].strKey));
			TextOut(getMemDC(), 20, 320, tileMenu_obj[now + 2].strKey, strlen(tileMenu_obj[now + 2].strKey));
			TextOut(getMemDC(), 20, 340, tileMenu_obj[now + 3].strKey, strlen(tileMenu_obj[now + 3].strKey));
			TextOut(getMemDC(), 20, 360, tileMenu_obj[now + 4].strKey, strlen(tileMenu_obj[now + 4].strKey));
		}
		else if (UI.tileSort == SORT_ENEMY)
		{
			//타일 프리뷰 화면 출력 UI.rc_preview = RectMake(UI.rc_miniMap.left, UI.rc_save.bottom + 4, 140, 110);
			if (tileMenu_enemy[UI.num_choice + now].img->getHeight() > 110) tileMenu_enemy[UI.num_choice + now].img_mini->scaleRender(getMemDC(), UI.rc_preview.left + 36, UI.rc_preview.top + 20, (94 / tileMenu_enemy[UI.num_choice + now].img_mini->getHeight()));
			else tileMenu_enemy[UI.num_choice + now].img->render(getMemDC(), UI.rc_preview.left + 36, UI.rc_preview.top + 20);
			//타일 파일명 선택 표시 렉트 출력
			FrameRect(getMemDC(), UI.rc_choice, RGB(0, 0, 0));
			TextOut(getMemDC(), 20, 280, tileMenu_enemy[now + 0].strKey, strlen(tileMenu_enemy[now].strKey));
			TextOut(getMemDC(), 20, 300, tileMenu_enemy[now + 1].strKey, strlen(tileMenu_enemy[now + 1].strKey));
			TextOut(getMemDC(), 20, 320, tileMenu_enemy[now + 2].strKey, strlen(tileMenu_enemy[now + 2].strKey));
			TextOut(getMemDC(), 20, 340, tileMenu_enemy[now + 3].strKey, strlen(tileMenu_enemy[now + 3].strKey));
			TextOut(getMemDC(), 20, 360, tileMenu_enemy[now + 4].strKey, strlen(tileMenu_enemy[now + 4].strKey));
		}
		else if (UI.tileSort == SORT_BLOCK)
		{
			//타일 프리뷰 화면 출력
			IMAGEMANAGER->findImage("tile_block")->scaleRender(getMemDC(), UI.rc_preview.left, UI.rc_preview.top + 30, 2.2);
			FrameRect(getMemDC(), RectMake(UI.rc_preview.left + 2, UI.rc_preview.bottom + 6, 136, 20), RGB(0, 0, 0));
			TextOut(getMemDC(), 20, 280, "tile_block.bmp", strlen("tile_block.bmp"));
		}

		//분류 출력
		IMAGEMANAGER->findImage("menu_bg")->alphaRender(getMemDC(), UI.rc_sortBG.left, UI.rc_sortBG.top, 0, 0, UI.rc_sortBG.right - UI.rc_sortBG.left, UI.rc_sortBG.bottom - UI.rc_sortBG.top, 160);
		FrameRect(getMemDC(), UI.rc_sortBG, RGB(0, 0, 0));
		TextOut(getMemDC(), UI.rc_tile.left, UI.rc_tile.top, "Tile", strlen("Tile"));
		TextOut(getMemDC(), UI.rc_obj.left, UI.rc_obj.top, "Obj", strlen("Obj"));
		TextOut(getMemDC(), UI.rc_enemy.left, UI.rc_enemy.top, "Enemy", strlen("Enemy"));
		TextOut(getMemDC(), UI.rc_block.left, UI.rc_block.top, "Block", strlen("Block"));
		if (UI.tileSort == SORT_TILE) FrameRect(getMemDC(), UI.rc_tile, RGB(0, 0, 0));
		if (UI.tileSort == SORT_OBJ) FrameRect(getMemDC(), UI.rc_obj, RGB(0, 0, 0));
		if (UI.tileSort == SORT_ENEMY) FrameRect(getMemDC(), UI.rc_enemy, RGB(0, 0, 0));
		if (UI.tileSort == SORT_BLOCK) FrameRect(getMemDC(), UI.rc_block, RGB(0, 0, 0));

		//메뉴얼 출력
		FrameRect(getMemDC(), UI.rc_manual, RGB(200, 200, 200));
		IMAGEMANAGER->findImage("menu_bg")->alphaRender(getMemDC(), UI.rc_manual.left, UI.rc_manual.top, 0, 0, UI.rc_manual.right - UI.rc_manual.left, UI.rc_manual.bottom - UI.rc_manual.top, 160);
		if(!UI.isManual) textOutFont(getMemDC(), UI.rc_manual.left + 2, UI.rc_manual.top + 2, "▲Manual", 20, RGB(00, 00, 00));
		else 
		{
			IMAGEMANAGER->findImage("keyInfo.1280.350")->alphaRender(getMemDC(), UI.rc_bg.right + 10, UI.rc_bg.top + 340, 160);
			textOutFont(getMemDC(), UI.rc_manual.left + 2, UI.rc_manual.top + 2, "▼Manual", 20, RGB(00, 00, 00));
		}
	}

	//세이브, 로드 팝업창 렌더
	if (UI.isSave)
	{
		this->drowRect(UI.rc_popUP_BG, RGB(210, 210, 210));
		textOutFont(getMemDC(), UI.rc_popUP_BG.left + 60, UI.rc_popUP_BG.top + 50, "저장 하시겠습니까?", 24);
	}
	if (UI.isLoad)
	{
		this->drowRect(UI.rc_popUP_BG, RGB(210, 210, 210));
		textOutFont(getMemDC(), UI.rc_popUP_BG.left + 60, UI.rc_popUP_BG.top + 50, "불러 오시겠습니까?", 24);
	}

	//클리핑 렉터 출력
	if (KEYMANAGER->isToggleKey(VK_F9))
	{
		FrameRect(getMemDC(), rc_clipping_mini, RGB(255, 0, 255));
		FrameRect(getMemDC(), rc_clipping, RGB(255, 0, 255));
	}
	

	SetBkMode(getMemDC(), 2);
	//textOutMouse(getMemDC());
}

//마름모 타일 렌더 함수 PS_DOT
void mapToolScene::drowDiamond(tagTile tile, int i, int j, int iStyle, COLORREF color)
{

	HPEN Pen, oldPen;
	Pen = CreatePen(iStyle, 1, color);
	oldPen = (HPEN)SelectObject(getMemDC(), Pen);

	//마름모 그리기
	MoveToEx(getMemDC(), tile.x - (TILEWIDTH / 2), tile.y, NULL);
	LineTo(getMemDC(), tile.x, tile.y - (TILEHEIGHT / 2));
	LineTo(getMemDC(), tile.x + (TILEWIDTH / 2), tile.y);
	LineTo(getMemDC(), tile.x, tile.y + (TILEHEIGHT / 2));
	LineTo(getMemDC(), tile.x - (TILEWIDTH / 2), tile.y);

	SelectObject(getMemDC(), oldPen);
	DeleteObject(Pen);
}

void mapToolScene::drowRect(RECT rc, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(getMemDC(), &rc, brush);
	DeleteObject(brush);
	FrameRect(getMemDC(), rc, RGB(0, 0, 0));
	FrameRect(getMemDC(), UI.rc_popUP_yes, RGB(0, 0, 0));
	FrameRect(getMemDC(), UI.rc_popUP_no, RGB(0, 0, 0));
	textOutFont(getMemDC(), UI.rc_popUP_yes.left + 14, UI.rc_popUP_yes.top + 4, "YES", 24);
	textOutFont(getMemDC(), UI.rc_popUP_no.left + 20, UI.rc_popUP_no.top + 4, "NO", 24);
}

//해당 타일 좌표(인덱스) 표시 함수
void mapToolScene::drowTileIndex(tagTile tile, int i, int j)
{
	//좌표 표시
	char str[128];
	sprintf(str, "(%d,%d)", i, j);
	TextOut(getMemDC(), tile.x - 12, tile.y - 8, str, strlen(str));
}

//유저 컨트롤 함수 : 맵크기조정(+,-), 맵슬라이드(wasd), 타일 선택(방향키)
void mapToolScene::userControl()
{
	//타일 크기 조정
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS) && tileSize < MAXTILESIZE)
	{
		tileSize++; 
		SOUNDMANAGER->play("버튼");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS) && tileSize > 1)
	{
		tileSize--;
		SOUNDMANAGER->play("버튼");
	}

	//맵 슬라이드
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		pt_tileMark.x -= 4;
		pt_tileMark_mini_x -= 0.4f;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		pt_tileMark.x += 4;
		pt_tileMark_mini_x += 0.4f;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		pt_tileMark.y -= 4;
		pt_tileMark_mini_y -= 0.4f;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		pt_tileMark.y += 4;
		pt_tileMark_mini_y += 0.4f;
	}

	//타일 선택(방향키)
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && UI.num_choice >= 0)
	{
		if (UI.num_choice > 0)
		{
			UI.num_choice--;
			UI.rc_choice = RectMake(UI.rc_preview.left + 2, UI.rc_preview.bottom + 6 + 20 * (UI.num_choice), 136, 20);
			SOUNDMANAGER->play("meter");
		}
		else if (UI.num_choice == 0)
		{
			now--;
			if (now < 0) now++;
			SOUNDMANAGER->play("meter");
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && UI.num_choice <= 4)
	{
		if (UI.num_choice < 4)
		{
			UI.num_choice++;
			UI.rc_choice = RectMake(UI.rc_preview.left + 2, UI.rc_preview.bottom + 6 + 20 * (UI.num_choice), 136, 20);
			SOUNDMANAGER->play("meter");
		}
		else if (UI.num_choice == 4)
		{
			now++;
			if (UI.tileSort == SORT_TILE)
			{
				if (now > TILE_LAND_MAX - 1 - 4) now--;
				SOUNDMANAGER->play("meter");
			}
			else if (UI.tileSort == SORT_OBJ)
			{
				if (now > TILE_OBJ_MAX - 1 - 4) now--;
				SOUNDMANAGER->play("meter");
			}
			else if (UI.tileSort == SORT_ENEMY)
			{
				if (now > TILE_ENEMY_MAX - 1 - 4) now--;
				SOUNDMANAGER->play("meter");
			}
		}
	}

	//분류 선택(방향키)
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		now = 0;
		if(UI.tileSort == SORT_TILE) UI.tileSort = SORT_OBJ;
		else if(UI.tileSort == SORT_OBJ) UI.tileSort = SORT_ENEMY;
		else if(UI.tileSort == SORT_ENEMY) UI.tileSort = SORT_BLOCK;
		SOUNDMANAGER->play("meter");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		now = 0;
		if (UI.tileSort == SORT_BLOCK) UI.tileSort = SORT_ENEMY;
		else if (UI.tileSort == SORT_ENEMY) UI.tileSort = SORT_OBJ;
		else if (UI.tileSort == SORT_OBJ) UI.tileSort = SORT_TILE;
		SOUNDMANAGER->play("meter");
	}

	//타일 입히기
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < tileSize; i++)
		{
			for (int j = 0; j < tileSize; j++)
			{
				if (UI.tileSort == SORT_TILE)
				{
					if (PtInRect(&tile[i][j].rc_picking, _ptMouse))
					{
						tile[i][j].isImg = true;
						tile[i][j].img = tileMenu_land[UI.num_choice + now].img;
						tile[i][j].img_mini = tileMenu_land[UI.num_choice + now].img_mini;
						if(!SOUNDMANAGER->isPlaySound("battle02")) SOUNDMANAGER->play("battle02", 0.2f);
					}
				}
				else if (UI.tileSort == SORT_OBJ)
				{
					if (PtInRect(&tile[i][j].rc_picking, _ptMouse))
					{
						tile[i][j].isImg_obj = true;
						tile[i][j].img_obj = tileMenu_obj[UI.num_choice + now].img;
						tile[i][j].img_mini_obj = tileMenu_obj[UI.num_choice + now].img_mini;
						if (!SOUNDMANAGER->isPlaySound("battle02")) SOUNDMANAGER->play("battle02", 0.2f);
					}
				}
				else if (UI.tileSort == SORT_ENEMY)
				{
					if (PtInRect(&tile[i][j].rc_picking, _ptMouse))
					{
						tile[i][j].isImg_enemy = true;
						tile[i][j].img_enemy = tileMenu_enemy[UI.num_choice + now].img;
						tile[i][j].img_mini_enemy = tileMenu_enemy[UI.num_choice + now].img_mini;
						if (!SOUNDMANAGER->isPlaySound("battle02")) SOUNDMANAGER->play("battle02", 0.2f);
					}
				}
				else if (UI.tileSort == SORT_BLOCK)
				{
					if (PtInRect(&tile[i][j].rc_picking, _ptMouse))
					{
						tile[i][j].state_obj = BLOCK;
						if (!SOUNDMANAGER->isPlaySound("battle02")) SOUNDMANAGER->play("battle02", 0.2f);
					}
				}
			}
		}
	}

	//타일 지우기
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < tileSize; i++)
		{
			for (int j = 0; j < tileSize; j++)
			{
				if (UI.tileSort == SORT_TILE) //타일 제거
				{
					if (PtInRect(&tile[i][j].rc_picking, _ptMouse))
					{
						if (tile[i][j].floor > 0) tile[i][j].floor--;
						else if (tile[i][j].floor == 0)
						{
							tile[i][j].isImg = false;
							tile[i][j].img = IMAGEMANAGER->findImage("빈이미지");
							tile[i][j].img_mini = IMAGEMANAGER->findImage("빈이미지");
							if (!SOUNDMANAGER->isPlaySound("battle02")) SOUNDMANAGER->play("battle02", 0.2f);
						}
					}
				}
				else if (UI.tileSort == SORT_OBJ) //오브젝트 제거
				{
					if (PtInRect(&tile[i][j].rc_picking, _ptMouse))
					{
						tile[i][j].isImg_obj = false;
						tile[i][j].img_obj = IMAGEMANAGER->findImage("빈이미지");
						tile[i][j].img_mini_obj = IMAGEMANAGER->findImage("빈이미지");
						if (!SOUNDMANAGER->isPlaySound("battle02")) SOUNDMANAGER->play("battle02", 0.2f);
					}
				}
				else if (UI.tileSort == SORT_ENEMY) //에너미 제거
				{
					if (PtInRect(&tile[i][j].rc_picking, _ptMouse))
					{
						tile[i][j].isImg_enemy = false;
						tile[i][j].img_enemy = IMAGEMANAGER->findImage("빈이미지");
						tile[i][j].img_mini_enemy = IMAGEMANAGER->findImage("빈이미지");
						if (!SOUNDMANAGER->isPlaySound("battle02")) SOUNDMANAGER->play("battle02", 0.2f);
					}
				}
				else if (UI.tileSort == SORT_BLOCK) //이동 범위 블록 제거
				{
					if (PtInRect(&tile[i][j].rc_picking, _ptMouse))
					{
						tile[i][j].state_obj = NONE;
						if (!SOUNDMANAGER->isPlaySound("battle02")) SOUNDMANAGER->play("battle02", 0.2f);
					}
				}
			}
		}
	}
	
	//높이 구현(4층 까지 구현 가능)
	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
	{
		for (int i = 0; i < tileSize; i++)
		{
			for (int j = 0; j < tileSize; j++)
			{
				if (PtInRect(&tile[i][j].rc_picking, _ptMouse) && tile[i][j].img != IMAGEMANAGER->findImage("빈이미지"))
				{
					tile[i][j].floor++;
					if (!SOUNDMANAGER->isPlaySound("battle08")) SOUNDMANAGER->play("battle08");
					if(tile[i][j].floor == 5) tile[i][j].floor--;
				}
			}
		}
	}

	//생성 타일 저장/로드
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&UI.rc_save, _ptMouse))
		{
			UI.isSave = true;
			SOUNDMANAGER->play("버튼");
		}
		if (PtInRect(&UI.rc_load, _ptMouse))
		{
			UI.isLoad = true;
			SOUNDMANAGER->play("버튼");
		}

		//세이브 팝업
		if (PtInRect(&UI.rc_popUP_yes, _ptMouse) && UI.isSave)
		{
			this->saveMap();
			SOUNDMANAGER->play("find");
			UI.isSave = false;
		}
		if (PtInRect(&UI.rc_popUP_no, _ptMouse) && UI.isSave)
		{
			UI.isSave = false;
			SOUNDMANAGER->play("버튼");
		}
		//로드 팝업
		if (PtInRect(&UI.rc_popUP_yes, _ptMouse) && UI.isLoad)
		{
			this->loadMap();
			SOUNDMANAGER->play("find");
			UI.isLoad = false;
		}
		if (PtInRect(&UI.rc_popUP_no, _ptMouse) && UI.isLoad)
		{
			UI.isLoad = false;
			SOUNDMANAGER->play("버튼");
		}

		//메뉴얼 출력
		if (PtInRect(&UI.rc_manual, _ptMouse) && !UI.isManual)
		{
			UI.isManual = true;
			SOUNDMANAGER->play("버튼");
		}
		else if (PtInRect(&UI.rc_manual, _ptMouse) && UI.isManual)
		{
			UI.isManual = false;
			SOUNDMANAGER->play("버튼");
		}
	}
}

//타일 맵 저장
void mapToolScene::saveMap()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, tile, sizeof(tagTile) * MAXTILESIZE * MAXTILESIZE, &write, NULL);
	CloseHandle(file);
}
//타일 맵 로드
void mapToolScene::loadMap()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, tile, sizeof(tagTile) * MAXTILESIZE * MAXTILESIZE, &read, NULL);
	CloseHandle(file);
}

//메뉴 타일 속성 초기화
void mapToolScene::initMenu_tile()
{
	//맵 이미지 할당
	tileMenu_land[0].img = IMAGEMANAGER->findImage("st51a_01");
	tileMenu_land[1].img = IMAGEMANAGER->findImage("st51a_02");
	tileMenu_land[2].img = IMAGEMANAGER->findImage("st51a_03");
	tileMenu_land[3].img = IMAGEMANAGER->findImage("st51a_04");
	tileMenu_land[4].img = IMAGEMANAGER->findImage("st51a_08");
	tileMenu_land[5].img = IMAGEMANAGER->findImage("st51a_09");
	tileMenu_land[6].img = IMAGEMANAGER->findImage("st51a_10");
	tileMenu_land[7].img = IMAGEMANAGER->findImage("st51a_11");
	tileMenu_land[8].img = IMAGEMANAGER->findImage("st51a_15");
	tileMenu_land[9].img = IMAGEMANAGER->findImage("st51a_16");
	tileMenu_land[10].img = IMAGEMANAGER->findImage("st51a_17");
	tileMenu_land[11].img = IMAGEMANAGER->findImage("st51a_18");
	tileMenu_land[12].img = IMAGEMANAGER->findImage("st51a_22");
	tileMenu_land[13].img = IMAGEMANAGER->findImage("st51a_23");
	tileMenu_land[14].img = IMAGEMANAGER->findImage("st51a_24");
	tileMenu_land[15].img = IMAGEMANAGER->findImage("st51a_25");
	tileMenu_land[16].img = IMAGEMANAGER->findImage("st51a_30");
	tileMenu_land[17].img = IMAGEMANAGER->findImage("st51a_31");
	tileMenu_land[18].img = IMAGEMANAGER->findImage("st51a_32");
	tileMenu_land[19].img = IMAGEMANAGER->findImage("st51a_37");
	tileMenu_land[20].img = IMAGEMANAGER->findImage("st51a_38");
	tileMenu_land[21].img = IMAGEMANAGER->findImage("st51a_39");
	tileMenu_land[22].img = IMAGEMANAGER->findImage("st51a_45");
	tileMenu_land[23].img = IMAGEMANAGER->findImage("st51a_46");
	tileMenu_land[24].img = IMAGEMANAGER->findImage("st51a_52");
	tileMenu_land[25].img = IMAGEMANAGER->findImage("st51a_53");
	tileMenu_land[26].img = IMAGEMANAGER->findImage("st51a_59");
	tileMenu_land[27].img = IMAGEMANAGER->findImage("st51a_60");
	

	//미니맵 이미지 할당
	tileMenu_land[0].img_mini = IMAGEMANAGER->findImage("mini_st51a_01");
	tileMenu_land[1].img_mini = IMAGEMANAGER->findImage("mini_st51a_02");
	tileMenu_land[2].img_mini = IMAGEMANAGER->findImage("mini_st51a_03");
	tileMenu_land[3].img_mini = IMAGEMANAGER->findImage("mini_st51a_04");
	tileMenu_land[4].img_mini = IMAGEMANAGER->findImage("mini_st51a_08");
	tileMenu_land[5].img_mini = IMAGEMANAGER->findImage("mini_st51a_09");
	tileMenu_land[6].img_mini = IMAGEMANAGER->findImage("mini_st51a_10");
	tileMenu_land[7].img_mini = IMAGEMANAGER->findImage("mini_st51a_11");
	tileMenu_land[8].img_mini = IMAGEMANAGER->findImage("mini_st51a_15");
	tileMenu_land[9].img_mini = IMAGEMANAGER->findImage("mini_st51a_16");
	tileMenu_land[10].img_mini = IMAGEMANAGER->findImage("mini_st51a_17");
	tileMenu_land[11].img_mini = IMAGEMANAGER->findImage("mini_st51a_18");
	tileMenu_land[12].img_mini = IMAGEMANAGER->findImage("mini_st51a_22");
	tileMenu_land[13].img_mini = IMAGEMANAGER->findImage("mini_st51a_23");
	tileMenu_land[14].img_mini = IMAGEMANAGER->findImage("mini_st51a_24");
	tileMenu_land[15].img_mini = IMAGEMANAGER->findImage("mini_st51a_25");
	tileMenu_land[16].img_mini = IMAGEMANAGER->findImage("mini_st51a_30");
	tileMenu_land[17].img_mini = IMAGEMANAGER->findImage("mini_st51a_31");
	tileMenu_land[18].img_mini = IMAGEMANAGER->findImage("mini_st51a_32");
	tileMenu_land[19].img_mini = IMAGEMANAGER->findImage("mini_st51a_37");
	tileMenu_land[20].img_mini = IMAGEMANAGER->findImage("mini_st51a_38");
	tileMenu_land[21].img_mini = IMAGEMANAGER->findImage("mini_st51a_39");
	tileMenu_land[22].img_mini = IMAGEMANAGER->findImage("mini_st51a_45");
	tileMenu_land[23].img_mini = IMAGEMANAGER->findImage("mini_st51a_46");
	tileMenu_land[24].img_mini = IMAGEMANAGER->findImage("mini_st51a_52");
	tileMenu_land[25].img_mini = IMAGEMANAGER->findImage("mini_st51a_53");
	tileMenu_land[26].img_mini = IMAGEMANAGER->findImage("mini_st51a_59");
	tileMenu_land[27].img_mini = IMAGEMANAGER->findImage("mini_st51a_60");

	//파일명 할당
	tileMenu_land[0].strKey = "st51a_01.bmp";
	tileMenu_land[1].strKey = "st51a_02.bmp";
	tileMenu_land[2].strKey = "st51a_03.bmp";
	tileMenu_land[3].strKey = "st51a_04.bmp";
	tileMenu_land[4].strKey = "st51a_08.bmp";
	tileMenu_land[5].strKey = "st51a_09.bmp";
	tileMenu_land[6].strKey = "st51a_10.bmp";
	tileMenu_land[7].strKey = "st51a_11.bmp";
	tileMenu_land[8].strKey = "st51a_15.bmp";
	tileMenu_land[9].strKey = "st51a_16.bmp";
	tileMenu_land[10].strKey = "st51a_17.bmp";
	tileMenu_land[11].strKey = "st51a_18.bmp";
	tileMenu_land[12].strKey = "st51a_22.bmp";
	tileMenu_land[13].strKey = "st51a_23.bmp";
	tileMenu_land[14].strKey = "st51a_24.bmp";
	tileMenu_land[15].strKey = "st51a_25.bmp";
	tileMenu_land[16].strKey = "st51a_30.bmp";
	tileMenu_land[17].strKey = "st51a_31.bmp";
	tileMenu_land[18].strKey = "st51a_32.bmp";
	tileMenu_land[19].strKey = "st51a_37.bmp";
	tileMenu_land[20].strKey = "st51a_38.bmp";
	tileMenu_land[21].strKey = "st51a_39.bmp";
	tileMenu_land[22].strKey = "st51a_45.bmp";
	tileMenu_land[23].strKey = "st51a_46.bmp";
	tileMenu_land[24].strKey = "st51a_52.bmp";
	tileMenu_land[25].strKey = "st51a_53.bmp";
	tileMenu_land[26].strKey = "st51a_59.bmp";
	tileMenu_land[27].strKey = "st51a_60.bmp";

	//타일 오브젝트 속성
	for (int i = 0; i < TILE_LAND_MAX; i++) tileMenu_land[i].state_obj = NONE;
}
//메뉴 오브젝트 속성 초기화
void mapToolScene::initMenu_obj()
{
	//오브젝트 이미지 할당
	tileMenu_obj[0].img = IMAGEMANAGER->findImage("sign_2_04");
	tileMenu_obj[1].img = IMAGEMANAGER->findImage("sign_2_05");
	tileMenu_obj[2].img = IMAGEMANAGER->findImage("sign_2_06");
	tileMenu_obj[3].img = IMAGEMANAGER->findImage("tree.64.138");
	tileMenu_obj[4].img = IMAGEMANAGER->findImage("bush1.64.55");
	tileMenu_obj[5].img = IMAGEMANAGER->findImage("bush2.64.45");
	tileMenu_obj[6].img = IMAGEMANAGER->findImage("bush3.64.48");
	tileMenu_obj[7].img = IMAGEMANAGER->findImage("bush4.64.37");
	tileMenu_obj[8].img = IMAGEMANAGER->findImage("bush5.64.58");
	tileMenu_obj[9].img = IMAGEMANAGER->findImage("bush6.64.48");
	tileMenu_obj[10].img = IMAGEMANAGER->findImage("bush7.64.45");
	tileMenu_obj[11].img = IMAGEMANAGER->findImage("bush8.64.37");
	tileMenu_obj[12].img = IMAGEMANAGER->findImage("barrel.64.58");
	tileMenu_obj[13].img = IMAGEMANAGER->findImage("palmtree1.440.252");
	tileMenu_obj[14].img = IMAGEMANAGER->findImage("palmtree2.344.318");
	tileMenu_obj[15].img = IMAGEMANAGER->findImage("st50a");
	tileMenu_obj[16].img = IMAGEMANAGER->findImage("st50b");
	tileMenu_obj[17].img = IMAGEMANAGER->findImage("st50c");


	//미니맵 이미지 할당
	tileMenu_obj[0].img_mini = IMAGEMANAGER->findImage("mini_sign_2_04");
	tileMenu_obj[1].img_mini = IMAGEMANAGER->findImage("mini_sign_2_05");
	tileMenu_obj[2].img_mini = IMAGEMANAGER->findImage("mini_sign_2_06");
	tileMenu_obj[3].img_mini = IMAGEMANAGER->findImage("mini_tree.64.138");
	tileMenu_obj[4].img_mini = IMAGEMANAGER->findImage("mini_bush1.64.55");
	tileMenu_obj[5].img_mini = IMAGEMANAGER->findImage("mini_bush2.64.45");
	tileMenu_obj[6].img_mini = IMAGEMANAGER->findImage("mini_bush3.64.48");
	tileMenu_obj[7].img_mini = IMAGEMANAGER->findImage("mini_bush4.64.37");
	tileMenu_obj[8].img_mini = IMAGEMANAGER->findImage("mini_bush5.64.58");
	tileMenu_obj[9].img_mini = IMAGEMANAGER->findImage("mini_bush6.64.48");
	tileMenu_obj[10].img_mini = IMAGEMANAGER->findImage("mini_bush7.64.45");
	tileMenu_obj[11].img_mini = IMAGEMANAGER->findImage("mini_bush8.64.37");
	tileMenu_obj[12].img_mini = IMAGEMANAGER->findImage("mini_barrel.64.58");
	tileMenu_obj[13].img_mini = IMAGEMANAGER->findImage("mini_palmtree1.440.252");
	tileMenu_obj[14].img_mini = IMAGEMANAGER->findImage("mini_palmtree2.344.318");
	tileMenu_obj[15].img_mini = IMAGEMANAGER->findImage("mini_st50a");
	tileMenu_obj[16].img_mini = IMAGEMANAGER->findImage("mini_st50b");
	tileMenu_obj[17].img_mini = IMAGEMANAGER->findImage("mini_st50c");


	//파일명 할당
	tileMenu_obj[0].strKey = "sign_2_04.bmp";
	tileMenu_obj[1].strKey = "sign_2_05.bmp";
	tileMenu_obj[2].strKey = "sign_2_06.bmp";
	tileMenu_obj[3].strKey = "tree.64.138.bmp";
	tileMenu_obj[4].strKey = "bush1.64.55.bmp";
	tileMenu_obj[5].strKey = "bush2.64.45.bmp";
	tileMenu_obj[6].strKey = "bush3.64.48.bmp";
	tileMenu_obj[7].strKey = "bush4.64.37.bmp";
	tileMenu_obj[8].strKey = "bush5.64.58.bmp";
	tileMenu_obj[9].strKey = "bush6.64.48.bmp";
	tileMenu_obj[10].strKey = "bush7.64.45.bmp";
	tileMenu_obj[11].strKey = "bush8.64.37.bmp";
	tileMenu_obj[12].strKey = "barrel.64.58.bmp";
	tileMenu_obj[13].strKey = "palm1.440.252.bmp";
	tileMenu_obj[14].strKey = "palm2.344.318.bmp";
	tileMenu_obj[15].strKey = "st50a.bmp";
	tileMenu_obj[16].strKey = "st50b.bmp";
	tileMenu_obj[17].strKey = "st50c.bmp";

}
//메뉴 에너미 속성 초기화
void mapToolScene::initMenu_enemy()
{
	//오브젝트 이미지 할당
	tileMenu_enemy[0].img = IMAGEMANAGER->findImage("char_15e");
	tileMenu_enemy[1].img = IMAGEMANAGER->findImage("necro1");
	tileMenu_enemy[2].img = IMAGEMANAGER->findImage("char_33a");
	tileMenu_enemy[3].img = IMAGEMANAGER->findImage("char_68e");
	tileMenu_enemy[4].img = IMAGEMANAGER->findImage("char_15e");

	//미니맵 이미지 할당
	tileMenu_enemy[0].img_mini = IMAGEMANAGER->findImage("mini_char_15e");
	tileMenu_enemy[1].img_mini = IMAGEMANAGER->findImage("mini_necro1");
	tileMenu_enemy[2].img_mini = IMAGEMANAGER->findImage("mini_char_33a");
	tileMenu_enemy[3].img_mini = IMAGEMANAGER->findImage("mini_char_68e");
	tileMenu_enemy[4].img_mini = IMAGEMANAGER->findImage("mini_char_15e");

	//파일명 할당
	tileMenu_enemy[0].strKey = "char_15e.bmp";
	tileMenu_enemy[1].strKey = "necro1.bmp";
	tileMenu_enemy[2].strKey = "char_33a.bmp";
	tileMenu_enemy[3].strKey = "char_68e.bmp";
	tileMenu_enemy[4].strKey = "char_14e.bmp";
}

