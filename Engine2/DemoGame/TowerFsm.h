#pragma once
#include "../D2DEngine/FSMState.h"

class TowerFSM : public FSMState
{
public:
	TowerFSM(FiniteStateMachine* pOwner, std::string Name);
	~TowerFSM();
	virtual void EnterState()override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

class TowerShared : public TowerFSM //���������Դϴ�. ���� ���¸� ������Ʈ�ϱ����� ȣ��Ǿ� ���������� Ư�������� �����ϸ� ���¸� �����մϴ�. 
{
public:
	TowerShared(FiniteStateMachine* pOwner, std::string Name);
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

class TowerIdle : public TowerFSM //��� Ÿ���� ���� ���¸ӽ��� ��������������?  ���⼭ �ٸ� ��Ŀ�������� �۵��ϴ� Ÿ���������Ҽ�������?
{
public:
	TowerIdle(FiniteStateMachine* pOwner, std::string Name) : TowerFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

