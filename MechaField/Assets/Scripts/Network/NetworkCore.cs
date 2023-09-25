using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace DNNet { 
	public enum eNetworkState
	{
		Disconnect = 0,
		Connect = 1
	}
	public enum eSessionType
	{
		GameServer
	}
	public class NetworkCore
	{
		public Dictionary<eSessionType ,Session> m_session;
		public EventBus<NetworkEvent> eventBus = new EventBus<NetworkEvent>();

		public NetworkCore()
		{
			m_session = new Dictionary<eSessionType, Session>();
			m_session.Add(eSessionType.GameServer, new Session());
		}

		public Session GetSession(eSessionType _session_type)
		{
			return m_session[_session_type];
		}

		public bool ConnectGameServer(string _ip, int _port)
		{
			NetworkResult result = GetSession(eSessionType.GameServer).ConnectGameServer(_ip, _port);
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