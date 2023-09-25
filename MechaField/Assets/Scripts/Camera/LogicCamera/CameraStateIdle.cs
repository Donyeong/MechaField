using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraStateIdle : CameraState
{
	public override void OnEnter()
	{
		cameraStateController.target = GameObject.Find("Player").transform;
		return;
	}

	public override void OnExit()
	{
		return;
	}

	public override void Update()
	{
		Debug.Log("IdleUpdate");
		cameraStateController.position = cameraStateController.target.position;
		return;
	}
}
