#pragma once

class IProtocolCallback
{
public:
    virtual void OnHttp() = 0;
    virtual void OnOpen() = 0;
    virtual void OnClose() = 0;
};

class FTsuWebSocketServer
{
public:
    // Manages connections. Unfortunately this is public because static callback for
    // libwebsockets is defined outside the instance and needs access to it.
    // TMap<int,Connection*> connections;

    // Constructor / Destructor
    FTsuWebSocketServer();
    ~FTsuWebSocketServer();

    void AddProtocol(const char* Name, size_t BufferSize, IProtocolCallback* Callback);

    bool Start(int port);
    void Run(       uint64_t timeout = 50     );
    void Wait(      uint64_t timeout = 50     );
    void Send(      int socketID, const FString& data );
    void Broadcast( const FString& data               );
    void Stop();

    /*
    // Key => value storage for each connection
    FString getValue( int socketID, const FString& name );
    void   setValue( int socketID, const FString& name, const FString& value );
    int    getNumberOfConnections( );

    // Overridden by children
    virtual void onConnect(    int socketID                        ) {}
    virtual void onMessage(    int socketID, const FString& data    ) {}
    virtual void onDisconnect( int socketID                        ) {}
    virtual void   onError(    int socketID, const FString& message ) {}

    // Wrappers, so we can take care of some maintenance
    void onConnectWrapper(    int socketID );
    void onDisconnectWrapper( int socketID );
    void onErrorWrapper( int socketID, const FString& message );
*/

private:
    struct ProtocolInfo
    {
        const char* Name;
        size_t BufferSize;
        mutable IProtocolCallback* Callback;
    };

    static int ProtocolCallback(
        struct lws *wsi,
        enum lws_callback_reasons reason,
        void *user,
        void *in,
        size_t len);

    TArray<struct ProtocolInfo> Protocols;

    lws_context* WebSocketContext;
    lws_protocols* WebSocketProtocols;


    void _removeConnection( int socketID );
};
