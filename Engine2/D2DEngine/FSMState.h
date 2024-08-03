#pragma once

class FiniteStateMachine;
class FSMState
{
public:
	FSMState(FiniteStateMachine* pOwner, std::string Name)
		:owner(pOwner)
		, name(Name)
	{

	}
	virtual ~FSMState()
	{

	}
	std::string name;
	FiniteStateMachine* owner;

public:
	void SetOwner(FiniteStateMachine* pOwner) { owner = pOwner; }

	const std::string& GetName() { return name; }

	virtual void EnterState() = 0;	// ���� ������ ������ ����
	virtual void Update(float DeltaTime) = 0; // ���� �϶� ��� ������ ����, ���� ���� �˻� (Check Transition Condition) �� ���� �Ѵ�.
	virtual void ExitState() = 0;	// ���� Ż�⶧ ������ ����
};
