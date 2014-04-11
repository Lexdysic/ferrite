
#include "NetPch.h"

namespace Network
{

//=============================================================================
CConnection::CConnection (Socket && socket) :
    m_socket(std::forward<Socket>(socket))
{
}

//=============================================================================
CConnection::~CConnection ()
{
}

//=============================================================================
void CConnection::Update ()
{
    // Read in available data
    if (const uint bytesAvailable = m_socket.BytesAvailable())
    {
        TArray<byte> buffer;
        buffer.Resize(bytesAvailable);

        m_socket.Recv(buffer.Ptr(), buffer.Count());

        m_readBuffer.Add(buffer);
    }

    // Send off waiting data
    if (m_sendBuffer.Count())
    {
        m_socket.Send(m_sendBuffer.Ptr(), m_sendBuffer.Count());
        m_sendBuffer.Clear();
    }
}

//=============================================================================
void CConnection::Send (const byte data[], const uint length)
{
    m_sendBuffer.Add(data, length);
}

//=============================================================================
void CConnection::Read (byte data[], const uint length)
{
    ASSERT(length <= m_readBuffer.Count());
    MemCopy(data, m_readBuffer.Ptr(), length);
    m_readBuffer.RemoveOrdered(0, length);
}

//=============================================================================
unsigned CConnection::BytesAvailable () const
{
    return m_readBuffer.Count();
}

} // namespace Network