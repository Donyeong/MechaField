using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Peng92 : Actor
{
    void Awake()
    {
        InitActor(new NPCStateController(this));
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    public override void UpdateActor()
    {

    }

    public override void OnDie()
	{

	}
}
