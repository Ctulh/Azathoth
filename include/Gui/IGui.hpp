//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IGUI_HPP
#define AZATHOTH_IGUI_HPP

#include <memory>

namespace gui {

    class IGui {
    public:
        virtual bool isInited() = 0;
        virtual void setWindow(std::shared_ptr<void> window) = 0;
        virtual void draw() = 0;
    public:
        virtual ~IGui() = default;
    };

}

#endif //AZATHOTH_IGUI_HPP
