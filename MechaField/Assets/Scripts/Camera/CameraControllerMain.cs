using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraControllerMain : MonoBehaviour
{
    public CameraStateController m_stateController;
    Camera m_camera;

    void Awake()
	{
        m_stateController = new CameraStateController();
        m_stateController.buildState();
        m_camera = GetComponentInChildren<Camera>();

    }
	void Start()
    {
        m_stateController.Init(ECameraState.Idle);
    }

    // Update is called once per frame
    void Update()
    {
        m_stateController.Update();
        transform.position = m_stateController.position;
        transform.rotation = m_stateController.rotation;
    }

}
