#include "PlayerStateFactory.h"

#include "../State/IdlingState.h"
#include "../State/JumpingState.h"
#include "../State/RollingState.h"
#include "../State/ClearState.h"
#include "../State/DyingState.h"

#include "../../Player.h"

PlayerStateFactory* PlayerStateFactory::instance = nullptr;

void PlayerStateFactory::Initialize(class Player& player)
{
	idle = new IdlingState(&player);
	roll = new RollingState(&player);
	jump = new JumpingState(&player);
	clear = new ClearState(&player);
	die = new DyingState(&player);
}

PlayerStateBase* PlayerStateFactory::Get(Player& player, ePlayerState state)
{
	if(instance== nullptr)
	{
		instance = new PlayerStateFactory();
		instance->Initialize(player);
	}

	PlayerStateBase* ret = nullptr;
	switch (state)
	{
	case ePlayerState::IDLE:
		instance->idle->Initialize();
		ret = instance->idle;
		break;
	case ePlayerState::ROLL:
		instance->roll->Initialize();
		ret = instance->roll;
		break;
	case ePlayerState::JUMP:
		instance->jump->Initialize();
		ret = instance->jump;
		break;
	case ePlayerState::CLEAR:
		instance->clear->Initialize();
		ret = instance->clear;
		break;
	case ePlayerState::DIE:
		instance->die->Initialize();
		ret = instance->die;
		break;
	}
	return ret;
}
