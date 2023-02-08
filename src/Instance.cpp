#include <iostream>
#include "Instance.hpp"

void Instance::Init(const long long int clientID)
{
    const discord::ClientId CLIENT_ID = clientID;
    discord::Result coreResult;
    coreResult = discord::Core::Create(CLIENT_ID, DiscordCreateFlags_NoRequireDiscord, &this->core);
    coreResult == discord::Result::Ok && this->core ? std::cout << "Core ok\n" : std::cout << "Core not ok, code: "
                                                                                     << (int) coreResult << "\n";

    activity.SetDetails("Details test");
    activity.SetState("In game");
    activity.GetAssets().SetLargeImage("dreampyavatar");
    activity.SetType(discord::ActivityType::Playing);
}

void Instance::SetDetails(const std::string &details)
{
    this->activity.SetDetails(details.c_str());
    this->UpdateActivity();
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