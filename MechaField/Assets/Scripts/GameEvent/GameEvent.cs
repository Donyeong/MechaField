using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class HandInteractionItemEvent
{
    public Item hand;
    public HandInteractionItemEvent(Item hand)
    {
        this.hand = hand;
    }
}

public class CreateActorEvent : GameEvent
{
    public CreateActorEvent()
    {
    }
    public override void Serialize(ByteBuffer _serializer)
	{

	}
    public override void Deserialize(ByteBuffer _serializer)
	{
        
	}
}
public class TestGameEvent : GameEvent
{
    public int test_value;
    public TestGameEvent()
    {
        test_value = 111;
    }
    public override void Serialize(ByteBuffer _serializer)
    {
        _serializer.WriteInteger(test_value);
    }
    public override void Deserialize(ByteBuffer _serializer)
    {
        test_value = _serializer.ReadInteger();
    }
}


public abstract class GameEvent : ISerializable
{
    public GameEvent()
    {
    }
    public abstract void Serialize(ByteBuffer _serializer);
    public abstract void Deserialize(ByteBuffer _serializer);
}