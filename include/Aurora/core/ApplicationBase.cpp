#include "ApplicationBase.h"

#include "source/core/ApplicationBaseImpl.h"

namespace Aurora::Core {

    ApplicationBase::ApplicationBase() : m_Pimpl(std::make_unique<ApplicationBaseImpl>(*this))
    {
    }

    ApplicationBase::~ApplicationBase() = default;

    void ApplicationBase::Run() const
    {
        m_Pimpl->Run();
    }

} // namespace Aurora::Core