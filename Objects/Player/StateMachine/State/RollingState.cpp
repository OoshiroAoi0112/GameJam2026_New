#include "RollingState.h"

#include "DxLib.h"
#include "../../../../Utility/InputControl.h"
#include "../../Player.h"
#include <math.h>

RollingState::RollingState(class Player* p) :
	PlayerStateBase(p),
	input(nullptr)
{
}

RollingState::~RollingState()
{
}

void RollingState::Initialize()
{
	input = InputControl::GetInstance();
}

void RollingState::Update(float delta_second)
{
	if (input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress ||
		input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::eHold)
	{
		player->velocity.x += -D_PLAYER_SPEED * delta_second;
	}
	if (input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress ||
		input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::eHold)
	{
		player->velocity.x += D_PLAYER_SPEED * delta_second;
	}

	// 入力がない場合は減速処理
	if (input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::eNone &&
		input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::eNone) 
	{
		// 減速処理
		if (player->velocity.x < 0)
		{
			player->velocity.x += D_PLAYER_SPEED * delta_second;
		}
		else if (player->velocity.x > 0)
		{
			player->velocity.x -= D_PLAYER_SPEED * delta_second;
		}
	}
	
	// Idle遷移条件
	if (fabsf(player->velocity.x) < 0.1f)
	{
		player->velocity.x = 0.0f;
		player->SetNextState(ePlayerState::IDLE);
	}

	// プレイヤーのjump状態への遷移
	if (input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		player->SetNextState(ePlayerState::JUMP);
	}
}

void RollingState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);
}

void RollingState::Finalize()
{
}

ePlayerState RollingState::GetState() const
{
	return ePlayerState::ROLL;
}
