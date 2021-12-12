#ifndef MEP_LIGHT_TCP_CLIENT
#define MEP_LIGHT_TCP_CLIENT
#include<MEPWindow/OSSetUp.h>
#include<MEPTools/Log.h>
#include<string>

#ifndef MEP_LIVE_VIEW_IPADDRESS
#define MEP_LIVE_VIEW_IPADDRESS "127.0.0.1"
#endif

#ifndef MEP_LIVE_VIEW_PORT
#define MEP_LIVE_VIEW_PORT 8080
#endif


#if defined(MEP_WINDOWS)

#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#elif defined(MEP_LINUX)

#endif

namespace MEP
{
	class TCP_Client
	{
		bool serverStatus;
		bool connectionStatus;
		bool forceReconnecting;
		SOCKET sock;
		sockaddr_in hint;
		bool init()
		{
			WSAData data;
			WORD ver = MAKEWORD(2, 2);
			int result = WSAStartup(ver, &data);
			if (result != 0)
			{
				Log(Error) << "Could not initialize winsock, error code: " << result;
				return false;
			}
			sock = socket(AF_INET, SOCK_STREAM, 0);
			if (sock == INVALID_SOCKET)
			{
				Log(Error) << "Could not create a socket, error code: " << WSAGetLastError();
				return false;
			}

			hint.sin_family = AF_INET;
			hint.sin_port = htons(MEP_LIVE_VIEW_PORT);
			inet_pton(AF_INET, MEP_LIVE_VIEW_IPADDRESS, &hint.sin_addr);

		}
	public:
		TCP_Client() :
			serverStatus(true),
			connectionStatus(false),
			forceReconnecting(true)
		{
			init();
		}
		void stopReconnecting()
		{
			forceReconnecting = false;
		}
		void shutdown()
		{
			Log(Info) << "Shutdown";
			serverStatus = false;
		}
		bool MEPsend(std::string& msg)
		{
			if (IsConnected())
			{
				char BUF[1024];
				if (msg.size() > 0)
				{
					Log(Info) << "Sending";
					int sendResult = send(sock, msg.c_str(), msg.size() + 1, 0);
					if (sendResult != SOCKET_ERROR)
					{
						ZeroMemory(BUF, 1024);
						int bytesReceived = recv(sock, BUF, 1024, 0);
						if (bytesReceived > 0)
						{
							Log(Info) << "Message receive: " << BUF;
						}
						else if (bytesReceived == 0)
						{
							Log(Info) << "Connection closed.";
							connectionStatus = false;
							return false;
						}
						else
						{
							Log(Error) << "Receive error, error code: " << WSAGetLastError();
							return false;
						}
					}
				}
				return true;
			}
			return false;
		}
		void MEPconnect()
		{
			int connResult = 0;
			do
			{
				Log(Info) << "Connecting";
				connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
				if (connResult == SOCKET_ERROR)
				{
					Log(Error) << "Could not connect to the server, error code: " << WSAGetLastError() << ", reconnecting.";
				}
			} while (forceReconnecting == true and serverStatus == true and connResult == SOCKET_ERROR);
			if (connResult != SOCKET_ERROR)
			{
				connectionStatus = true;
			}
		}
		bool IsConnected() const 
		{
			return connectionStatus;
		}
		~TCP_Client()
		{
			closesocket(sock);
			WSACleanup();
		}
	};
}

#endif