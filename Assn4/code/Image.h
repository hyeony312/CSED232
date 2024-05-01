#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include "SharedPtr.h"

///////////////////////////////////////////////////////////////////////////
// RGB pixel type
//    Usage:
//      - RGB<float> rgb(0.5f, 0.1f, 0.3f);
//        rgb[0] = 0.2f; // or equivalently, rgb.r = 0.2f;
template<typename ValType>
struct RGB
{
	union {
		ValType data[3];
		struct {
			ValType r, g, b;
		};
	};

	RGB() {}
	RGB(ValType r_, ValType g_, ValType b_) : r(r_), g(g_), b(b_) {}

	ValType operator[](int idx) const { return data[idx]; }
	ValType& operator[](int idx) { return data[idx]; }
};

typedef RGB<uint8_t>	RGB8b;
typedef RGB<float>		RGBf;


///////////////////////////////////////////////////////////////////////////
// Image class template
//
template<typename PixelType>
class Image
{
private:
    size_t m_width;     // 이미지의 너비
    size_t m_height;    // 이미지의 높이
    SharedArray<PixelType> m_buff;    // 동적으로 할당되는 이미지 데이터

public:
    ////////////////////////////////////////////
    // constructors & destructor
    ////////////////////////////////////////////

    Image() : m_width(0), m_height(0) {}
    Image(size_t width, size_t height) : m_width(width), m_height(height)
    {
        m_buff = SharedArray<PixelType>(new PixelType[m_width * m_height]);
    }
    Image(size_t width, size_t height, const PixelType& val) : Image(width, height)
    {
        for (int i = 0; i < m_height; i++) {
            for (int j = 0; j < m_width; j++) {
                int index = i * m_width + j;
                m_buff[index] = val;
            }
        }
    }
    Image(const Image<PixelType>& img) : m_width(img.m_width), m_height(img.m_height)
    {
        m_buff = SharedArray<PixelType>(new PixelType[m_width * m_height]);

        for (int i = 0; i < m_height; i++) {
            for (int j = 0; j < m_width; j++) {
                int index = i * m_width + j;
                m_buff[index]= img.m_buff[index];
            }
        }
    }

    ~Image() {}

    ////////////////////////////////////////////
    // assignment operator
    ////////////////////////////////////////////

    // 대입 연산자 (같은 픽셀 타입을 사용하는 이미지 객체로부터 대입받는 연산자)
    Image<PixelType>& operator=(const Image<PixelType>& other)
    {
        if (this != &other) {
            m_width = other.m_width;
            m_height = other.m_height;

            m_buff = SharedArray<PixelType>(new PixelType[m_width * m_height]);
            for (int i = 0; i < m_height; i++) {
                for (int j = 0; j < m_width; j++) {
                    int index = i * m_width + j;
                    m_buff[index] = other.m_buff[index];
                }
            }
        }
        return *this;
    }

    ////////////////////////////////////////////
    // element access operators
    ////////////////////////////////////////////

    PixelType* operator[](int y) { return &m_buff[y * m_width]; }
    const PixelType* operator[](int y) const { return &m_buff[y * m_width]; }

    ////////////////////////////////////////////
    // other methods
    ////////////////////////////////////////////

    // 이미지의 가로 길이 반환
    size_t width() const { return m_width; }

    // 이미지의 세로 길이 반환
    size_t height() const { return m_height; }
};


// ======= ADD CODE HERE IF NEEDED =========


// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst);
void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst);

bool load_bmp(const char* path, Image<RGB8b>& img);
bool save_bmp(const char* path, const Image<RGB8b>& img);

#endif
