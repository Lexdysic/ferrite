
namespace Network
{

class CConnection : public IConnection
{
public: // Internal -----------------------------------------------------------

    CConnection (Socket && socket);
    ~CConnection ();

    void Update ();

private: // IConnection -------------------------------------------------------

    void Send (const byte data[], const uint length) override;

    void Read (byte data[], const uint length) override;
    uint BytesAvailable () const override;

public: // Links --------------------------------------------------------------

    LIST_LINK(CConnection) m_link;

private: // -------------------------------------------------------------------

    Socket       m_socket;
    TQueue<byte> m_readBuffer;
    TQueue<byte> m_sendBuffer;

};

} // namespace Network