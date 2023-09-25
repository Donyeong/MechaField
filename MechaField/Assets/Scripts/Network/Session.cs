using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using UnityEngine;
namespace DNNet
{
	public enum ePacketType
	{
		TCP
	}
	public enum eNetworkError {
		None = 0,
		AlreadyConnected,
		ConnectException,
		Unknown10001,
		Unknown10002,
		Unknown10003,
	}

	public struct NetworkResult
	{
		public bool is_success;
		public eNetworkError error_code;
		public NetworkResult(bool _is_success)
		{
			if(!_is_success)
			{
				// 
			}
			is_success = _is_success;
			error_code = eNetworkError.None;
		}
		public NetworkResult(bool _is_success, eNetworkError _error_code)
		{
			is_success = _is_success;
			error_code = _error_code;
		}

		public NetworkResult setErrorCode(eNetworkError _error_code)
		{
			error_code = _error_code;
			return this;
		}
	}
	public class Session
	{
		bool isConnected = false;
		TcpClient PlayerSocket;
		public byte[] asyncBuff;
		public NetworkStream myStream;
		public StreamReader myReader;
		public StreamWriter myWriter;
		public Queue<byte[]> message_queue;



		const int BUF_SIZE = 32;
		public NetworkResult ConnectGameServer(string _ip, int _port)
		{
			if (PlayerSocket != null)
			{
				if (PlayerSocket.Connected || isConnected)
					return new NetworkResult(false, eNetworkError.AlreadyConnected);
				PlayerSocket.Close();
				PlayerSocket = null;
			}

			PlayerSocket = new TcpClient();
			PlayerSocket.ReceiveBufferSize = BUF_SIZE;
			PlayerSocket.SendBufferSize = BUF_SIZE;
			PlayerSocket.NoDelay = true;
			Array.Resize(ref asyncBuff, BUF_SIZE);
			try
			{
				PlayerSocket.Connect(_ip, _port);
			}
			catch (Exception ex)
			{
				isConnected = false;
				Debug.LogError(ex.Message);
				return new NetworkResult(false, eNetworkError.ConnectException);
			}

			//PlayerSocket.BeginConnect(ServerIP, ServerPort, new AsyncCallback(ConnectCallback), PlayerSocket);
			if (PlayerSocket == null)
			{
				return new NetworkResult(false, eNetworkError.Unknown10003);
			}
			PlayerSocket.NoDelay = true;
			myStream = PlayerSocket.GetStream();

			if (PlayerSocket.Connected == false)
			{
				isConnected = false;
				return new NetworkResult(false, eNetworkError.Unknown10002);
			}
			else
			{
				OnConnected();
				return new NetworkResult(true);
			}
		}

		void OnConnected()
		{
			myStream.BeginRead(asyncBuff, 0, BUF_SIZE, OnReceive, null);
			myWriter = new StreamWriter(myStream);
			//IPEndPoint iep = PlayerSocket.Client.RemoteEndPoint as IPEndPoint;
			isConnected = true;
		}

		void FailConnection(int _error_code)
		{
			
		}

		void OnClose()
		{
			PlayerSocket.Close();
		}
		public void OnReceive(IAsyncResult result)
		{
			if (PlayerSocket != null)
			{
				int recived_size = myStream.EndRead(result);
				if (recived_size == 0)
				{
					OnClose();
					return;
				}
				AddPacket(asyncBuff);
				asyncBuff = new byte[BUF_SIZE];
				
				while (myStream.DataAvailable)
				{
					recived_size = myStream.Read(asyncBuff, 0, BUF_SIZE);
					if (recived_size == 0)
					{
						OnClose();
						return;
					}
					AddPacket(asyncBuff);
					asyncBuff = new byte[BUF_SIZE];
				}
				

				myStream.BeginRead(asyncBuff, 0, BUF_SIZE, OnReceive, null);

			}
		}

		public void AddPacket(byte[] _packet)
		{
			Debug.Log($"Packet Received , size{_packet.Length}");
			message_queue.Enqueue(asyncBuff);
		}
		public void UpdateConnectionState()
		{
			if (PlayerSocket.Connected == false)
			{
				isConnected = false;
				FailConnection(10005);
				return;
			}
		}

		public void SendDataToServer(byte[] data, ePacketType packetType = ePacketType.TCP)
		{
			UpdateConnectionState();
			if (isConnected == false) return;
			if (myStream.CanWrite == false)
			{
				FailConnection(10004);
				return;
			}
			ByteBuffer packetBuffer = new ByteBuffer();

			if (packetType == ePacketType.TCP)
			{
				packetBuffer.WriteInteger(data.Length);
				packetBuffer.WriteBytes(data);
				myStream.Write(packetBuffer.ToArray(), 0, packetBuffer.ToArray().Length);
			}
			packetBuffer.Dispose();
		}



	}
}
