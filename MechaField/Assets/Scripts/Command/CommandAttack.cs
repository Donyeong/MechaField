using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CommandAttack : IGameCommand
{
	public AttackInfo attack_info;
	public Quaternion rotation;
	public Vector3 size;
	public Vector3 position;
	public CommandAttack()
	{
	}

	public void Excute()
	{
		BattleData battle_data = Game.Instance.battleData;
		LayerMask layer_hit_target = battle_data.layermask_actor;
		Collider[] hits = Physics.OverlapBox(this.position, this.size, this.rotation, layer_hit_target);

		foreach(Collider hit in hits)
		{
			IHitable hit_target = hit.GetComponent<IHitable>();
			BattleInfo battle_info;
			battle_info.attack_info = attack_info;
			battle_info.hit_target = hit_target;
			DamageProccess damageProccess = DamageProccess.GetDamageProccess(battle_info);
			damageProccess.Excute();
		}
	}

	public void Init()
	{

	}
	public void Init(
		Vector3 _direction,
		Vector3 _size,
		Vector3 _position,
		AttackInfo _attackInfo)
	{
		this.size = _size;
		this.position = _position;
		this.rotation = DNMath.VectorToQuaternion(_direction);
		this.attack_info = _attackInfo;

	}

	public void ReturnObjectPool()
	{

	}
}
