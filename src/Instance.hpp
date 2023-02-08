#ifndef DISCORDBRIDGE_INSTANCE_HPP
#define DISCORDBRIDGE_INSTANCE_HPP

#include <string>
#include <thread>
#include "../discord_gamesdk_cmake/src/discord.h"

class ActivityInfo
{
public:
    std::string details;
    std::string state;
    std::string smallText;
    std::string smallImage;
    std::string largeText;
    std::string largeImage;
};

class Instance
{
public:
    void Init(long long int clientID);
    void SetDetails(const std::string&);
    void SetState(const std::string&);
    void EditCurrentActivity();
    void UpdateActivity();
    void RuntimeCallbacks();

    ActivityInfo activityInfo;

private:
    discord::Core* core;
    discord::Activity activity;
};

#endif //DISCORDBRIDGE_INSTANCE_HPP
