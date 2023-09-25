using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameCommandManager
{

    Queue<IGameCommand> gameCommandQueue;

    public T GetCommand<T>() where T : IObjectPoolable, new()
    {
        return StaticObjectPool<T>.NewObject();
    }

    public void PushCommand(IGameCommand _command)
    {
        gameCommandQueue.Enqueue(_command);
    }

    public GameCommandManager()
	{
        gameCommandQueue = new Queue<IGameCommand>(100);
    }

    public void Update()
    {
        while(gameCommandQueue.Count > 0)
		{
            IGameCommand gameCommand = gameCommandQueue.Dequeue();
            gameCommand.Excute();
            gameCommand.ReturnObjectPool();
		}
    }
}
