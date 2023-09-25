using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[RequireComponent(typeof(EntityPhysics))]
public abstract class Actor : MonoBehaviour, IHitable
{
	private const int INVENTORY_DEFAULT_SIZE = 16;

	[SerializeField] private ActorStat m_stat;
	private Inventory m_inventory;

	private EventBus<ActorEvent> m_actor_event;
	private ActorStateController m_stateController;
	private EntityPhysics m_entityPhysics;
	private Dictionary<eStatusEffectType, List<StatusEffect>> m_status_effects;
	private Queue<StatusEffect> m_queue_status_effect_delete = new Queue<StatusEffect>();

	private Queue<IActorCommand> m_commandQueue;

	public ActorStateController stateController
	{
		get => m_stateController;
	}
	public EntityPhysics entityPhysics
	{
		get => m_entityPhysics;
	}

	public EventBus<ActorEvent> actor_event
	{
		get => m_actor_event;
	}

	public ActorStat stat
	{
		get => m_stat;
	}

	public Inventory inventory
	{
		get => m_inventory;
	}

	public void Damage(AttackInfo attackInfo)
	{
		float damage = Battle.GetDamage(attackInfo);
		stat.life -= damage;
	}

	//public abstract void OnHit();
	public HitInfo OnHit(AttackInfo attackInfo)
	{
		float damage = Battle.GetDamage(attackInfo);
		stat.life -= damage;
		Debug.Log($"Hit Attacker{attackInfo.attackActor.gameObject.name} HitTarget{gameObject.name}");

		if(stat.life <= 0)
		{
			OnDie();
		}

		HitInfo ret;
		ret.final_damage = damage;
		ret.hit_target = this;
		ret.is_damaged = true;
		ret.target_die = false;
		return ret;
	}

	public abstract void OnDie();

	public void DestroyActor()
	{
		Destroy(this);
	}

	public void InitActor(ActorStateController actorStateController)
	{
		if (m_stat == null) m_stat = new ActorStat(this);
		m_stat.Init(this);
		m_inventory = new Inventory(INVENTORY_DEFAULT_SIZE);
		m_status_effects = new Dictionary<eStatusEffectType, List<StatusEffect>>();
		m_commandQueue = new Queue<IActorCommand>();
		m_actor_event = new EventBus<ActorEvent>();
		m_stateController = actorStateController;
		m_entityPhysics = GetComponent<EntityPhysics>();
		
	}

	public void AddCommand(IActorCommand command)
	{
		m_commandQueue.Enqueue(command);
	}

	public void AddStatusEffect(StatusEffect _status_effect)
	{
		eStatusEffectType effect_type = _status_effect.GetEffectType();
		GetStatusEffects_ByType(effect_type).Add(_status_effect);
		_status_effect.OnEnter();
	}

	public List<StatusEffect> GetStatusEffects_ByType(eStatusEffectType _type)
	{
		if(!m_status_effects.ContainsKey(_type))
		{
			List<StatusEffect> list_status_effect = new List<StatusEffect>();
			m_status_effects.Add(_type, list_status_effect);
		}
		return m_status_effects[_type];
	}

	public void RemoveStatusEffect(StatusEffect _status_effect)
	{
		m_queue_status_effect_delete.Enqueue(_status_effect);
	}
	private void Update()
	{
		UpdateActor();
	}

	public virtual void UpdateActor()
	{
		if (Game.Instance.IsUILock()) return;
		stateController.Update();
		UpdateStatusEffects();
		ExcuteCommandQueue();
	}
	private void UpdateStatusEffects()
	{
		foreach(var pair_status_effect in m_status_effects)
		{
			List<StatusEffect> list_status_effect = pair_status_effect.Value;
			foreach (StatusEffect status_effect in list_status_effect)
			{
				status_effect.UpdateEffect();
				status_effect.UpdateTime();
				if (status_effect.IsEnd())
				{
					m_queue_status_effect_delete.Enqueue(status_effect);
				}
			}
		}
		while (m_queue_status_effect_delete.Count > 0)
		{
			StatusEffect status_effect = m_queue_status_effect_delete.Dequeue();
			status_effect.OnEnd();
			eStatusEffectType effect_type = status_effect.GetEffectType();
			List<StatusEffect> list_status_effect = GetStatusEffects_ByType(effect_type);
			list_status_effect.Remove(status_effect);
		}
	}
	private void ExcuteCommandQueue()
	{
		while(m_commandQueue.Count > 0)
		{
			var command = m_commandQueue.Dequeue();
			command.Excute(this);
			command.ReturnObjectPool();
		}
	}
}