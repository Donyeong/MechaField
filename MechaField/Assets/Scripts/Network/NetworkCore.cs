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
			}
			return result.is_success;
		}
	}
}