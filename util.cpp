#include "stdafx.h"
#include "util.h"

float MY_UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float MY_UTIL::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	float distance = sqrtf(x * x + y * y);
	float angle = acosf(x / distance);
	if (endY > startY)
	{
		angle = PI2 - angle;
	}
	return angle;
}


// < 이미지넘버 > (string 이미지키, HDC hdc, int 출력x좌표, int 출력y좌표, int 출력숫자, int 숫자간격)
void MY_UTIL::imageNum(string keyName, HDC hdc, int x, int y, int num, int gapNum)
{
	if (num < 10)
	{
		IMAGEMANAGER->findImage(keyName)->setFrameX(num % 10);
		return IMAGEMANAGER->frameRender(keyName, hdc, x, y);
	}
	IMAGEMANAGER->findImage(keyName)->setFrameX(num % 10);
	IMAGEMANAGER->frameRender(keyName, hdc, x, y);
	return imageNum(keyName, hdc, x - gapNum, y, num / 10, gapNum);
}

void MY_UTIL::imagescaleNum(string keyName, HDC hdc, int x, int y, int num, int gapNum, float scale)
{
	if (num < 10)
	{
		IMAGEMANAGER->findImage(keyName)->setFrameX(num % 10);
		return IMAGEMANAGER->scaleFrameRender(keyName, hdc, x, y, IMAGEMANAGER->findImage("숫자2")->getFrameX(), IMAGEMANAGER->findImage("숫자2")->getFrameY(), scale);
	}
	IMAGEMANAGER->findImage(keyName)->setFrameX(num % 10);
	IMAGEMANAGER->scaleFrameRender(keyName, hdc, x, y, IMAGEMANAGER->findImage("숫자2")->getFrameX(), IMAGEMANAGER->findImage("숫자2")->getFrameY(), scale);
	return imagescaleNum(keyName, hdc, x - gapNum, y, num / 10, gapNum, scale);
}


void MY_UTIL::textOutMouse(HDC hdc)
{
	char strMouse[128];
	sprintf(strMouse, "x: %d, y: %d", _ptMouse.x, _ptMouse.y);
	TextOut(hdc, WINSIZEX - 90, 50, strMouse, strlen(strMouse));
}

void MY_UTIL::textOutDbug(HDC hdc, int x, int y, float num)
{
	char strDbug[128];
	sprintf(strDbug, "%.2f", num);
	TextOut(hdc, x, y, strDbug, strlen(strDbug));
}



void MY_UTIL::savePlayer()
{
	//세이브 테스트
	char str[2][128];
	INIDATA->addData("유저정보", "골드", itoa(playerData::getSingleton()->gold, str[0], 10));
	INIDATA->addData("유저정보", "성", itoa(playerData::getSingleton()->lv_castle, str[1], 10));

	INIDATA->saveINI("playerData");
}

void MY_UTIL::loadPlayer()
{
	//로드 테스트
	playerData::getSingleton()->gold = INIDATA->loadDataInteger("playerData", "유저정보", "골드");
	playerData::getSingleton()->lv_castle = INIDATA->loadDataInteger("playerData", "유저정보", "성");
}



void MY_UTIL::textOutFont(HDC hdc, int x, int y, const char* str, int size, COLORREF color, const char* font)
{
	SetBkMode(hdc, 1);
	SetTextColor(hdc, color);

	HFONT hFont, oldFont;
	//(높이, 폭, 엥글, 한글자엥글(안됨), 두께(안됨), ?, ?, ?, 문자셋, 출력정확도, 클리핑정확도, ?, 폰트피치와그룹, 글꼴이름)
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT(font));
	oldFont = (HFONT)SelectObject(hdc, hFont);
	TextOut(hdc, x, y, str, strlen(str));

	//복귀
	SetBkMode(hdc, 2);
	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void MY_UTIL::textOutFontNum(HDC hdc, int x, int y, int Stat, int size, COLORREF color, const char* font)
{
	SetBkMode(hdc, 1);
	SetTextColor(hdc, color);

	char Num[128];
	sprintf(Num, "%d", Stat);

	HFONT hFont, oldFont;
	//(높이, 폭, 엥글, 한글자엥글(안됨), 두께(안됨), ?, ?, ?, 문자셋, 출력정확도, 클리핑정확도, ?, 폰트피치와그룹, 글꼴이름)
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT(font));
	oldFont = (HFONT)SelectObject(hdc, hFont);

	TextOut(hdc, x, y, Num, strlen(Num));

	//복귀
	SetBkMode(hdc, 2);
	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}


