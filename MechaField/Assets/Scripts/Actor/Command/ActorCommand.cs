using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface IActorCommand : IObjectPoolable
{
	public void Excute(Actor actor);
	public void ReturnObjectPool();
}

public class MoveCommand : IActorCommand
{

	public Vector3 velocity;

	public void Init() {
	}

	public void ReturnObjectPool()
	{
		StaticObjectPool<MoveCommand>.ReturnObject(this);
	}
	public void Excute(Actor actor)
	{
		actor.entityPhysics.AddMoveVelocity(velocity * Time.deltaTime);
		actor.actor_event.Publish(new MoveEvent(velocity * Time.deltaTime));
	}
}

public class JumpCommand : IActorCommand
{

	public float power;
	public void Init()
	{
	}
	public void ReturnObjectPool()
	{
		StaticObjectPool<JumpCommand>.ReturnObject(this);
	}
	public void Excute(Actor actor)
	{
		actor.entityPhysics.Jump(power);
	}
}

//public class BlockPlaceCommand : IActorCommand
//{
//	public Vector3 worldPosition;

//	public void Init()
//	{
//	}
//	public void ReturnObjectPool()
//	{
//		StaticObjectPool<BlockPlaceCommand>.ReturnObject(this);
//	}
//	public void Excute(Actor actor)
//	{
//		Vector3Int blockPosition =  GameMap.GetBlockPosition(worldPosition);
//		bool canPlace = GameMap.Instance.CheckCanPlace(blockPosition);
//		if (canPlace == false) return;
		
//		Item handItem = actor.inventory.GetHandItem();
//		if(handItem == null) return;
//		ItemType type = handItem.GetItemType();
//		if (type.option.canPlace == false || handItem.count == 0) return;
//		int blockId = type.id;
//		bool isPlace = GameMap.Instance.SetBlock(blockPosition, blockId);

//		if(isPlace)
//		{
//			bool success = actor.inventory.RemoveHandItem(1, false) !=0;
//			Debug.Assert(success);
//		}
		
//	}
//}

//public class BlockDestroyCommand : IActorCommand
//{
//	public Vector3 worldPosition;

//	public void Init()
//	{
//	}
//	public void ReturnObjectPool()
//	{
//		StaticObjectPool<BlockDestroyCommand>.ReturnObject(this);
//	}
//	public void Excute(Actor actor)
//	{
//		Vector3 blockPosition = GameMap.GetBlockPosition(worldPosition);
//		/*
//		Item weaponItem = actor.inventory.GetHandItem();
//		*/
//		float damage = actor.GetMIningPower();
//		int blockId = GameMap.Instance.GetBlock(blockPosition);
//		bool isDestroy = GameMap.Instance.DamageBlock(blockPosition, damage * Time.deltaTime);
		
		
//	}
//}

public class AttackCommand : IActorCommand
{
	AttackInfo attackInfo;
	public void Init()
	{
	}
	public void ReturnObjectPool()
	{
		StaticObjectPool<AttackCommand>.ReturnObject(this);
	}
	public void Excute(Actor actor)
	{

	}
}