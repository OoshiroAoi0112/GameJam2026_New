#include "ClearState.h"

#include "DxLib.h"
#include "../PlayerStateBase.h"

ClearState::ClearState(class Player* p) :
	PlayerStateBase(p)
{
}

ClearState::~ClearState()
{
}

void ClearState::Initialize()
{
}

void ClearState::Update(float delta_second)
{
}

void ClearState::Draw() const
{
}

void ClearState::Finalize()
{
}

ePlayerState ClearState::GetState() const
{
	return ePlayerState::CLEAR;
}
