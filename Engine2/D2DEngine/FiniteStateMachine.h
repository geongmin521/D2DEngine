#pragma once
#include "Component.h"

class FSMState;
class FiniteStateMachine :
    public Component
{
public:
	FiniteStateMachine() = default;
	virtual ~FiniteStateMachine();
	void SetNextState(std::string stateName); 
	void SetSharedTransition(FSMState* share);

	template<typename T>
	void CreateState(const std::string StateName)
	{
		T* pState = new T(this, StateName);
		states.insert(std::make_pair(pState->GetName(), pState));
	}


protected:
	FSMState* currState = nullptr;  // ���� ����	
	FSMState* nextState = nullptr;	// ���� ����
	//���̰����� ���⶧���� �̰� �ϳ�������
	FSMState* sharedTransition = nullptr;	// ��������

	std::map<std::string, FSMState*> states;	// ������ FSMState���� �����ϴ� �����̳�

	virtual void Update(float DeltaTime);
};

