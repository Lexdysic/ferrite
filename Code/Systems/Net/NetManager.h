
namespace Network
{

class CManager : public IManager
{
public: // Internal

    CManager ();
    ~CManager ();

    void OnCreate (CConnection * connection);

public: // Static

    static CManager s_manager;
    static CManager * Get () { return &s_manager; }

private: // IManager

    void Update () override;

    void SetListenPort (Port port) override;

    IConnection * CreateConnection (IpAddress address, Port port) override;

private: //

    typedef LIST_DECLARE(CConnection, m_link) ConnectionList;
    typedef TNotifier<IManagerNotify> CNotifier;

    CNotifier      m_notify;
    ConnectionList m_connections;
    Port           m_listenPort;
    Socket         m_listenSocket;

};

} // namespace Network