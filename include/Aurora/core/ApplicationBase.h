#pragma once

#include <memory>

namespace Aurora::Core {

    class ApplicationBaseImpl;

    class AURORA_API ApplicationBase
    {
    public:
        ApplicationBase();
        virtual ~ApplicationBase();

        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Shutdown() = 0;

        void Run() const;

    private:
        std::unique_ptr<ApplicationBaseImpl> m_Pimpl;
    };

} // namespace Aurora::Core