#include<MEPWindow/Application.h>

namespace MEP 
{
    namespace Template
    {
        void Application::update() {
            BaseManager::execute([this](auto& x) {
                if (x.second.get()->getStatus() != BaseWindow::Status::NullAction) {
                    x.second.get()->update(getGlobalTime());
                }
                });
        }

        void Application::handleEvents() {
            sf::Event event;
            while (pollEvent(event))
            {
                BaseManager::execute([this, &event](auto& x) {
                    if (x.second.get()->getStatus() == BaseWindow::Status::Main)
                        x.second.get()->handleEvent(*this, event);
                });
            }
        }
        
        void Application::render() {
            clear(m_backgroundColor);
            bool ready = true;
            BaseManager::execute([&ready, this](auto& x) {
                if (x.second.get()->getStatus() != BaseWindow::Status::NullAction) {
                    if (x.second.get()->customView()) {
                        if (!x.second.get()->render(*this))
                            ready = false;
                    }
                    else {
                        if (!x.second.get()->render(*this))
                            ready = false;
                    }
                }
                });
            if (ready)
                display();
        }
        
        void Application::onResize() {
            m_resolution = getSize();
            m_view.setCenter({ (float)m_resolution.x / 2, (float)m_resolution.y / 2 });
            m_view.setSize({ (float)m_resolution.x, (float)m_resolution.y });
            setView(m_view);
            BaseManager::execute([this](auto& x) {
                if (x.second.get()->getStatus() != BaseWindow::Status::NullAction)
                    x.second.get()->onResize(m_resolution);
                });
        }
        Application::Application(const char* title,
            const char* resPath,
            const sf::Vector2u& mainResolution,
            U_int32 style,
            sf::ContextSettings settings)
            :
            WindowData(title, mainResolution, style, settings),
            Resources(resPath),
            BaseManager()
        {
        }
        Application::~Application() 
        {}

        void Application::setWindowTransparent() {
            PLATFORM::transparent(getSystemHandle());
        }

        void Application::setWindowTransparency(unsigned char alpha) {
            PLATFORM::transparency(getSystemHandle(), alpha);
        }

        void Application::initApp() {
            try {
                createResources();
                initWindow();
            }
            catch (const MEP::ResourceException& x) {
                throw MEP::WindowException(-1, x);
            }
            try {
                createWindows();
            }
            catch (const MEP::WindowException& x) {
                throw x;
            }
            isInit = true;
        }

        bool Application::run() {
            if (isInit == false) {
                throw MEP::WindowException("Appliaction is not initialized!");
            }
            sf::Clock clock;
            while (isOpen())
            {
                sf::Time dt = clock.restart();
                getGlobalTime() += dt;
                handleEvents();
                try {
                    update();
                }
                catch (const MEP::WindowException& x) {
                    throw x;
                }
                render();
                updateStatistics(dt);
            }
            return false;
        }
    }
}