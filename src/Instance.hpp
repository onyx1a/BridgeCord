#ifndef DISCORDBRIDGE_INSTANCE_HPP
#define DISCORDBRIDGE_INSTANCE_HPP

#include <string>
#include <sstream>
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
    Instance(bool debugging);
    void Init(long long int clientID);
    void SetDetails(const std::string&);
    void SetState(const std::string&);
    void EditCurrentActivity();
    void UpdateActivity();
    void RunCallbacks();
    void SetTimestampsStart(long long int);
    void SetTimestampsEnd(long long int);
    void InitForParty(int curSize, int maxSize, const char* id, const char* secret, bool isPrivate);
    discord::User GetCurrentUser();

    ActivityInfo activityInfo;
    bool isDebugging;

private:
    void DebugPrint(const std::string&) const;
    void DebugPrint(const std::stringstream&) const;

    discord::Core* core{};
    discord::Activity activity{};
    discord::User currentUser;
};

#endif //DISCORDBRIDGE_INSTANCE_HPP
