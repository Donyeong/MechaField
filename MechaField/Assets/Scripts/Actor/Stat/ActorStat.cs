using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

[Serializable]
public class ActorStat
{

	float m_life;
	float m_maxLife;
	public float jumpPower;
	public float moveSpeed;
	public float viewRange;

	Actor m_actor;
	List<StatusEffect> m_statusEffects;

	public ActorStat(Actor actor)
	{
		Init(actor);
	}

	public void Init(Actor actor)
	{
		m_actor = actor;
		m_statusEffects = new List<StatusEffect>();
	}

	public float maxLife
	{
		set
		{
			m_maxLife = value;
			m_actor.actor_event.Publish(new StatUpdateEvent(this));
		}
		get
		{
			return m_maxLife;
		}
	}
	public float life
	{
		set
		{
			SetHp(value);
		}
		get
		{
			return m_life;
		}
	}
	public void SetHp(float amount, bool isClamp = true)
	{
		m_life = amount;

		if(isClamp)
		{
			m_life = Mathf.Clamp(m_life, 0, m_maxLife);
		}
		m_actor.actor_event.Publish(new StatUpdateEvent(this));
	}

}
