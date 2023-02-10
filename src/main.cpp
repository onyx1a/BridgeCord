#include "../discord_gamesdk_cmake/src/discord.h"
#include "Instance.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

std::string TestBridge()
{
    return "Make Bridge!";
}

PYBIND11_MODULE(discordBridge, m) {
    m.def("TestBridge", &TestBridge);

    py::class_<discord::User>(m, "DiscordUser")
            .def_property_readonly("username", &discord::User::GetUsername)
            .def_property_readonly("discriminator", &discord::User::GetDiscriminator)
            .def_property_readonly("avatar_hash", &discord::User::GetAvatar)
            .def_property_readonly("avatar_url", [](discord::User& user) -> py::str
            {
                std::stringstream url;
                url << "https://cdn.discordapp.com/avatars/" << user.GetId() << "/" << user.GetAvatar() << ".png";
                return url.str();
            }, R"pbdoc(
        Generate link to open avatar. See details:
        https://discord.com/developers/docs/reference#image-formatting
    )pbdoc")
            .def_property_readonly("is_bot", &discord::User::GetBot)
            .def_property_readonly("id", &discord::User::GetId)
            ;
    py::class_<Instance>(m, "Instance")
            .def(py::init<bool>(), py::arg("debugging") = true)
            .def("init", &Instance::Init, py::arg("clientID"))
            .def("set_details", &Instance::SetDetails)
            .def("set_state", &Instance::SetState)
            .def("update_activity", &Instance::UpdateActivity)
            .def("run_callbacks", &Instance::RunCallbacks)
            .def("edit_current_activity", &Instance::EditCurrentActivity)
            .def("set_timestamps_start", &Instance::SetTimestampsStart)
            .def("set_timestamps_end", &Instance::SetTimestampsEnd)
            .def("init_for_party", &Instance::InitForParty,
                 py::arg("cur_size"),
                 py::arg("max_size"),
                 py::arg("id"),
                 py::arg("secret"),
                 py::arg("is_private"))
            .def("current_user", &Instance::GetCurrentUser)
            .def_readwrite("activity_info", &Instance::activityInfo)
            .def_readwrite("is_debugging", &Instance::isDebugging)
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
