#pragma once
#include "Enum/PlayerState.h"

class PlayerStateBase
{
protected:
	class Player* player;

public:
	PlayerStateBase(class Player* p) : player(p)
	{

	}

	virtual ~PlayerStateBase() = default;

public:
	virtual void Initialize() = 0;
	virtual void Update(float delta_second) = 0;
	virtual void Draw()const = 0;
	virtual void Finalize() = 0;

	virtual ePlayerState GetState() const = 0;
};