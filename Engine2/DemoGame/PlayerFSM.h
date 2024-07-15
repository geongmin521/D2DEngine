#pragma once
#include "../D2DEngine/FSMState.h"

class Animation;
class PlayerFSM : public FSMState
{
public:
	PlayerFSM(FiniteStateMachine* pOwner, std::string Name);
	~PlayerFSM();
	Animation* ani; //�̷��� �ص� �ڽı��� ���������� �߳Ѿ������?
};
//�������̴� ��Ը��鷯��.. ����带 ���� �ű⼭ �� ó���ϰ��ϸ�ǳ�? 

class PlayerIdle : public PlayerFSM
{
public:
	PlayerIdle(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};


class PlayerAttack : public PlayerFSM //��� Ŭ������ �ϳ��� �ִϸ��̼� �����͸� �����������ڴµ�..
	//�̷������� ��ӹ����� ���°� ���涧���� �ִϿ� ���� ������ �ϳ��� �þ.. 
{
public:
	PlayerAttack(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {}; //�θ��� ������ ȣ��
private:
	virtual void EnterState() override;	
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
}; //�ƴϸ� �ٸ������ ������?? 

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

