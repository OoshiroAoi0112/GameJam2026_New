#include "JumpingState.h"

#include "DxLib.h"
#include "../../../../Utility/InputControl.h"
#include "../../Player.h"

JumpingState::JumpingState(class Player* p) :
	PlayerStateBase(p),
	input(nullptr)
{
}

JumpingState::~JumpingState()
{
}

void JumpingState::Initialize()
{
	input = InputControl::GetInstance();

	player->velocity.y = -D_JUMP_POWER;
	player->on_ground = false;
}

void JumpingState::Update(float delta_second)
{
	if (player->on_ground == true)
	{
		player->SetNextState(ePlayerState::IDLE);
	}
}

void JumpingState::Draw() const
{
	//À•Wî•ñ‚ð®”’l‚É•ÏŠ·
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);
}

void JumpingState::Finalize()
{
}

void JumpingState::Animation(float delta_second)
{
}

ePlayerState JumpingState::GetState() const
{
	return ePlayerState::JUMP;
}
