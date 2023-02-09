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
    std::string message = "Discord Core " + std::string(coreResult == discord::Result::Ok && core ? "ok " : "not ok ") +
                          std::to_string((int) coreResult);
    std::cout << message << std::endl;
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
            std::string message = "UpdateActivity status: " + std::to_string((int) result);
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

void Instance::EditCurrentActivity()
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

void Instance::DebugPrint(const std::string &message)
{
    if (isDebugging)
    {
        std::cout << message << std::endl;
    }
}
