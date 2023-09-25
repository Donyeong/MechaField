using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class NetworkConnect : NetworkEvent
{
    public NetworkConnect()
    {
    }
}
public class NetworkDisconnect : NetworkEvent
{
    public NetworkDisconnect()
    {
    }
}
public abstract class NetworkEvent
{
    public NetworkEvent()
    {
    }
}