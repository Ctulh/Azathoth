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

        virtual void setUniformMatrix4f(std::string const&, const float*) {}
        virtual void setUniformVec3f(std::string const&, const float*) {}
        virtual void setUniformVec4f(std::string const&, const float*) {}
    };

}

#endif //AZATHOTH_ISHADER_HPP
