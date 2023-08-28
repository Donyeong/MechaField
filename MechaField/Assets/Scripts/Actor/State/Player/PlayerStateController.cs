using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStateController : ActorStateController
{

	public PlayerStateController(Player pc) : base(pc)
	{
		m_stateInstances.Add(eActorStateType.Idle, new IdleState());
		m_stateInstances.Add(eActorStateType.Movement, new MoveState());
		m_currentState = m_stateInstances[eActorStateType.Idle];
		m_currentState.OnEnter(this);
	}
}