#pragma once

#include "../PlayerStateBase.h"

class PlayerStateFactory
{
private:
	static PlayerStateFactory* instance;

private:
	PlayerStateFactory() = default;
	~PlayerStateFactory() = default;	
	PlayerStateFactory& operator=(const PlayerStateFactory&) = delete;

private:
	class IdlingState* idle;
	class RollingState* roll;
	class JumpingState* jump;
	class ClearState* clear;
	class DyingState* die;

public:
	void Initialize(class Player& player);

public:
	static PlayerStateBase* Get(class Player& player, ePlayerState type);
	static void Finalize();
};