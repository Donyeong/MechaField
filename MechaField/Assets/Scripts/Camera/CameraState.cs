using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class CameraState : IState
{
	CameraStateController m_cameraStateCntroller;
	public CameraState setController(CameraStateController _stateController)
	{
		m_cameraStateCntroller = _stateController;
		return this;
	}
	
	public CameraStateController cameraStateController
	{
		get { return m_cameraStateCntroller; }
	}


	public abstract void OnEnter();
	public abstract void Update();
	public abstract void OnExit();

}
