using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class Battle
{
	public static float GetDamage(AttackInfo info)
	{
		Actor attacker = info.attackActor;
		Item weapon = attacker.inventory.GetHandItem();

		float finalDamage = 1;
		//damage = weapon.damage;

		return finalDamage;
	}
}