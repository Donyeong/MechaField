using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class EntityPhysics : MonoBehaviour
{
	[SerializeField] float drag = 0.3f;
	[SerializeField] float airDrag = 0.3f;
	[SerializeField] float speed = 2f;
	public Vector3 velocity = Vector3.zero;
	public bool bGravity = true;
	public Vector3 wallNormal = Vector3.up;

	public float moveMulSpeed = 1.0f;

	public Vector3 moveDir;

	[SerializeField] float mGravity = 1f;
	CharacterController mCharController;

	public Vector3 wallForward = Vector3.forward;

	public CharacterController charController
	{
		get { return mCharController; }
	}

	public bool IsGrounded()
	{
		return mCharController.isGrounded;
	}

	void Awake()
	{
		mCharController = GetComponent<CharacterController>();
	}

	// Start is called before the first frame update
	void Start()
	{

	}

	// Update is called once per frame
	void Update()
	{
		if (Game.Instance.IsUILock()) return;
		if (IsGrounded() == false)
		{
			moveMulSpeed = 1.0f;
		}
		UpdatePosition();

		moveMulSpeed = 1.0f;
	}


	public bool AddMoveVelocity(Vector3 input)
	{
		if (IsGrounded())
		{
			velocity += input;
		}
		else
		{
			velocity += input * 1f * moveMulSpeed;
		}
		return input != Vector3.zero;

	}

	public void Move(Vector3 vec)
	{
		mCharController.Move(vec);
	}


	public void Jump(float power)
	{
		if (IsGrounded() == false)
			return;
		velocity.y = power;
	}



	void UpdatePosition()
	{
		Vector3 xzVel = Vector3.zero;
		xzVel.x = velocity.x;
		xzVel.z = velocity.z;
		Vector3 yVel = Vector3.zero;
		if (bGravity)
		{
			yVel.y = velocity.y - (mGravity * Time.deltaTime);

		}
		else
		{
			yVel.y = 0;
		}


		moveDir = xzVel * Time.deltaTime * speed;


		mCharController.Move(moveDir * moveMulSpeed);

		CollisionFlags flag = mCharController.Move(yVel * Time.deltaTime);



		if (mCharController.isGrounded == true)
		{
			yVel.y = 0f;

			float lerp = 1 - Mathf.Pow(1 - drag, Time.deltaTime * 60);
			xzVel = Vector3.Lerp(xzVel, Vector3.zero, lerp);

		}
		else
		{
			float lerp = 1 - Mathf.Pow(1 - airDrag, Time.deltaTime * 60);
			xzVel = Vector3.Lerp(xzVel, Vector3.zero, lerp);
		}



		velocity.Set(xzVel.x, yVel.y, xzVel.z);


	}
}
