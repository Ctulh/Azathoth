//
// Created by egor on 2/10/22.
//

#ifndef AZATHOTH_GRAPHICSCONTEXTOPENGL_HPP
#define AZATHOTH_GRAPHICSCONTEXTOPENGL_HPP

#include "Renderer/IGraphicsContext.hpp"
struct GLFWwindow;

namespace renderer {

    class GraphicsContextOpenGL: public IGraphicsContext {
    public:
        GraphicsContextOpenGL(std::shared_ptr<GLFWwindow>);
        void init() override;
        void swapBuffers() override;
    private:
        std::shared_ptr<GLFWwindow> m_window;
    };

}

#endif //AZATHOTH_GRAPHICSCONTEXTOPENGL_HPP
