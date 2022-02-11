//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_ISHADER_HPP
#define AZATHOTH_ISHADER_HPP

namespace renderer {

    class IShader {
    public:
        ~IShader() = default;
    public:
        virtual void bind() const = 0;
        virtual void unBind() const = 0;
    };

}

#endif //AZATHOTH_ISHADER_HPP
