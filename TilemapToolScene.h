#pragma once
#include "GameEntity.h"
#include "Config.h"
#include "MapInfo.h"
#include <vector>

typedef struct tagSampleTile
{
	tagSampleTile() :
		rc{ }, frameX{ NULL }, frameY{ NULL }
	{};
	RECT rc;
	int frameX, frameY;
} SAMPLE_TILE_INFO;

class Image;
class TilemapToolScene : public GameEntity
{
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	TilemapToolScene() :
		pen{},
		oPen{},
		sampleTileInfo{},
		selectedSampleTile{},
		sampleTileWidth{ NULL }, sampleTileHeight{ NULL },
		selectDungeon{ nullptr },
		dungeonGray{ nullptr },
		dungeonIce{ nullptr },
		dungeonIce2{ nullptr },
		dungeonRed{ nullptr },
		dungeonSand{ nullptr },
		dungeonSand2{ nullptr },
		dungeonSlime{ nullptr },
		dungeonSoil{ nullptr },
		dungeonStone{ nullptr },
		layerNumImage{ nullptr },
		layerModeImage{ nullptr }, 
		layerNum{ 0 },
		layerMode{ 0 }, 
		mouse{},
		mapInfo{},
		mapPrintX{ 20 }, mapPrintY{ 20 }, 
		mapPosX{ 0 }, mapPosY{ 0 },
		tileState{ Tile_State::Empty }
	{};
	virtual ~TilemapToolScene() = default;
	void Save();
	void Load();

private:
	HPEN pen, oPen;
	SAMPLE_TILE_INFO sampleTileInfo[20][20];	//	샘플 타일
	SAMPLE_TILE_INFO selectedSampleTile;		//	선택된 샘플타일
	int sampleTileWidth, sampleTileHeight;							// 선택된 샘플타일의 너비와 높이
	Image* selectDungeon;	//==============
	Image* dungeonGray;		//
	Image* dungeonIce;		//
	Image* dungeonIce2;		//
	Image* dungeonRed;		//	던전 샘플타일들
	Image* dungeonSand;		//
	Image* dungeonSand2;	//
	Image* dungeonSlime;	//
	Image* dungeonSoil;		//
	Image* dungeonStone;	//==============
	Image* layerNumImage;	//	타일의 레이어 넘버 이미지
	int layerNum;			//	타일의 레이어 넘버
	Image* layerModeImage;	//	타일의 레이어 출력 모드 이미지
	int layerMode;			//	타일의 레이어 출력 모드
	Image* tileStateImage;	//  맵 타일의 상태 이미지
	Tile_State tileState;	//  맵 타일의 상태(열거형)
	POINT mouse;			//	마우스 위치
	MAP_INFO mapInfoTemp;		// 저장할 맵 템프
	MAP_INFO mapInfo;
	int mapPrintX, mapPrintY;	// 맵 출력 범위
	int mapPosX, mapPosY;		// 현재 보는 맵 위치
};

