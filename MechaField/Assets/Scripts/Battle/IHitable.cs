using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface IHitable
{
    public HitInfo OnHit(AttackInfo _attackInfo);
}
