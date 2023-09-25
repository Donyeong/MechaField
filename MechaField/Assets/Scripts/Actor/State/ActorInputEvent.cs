using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class ActorInputEvent
{
	public enum eEventType
	{
		Attack,
		Move,
		Jump,
		Hit,
		MiningStart,
		MiningEnd,
	}

	eEventType m_eventType;
	public eEventType eventType
	{
		get => m_eventType;
	}

	public ActorInputEvent(eEventType type)
	{
		m_eventType = type;
	}
}
public class MoveInputEvent : ActorInputEvent
{
	public Vector3 direction;
	public float speed;

	public MoveInputEvent(Vector3 direction, float speed) : base(eEventType.Move)
	{
		this.direction = direction;
		this.speed = speed;
	}
}

public class JumpInputEvent : ActorInputEvent
{
	public float power;

	public JumpInputEvent(float power) : base(eEventType.Jump)
	{
		this.power = power;
	}
}


public class AttackInputEvent : ActorInputEvent
{

	public AttackInputEvent() : base(eEventType.Attack)
	{
	}
}
