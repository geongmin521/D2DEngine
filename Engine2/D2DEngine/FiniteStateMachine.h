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
		m_pStates.insert(std::make_pair(pState->GetName(), pState));
	}


protected:
	FSMState* m_pCurrState = nullptr;  // ���� ����	
	FSMState* m_pNextState = nullptr;	// ���� ����
	//���̰����� ���⶧���� �̰� �ϳ�������
	FSMState* m_pSharedTransition = nullptr;	// ��������

	std::map<std::string, FSMState*> m_pStates;	// ������ FSMState���� �����ϴ� �����̳�

	virtual void Update(float DeltaTime);
};

