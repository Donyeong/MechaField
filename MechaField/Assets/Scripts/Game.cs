using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Game : Singleton<Game>
{
    Player _player;

	ActorManager _actorManager;
    GameCommandManager _commandManager;

    public BattleData battleData;
    public GameCommandManager commandManager
    {
        get => _commandManager;
    }

    public EventBus<GameEvent> eventBus = new EventBus<GameEvent>();
    public Player GetPlayer()
	{
        return _player;

    }

    public bool IsUILock()
	{
        return false;
	}

    // Start is called before the first frame update
    void Awake()
    {
        _player = GameObject.Find("Player").GetComponent<Player>();


        _actorManager = new ActorManager();
        _commandManager = new GameCommandManager();
    }

    // Update is called once per frame
    void Update()
    {
        Physics.autoSimulation = this.IsUILock();
        _commandManager.Update();
        _actorManager.Update();
    }
    
}
