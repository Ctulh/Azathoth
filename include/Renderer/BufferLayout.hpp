//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_BUFFERLAYOUT_HPP
#define AZATHOTH_BUFFERLAYOUT_HPP

#include <vector>
#include <string>
#include <cstdint>

#include "DebugTools/AzathothAssert.hpp"

namespace renderer {

    enum class ShaderDataType {
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };

    static uint32_t shaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:   return 4;
            case ShaderDataType::Float2:  return 4 * 2;
            case ShaderDataType::Float3:  return 4 * 3;
            case ShaderDataType::Float4:  return 4 * 4;
            case ShaderDataType::Mat3:    return 4 * 3 * 3;
            case ShaderDataType::Mat4:    return 4 * 4 * 4;
            case ShaderDataType::Int:     return 4;
            case ShaderDataType::Int2:    return 4 * 2;
            case ShaderDataType::Int3:    return 4 * 3;
            case ShaderDataType::Int4:    return 4 * 4;
            case ShaderDataType::Bool:    return 1;
        }
        AZATHOTH_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }

    struct BufferElement {
    public:
        BufferElement() {}
        BufferElement(ShaderDataType dataType, std::string const& name_, bool normalized_ = false): type(dataType), name(name_),
        size(shaderDataTypeSize(type)), offset(0), normalized(normalized_) {}

        uint32_t getComponentCount() const {
            switch (type) {
                case ShaderDataType::Float:   return 1;
                case ShaderDataType::Float2:  return 2;
                case ShaderDataType::Float3:  return 3;
                case ShaderDataType::Float4:  return 4;
                case ShaderDataType::Mat3:    return 3 * 3;
                case ShaderDataType::Mat4:    return 4 * 4;
                case ShaderDataType::Int:     return 1;
                case ShaderDataType::Int2:    return 2;
                case ShaderDataType::Int3:    return 3;
                case ShaderDataType::Int4:    return 4;
                case ShaderDataType::Bool:    return 1;
            }
            AZATHOTH_ASSERT(false, "Unknown ShaderDataType");
            return 0;
        }
    public:
        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;
    };

    class BufferLayout {
    public:
        BufferLayout () {}
        BufferLayout(std::initializer_list<BufferElement> const& elements): m_elements(elements) {
            calculateOffsetAndStride();
        }
    public:
        std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

        uint32_t getStride() const { return m_stride; }
        [[nodiscard]] std::vector<BufferElement> const& getElements() const { return m_elements; }
    private:
        void calculateOffsetAndStride() {
            uint32_t offset = 0;
            m_stride = 0;
            for(auto& element: m_elements) {
                element.offset = offset;
                offset += element.size;
                m_stride += element.size;
            }
        }
    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride = 0;
    };

}

#endif //AZATHOTH_BUFFERLAYOUT_HPP
