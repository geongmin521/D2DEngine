#pragma once

class FiniteStateMachine;
class FSMState
{
public:
	FSMState(FiniteStateMachine* pOwner, std::string Name)
		:m_pOwner(pOwner)
		, m_Name(Name)
	{

	}
	virtual ~FSMState()
	{

	}
	std::string m_Name;
	FiniteStateMachine* m_pOwner;

public:
	void SetOwner(FiniteStateMachine* pOwner) { m_pOwner = pOwner; }

	const std::string& GetName() { return m_Name; }

	virtual void EnterState() = 0;	// 상태 진입전 실행할 내용
	virtual void Update(float DeltaTime) = 0; // 상태 일때 계속 실행할 내용, 전이 조건 검사 (Check Transition Condition) 도 같이 한다.
	virtual void ExitState() = 0;	// 상태 탈출때 실행할 내용
};

//하나로 관리할수있지만 세부구현은 직접 만들어야하지? 순수가상이니까. 