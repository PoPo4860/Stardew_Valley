#pragma once
#include "GameObject.h"
#include "MapInfo.h"
#include "Interaction.h"
#include "Character.h"
class SmallStone : public Interaction, public Character
{
private:
	Stone_Object_Info objectInfo;
	int frame;
public:
	SmallStone(Stone_Object_Info obj, int x, int y);
	~SmallStone() = default;
	virtual bool InteractionPick(int damage) override;
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

