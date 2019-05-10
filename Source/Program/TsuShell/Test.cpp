#include "CoreMinimal.h"
#include "LibWebSocketsWarpper.h"

#include "TsuWebSocket.h"

int main(int argc, char* argv[])
{
    FTsuWebSocketServer Server;
    Server.Start(0);
    //Server.run();
    //Server.wait();
    Server.Stop();
    return 0;
}
