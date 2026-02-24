#pragma once
#include "../PlayerStateBase.h"
#include <vector>

class RollingState : public PlayerStateBase
{
private:
	class InputControl* input;  // “ü—Íî•ñ

	std::vector<int> rolling_animation;

	int rolling_animation_num;
	int rolling_animation_count;
	float rolling_animation_time;

	int rolling_image;

	float start_x;

	float angle;

public:
	RollingState(class Player* p);
	virtual ~RollingState();

public:
	virtual void Initialize() override;

	virtual void Update(float delta_second) override;

	virtual void Draw(const Vector2D& screen_offset) const override;

	virtual void Finalize() override;

	virtual void Animation(float delta_second) override;

	virtual ePlayerState GetState() const override;
};