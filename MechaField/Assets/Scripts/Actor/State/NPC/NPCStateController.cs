using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NPCStateController : ActorStateController
{

	public NPCStateController(Actor pc) : base(pc)
	{
		m_stateInstances.Add(eActorStateType.Idle, new PengIdleState());
		m_stateInstances.Add(eActorStateType.Movement, new PengMoveState());
		m_currentState = m_stateInstances[eActorStateType.Idle];
		m_currentState.OnEnter(this);
	}
}