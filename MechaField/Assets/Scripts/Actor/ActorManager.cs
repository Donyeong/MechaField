using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActorManager
{
    List<Actor> actors;

    public ActorManager()
	{
        actors = new List<Actor>(100);
    }

    public void Add(Actor actor)
	{
        actors.Add(actor);
	}

    public void Remove(Actor actor)
	{
        actors.Remove(actor);
	}
    public void Update()
    {
		foreach (var item in actors)
		{
            item.UpdateActor();
		}
    }

    
}