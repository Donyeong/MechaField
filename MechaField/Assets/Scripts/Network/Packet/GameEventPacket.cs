using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DNNet
{
	public class GameEventPacket : ClientPacketBase
	{
		GameEvent game_event;
		
		public GameEventPacket(GameEvent _game_event)
		{
			this.game_event = _game_event;
		}

		protected override void SerializeBody(ByteBuffer _serializer)
		{
			game_event.Serialize(_serializer);
			//Debug.Log(game_event.GetType().Name);
		}
	}
}
