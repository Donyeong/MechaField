using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PlayerAnimationController : ActorAnimationController
{
	public void SetMove(bool isMove)
	{
		m_animator.SetBool("isMove", isMove);
	}
	public void Attack()
	{
		Debug.Log("Attack");
		m_animator.SetTrigger("tAttack");
	}
	public void SetGround(bool isGround)
	{
		m_animator.SetBool("isGround", isGround);
	}
	public void Jump()
	{
		m_animator.SetTrigger("tJump");
	}

	public void JumpDown()
	{
		m_animator.SetTrigger("tJumpDown");
	}


	void Start()
	{
		m_actor.actor_event.AddListner<MoveEvent>(OnMove);
		m_actor.actor_event.AddListner<MoveStopEvent>(OnMoveStop);
		m_actor.actor_event.AddListner<AttackEvent>(OnAttack);
	}

	private void Update()
	{
		m_animator.enabled = !Game.Instance.IsUILock();
	}

	void OnMove(MoveEvent _actorEvent)
	{
		Debug.Assert(_actorEvent != null);
		MoveEvent moveEvent = _actorEvent;
		float rotationSpeed = 0.2f;
		float lerp = 1 - Mathf.Pow(1 - rotationSpeed, Time.deltaTime * 60);
		modelTransform.rotation = Quaternion.Lerp(modelTransform.rotation, Quaternion.LookRotation(moveEvent.velocity), lerp);

		SetMove(true);
	}

	void OnMoveStop(MoveStopEvent _actorEvent)
	{
		SetMove(false);
	}
	void OnAttack(AttackEvent _actorEvent)
	{
		Attack();
	}
}
