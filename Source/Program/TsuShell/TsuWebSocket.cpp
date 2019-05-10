#include "CoreMinimal.h"
#include "LibWebSocketsWarpper.h"

#include "TsuWebSocket.h"

/*
static int callback_main(   struct lws *wsi,
                            enum lws_callback_reasons reason,
                            void *user,
                            void *in,
                            size_t len )
{
    int fd;
    unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 512 + LWS_SEND_BUFFER_POST_PADDING];
    unsigned char *p = &buf[LWS_SEND_BUFFER_PRE_PADDING];

    switch( reason ) {
        case LWS_CALLBACK_ESTABLISHED:
            self->onConnectWrapper( lws_get_socket_fd( wsi ) );
            lws_callback_on_writable( wsi );
            break;

        case LWS_CALLBACK_SERVER_WRITEABLE:
            fd = lws_get_socket_fd( wsi );
            while( !self->connections[fd]->buffer.empty( ) )
            {
                const char * message = self->connections[fd]->buffer.front( );
                int msgLen = strlen(message);
                int charsSent = lws_write( wsi, (unsigned char *)message, msgLen, LWS_WRITE_TEXT );
                if( charsSent < msgLen )
                    self->onErrorWrapper( fd, string( "Error writing to socket" ) );
                else
                    // Only pop the message if it was sent successfully.
                    self->connections[fd]->buffer.pop_front( );
            }
            lws_callback_on_writable( wsi );
            break;

        case LWS_CALLBACK_RECEIVE:
            self->onMessage( lws_get_socket_fd( wsi ), string( (const char *)in ) );
            break;

        case LWS_CALLBACK_CLOSED:
            self->onDisconnectWrapper( lws_get_socket_fd( wsi ) );
            break;

        default:
            break;
    }
    return 0;
}
*/

FTsuWebSocketServer::FTsuWebSocketServer()
{
}

FTsuWebSocketServer::~FTsuWebSocketServer()
{
}

void FTsuWebSocketServer::AddProtocol(const char* Name, size_t BufferSize, IProtocolCallback* Callback)
{
    Protocols.Add({Name, BufferSize, Callback});
}

bool FTsuWebSocketServer::Start(int Port)
{
    WebSocketProtocols = new struct lws_protocols[Protocols.Num() + 1];
    FMemory::Memzero(WebSocketProtocols, sizeof(lws_protocols) * Protocols.Num() + 1);

    for(auto i=0; i<Protocols.Num(); i++)
    {
        WebSocketProtocols[i].name = Protocols[i].Name;
        WebSocketProtocols[i].callback = ProtocolCallback;
        WebSocketProtocols[i].per_session_data_size = 0;
        WebSocketProtocols[i].rx_buffer_size = 10*1024;
        WebSocketProtocols[i].id = 0;
        WebSocketProtocols[i].user = Protocols[i].Callback;
        WebSocketProtocols[i].tx_packet_size = 0;
    }

    lws_set_log_level( 0, lwsl_emit_syslog ); // We'll do our own logging, thank you.
    struct lws_context_creation_info info;
    FMemory::Memzero(&info, sizeof(info));
    info.port = Port;
    info.iface = NULL;
    info.protocols = WebSocketProtocols;
    info.gid = -1;
    info.uid = -1;
    info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
    info.user = this;
    
    WebSocketContext = lws_create_context(&info);
    if (WebSocketContext == nullptr)
    {
        delete[] WebSocketProtocols;
        WebSocketProtocols = NULL;
        return false;
    }

    return true;
}

void FTsuWebSocketServer::Stop( )
{
    /*
    // Free up some memory
    for( map<int,Connection*>::const_iterator it = this->connections.begin( ); it != this->connections.end( ); ++it )
    {
        Connection* c = it->second;
        this->connections.erase( it->first );
        delete c;
    }
    */

    if (WebSocketContext!=nullptr)
    {
        lws_context_destroy(WebSocketContext);
        WebSocketContext = nullptr;

    }

    if (WebSocketProtocols!=nullptr)
    {
        delete WebSocketProtocols;
    }
}

int FTsuWebSocketServer::ProtocolCallback(
        struct lws *wsi,
        enum lws_callback_reasons reason,
        void *user,
        void *in,
        size_t len)
{
    auto protocols = lws_get_protocols(wsi);

    

    return 0;
}



/*

void FTsuWebSocketServer::onConnectWrapper( int socketID )
{
    Connection* c = new Connection;
    c->createTime = time( 0 );
    this->connections[ socketID ] = c;
    this->onConnect( socketID );
}

void FTsuWebSocketServer::onDisconnectWrapper( int socketID )
{
    this->onDisconnect( socketID );
    this->_removeConnection( socketID );
}

void FTsuWebSocketServer::onErrorWrapper( int socketID, const string& message )
{
    Util::log( "Error: " + message + " on socketID '" + Util::toString( socketID ) + "'" );
    this->onError( socketID, message );
    this->_removeConnection( socketID );
}

void FTsuWebSocketServer::send( int socketID, string data )
{
    // Push this onto the buffer. It will be written out when the socket is writable.
    this->connections[socketID]->buffer.push_back( data.c_str() );
}

void FTsuWebSocketServer::broadcast(string data )
{
    for( map<int,Connection*>::const_iterator it = this->connections.begin( ); it != this->connections.end( ); ++it )
        this->send( it->first, data );
}

void FTsuWebSocketServer::setValue( int socketID, const string& name, const string& value )
{
    this->connections[socketID]->keyValueMap[name] = value;
}

string FTsuWebSocketServer::getValue( int socketID, const string& name )
{
    return this->connections[socketID]->keyValueMap[name];
}
int FTsuWebSocketServer::getNumberOfConnections( )
{
    return this->connections.size( );
}

void FTsuWebSocketServer::run( uint64_t timeout )
{
    while( 1 )
    {
        this->wait( timeout );
    }
}

void FTsuWebSocketServer::wait( uint64_t timeout )
{
    if( lws_service( this->_context, timeout ) < 0 )
        throw "Error polling for socket activity.";
}

void FTsuWebSocketServer::_removeConnection( int socketID )
{
    Connection* c = this->connections[ socketID ];
    this->connections.erase( socketID );
    delete c;
}
*/
