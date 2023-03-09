#include <iostream>
#include "Instance.hpp"

Instance::Instance(bool debugging)
{
    isDebugging = debugging;
}

void Instance::Init(const long long int clientID)
{
    const discord::ClientId CLIENT_ID = clientID;
    discord::Result coreResult;
    coreResult = discord::Core::Create(CLIENT_ID, DiscordCreateFlags_NoRequireDiscord, &core);
    std::stringstream mes;
    mes << "Discord Core " << (coreResult == discord::Result::Ok && core ? "ok " : "not ok ") << (int)coreResult;
    std::cout << mes.str() << std::endl;
}

void Instance::SetDetails(const std::string& details)
{
    activityInfo.details = details;
    activity.SetDetails(details.c_str());
    UpdateActivity();
}

void Instance::UpdateActivity()
{
    if (core)
    {
        core->ActivityManager().UpdateActivity(activity, [this](discord::Result result)
        {
            std::stringstream message;
            message << "UpdateActivity status: " << (int) result;
            this->DebugPrint(message);
        });
    } else
    {
        this->DebugPrint("Discord is not running");
    }
}

void Instance::RunCallbacks()
{
    if (core)
    {
        core->RunCallbacks();
    }
}

void Instance::SetState(const std::string& state)
{
    activityInfo.state = state;
    activity.SetState(state.c_str());
    UpdateActivity();
}

void Instance::UpdateCurrentActivity()
{
    activity.SetDetails(activityInfo.details.c_str());
    activity.SetState(activityInfo.state.c_str());
    activity.GetAssets().SetSmallImage(activityInfo.smallImage.c_str());
    activity.GetAssets().SetSmallText(activityInfo.smallText.c_str());
    activity.GetAssets().SetLargeImage(activityInfo.largeImage.c_str());
    activity.GetAssets().SetLargeText(activityInfo.largeText.c_str());
    UpdateActivity();
}

void Instance::SetTimestampsStart(long long int timestamps)
{
    activity.GetTimestamps().SetStart(timestamps);
}

void Instance::SetTimestampsEnd(long long int timestamps)
{
    activity.GetTimestamps().SetEnd(timestamps);
}

void Instance::DebugPrint(const std::string &message) const
{
    if (isDebugging)
    {
        std::cout << message << std::endl;
    }
}

void Instance::DebugPrint(const std::stringstream &message) const
{
    if (isDebugging)
    {
        std::cout << message.str() << std::endl;
    }
}

void Instance::EditPartyInfo(int curSize, int maxSize, const char* id, const char* secret, bool isPrivate)
{
    activity.GetParty().GetSize().SetCurrentSize(curSize);
    activity.GetParty().GetSize().SetMaxSize(maxSize);
    activity.GetParty().SetId(id);
    activity.GetSecrets().SetJoin(secret);
    if (isPrivate)
    {
        activity.GetParty().SetPrivacy(discord::ActivityPartyPrivacy::Private);
    } else
    {
        activity.GetParty().SetPrivacy(discord::ActivityPartyPrivacy::Public);
    }
}

std::pair<int, discord::User> Instance::GetCurrentUser()
{
    auto result = core->UserManager().GetCurrentUser(&currentUser);
    return std::pair<int, discord::User>{(int)result, currentUser};
}

int Instance::OnCurrentUserUpdateConnect(const std::function<void()>& callback)
{
    if (!core)
    {
        return -1;
    }

    return core->UserManager().OnCurrentUserUpdate.Connect(callback);
}

void Instance::OnCurrentUserUpdateDisconnect(int token)
{
    if (!core)
    {
        return;
    }
    core->UserManager().OnCurrentUserUpdate.Disconnect(token);
}

int Instance::OnActivityJoinRequestConnect(const std::function<void(const discord::User &)> &callback)
{
    if (!core)
    {
        return -1;
    }

    return core->ActivityManager().OnActivityJoinRequest.Connect(callback);
}

void Instance::SendRequestReply(discord::UserId userId, short reply)
{
    if (!core)
    {
        return;
    }
    std::cout << "SendRequestReply" << std::endl;
    if (SendReplyCallback)
    {
        core->ActivityManager().SendRequestReply(userId, (discord::ActivityJoinRequestReply)reply,[this](discord::Result result)
        {
            SendReplyCallback((int) result);
        });
    } else
    {
        DebugPrint("No one SendRequestReply callback. See `set_send_request_reply_callback` method");
    }
}

void Instance::SetSendRequestReplyCallback(std::function<void(int)> &callback)
{
    SendReplyCallback = callback;
}

void Instance::SendInvite(discord::UserId userId, const char* content)
{
    if (!core)
    {
        return;
    }

    if (SendInviteCallback)
    {
        core->ActivityManager().SendInvite(userId, discord::ActivityActionType::Join, content, [this](discord::Result result)
        {
            SendReplyCallback((int)result);
        });
    } else
    {
        DebugPrint("No one SendRequestReply callback. See `set_send_invite_callback` method");
    }
}

void Instance::SetSendInviteCallback(std::function<void(int)> &callback)
{
    SendInviteCallback = callback;
}
