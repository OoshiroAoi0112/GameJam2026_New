#pragma once
#include "../PlayerStateBase.h"

class RollingState : public PlayerStateBase
{
private:
	class InputControl* input;  // “ü—Íî•ñ

public:
	RollingState(class Player* p);
	virtual ~RollingState();

public:
	virtual void Initialize() override;

	virtual void Update(float delta_second) override;

	virtual void Draw()const override;

	virtual void Finalize() override;

	virtual ePlayerState GetState()const override;
};