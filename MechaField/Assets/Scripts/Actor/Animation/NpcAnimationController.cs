using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class NpcAnimationController : ActorAnimationController
{
	public void SetMove(float move)
	{
		m_animator.SetInteger("Walk", move > 0 ? 1 : 0);
	}
	public void Jump()
	{
		m_animator.SetTrigger("jump");
	}


	void Start()
	{
		m_actor.actor_event.AddListner<MoveEvent>(OnMove);
		m_actor.actor_event.AddListner<MoveStopEvent>(OnMoveStop);
	}

	private void Update()
	{
		m_animator.enabled = !Game.Instance.IsUILock();
	}

	void OnMove(MoveEvent _moveEvent)
	{
		float rotationSpeed = 0.2f;
		float lerp = 1 - Mathf.Pow(1 - rotationSpeed, Time.deltaTime * 60);
		modelTransform.rotation = Quaternion.Lerp(modelTransform.rotation, Quaternion.LookRotation(_moveEvent.velocity), lerp);

		SetMove(_moveEvent.velocity.magnitude);
	}

	void OnMoveStop(MoveStopEvent _moveStopEvent)
	{
		SetMove(0);
	}
}
