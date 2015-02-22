#ifndef SYSTEMS_NET_H
#define SYSTEMS_NET_H

#include "Utilities\Notifier\Notifier.h"
#include "Basics\Time\Time.h"

//=============================================================================
//
// Basic Types
//
//=============================================================================
typedef uint32 IpAddress;
typedef uint16 Port;


const IpAddress NET_IP_ADDRESS_INVALID = 0xffffffff;

//=============================================================================
//
// Setup
//
//=============================================================================
void NetInitialize ();
void NetUninitialize ();


//=============================================================================
//
// Helpers
//
//=============================================================================
IpAddress NetGetAddress (const char name[]);


//=============================================================================
//
// Socket
//
//=============================================================================
class Socket
{
public:
    Socket ();
    Socket (const Socket & socket);
    Socket (Socket && socket);
    ~Socket ();

    bool IsValid () const;

    void Close ();

    bool Listen (Port port);
    bool Connect (IpAddress ip, Port port);

    Socket Accept ();

    bool Send (const byte data[], unsigned len);
    unsigned Recv (byte data[], unsigned len);
    uint BytesAvailable () const;
    

    void SetBlocking (bool value);
	void SetTimeout (Time::Delta timeout);
    void SetDelayed (bool value);

private:
    explicit Socket (unsigned int socket);

    void Init ();
    void HandleErrors ();

    unsigned int m_socket;
};



namespace Network
{

interface IManager;
interface IManagerNotify;
interface IConnection;




//=============================================================================
//
// IManager
//
//=============================================================================
interface IManager
{
    virtual void Update () pure;

    virtual void SetListenPort (Port port) pure;

    virtual IConnection * CreateConnection (IpAddress address, Port port) pure;
};

IManager * GetMananger ();



//=============================================================================
//
// IManagerNotify
//
//=============================================================================
interface IManagerNotify : TNotifyTarget<IManagerNotify>
{
    virtual void OnNetConnectionOpen (IConnection * connection);
    virtual void OnNetConnectionClose (IConnection * connection);
};



//=============================================================================
//
// IConnection
//
//=============================================================================
interface IConnection
{
    virtual void Send (const byte data[], const uint length) pure;

    virtual void Read (byte data[], const uint length) pure;
    virtual unsigned BytesAvailable () const pure;
};

} // namespace Network

#endif // SYSTEMS_NET_H