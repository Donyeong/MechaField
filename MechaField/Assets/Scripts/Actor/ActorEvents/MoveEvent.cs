using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveEvent : ActorEvent
{
	public Vector3 velocity;
	public MoveEvent(Vector3 velocity)
	{
		this.velocity = velocity;
	}
}