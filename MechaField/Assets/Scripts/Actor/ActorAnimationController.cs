using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Actor))]
public class ActorAnimationController : MonoBehaviour
{
	public Transform modelTransform;
	protected Animator m_animator;
	protected Actor m_actor;

	protected virtual void Awake()
	{
		m_actor = GetComponent<Actor>();
		m_animator = GetComponentInChildren<Animator>();
		Debug.Assert(m_actor);
		Debug.Assert(m_animator);
	}
}