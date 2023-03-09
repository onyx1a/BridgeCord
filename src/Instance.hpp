#ifndef BRIDGECORD_INSTANCE_HPP
#define BRIDGECORD_INSTANCE_HPP

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
    void UpdateCurrentActivity();
    void UpdateActivity();
    void RunCallbacks();
    void SetTimestampsStart(long long int);
    void SetTimestampsEnd(long long int);
    void EditPartyInfo(int curSize, int maxSize, const char* id, const char* secret, bool isPrivate);
    void OnCurrentUserUpdateDisconnect(int token);
    void SendRequestReply(discord::UserId userId, short reply);
    void SetSendRequestReplyCallback(std::function<void(int)>& callback);
    void SendInvite(discord::UserId userId, const char* content);
    void SetSendInviteCallback(std::function<void(int)>& callback);

    int OnCurrentUserUpdateConnect(const std::function<void()>& callback);
    int OnActivityJoinRequestConnect(const std::function<void(discord::User const&)>& callback);
    std::pair<int, discord::User> GetCurrentUser();

    ActivityInfo activityInfo;
    bool isDebugging;

private:
    void DebugPrint(const std::string&) const;
    void DebugPrint(const std::stringstream&) const;

    discord::Core* core{};
    discord::Activity activity{};
    discord::User currentUser;
    std::function<void(int)> SendReplyCallback;
    std::function<void(int)> SendInviteCallback;
};

#endif //BRIDGECORD_INSTANCE_HPP
