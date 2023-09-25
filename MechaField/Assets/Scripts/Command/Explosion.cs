using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExplosionCommand : IGameCommand
{
	public float range;
	public float damage;
	public Vector3 position;
	public ExplosionCommand()
	{
	}

	public void Excute()
	{
	}

	public void Init()
	{
		this.damage = 0;
		this.range = 0;
		this.position = Vector3.zero;
	}

	public void Init(float range, Vector3 position, float damage)
	{
		this.damage = damage;
		this.range = range;
		this.position = position;
	}

	public void ReturnObjectPool()
	{
	}
}
