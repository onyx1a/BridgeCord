#include "../discord_gamesdk_cmake/src/discord.h"
#include "Instance.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

std::string TestBridge()
{
    return "Make Bridge!";
}


PYBIND11_MODULE(DiscordBridge, m) {
    m.def("TestBridge", &TestBridge);

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
            .def_readwrite("activityInfo", &Instance::activityInfo)
            .def_readwrite("isDebugging", &Instance::isDebugging)
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
