using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Singleton<T> : MonoBehaviour where T : Component
{
    protected static T instance;

    public bool IsDontDestroy = false;

    public static T Instance
    {
        get
        {
            if (instance == null)
            {

                instance = FindObjectOfType<T>();
                if (instance == null)
                {
                    Debug.LogError($"not found {typeof(T).ToString()} by scene");
                    Debug.Break();
                }

            }

            return instance;
        }
    }

    protected virtual void Awake()
    {
        if (instance == null)
        {
            instance = this as T;

            if (IsDontDestroy)
                DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    protected virtual void OnDestroy()
    {
        instance = null;
    }
}