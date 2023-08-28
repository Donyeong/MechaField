using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventBus<B>
{
    Dictionary<Type, List<Delegate>> dic;
    public EventBus()
    {
        dic = new Dictionary<Type, List<Delegate>>();
    }

    public void AddListner<T>(Action<T> action) where T : B
    {
        Debug.Log($" AddListner {action.GetType().Name}");
        if (!dic.ContainsKey(typeof(T)))
        {
            dic.Add(typeof(T), new List<Delegate>());
            dic[typeof(T)].Add(action as Delegate);
        }
        else
        {
            dic[typeof(T)].Add(action as Delegate);
        }
    }


    public void RemoveListner<T>(Action<T> action) where T : B
    {
        Debug.Log($" RemoveListner {action.GetType().Name}");
        dic[typeof(T)].Remove(action);
    }
    public void Publish<T>(T ev) where T : B
    {
        Debug.Log($" Publish {ev.GetType().Name}");
        if(!dic.ContainsKey(typeof(T)))
		{
            return;
		}
        foreach (var i in dic[typeof(T)])
        {
            (i as Action<T>).Invoke(ev);
        }
    }
}