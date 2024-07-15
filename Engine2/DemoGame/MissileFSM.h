#pragma once

#include "../D2DEngine/FSMState.h"

class Animation;
class Missile;
class MissileFSM : public FSMState
{
public:
	MissileFSM(FiniteStateMachine* pOwner, std::string Name);
	~MissileFSM();
	Animation* ani; //이렇게 해도 자식까지 순수가상이 잘넘어오겠지?
	Missile* missile; //이렇게 해도 자식까지 순수가상이 잘넘어오겠지?
};

class MissileIdle : public MissileFSM
{
public:
	MissileIdle(FiniteStateMachine* pOwner, std::string Name) : MissileFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};


class MissileChase : public MissileFSM
{
public:
	MissileChase(FiniteStateMachine* pOwner, std::string Name) : MissileFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};


class MissileAttack : public MissileFSM
{
public:
	MissileAttack(FiniteStateMachine* pOwner, std::string Name) : MissileFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

