#pragma once
#include "../D2DEngine/FSMState.h"

class Animation;
class Movement;
class Character;
class PlayerFSM : public FSMState
{
public:
	PlayerFSM(FiniteStateMachine* pOwner, std::string Name);
	~PlayerFSM();
	//공유전이를 이 위쪽에서 처리하면될거같은데?
	virtual void EnterState()override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
	Animation* ani; 
	Movement* move;
	Character* character;
};


class PlayerIdle : public PlayerFSM
{
public:
	PlayerIdle(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

class PlayerShared : public PlayerFSM
{
public:
	PlayerShared(FiniteStateMachine* pOwner, std::string Name);
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

class PlayerHanging : public PlayerFSM
{
public:
	float SwingSpeed = 50;
	float Distance = 300;
	float timer = 0;
	//float SwingTimer = 300;
	PlayerHanging(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};


class PlayerAttack : public PlayerFSM 
{
public:
	PlayerAttack(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {}; 
private:
	virtual void EnterState() override;	
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
}; 

class PlayerHit : public PlayerFSM
{
public:
	PlayerHit(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

class PlayerRun : public PlayerFSM
{
public:
	PlayerRun(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

class PlayerDie : public PlayerFSM
{
public:
	PlayerDie(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

class PlayerJump : public PlayerFSM
{
public:
	PlayerJump(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {};
private:
	bool doublejump;
	float doublejumpTimer; //최소 더블점프 가능한 시간
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

