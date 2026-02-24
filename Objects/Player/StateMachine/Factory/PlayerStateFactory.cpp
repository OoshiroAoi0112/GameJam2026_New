#include "PlayerStateFactory.h"

#include "../State/IdlingState.h"
#include "../State/JumpingState.h"
#include "../State/RollingState.h"
#include "../State/ClearState.h"
#include "../State/DyingState.h"

#include "../../Player.h"

PlayerStateFactory* PlayerStateFactory::instance = nullptr;

void PlayerStateFactory::Initialize(Player& player)
{
    idle = new IdlingState(&player);
    roll = new RollingState(&player);
    jump = new JumpingState(&player);
    clear = new ClearState(&player);
    die = new DyingState(&player);
}

PlayerStateBase* PlayerStateFactory::Get(Player& player, ePlayerState type)
{
    if (instance == nullptr)
    {
        instance = new PlayerStateFactory();
        instance->Initialize(player);
    }

    // ★ここが本丸：毎回「今のPlayer」に差し替える
    if (instance->idle)  instance->idle->SetOwner(&player);
    if (instance->roll)  instance->roll->SetOwner(&player);
    if (instance->jump)  instance->jump->SetOwner(&player);
    if (instance->clear) instance->clear->SetOwner(&player);
    if (instance->die)   instance->die->SetOwner(&player);

    PlayerStateBase* ret = nullptr;

    switch (type)
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

    default:
        // NONEなど
        ret = nullptr;
        break;
    }

    return ret;
}

void PlayerStateFactory::Finalize()
{
    if (instance == nullptr) return;

    delete instance->idle;  instance->idle = nullptr;
    delete instance->roll;  instance->roll = nullptr;
    delete instance->jump;  instance->jump = nullptr;
    delete instance->clear; instance->clear = nullptr;
    delete instance->die;   instance->die = nullptr;

    delete instance;
    instance = nullptr;
}