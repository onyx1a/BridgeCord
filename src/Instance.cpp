#include <iostream>
#include "Instance.hpp"

void Instance::Init(const long long int clientID)
{
    const discord::ClientId CLIENT_ID = clientID;
    discord::Result coreResult;
    coreResult = discord::Core::Create(CLIENT_ID, DiscordCreateFlags_NoRequireDiscord, &this->core);
    coreResult == discord::Result::Ok && this->core ? std::cout << "Core ok\n" : std::cout << "Core not ok, code: "
                                                                                     << (int) coreResult << "\n";
}

void Instance::SetDetails(const std::string& details)
{
    activityInfo.details = details;
    activity.SetDetails(details.c_str());
    UpdateActivity();
}

void Instance::UpdateActivity()
{
    if (this->core)
    {
        this->core->ActivityManager().UpdateActivity(activity, [](discord::Result result)
        {
            std::cout << "UpdateActivity status: " << (int) result << std::endl;
        });
    } else
    {
        std::cout << "Discord is not running" << std::endl;
    }
}

void Instance::RuntimeCallbacks()
{
    if (this->core)
    {
        this->core->RunCallbacks();
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
