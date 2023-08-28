using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IdleState : CommonActorState, IActorState
{
	public void OnEvent(ActorInputEvent _actor_event, ActorStateController _state_controller)
	{
		CommonEventHandle(_actor_event, _state_controller);
		switch (_actor_event.eventType)
		{
			case ActorInputEvent.eEventType.Move:
				{
					OnMove((MoveInputEvent)_actor_event, _state_controller);
					break;
				}
			case ActorInputEvent.eEventType.Jump:
				{
					OnJump((JumpInputEvent)_actor_event, _state_controller);
					break;
				}
			case ActorInputEvent.eEventType.Attack:
				{
					OnAttack((AttackInputEvent)_actor_event, _state_controller);
					break;
				}
		}
	}
	public void OnEnter(ActorStateController stateController)
	{

	}
	public void OnExit(ActorStateController stateController)
	{

	}
	public void Update(ActorStateController stateController)
	{
	}
	void OnMove(MoveInputEvent moveEvent, ActorStateController stateController)
	{
		if (moveEvent.direction == Vector3.zero)
			return;
		stateController.ChangeState(eActorStateType.Movement);
		stateController.CallEvent(moveEvent);
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

