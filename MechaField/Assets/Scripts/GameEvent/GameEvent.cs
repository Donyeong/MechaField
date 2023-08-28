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
public abstract class GameEvent
{
    public GameEvent()
    {
    }
}