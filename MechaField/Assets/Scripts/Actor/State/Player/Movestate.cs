using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class MoveState : IActorState
{

	public void OnEvent(ActorInputEvent actorEvent, ActorStateController stateController)
	{
		switch (actorEvent.eventType)
		{
			case ActorInputEvent.eEventType.Move:
				{
					OnMove((MoveInputEvent)actorEvent, stateController);
					break;
				}
			case ActorInputEvent.eEventType.Jump:
				{
					OnJump((JumpInputEvent)actorEvent, stateController);
					break;
				}
			case ActorInputEvent.eEventType.Attack:
				{
					OnAttack((AttackInputEvent)actorEvent, stateController);
					break;
				}
		}
	}
	public void OnEnter(ActorStateController stateController)
	{
	}
	public void OnExit(ActorStateController stateController)
	{
		Actor actor = stateController.actor;
		actor.actor_event.Publish( new MoveStopEvent());
	}
	public void Update(ActorStateController stateController)
	{
	}

	void OnMove(MoveInputEvent moveEvent, ActorStateController stateController)
	{
		Actor actor = stateController.actor;
		Vector3 velocity = moveEvent.direction.normalized * moveEvent.speed;

		if (velocity == Vector3.zero)
		{
			stateController.ChangeState(eActorStateType.Idle);
		}
		else
		{
			var moveCommand = StaticObjectPool<MoveCommand>.NewObject();
			moveCommand.velocity = velocity;
			actor.AddCommand(moveCommand);
		}
	}
	void OnJump(JumpInputEvent jumpEvent, ActorStateController stateController)
	{
		Actor actor = stateController.actor;
		var jump = StaticObjectPool<JumpCommand>.NewObject();
		jump.power = jumpEvent.power;
		actor.AddCommand(jump);
	}

	void OnAttack(AttackInputEvent attackEvent, ActorStateController stateController)
	{
		Actor actor = stateController.actor;
		actor.actor_event.Publish(new AttackEvent());
	}
}