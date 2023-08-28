using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActorHpBar : MonoBehaviour
{
	private Actor m_target_actor;
	[SerializeField]
	private Transform holder;
	[SerializeField]
	private DNImage hp_bar_front;
	[SerializeField]
	private DNImage hp_bar_back;

	public void Start()
	{

	}
	public void Update()
	{
	}
	public void Init(Actor _actor)
	{
		Debug.Assert(null != _actor);
		m_target_actor = _actor;
		m_target_actor.actor_event.AddListner<StatUpdateEvent>(OnStatUpdate);
	}
	

	public void OnStatUpdate(StatUpdateEvent _actor_event)
	{
		float cur_life = _actor_event.actorStat.life;
		float max_life = _actor_event.actorStat.maxLife;
		if (0 == max_life)
		{
			max_life = 1;
		}
		hp_bar_front.fillAmount = cur_life / max_life;
		Debug.Log(hp_bar_front.fillAmount);
	}

	public static ActorHpBar AddActorHpBar(Actor _actor)
	{
		Debug.Assert(null != _actor);
		GameObject prefab = Resources.Load("ActorHpBar") as GameObject;
		GameObject instance = Instantiate(prefab, _actor.transform);
		ActorHpBar actor_hp_bar = instance.GetComponent<ActorHpBar>();
		Debug.Assert(null != actor_hp_bar);
		actor_hp_bar.Init(_actor);
		return actor_hp_bar;
	}
}
