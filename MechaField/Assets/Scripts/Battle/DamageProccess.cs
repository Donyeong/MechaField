using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class DamageProccess
{
	private BattleInfo m_battle_info;
	private DamageProccess(BattleInfo _battle_info)
	{
		m_battle_info = _battle_info;
	}

	public static DamageProccess GetDamageProccess(BattleInfo _battle_info)
	{
		return new DamageProccess(_battle_info);
	}



	public void Excute()
	{
		IHitable hit_target = m_battle_info.hit_target;
		HitInfo hit_info = hit_target.OnHit(m_battle_info.attack_info);
		AttackInfo attack_info = m_battle_info.attack_info;
		Actor attack_actor = attack_info.attackActor;
		attack_actor.actor_event.Publish(new PostAttackSuccessEvent(m_battle_info));
	}

}

