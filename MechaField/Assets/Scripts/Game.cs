using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DNNet;
using System.Threading.Tasks;
using System.Threading;
public class Game : Singleton<Game>
{
    Player _player;

    NetworkCore net_core;
	ActorManager _actorManager;
    GameCommandManager _commandManager;

    public BattleData battleData;
    public GameCommandManager commandManager
    {
        get => _commandManager;
    }
    public NetworkCore netCore
    {
        get => net_core;
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

        net_core = new NetworkCore();
        _actorManager = new ActorManager();
        _commandManager = new GameCommandManager();
    }

	private void Start()
	{
        //Game Start Logic
        // #1 Net
        RunNet();
        eventBus.AddPostAction(SendPacket_GameEvent);
    }

    void SendPacket_GameEvent(GameEvent _game_event)
    {
        ByteBuffer byte_buffer = StaticObjectPool<ByteBuffer>.NewObject();
        _game_event.Serialize(byte_buffer);

        Session game_session = netCore.GetSession(eSessionType.GameServer);
        game_session.SendDataToServer(byte_buffer.ToArray());

    }

	// Update is called once per frame
	void Update()
    {
        Physics.autoSimulation = this.IsUILock();
        _commandManager.Update();
        _actorManager.Update();
    }
    private async void RunNet()
    {
        bool result = false;

        await Task.Run(() =>
        {
            result = net_core.ConnectGameServer("127.0.0.1", 8888);
        });
        if (result)
        {
            Debug.Log("connect success");
        } else
		{
            //Debug.LogError("fail connection");
		}
    }

}
