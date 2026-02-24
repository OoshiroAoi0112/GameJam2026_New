#include "RollingState.h"

#include "DxLib.h"
#include "../../../../Utility/InputControl.h"
#include "../../Player.h"
#include "../../../../Utility/ResourceManager.h"
#include "../../../../Utility/Vector2D.h"
#include <math.h>

RollingState::RollingState(class Player* p) :
	rolling_animation(),
	PlayerStateBase(p),
	rolling_animation_count(0),
	rolling_animation_time(0.0f),
	input(nullptr)
{
	start_x = 0;

	ResourceManager* rm = ResourceManager::GetInstance();
	rolling_animation = rm->GetImages("Resource/image/Player/Normal/Rolling/Normal_Rolling_3.png", 1, 1, 1, 200, 200);
	rolling_image = rolling_animation[0];
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

	angle += (player->velocity.x * 0.0001f);
}

void RollingState::Draw(const Vector2D& screen_offset) const
{
	// 画面に描画する座標（←ここが超重要）
	int drawX = static_cast<int>(player->location.x + screen_offset.x);
	int drawY = static_cast<int>(player->location.y + screen_offset.y);

	DrawRotaGraph(drawX, drawY + 20, 0.06, angle, rolling_image, TRUE);
}

void RollingState::Finalize()
{
	
}

void RollingState::Animation(float delta_second)
{
	rolling_animation_time += delta_second;
	if (rolling_animation_time >= 0.5f)
	{
		rolling_animation_time = 0.0f;
		rolling_animation_count++;
		if (rolling_animation_count >= rolling_animation.size())
		{
			rolling_animation_count = 0;
		}
		rolling_image = rolling_animation[rolling_animation_count];
	}
}

ePlayerState RollingState::GetState() const
{
	return ePlayerState::ROLL;
}
