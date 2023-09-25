using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class PengMoveState : IActorState
{
	public void OnEvent(ActorInputEvent actorEvent, ActorStateController stateController)
	{
	}
	public void OnEnter(ActorStateController stateController)
	{
	}
	public void OnExit(ActorStateController stateController)
	{
		Actor actor = stateController.actor;
		actor.actor_event.Publish(new MoveStopEvent());
	}
	public void Update(ActorStateController stateController)
	{

	}
}