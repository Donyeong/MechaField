using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public enum eParticleType
{
	Explosion
}

public class ParticleManager : Singleton<ParticleManager>
{
	GameObject[] mParticlePrefabs;
	string mResourcePath = "ParticlePrefabs/";
	/*
	public GameObject playEffect(Vector3 pos, Quaternion rot, eParticleType type, bool isNetworkSync = false)
	{
		Vector3 p = pos;
		var newObj = pool[type].NewObjectInstance();
		newObj.transform.position = p;
		newObj.transform.rotation = rot;
		var particle = newObj.GetComponent<Particle>();
		particle.type = type;
		particle.Play();

		if (isNetworkSync)
		{
			Network.instance.SendParticlePlay(type, pos, rot);
		}
		return ret;

	}
	*/
	public void playEffect(Vector3 pos, Quaternion rot, eParticleType type)
	{
		Vector3 p = pos;
		var newObj = pool[type].NewObjectInstance();

		newObj.transform.position = p;
		newObj.transform.rotation = rot;
		var particle = newObj.GetComponent<Particle>();
		particle.type = type;
		particle.Play();
	}

	public void ReturnPool(Particle particle)
	{
		var type = particle.type;
		pool[type].ReturnObjectInstance(particle.gameObject);
		particle.gameObject.transform.SetParent(transform);
		particle.gameObject.SetActive(false);
	}

	protected override void Awake()
	{
		base.Awake();
		LoadParticleResources();
	}

	Dictionary<eParticleType, GameObjectPool> pool = new Dictionary<eParticleType, GameObjectPool>();

	void LoadParticleResources()
	{
		string[] particleResourcesNames = Enum.GetNames(typeof(eParticleType));
		mParticlePrefabs = new GameObject[particleResourcesNames.Length];

		for (int i = 0; i < particleResourcesNames.Length; i++)
		{
			string path = mResourcePath + particleResourcesNames[i];
			mParticlePrefabs[i] = Resources.Load(path, typeof(GameObject)) as GameObject;

			Debug.Assert(mParticlePrefabs[i] != null, $"Not found Particle Resource, path[{path}]");

			pool.Add((eParticleType)i, new GameObjectPool(mParticlePrefabs[i], transform));
		}
	}
}
