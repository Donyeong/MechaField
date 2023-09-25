using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimationEventHandler : MonoBehaviour
{
	public  Player player;
	private void OnHit()
	{
		GameCommandManager gcm = Game.Instance.commandManager;
		AttackInfo attackInfo = new AttackInfo(); //TODO : 오브젝트 풀링
		attackInfo.attackActor = player;
		attackInfo.attackType = eAttackType.Normal;

		CommandAttack commandAttack = gcm.GetCommand<CommandAttack>();
		commandAttack.Init(
			Vector3.forward,
			Vector3.one,
			player.gameObject.transform.position,
			attackInfo
			);
		gcm.PushCommand(commandAttack);
	}
}
