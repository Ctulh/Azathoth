//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_APPLICATION_HPP
#define AZATHOTH_APPLICATION_HPP

#include "IApplication.hpp"
#include "Layers/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Window/IWindow.hpp"
#include "Gui/IGui.hpp"
#include "GraphicApiFactory/IGraphicApiFactory.hpp"

#include <memory>
#include <atomic>

namespace application {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    using graphicApiFactory::IGraphicApiFactory;
    using layers::LayerStack;
    using window::IWindow;
    using layers::Layer;
    using events::Event;
    using gui::IGui;

    class Application: public IApplication {
    public:
        Application(IGraphicApiFactory const&);
    public:
        void run() override;
        void shutDown() override;
        void onEvent(Event&) override;
        void pushLayer(Layer*) override;
        void pushOverlay(Layer*) override;
    private:
        std::shared_ptr<IWindow> m_window;
        std::shared_ptr<IGui> m_gui;
        std::shared_ptr<LayerStack> m_layerStack;
        std::atomic_flag m_isRunning = false;
    private:
        bool onWindowClose(events::WindowCloseEvent& event);
    };

}

#endif //AZATHOTH_APPLICATION_HPP
