#pragma once
#include "GameObject.h"
#include "Character.h"
class Image;
enum MoveDirection { Up = 0, Down = 1, Left = 2, Right = 3 };
enum class PlayerState { Normal, Pick };
struct PlayerImage
{
	PlayerImage() :
		move{ nullptr },
		pick{ nullptr }
	{}
	Image* move;
	Image* pick;
};
class Player : public GameObject, public Character
{
private:
	MoveDirection direction;
	PlayerState playerState;
	PlayerImage playerImage;
	float frameX;
	bool actionCheck;
	// ������ ����

	void Move(float posX, float posY);
	void StateNormalUpdate();
	void StateNormalRender(HDC hdc, int frame);
	void StatePickUpdate();
	void StatePickRender(HDC hdc, int frame);

	POINT GetFrontTilePos();
	void ActionPick();


	int GetFrame();
	float time;
public:
	Player();
	
	virtual HRESULT Init()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
	virtual void Release()override;
	virtual ~Player() = default;
};
