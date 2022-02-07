//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_IRENDERER_HPP
#define AZATHOTH_IRENDERER_HPP

namespace renderer {
    class IRenderer {
    public:
        virtual void run() const = 0;
        virtual void stop() const = 0;
    public:
        virtual ~IRenderer() = default;
    };
}

#endif //AZATHOTH_IRENDERER_HPP
