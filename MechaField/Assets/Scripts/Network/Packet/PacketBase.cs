using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace DNNet
{
	public abstract class PacketBase : ISerializable
	{
		public int packet_type;
		public int data_size;

		protected abstract void SerializeBody(ByteBuffer _serializer);
		protected abstract void DeserializeBody(ByteBuffer _serializer);
		protected int GetPacketType()
		{
			return 0;
		}

		public void Serialize(ByteBuffer _serializer)
		{
			int _prev_size = _serializer.Length();
			SerializeBody(_serializer);
			data_size = _serializer.Length() - _prev_size;
			packet_type = GetPacketType();
		}

		public void Deserialize(ByteBuffer _serializer)
		{
			int _prev_pos = _serializer.GetReadPos();
			DeserializeBody(_serializer);
			data_size = _serializer.GetReadPos() - _prev_pos;
			packet_type = GetPacketType();
		}
	}
	public abstract class ClientPacketBase : PacketBase
	{
		protected override void DeserializeBody(ByteBuffer _serializer) { }
	}
	public abstract class ServerPacketBase : PacketBase
	{
		protected override void SerializeBody(ByteBuffer _serializer) { }
	}
}