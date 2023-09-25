using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class StateController
{
    IState m_currenState;

    public IState getCurrentState()
	{
		return m_currenState;
	}

	public bool changeState(IState _state)
	{
		if (m_currenState == _state)
		{
			return false;
		}
		m_currenState.OnExit();
		m_currenState = _state;
		_state.OnEnter();

		return true;
	}


	public void Init(IState _state)
	{
		m_currenState = _state;
		m_currenState.OnEnter();
	}

	public void Update()
	{
		m_currenState.Update();
	}

}
