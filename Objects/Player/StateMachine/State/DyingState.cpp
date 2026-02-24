#include "DyingState.h"

#include "DxLib.h"
#include "../PlayerStateBase.h"

DyingState::DyingState(class Player* p) :
	PlayerStateBase(p)
{
}

DyingState::~DyingState()
{
}

void DyingState::Initialize()
{
}

void DyingState::Update(float delta_second)
{
}

void DyingState::Draw() const
{
}

void DyingState::Finalize()
{
}

void DyingState::Animation(float delta_second)
{
}

ePlayerState DyingState::GetState() const
{
	return ePlayerState::DIE;
}
