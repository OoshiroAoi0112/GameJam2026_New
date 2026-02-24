#pragma once
#include "../PlayerStateBase.h"

class DyingState : public PlayerStateBase
{
public:
	DyingState(class Player* p);
	~DyingState();

public:
	virtual void Initialize() override;

	virtual void Update(float delta_second) override;

	virtual void Draw()const override;

	virtual void Finalize() override;

	virtual ePlayerState GetState()const override;
};