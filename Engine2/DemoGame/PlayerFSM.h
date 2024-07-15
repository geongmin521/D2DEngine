#pragma once
#include "../D2DEngine/FSMState.h"

class Animation;
class PlayerFSM : public FSMState
{
public:
	PlayerFSM(FiniteStateMachine* pOwner, std::string Name);
	~PlayerFSM();
	Animation* ani; //이렇게 해도 자식까지 순수가상이 잘넘어오겠지?
};
//공유전이는 어떻게만들러나.. 쉐어드를 만들어서 거기서 걍 처리하게하면되나? 

class PlayerIdle : public PlayerFSM
{
public:
	PlayerIdle(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};


class PlayerAttack : public PlayerFSM //모든 클래스가 하나의 애니메이션 포인터를 가졌으면좋겠는데..
	//이런식으로 상속받으면 상태가 생길때마다 애니에 대한 참조가 하나씩 늘어남.. 
{
public:
	PlayerAttack(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name) {}; //부모의 생성자 호출
private:
	virtual void EnterState() override;	
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
}; //아니면 다른방법이 있을까?? 

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

