#pragma once
#include "../PlayerStateBase.h"
#include <vector>

class JumpingState : public PlayerStateBase
{
private:
	class InputControl* input;  // “ü—Íî•ñ

	std::vector<int> jumping_animation;

	int jumping_animation_num;
	int jumping_animation_count;
	float jumping_animation_time;

	int jumping_image;

	float start_x;

	float jump_angle;

public:
	JumpingState(class Player* p);
	virtual ~JumpingState();

public:
	virtual void Initialize() override;

	virtual void Update(float delta_second) override;

	virtual void Draw(const Vector2D& screen_offset) const override;

	virtual void Finalize() override;

	virtual void Animation(float delta_second) override;

	virtual ePlayerState GetState()const override;
};