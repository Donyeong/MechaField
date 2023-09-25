using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(ParticleSystem))]
public class Particle : MonoBehaviour
{
    public eParticleType type;
	ParticleSystem m_particleSystem;
	public void Awake()
	{
		m_particleSystem = GetComponent<ParticleSystem>();
	}
	public void OnParticleSystemStopped()
    {
		ParticleManager.Instance.ReturnPool(this);
    }

    public void Play()
	{
		gameObject.SetActive(true);
		m_particleSystem.Play(true);
	}
}
