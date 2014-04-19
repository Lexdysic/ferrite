
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
    TArray<byte> m_readBuffer; // TODO: change to a queue type
    TArray<byte> m_sendBuffer; // TODO: change to a queue type

};

} // namespace Network