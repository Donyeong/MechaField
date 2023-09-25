using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PostAttackSuccessEvent : ActorEvent
{
	public BattleInfo battle_info;
	public PostAttackSuccessEvent(BattleInfo _battle_info)
	{
		battle_info = _battle_info;	
	}
}