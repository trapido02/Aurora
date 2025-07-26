#pragma once

namespace Aurora::Core {

    class ApplicationBase;

    class ApplicationBaseImpl
    {
    public:
        explicit ApplicationBaseImpl(ApplicationBase& selfRef);
        ~ApplicationBaseImpl();

        ApplicationBaseImpl(const ApplicationBaseImpl&) = delete;
        ApplicationBaseImpl& operator=(const ApplicationBaseImpl&) = delete;
        ApplicationBaseImpl(ApplicationBaseImpl&&) = delete;
        ApplicationBaseImpl& operator=(ApplicationBaseImpl&&) = delete;

        void Run();

    private:
        ApplicationBase& self; // reference to call virtual methods
        bool m_IsRunning = false;
    };

} // namespace Aurora::Core