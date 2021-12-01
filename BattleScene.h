#pragma once
#include "GameEntity.h"
#include "Config.h"
#include "MapInfo.h"

class Image;
class BattleScene : public GameEntity
{
private:

	MAP_INFO mapInfo;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;	// 오버로딩
	virtual void Release() override;
	virtual ~BattleScene() = default;
	int Load(int num);
};

