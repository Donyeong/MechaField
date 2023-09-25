using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum ECameraState
{
	Idle
}
public class CameraStateController : StateController
{
	public Vector3 position;
	public Quaternion rotation;
	public Transform target;
	public float fov;

    public void buildState()
	{
	}

	public CameraState getState(ECameraState _state)
	{
		return null;
	}
	
	public void Init(ECameraState _default_state)
	{
	}
}
