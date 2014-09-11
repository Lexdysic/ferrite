#include <winsock2.h>
#include <ws2tcpip.h>

#define USES_ENGINE_NET

#include "EngineDeps.h"

#pragma comment(lib, "ws2_32.lib")

//=============================================================================
void NetInitialize ()
{
	WSADATA wsaData;
	const int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
}

//=============================================================================
void NetUninitialize ()
{
    WSACleanup();
}

//=============================================================================
IpAddress NetGetAddress (const char name[])
{
    addrinfo * info = null;

    if (::getaddrinfo(name, null, null, &info) != 0)
        return NET_IP_ADDRESS_INVALID;

    IpAddress ip = reinterpret_cast<sockaddr_in *>(info->ai_addr)->sin_addr.S_un.S_addr;

    ::freeaddrinfo(info);

    return ip;
}


//=============================================================================
//
// Socket
//
//=============================================================================

//=============================================================================
// Default
Socket::Socket () :
    m_socket(INVALID_SOCKET)
{
}

//=============================================================================
// Copy
Socket::Socket (const Socket & socket) :
    m_socket(socket.m_socket)
{
}

//=============================================================================
// Move
Socket::Socket (Socket && socket) :
    m_socket(socket.m_socket)
{
    socket.m_socket = INVALID_SOCKET;
}

//=============================================================================
Socket::Socket (unsigned int socket) :
    m_socket(socket)
{

}

//=============================================================================
Socket::~Socket ()
{
    Close();
}

//=============================================================================
bool Socket::IsValid () const
{
    return m_socket != INVALID_SOCKET;
}

//=============================================================================
void Socket::Init ()
{
    ASSERT(!IsValid());
    //m_socket = ::WSASocket(PF_INET, SOCK_STREAM, 0, null, 0, WSA_FLAG_OVERLAPPED);
    m_socket = ::socket(AF_INET, SOCK_STREAM, 0);
    ASSERT(IsValid());
}

//=============================================================================
void Socket::Close ()
{
    if (!IsValid())
        return;

    ::shutdown(m_socket, 0);
    ::closesocket(m_socket);

    m_socket = INVALID_SOCKET;
}

//=============================================================================
bool Socket::Listen (Port port)
{
    Init();

    sockaddr_in serverInfo;
	serverInfo.sin_family      = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port        = htons(port);
		
	if (::bind(m_socket, (const sockaddr *)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
		return false;

	if (::listen(m_socket, 1) == SOCKET_ERROR)
		return false;

    return true;
}

//=============================================================================
bool Socket::Connect (IpAddress ip, Port port)
{
    Init();

	sockaddr_in serverInfo;
	serverInfo.sin_family      = AF_INET;
	serverInfo.sin_addr.s_addr = ip;
	serverInfo.sin_port        = htons(port);

    if (::connect(m_socket, (const sockaddr *)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
        return false;

    return true;
}

//=============================================================================
Socket Socket::Accept ()
{
    ASSERT(IsValid());

    const unsigned int socket = ::accept(m_socket, null, null);
    return Socket(socket);
}

//=============================================================================
bool Socket::Send (const byte data[], unsigned len)
{ 
    ASSERT(IsValid());
    const int ret = ::send(m_socket, (const char *)data, len, 0);
    if (ret > 0)
        return true;

    HandleErrors();
    return false;
}

//=============================================================================
unsigned Socket::Recv (byte data[], unsigned len)
{
    ASSERT(IsValid());
    const int ret = ::recv(m_socket, (char *)data, len, 0);
    if (ret > 0)
        return ret;

    HandleErrors();
    return 0;
}

//=============================================================================
uint Socket::BytesAvailable () const
{
    u_long bytes = 0;
    ::ioctlsocket(m_socket, FIONREAD, &bytes);
    return bytes;
}

//=============================================================================
void Socket::SetBlocking (bool value)
{
    ASSERT(IsValid());

    // Set as non-blocking by default
    u_long nonBlocking = !value;
    ::ioctlsocket(m_socket, FIONBIO, &nonBlocking);
}

//=============================================================================
void Socket::SetTimeout (Time::Delta timeout)
{
    const unsigned ms = FloatToUint(timeout.GetSeconds());

    // Recieve
    {
        unsigned value = ms;
        ::setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&value, sizeof(value));
    }

    // Send
    {
        unsigned value = ms;
        ::setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, (const char *)&value, sizeof(value));
    }
}

//=============================================================================
void Socket::SetDelayed (bool delayed)
{
    unsigned value = !delayed;
    ::setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, (const char *)&value, sizeof(value));
}

//=============================================================================
void Socket::HandleErrors ()
{
    const int error = WSAGetLastError();
    switch (error)
    {
        case WSAEWOULDBLOCK:
        break;

        case WSAECONNRESET:
        case WSAESHUTDOWN:
        case WSAETIMEDOUT:
        case WSAEINVAL:
            Close();
        break;

        DEFAULT_FATAL("Unknown error");

    }
}
