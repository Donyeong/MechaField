using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum eActorStateType
{
	Idle,
	Movement,
	GoIdle,
	Attack,
}

public interface IActorState
{
	public void OnEvent(ActorInputEvent actorEvent, ActorStateController stateController);
	public void OnEnter(ActorStateController stateController);
	public void OnExit(ActorStateController stateController);
	public void Update(ActorStateController stateController);
}

