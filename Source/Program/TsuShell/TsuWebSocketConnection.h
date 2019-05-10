#pragma once

class FTsuWebSocketConnection
{
public:
        TArray<const char*> buffer;     // Ordered list of pending messages to flush out when socket is writable
        TMap<FString, FString> keyValueMap;
        time_t             createTime;
}
