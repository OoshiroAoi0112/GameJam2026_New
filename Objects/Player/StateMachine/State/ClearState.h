#pragma once
#include "../PlayerStateBase.h"

class ClearState : public PlayerStateBase
{
public:
	ClearState(class Player* p);
	~ClearState();

public:
	virtual void Initialize() override;

	virtual void Update(float delta_second) override;

	virtual void Draw()const override;

	virtual void Finalize() override;

	virtual ePlayerState GetState()const override;
};