#ifndef DISCORDBRIDGE_INSTANCE_HPP
#define DISCORDBRIDGE_INSTANCE_HPP

#include <string>
#include <thread>
#include "../discord_gamesdk_cmake/src/discord.h"

class Instance
{
public:
    void Init(long long int clientID);
    void SetDetails(const std::string&);
    void UpdateActivity();
    void RuntimeCallbacks();

private:
    discord::Core* core;
    discord::Activity activity;
};

#endif //DISCORDBRIDGE_INSTANCE_HPP
