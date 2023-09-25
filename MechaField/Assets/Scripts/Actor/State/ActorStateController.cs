using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public abstract class ActorStateController
{
	protected Dictionary<eActorStateType, IActorState> m_stateInstances = new Dictionary<eActorStateType, IActorState>();
	protected IActorState m_currentState;
	protected eActorStateType m_currentStateType;

	Actor m_actor;
	public Actor actor
	{
		get => m_actor;
	}

	public ActorStateController(Actor actor, eActorStateType state = eActorStateType.Idle)
	{
		m_actor = actor;
		m_currentStateType = state;
	}
	public void Update()
	{
		m_currentState.Update(this);
	}

	public bool ChangeState(eActorStateType state)
	{
		if (m_stateInstances.ContainsKey(state) == false)
			return false;

		var before = m_currentStateType;
		m_currentStateType = state;
		m_currentState.OnExit(this);
		m_currentState = m_stateInstances[state];
		m_currentState.OnEnter(this);

		actor.actor_event.Publish(new StateChangeEvent(before, state));

		return true;
	}

	public void CallEvent(ActorInputEvent inputEvent)
	{
		Debug.Assert(inputEvent != null);
		m_currentState.OnEvent(inputEvent, this);
	}
}
