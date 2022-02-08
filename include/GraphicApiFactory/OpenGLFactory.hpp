//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_OPENGLFACTORY_HPP
#define AZATHOTH_OPENGLFACTORY_HPP

#include "IGraphicApiFactory.hpp"
#include "Window/OpenGLWindow.hpp"

namespace graphicApiFactory {

    using window::OpenglWindow;
    using window::IWindow;


    class OpenGLFactory: public IGraphicApiFactory<OpenglWindow::windowType>{
    private:
        using returnedWindowType = IWindow<OpenglWindow::windowType>;
    public:
        using windowInstantiationType = OpenglWindow::windowType;
        std::shared_ptr<returnedWindowType> createWindow() const override {
            return std::make_shared<OpenglWindow>();
        }
    };

}

#endif //AZATHOTH_OPENGLFACTORY_HPP
