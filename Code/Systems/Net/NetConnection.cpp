#define _SCL_SECURE_NO_WARNINGS

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

        m_readBuffer.AddBack(buffer);
    }

    // Send off waiting data
    if (m_sendBuffer.Count())
    {
        // Need to copy to continuous memory before sending
        TArray<byte> sendArray;
        sendArray.Reserve(m_sendBuffer.Count());
        std::copy(m_sendBuffer.begin(), m_sendBuffer.end(), sendArray.begin());

        m_socket.Send(sendArray.Ptr(), sendArray.Count());

        m_sendBuffer.Clear();
    }
}

//=============================================================================
void CConnection::Send (const byte data[], const uint length)
{
    m_sendBuffer.AddBack(data, length);
}

//=============================================================================
void CConnection::Read (byte data[], const uint length)
{
    ASSERT(length <= m_readBuffer.Count());

    std::copy(m_readBuffer.begin(), m_readBuffer.end(), data);
    m_readBuffer.Remove(0, length);
}

//=============================================================================
uint CConnection::BytesAvailable () const
{
    return m_readBuffer.Count();
}

} // namespace Network