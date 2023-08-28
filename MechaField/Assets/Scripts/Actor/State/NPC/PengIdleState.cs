using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PengIdleState : IActorState
{
	public void OnEvent(ActorInputEvent actorEvent, ActorStateController stateController)
	{
	}
	public void OnEnter(ActorStateController stateController)
	{

	}
	public void OnExit(ActorStateController stateController)
	{

	}
	public void Update(ActorStateController stateController)
	{
		float range = 10f;
		Actor actor = stateController.actor;
		Actor player = Game.Instance.GetPlayer();

		Vector3 toPlayerVec = player.transform.position - actor.transform.position;

		if (toPlayerVec.magnitude < range)
		{
			stateController.ChangeState(eActorStateType.Movement);
		}
	}
}

