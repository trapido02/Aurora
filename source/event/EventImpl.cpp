#include "pch.h"
#include "EventImpl.h"

#include "Aurora/event/Event.h"

namespace Aurora::Event {

    EventDispatcher::EventDispatcher() : m_Pimpl(std::make_unique<EventImpl>())
    {
    }

    EventDispatcher::~EventDispatcher() = default;

    void EventDispatcher::Subscribe(const char* descriptor, EventCallback&& callback) const
    {
        ZoneScoped;
        m_Pimpl->m_Observers[descriptor].emplace_back(std::move(callback));
    }

    void EventDispatcher::Dispatch(const Event& event) const
    {
        ZoneScoped;
        const char* desc = event.GetDescriptor();
        const auto iterator = m_Pimpl->m_Observers.find(desc);

        if (iterator == m_Pimpl->m_Observers.end())
        {
            return;
        }
        for (const auto& callback : iterator->second)
        {
            callback(event);
        }
    }

} // namespace Aurora::Event