using UnityEngine;



public class Player : Actor
{
	public LayerMask blockMask;
	public KeyCode jumpKey = KeyCode.Space;
	public KeyCode attackKey = KeyCode.Mouse0;
	public KeyCode interactKey = KeyCode.Mouse1;

	void Awake()
	{
		InitActor(new PlayerStateController(this));
	}


	// Start is called before the first frame update
	void Start()
	{
		stat.maxLife = 10;
		stat.life = 5;

		inventory.AddItem(4, 1);
	}

	// Update is called once per frame
	public override void UpdateActor()
    {
        if (Game.Instance.IsUILock()) return;
        base.UpdateActor();


        #region move input

        Vector3 moveDirection = Vector3.zero;
        moveDirection.x = Input.GetAxisRaw("Horizontal");
        moveDirection.z = Input.GetAxisRaw("Vertical");

        moveDirection = CameraController.cameraRotationX * moveDirection;

        stateController.CallEvent(new MoveInputEvent(moveDirection, stat.moveSpeed));

        #endregion

        #region jump input

        if (Input.GetKey(jumpKey))
        {
            stateController.CallEvent(new JumpInputEvent(stat.jumpPower));
        }
        #endregion


        if (Input.GetKeyDown(attackKey))
        {
            stateController.CallEvent(new AttackInputEvent());
        }

        HpRegen();

        //test use item
        UseItem();

    }

    private void UseItem()
    {
        if (Input.GetKeyDown(interactKey))
        {
			Item handItem = inventory.GetHandItem();
			//Game.Instance.eventBus.Publish(new GameEvent.HandInteractionItemEvent(handItem));
		}
	}

	void HpRegen()
	{
		//stat.life += Time.deltaTime * 0.1f;
	}
    public override void OnDie()
    {

    }
}
