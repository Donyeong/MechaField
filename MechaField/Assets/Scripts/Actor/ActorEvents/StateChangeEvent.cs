using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class StateChangeEvent : ActorEvent
{
	public eActorStateType before;
	public eActorStateType after;
	public StateChangeEvent(eActorStateType before, eActorStateType after)
	{
		this.before = before;
		this.after = after;
	}
}