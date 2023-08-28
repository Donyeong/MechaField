using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class StatUpdateEvent : ActorEvent
{
	enum eStatEventType
	{
		hp,
		maxHp,
	}
	public ActorStat actorStat;
	public StatUpdateEvent(ActorStat actorStat)
	{
		this.actorStat = actorStat;
	}
}