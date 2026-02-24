#pragma once

#include "../PlayerStateBase.h"

class Player;
class IdlingState;
class RollingState;
class JumpingState;
class ClearState;
class DyingState;

class PlayerStateFactory
{
private:
    static PlayerStateFactory* instance;

private:
    PlayerStateFactory() = default;
    ~PlayerStateFactory() = default;
    PlayerStateFactory& operator=(const PlayerStateFactory&) = delete;

private:
    IdlingState* idle = nullptr;
    RollingState* roll = nullptr;
    JumpingState* jump = nullptr;
    ClearState* clear = nullptr;
    DyingState* die = nullptr;

private:
    void Initialize(Player& player);

public:
    static PlayerStateBase* Get(Player& player, ePlayerState type);
    static void Finalize();
};