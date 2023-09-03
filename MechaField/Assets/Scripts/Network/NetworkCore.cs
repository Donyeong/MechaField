using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace DNNet { 
	public enum eNetworkState
	{
		Disconnect = 0,
		Connect = 1
}
	public class NetworkCore
	{
		Session m_session;
		public EventBus<NetworkEvent> eventBus = new EventBus<NetworkEvent>();

		public NetworkCore()
		{
			m_session = new Session();
		}

		public bool Connect(string _ip, int _port)
		{
			NetworkResult result = m_session.ConnectGameServer(_ip, _port);
			if(!result.is_success)
			{
				Debug.LogError($"error code {result.error_code}");
				eventBus.Publish<NetworkDisconnect>(new NetworkDisconnect());
			} else
			{
				eventBus.Publish<NetworkConnect>(new NetworkConnect());
			}
			return result.is_success;
		}
	}
}