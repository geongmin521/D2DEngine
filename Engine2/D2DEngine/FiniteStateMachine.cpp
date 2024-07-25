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
	if (m_pCurrState != m_pNextState) //상태만 바꿔주면 자동으로 알아서 해줌
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
		m_pSharedTransition->Update(DeltaTime);//공유전이 먼저 돌리기
		m_pCurrState->Update(DeltaTime);
	}
}

void FiniteStateMachine::SetNextState(std::string stateName)
{
	auto it = m_pStates.find(stateName);
	if (it != m_pStates.end() && it->second != m_pCurrState) //현재상태와 같지않아야함
	{
		m_pNextState = it->second;
	}
}

void FiniteStateMachine::SetSharedTransition(FSMState* share)
{
	m_pSharedTransition = share;
}

