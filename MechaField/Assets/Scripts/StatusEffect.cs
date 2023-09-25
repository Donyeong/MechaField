using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum eStatusEffectType
{
	Test
}
public abstract class StatusEffect
{
	private eStatusEffectType m_type;
	private Actor m_target_actor;
	private float m_duration;
	public StatusEffect(Actor _target_actor, eStatusEffectType _type)
	{
		m_type = _type;
		m_target_actor = _target_actor;
	}

	public eStatusEffectType GetEffectType()
	{
		return m_type;
	}


	public void UpdateTime()
	{
		m_duration -= Time.deltaTime;
	}

	public abstract void OnEnter();
	public abstract void UpdateEffect();

	public abstract void OnEnd();

	public virtual bool IsEnd()
	{
		return m_duration <= 0;
	}

}

public class StatusEffectTest : StatusEffect
{
	public StatusEffectTest(Actor _target_actor) : base(_target_actor, eStatusEffectType.Test)
	{
	}
	public override void OnEnter()
	{

	}
	public override void UpdateEffect()
	{

	}

	public override void OnEnd()
	{

	}
}

