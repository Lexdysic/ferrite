
#include "NetPch.h"

namespace Network
{

//=============================================================================
CManager::CManager ()
{
    m_listenSocket.SetBlocking(false);
}

//=============================================================================
CManager::~CManager ()
{
}

//=============================================================================
void CManager::OnCreate (CConnection * connection)
{
    m_connections.InsertTail(connection);
}

//=============================================================================
void CManager::Update ()
{
    // Create new connections
    while (m_listenSocket.Listen(m_listenPort))
    {
        Socket socket = m_listenSocket.Accept();

        auto * connection = new CConnection(std::move(socket));
        OnCreate(connection);
    }

    // Update connections
    for (auto * connection : m_connections)
    {
        connection->Update();
    }
}

//=============================================================================
void CManager::SetListenPort (Port port)
{
    m_listenPort = port;
}

//=============================================================================
IConnection * CManager::CreateConnection (IpAddress address, Port port)
{
    return null;
}


//=============================================================================
IManager * GetManager ()
{
    return CManager::Get();
}

} // namespace Network