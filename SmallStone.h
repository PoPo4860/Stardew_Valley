#pragma once
#include "GameObject.h"
#include "MapInfo.h"
#include "Interaction.h"
#include "Character.h"
class SmallStone : public Interaction, public Character
{
private:
	int frameX;
	int frameY;
	Dungeon_Tiles dungeonTiles;
	int hitAction;
	bool hitActionCheck;
	void SetStoneInfo();

public:
	SmallStone(Dungeon_Tiles dungeonTiles, int x, int y);
	virtual ~SmallStone() = default;
	virtual bool InteractionPick(int damage) override;
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	void HitAction();
	void CreateItem();
};

