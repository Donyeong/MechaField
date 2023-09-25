using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "BattleData", menuName = "Scriptable Object/BattleData", order = 1)]
public class BattleData : ScriptableObject
{
    public LayerMask layermask_actor;
}