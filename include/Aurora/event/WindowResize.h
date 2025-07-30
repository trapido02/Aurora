#pragma once

#include "Event.h"

namespace Aurora::Event {

    class AURORA_API WindowResize final : public Event
    {
    public:
        struct Data
        {
            int width, height;
        };

        static constexpr auto Descriptor = "WindowResize";
        WindowResize(const int width, const int height) : m_Data({.width = width, .height = height}) {};
        ~WindowResize() override = default;

        const char* GetDescriptor() const override { return Descriptor; }

        const Data& GetData() const { return m_Data; }

    private:
        Data m_Data;
    };

} // namespace Aurora::Event