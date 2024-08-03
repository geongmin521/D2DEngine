#include "pch.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"

FiniteStateMachine::~FiniteStateMachine()
{
	for (auto& state : states)
	{
		delete state.second;
	}
	states.clear();
}

void FiniteStateMachine::Update(float DeltaTime)
{
	if (currState != nextState) //���¸� �ٲ��ָ� �ڵ����� �˾Ƽ� ����
	{
		if (currState != nullptr)
		{
			currState->ExitState();
		}
		currState = nextState;
		currState->EnterState();
	}
	else
	{
		sharedTransition->Update(DeltaTime);//�������� ���� ������
		currState->Update(DeltaTime);
	}
}

void FiniteStateMachine::SetNextState(std::string stateName)
{
	auto it = states.find(stateName);
	if (it != states.end() && it->second != currState) //������¿� �����ʾƾ���
	{
		nextState = it->second;
	}
}

void FiniteStateMachine::SetSharedTransition(FSMState* share)
{
	sharedTransition = share;
}

