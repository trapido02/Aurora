#pragma once

#include <map>
#include <string>
#include <vector>
#include "include/Aurora/event/Event.h"

namespace Aurora::Event {

    class EventImpl
    {
    public:
        std::map<std::string, std::vector<EventCallback>> m_Observers;
    };

} // namespace Aurora::Event