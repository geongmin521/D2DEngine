#include "pch.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"

FiniteStateMachine::~FiniteStateMachine()
{
	for (auto& state : m_pStates)
	{
		delete state.second;
	}
	m_pStates.clear();
}

void FiniteStateMachine::Update(float DeltaTime)
{
	if (m_pCurrState != m_pNextState) //���¸� �ٲ��ָ� �ڵ����� �˾Ƽ� ����
	{
		if (m_pCurrState != nullptr)
		{
			m_pCurrState->ExitState();
		}
		m_pCurrState = m_pNextState;
		m_pCurrState->EnterState();
	}
	else
	{
		m_pSharedTransition->Update(DeltaTime);//�������� ���� ������
		m_pCurrState->Update(DeltaTime);
	}
}

void FiniteStateMachine::SetNextState(std::string stateName)
{
	auto it = m_pStates.find(stateName);
	if (it != m_pStates.end() && it->second != m_pCurrState) //������¿� �����ʾƾ���
	{
		m_pNextState = it->second;
	}
}

void FiniteStateMachine::SetSharedTransition(FSMState* share)
{
	m_pSharedTransition = share;
}

