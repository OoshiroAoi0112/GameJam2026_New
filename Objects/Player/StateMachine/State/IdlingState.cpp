#include "IdlingState.h"

#include "DxLib.h"
#include "../../../../Utility/InputControl.h"
#include "../../Player.h"
#include "../../../../Utility/ResourceManager.h"
#include "../../../../Utility/Vector2D.h"

IdlingState::IdlingState(class Player* p) :
	idling_animation(),
	PlayerStateBase(p),
	idling_animation_count(0),
	idling_animation_time(0.0f),
	input(nullptr)
{
	start_x = 0;

	ResourceManager* rm = ResourceManager::GetInstance();
	idling_animation = rm->GetImages("Resource/image/Player/Normal/Idling/Normal_Idling.png", 2, 2, 1, 276, 452);
	idling_image = idling_animation[0];
}

IdlingState::~IdlingState()
{
}

void IdlingState::Initialize()
{
	input = InputControl::GetInstance();
}

void IdlingState::Update(float delta_second)
{
	if(this->player->velocity.x < 0)
	{
		this->player->velocity.x += D_PLAYER_SPEED * delta_second;
	}
	if (this->player->velocity.x > 0)
	{
		this->player->velocity.x -= D_PLAYER_SPEED * delta_second;
	}
	if (this->player->velocity.x < 1.0f && this->player->velocity.x > -1.0f)
	{
		this->player->velocity.x = 0.0f;
	}

	if(input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress ||
		input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::eHold ||
		input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress ||
		input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::eHold)
	{
		player->SetNextState(ePlayerState::ROLL);
	}

	if(input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress ||
		input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::eHold)
	{
		player->SetNextState(ePlayerState::JUMP);
	}
}

void IdlingState::Draw() const
{
	//À•Wî•ñ‚ð®”’l‚É•ÏŠ·
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	DrawRotaGraph(x, y, 0.4, 0, idling_image, TRUE);

	DrawFormatString(640, 40, GetColor(255, 255, 255), "Player State : Idling");
}

void IdlingState::Finalize()
{
}

void IdlingState::Animation(float delta_second)
{
	idling_animation_time += delta_second;
	if (idling_animation_time >= 0.5f)
	{
		idling_animation_time = 0.0f;
		idling_animation_count++;
		if (idling_animation_count >= 2)
		{
			idling_animation_count = 0;
		}
		idling_image = idling_animation[idling_animation_num[idling_animation_count]];
	}
}

ePlayerState IdlingState::GetState() const
{
	return ePlayerState::IDLE;
}

//void IdlingState::AnimaCount(float delta_second)
//{
//	idling_animation_time += delta_second;
//	if (idling_animation_time >= 0.5f)
//	{
//		idling_animation_time = 0.0f;
//		idling_animation_count++;
//		if (idling_animation_count >= 2)
//		{
//			idling_animation_count = 0;
//		}
//		idling_image = idling_animation[idling_animation_num[idling_animation_count]];
//	}
//}
