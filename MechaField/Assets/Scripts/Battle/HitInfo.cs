public enum eHitType
{
	Normal,
}

public struct HitInfo
{
	public bool is_damaged;
	public float final_damage;
	public bool target_die;
	public IHitable hit_target;
}
