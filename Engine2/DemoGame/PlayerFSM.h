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
	Animation* ani; 
	Movement* move;
	Character* character;
};
//�������̰��� �������� �κ��� �������̴� �� ���ʿ��� ó���ϱ� 

class PlayerIdle : public PlayerFSM
{
public:
	PlayerIdle(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {};
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
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

