using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public enum eCameraState
{
    GamePlay,
    CursorControll,
    Attack
}



public class CameraController : Singleton<CameraController>
{
    public static Quaternion cameraRotationX = Quaternion.identity;
    public static Quaternion cameraRotation = Quaternion.identity;
    public static float effectZoom = 0;
    public static float updateZoom = 0;
    public static float addUpdateZoom = 0f;
    public static float addUpdateZoomSpeed = 5f;
    public static eCameraState cameraState = eCameraState.GamePlay;

    [SerializeField] bool xRotatable = false;
    [SerializeField] bool yRotatable = false;

    [SerializeField] Transform targetTransform;
    [SerializeField] Vector3 offset = Vector3.zero;

    [SerializeField] float sensitivityX = 2f;
    [SerializeField] float sensitivityY = 1f;
    [SerializeField] float zoomSensitivity = 0.7f;
    [SerializeField] float zoomOutSpeed = 0.4f;
    [SerializeField] float cameraDrag = 0.85f;

    [SerializeField] float CameraSpeed = 30;
    [SerializeField] float AttackCameraSpeed = 60;

    [SerializeField] LayerMask hitMask;

    Transform childCameraTransform;

    public float rotateX = 0;
    public float rotateY = 0;


    bool mbMoving = false;
    bool mbZooming = false;
   
    float mMinEulerY = -90;
    float mMaxEulerY = 80;

    [SerializeField] float zoomOffset = 4;

    [SerializeField] float minZoom = 2;
    [SerializeField] float maxZoom = 7;
    [HideInInspector] public Vector3 centor = Vector3.zero;
    Camera mCam;

    Vector3 childCameraLocalPosition = Vector3.zero;

    Vector3 updateShakeVector = Vector3.zero;
    Vector3 shakeVector = Vector3.zero;

    public Camera Cam
    {
        get
        {
            if (mCam == null)
            {
                mCam = GetComponentInChildren<Camera>();
            }
            return mCam;
        }
    }

    
    protected override void Awake()
    {
        base.Awake();
        childCameraTransform = GetComponentInChildren<Camera>().transform;
        if (targetTransform == null)
            targetTransform = GameObject.Find("Player").transform;
    }

	private void Start()
	{
        Player player = Game.Instance.GetPlayer();
        EventBus<ActorEvent> actor_event_eb = player.actor_event;
        actor_event_eb.AddListner<PostAttackSuccessEvent>(OnPlayerAttack);
    }

    void OnPlayerAttack(PostAttackSuccessEvent _ae)
	{
        Shake(0.3f);
	}

    public Ray GetRay()
	{
        //return Cam.ViewportPointToRay(Input.mousePosition);
        return new Ray(childCameraTransform.position, cameraRotation * Vector3.forward);
    }
	// Update is called once per frame
	void Update()
    {
        UpdateCameraState();
        InputCameraMode();

        cameraRotationX = Quaternion.Euler(0, rotateX, 0);

        if (cameraState == eCameraState.GamePlay)
        {
            UpdateRotate();
            UpdateZoom();
            UpdatePosition(CameraSpeed);
        }

        if (cameraState == eCameraState.Attack)
        {
            UpdateRotate();
            UpdatePosition(AttackCameraSpeed);
        }

        SmoothZoomPositionUpdate();
        float hitDistance = CheckCameraToPlayerRay();
        
        childCameraLocalPosition.z = Mathf.Max(-hitDistance, childCameraLocalPosition.z);

        childCameraTransform.localPosition = childCameraLocalPosition;
    }


    private void FixedUpdate()
    {
        shakeVector = shakeVector * -cameraDrag;
    }

    public void Shake(Vector3 dir, float power)
    {
        shakeVector = dir.normalized * power;
    }

    public void Shake(float power)
    {
        Vector3 vec;
        vec.x = Random.Range(-1f, 1f);
        vec.y = Random.Range(-1f, 1f);
        vec.z = Random.Range(-1f, 1f);
        Shake(vec.normalized, power);
    }

    void UpdatePosition(float speed)
    {

        //centor = Vector3.Lerp(centor, targetTransform.position, speed);
        Vector3 deltaVector = targetTransform.position - centor;
        deltaVector *= speed * Time.deltaTime;
        if (deltaVector.magnitude > (targetTransform.position - centor).magnitude)
        {
            deltaVector = deltaVector.normalized * (targetTransform.position - centor).magnitude;

        }

        centor += deltaVector;

        gameObject.transform.position = centor + offset + shakeVector;
    }


    void UpdateRotate()
    {
        if(xRotatable)
            rotateX += Input.GetAxis("Mouse X") * sensitivityX;
        if (yRotatable)
            rotateY -= Input.GetAxis("Mouse Y") * sensitivityY;
        ApplyRotate();
    }

    void UpdateZoom()
    {
        if (Input.mouseScrollDelta.y != 0)
        {
            zoomOffset += Input.mouseScrollDelta.y * zoomSensitivity;
            zoomOffset = Mathf.Clamp(zoomOffset, minZoom, maxZoom);
        }
    }

    void SmoothZoomPositionUpdate()
	{
        childCameraLocalPosition.z = Mathf.Lerp(childCameraLocalPosition.z, -zoomOffset, zoomOutSpeed);
        childCameraTransform.localPosition = childCameraLocalPosition;
    }


    void ApplyRotate()
    {
        rotateX = Mathf.Repeat(rotateX, 360);
        rotateY = Mathf.Clamp(rotateY, mMinEulerY, mMaxEulerY);
        Quaternion rotation = Quaternion.Euler(rotateY, rotateX, 0);
        gameObject.transform.rotation = rotation;
        cameraRotationX = Quaternion.Euler(0, rotateX, 0);
        cameraRotation = Quaternion.Euler(rotateY, rotateX, 0);
    }

    void InputCameraMode()
    {
        if (Input.GetKeyDown(KeyCode.LeftAlt))
        {
            switch (cameraState)
            {
                case eCameraState.CursorControll:
                    {
                        cameraState = eCameraState.GamePlay;
                    }
                    break;
                case eCameraState.GamePlay:
                    {
                        cameraState = eCameraState.CursorControll;
                    }
                    break;
                case eCameraState.Attack:
                    {
                        cameraState = eCameraState.CursorControll;
                    }
                    break;
            }
        }
    }
    void UpdateCameraState()
    {
        switch (cameraState)
        {
            case eCameraState.CursorControll:
                {
                    Cursor.lockState = CursorLockMode.None;
                }
                break;
            case eCameraState.GamePlay:
                {
                    Cursor.lockState = CursorLockMode.Locked;
                }
                break;
            case eCameraState.Attack:
                {
                    Cursor.lockState = CursorLockMode.Locked;
                }
                break;
        }
    }

    float CheckCameraToPlayerRay()
	{
        float length;

        float radius = 0.3f;
        //player -> camera Ray
        Vector3 origin = (centor + offset);
        Vector3 vec_PtoC = childCameraTransform.position - origin;
        Ray ray_PtoC = new Ray(origin, vec_PtoC);

        Debug.DrawRay(origin, vec_PtoC);
        RaycastHit hitData;
        bool isHit = Physics.SphereCast(ray_PtoC, radius, out hitData, vec_PtoC.magnitude, hitMask, QueryTriggerInteraction.Ignore);

        if (isHit)
        {
            length = hitData.distance;
        } else
		{
            length = vec_PtoC.magnitude;

        }

        return length;
    }


}
