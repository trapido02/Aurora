#include "ApplicationBaseImpl.h"
#include "WindowImpl.h"
#include "include/Aurora/core/ApplicationBase.h"

namespace Aurora::Core {

    ApplicationBaseImpl::ApplicationBaseImpl(ApplicationBase& selfRef) : self(selfRef)
    {
    }

    ApplicationBaseImpl::~ApplicationBaseImpl() = default;

    void ApplicationBaseImpl::Run()
    {
        m_IsRunning = true;

        WindowImpl& window = WindowImpl::GetInstance();
        window.Create();

        self.Init();

        while (m_IsRunning && !window.ShouldClose())
        {
            self.Update();

            if (window.ShouldClose())
            {
                m_IsRunning = false;
            }

            window.Update();
        }

        self.Shutdown();
        window.Destroy();
    }

} // namespace Aurora::Core