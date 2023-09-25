using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster : Actor
{
	void Awake()
	{
		InitActor(new NPCStateController(this));
        stat.maxLife = 10;
        stat.life = 8;
        ActorHpBar.AddActorHpBar(this);
    }

	// Start is called before the first frame update
	void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }
    public override void OnDie()
    {

    }
}
