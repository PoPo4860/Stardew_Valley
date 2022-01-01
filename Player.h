#pragma once
#include "GameObject.h"
#include "Character.h"
class Image;
enum MoveDirection { Up = 0, Down = 1, Left = 2, Right = 3 };
enum class PlayerState { Normal, Move, Pick };

class PlayerStateMove;
class PlayerStatePick;
class PlayerItemHold;
class Player : public GameObject, public Character
{
private:
	friend class PlayerStateMove;
	PlayerStateMove* playerStateMove;
	friend class PlayerStatePick;
	PlayerStatePick* playerStatePick;
	friend class PlayerItemHold;
	PlayerItemHold* playerItemHold;

	MoveDirection playerDirection;
	PlayerState playerState;

	const void SetPos(POINTFLOAT pos) { this->pos = pos; }
	const POINT GetFrontTilePos() const;
	void KeyDownChangeState();
public:
	Player();
	
	virtual HRESULT Init()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
	virtual void Release()override;
	virtual ~Player() = default;
};
