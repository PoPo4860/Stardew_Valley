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
	SAMPLE_TILE_INFO sampleTileInfo[20][20];	//	���� Ÿ��
	SAMPLE_TILE_INFO selectedSampleTile;		//	���õ� ����Ÿ��
	int sampleTileWidth, sampleTileHeight;							// ���õ� ����Ÿ���� �ʺ�� ����
	Image* selectDungeon;	//==============
	Image* dungeonGray;		//
	Image* dungeonIce;		//
	Image* dungeonIce2;		//
	Image* dungeonRed;		//	���� ����Ÿ�ϵ�
	Image* dungeonSand;		//
	Image* dungeonSand2;	//
	Image* dungeonSlime;	//
	Image* dungeonSoil;		//
	Image* dungeonStone;	//==============
	Image* layerNumImage;	//	Ÿ���� ���̾� �ѹ� �̹���
	int layerNum;			//	Ÿ���� ���̾� �ѹ�
	Image* layerModeImage;	//	Ÿ���� ���̾� ��� ��� �̹���
	int layerMode;			//	Ÿ���� ���̾� ��� ���
	Image* tileStateImage;	//  �� Ÿ���� ���� �̹���
	Tile_State tileState;	//  �� Ÿ���� ����(������)
	POINT mouse;			//	���콺 ��ġ
	MAP_INFO mapInfoTemp;		// ������ �� ����
	MAP_INFO mapInfo;
	int mapPrintX, mapPrintY;	// �� ��� ����
	int mapPosX, mapPosY;		// ���� ���� �� ��ġ
};

