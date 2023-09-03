using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class NetworkUI : MonoBehaviour
{
    [SerializeField] TextMeshProUGUI network_state;
    Queue<string> update_queue = new Queue<string>();
    // Start is called before the first frame update
    void Start()
    {
        Game.Instance.netCore.eventBus.AddListner<NetworkConnect>(OnConnect);
        Game.Instance.netCore.eventBus.AddListner<NetworkDisconnect>(OnDisconnect);
    }
	private void Update()
    {
        while(update_queue.Count > 0)
        {
            network_state.SetText(update_queue.Dequeue());
        }
	}
	void OnConnect(NetworkConnect _e)
	{
        update_queue.Enqueue("server connected");
    }
    void OnDisconnect(NetworkDisconnect _e)
    {
        update_queue.Enqueue("server disconnect");
    }
}
