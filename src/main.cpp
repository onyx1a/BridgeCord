#include "../discord_gamesdk_cmake/src/discord.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Instance.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void Log(discord::LogLevel level, const char* message)
{
    std::cout << "Log(" << (int)level << "): " << message << std::endl;
}

std::string TestBridge()
{
    return "Make Bridge!";
}

void RunBridge()
{
//    std::cout << "Hello, Discord Game SDK" << std::endl;
    const discord::ClientId CLIENT_ID = 1071058178701283439;

    discord::Core* core{};
    discord::Result coreResult;

    coreResult = discord::Core::Create(CLIENT_ID, DiscordCreateFlags_Default, &core);
    coreResult == discord::Result::Ok && core ? std::cout << "Core ok\n" : std::cout << "Core not ok, code: " << (int)coreResult << "\n";

    core->SetLogHook(discord::LogLevel::Debug, Log);
    core->SetLogHook(discord::LogLevel::Info, Log);
    core->SetLogHook(discord::LogLevel::Warn, Log);
    core->SetLogHook(discord::LogLevel::Error, Log);

    // {
    //     auto result = core->ActivityManager().RegisterCommand("ProjectDream.exe");
    //     std::cout << "Register command status: " << (int)result << std::endl;
    // }
    discord::Activity activity{};
    activity.SetDetails("Details test");
    activity.SetState("In game");
    // activity.GetAssets().SetSmallImage("dreampyavatar");
    // activity.GetAssets().SetSmallText("Mini text");
    activity.GetAssets().SetLargeImage("dreampyavatar");
    // activity.GetAssets().SetLargeText("Dream!");
    activity.SetType(discord::ActivityType::Playing);
    // activity.GetTimestamps().SetStart(time(0));

    core->ActivityManager().UpdateActivity(activity, [](discord::Result result)
    {
        // std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!" << std::endl;
        std::cout << "UpdateActivity status: " << (int)result << std::endl;
    });

    // {
    //     // discord::User currentUser;
    //     // auto user = core->UserManager().GetCurrentUser(&currentUser);
    //     // std::cout << "User: " << currentUser.GetId() << std::endl;
    //     core->UserManager().GetUser(1052579421875339284, [](discord::Result result, discord::User user)
    //     {
    //         if (result == discord::Result::Ok)
    //         {
    //             std::cout << "User: " << user.GetUsername() << std::endl;
    //         } else
    //         {
    //             std::cout << "User not found" << std::endl;
    //         }
    //     });
    // }

    while (true)
    {
        auto result = core->RunCallbacks();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
//        if (PyErr_CheckSignals() != 0)
//        {
//            throw py::error_already_set();
//        }
        // result == discord::Result::Ok ? std::cout << "Activity RunCallback ok\n" : std::cout << "Activity RunCallback not ok\n";
    }


    // return 0;
}

PYBIND11_MODULE(DiscordBridge, m) {
    m.def("TestBridge", &TestBridge);
    m.def("RunBridge", &RunBridge);

    py::class_<Instance>(m, "Instance")
            .def(py::init<>())
            .def("init", &Instance::Init, py::arg("clientID"))
            .def("set_details", &Instance::SetDetails)
            .def("set_state", &Instance::SetState)
            .def("update_activity", &Instance::UpdateActivity)
            .def("runtime_callbacks", &Instance::RuntimeCallbacks)
            .def("edit_current_activity", &Instance::EditCurrentActivity)
            .def_readwrite("activityInfo", &Instance::activityInfo)
            ;
    py::class_<ActivityInfo>(m, "ActivityInfo")
            .def(py::init())
            .def_readwrite("details", &ActivityInfo::details)
            .def_readwrite("state", &ActivityInfo::state)
            .def_readwrite("smallText", &ActivityInfo::smallText)
            .def_readwrite("smallImage", &ActivityInfo::smallImage)
            .def_readwrite("largeText", &ActivityInfo::largeText)
            .def_readwrite("largeImage", &ActivityInfo::largeImage)
            ;
}
