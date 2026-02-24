#pragma once
#include "../PlayerStateBase.h"
#include <vector>

class IdlingState : public PlayerStateBase
{
private:
	class InputControl* input;  // “ü—Íî•ñ

    std::vector<int> idling_animation;

    const int idling_animation_num[2] = { 0,1 };
    int idling_animation_count;
    float idling_animation_time;

    int idling_image;

    float start_x;

public:
	IdlingState(class Player* p);
	virtual ~IdlingState();

public:
	virtual void Initialize() override;

	virtual void Update(float delta_second) override;

	virtual void Draw()const override;

	virtual void Finalize() override;

	virtual void Animation(float delta_second) override;

	virtual ePlayerState GetState()const override;

	/*void AnimaCount(float delta_second);*/
};