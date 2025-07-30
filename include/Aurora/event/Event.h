#pragma once

#include <functional>
#include <memory>
#include "aurora_export.h"

namespace Aurora::Event {

    class EventImpl;

    class AURORA_API Event
    {
    public:
        virtual ~Event() = default;
        virtual const char* GetDescriptor() const = 0;
    };

    using EventCallback = std::function<void(const Event&)>;

    class AURORA_API EventDispatcher
    {
    public:
        EventDispatcher();
        ~EventDispatcher();

        void Subscribe(const char* descriptor, EventCallback&& callback) const;
        void Dispatch(const Event& event) const;

    private:
        std::unique_ptr<EventImpl> m_Pimpl;
    };

} // namespace Aurora::Event