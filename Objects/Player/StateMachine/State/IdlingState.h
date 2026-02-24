#pragma once
#include "../PlayerStateBase.h"

class IdlingState : public PlayerStateBase
{
private:
	class InputControl* input;  // “ü—Íî•ñ

public:
	IdlingState(class Player* p);
	virtual ~IdlingState();

public:
	virtual void Initialize() override;

	virtual void Update(float delta_second) override;

	virtual void Draw()const override;

	virtual void Finalize() override;

	virtual ePlayerState GetState()const override;
};