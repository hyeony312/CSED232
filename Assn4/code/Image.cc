#include <iostream>
#include <fstream>
#include <cstdint>
#include "Image.h"


void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst)
{
	dst = Image<RGBf>(src.width(), src.height());
	for(int y = 0; y < src.height(); y++) {
		for(int x = 0; x < src.width(); x++) {
			for(int ch = 0; ch < 3; ch++) {
				dst[y][x][ch] = static_cast<float>(src[y][x][ch]) / 255.0f;
			}
		}
	}
}

void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst)
{
	dst = Image<RGB8b>(src.width(), src.height());
	for(int y = 0; y < src.height(); y++) {
		for(int x = 0; x < src.width(); x++) {
			for(int ch = 0; ch < 3; ch++) {
				dst[y][x][ch] = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, src[y][x][ch] * 255.0f)));
			}
		}
	}
}

#pragma pack(push, 1)
struct BMPFileHeader {
	uint16_t file_type{ 0x4D42 };
	uint32_t file_size{ 0 };
	uint16_t reserved1{ 0 };
	uint16_t reserved2{ 0 };
	uint32_t offset_data{ 0 };
};

struct BMPInfoHeader {
	uint32_t size{ 0 };
	int32_t width{ 0 };
	int32_t height{ 0 };
    uint16_t planes{ 1 };
    uint16_t bit_count{ 0 };
    uint32_t compression{ 0 };
    uint32_t size_image{ 0 };
    int32_t x_pixels_per_meter{ 0 };
    int32_t y_pixels_per_meter{ 0 };
    uint32_t colors_used{ 0 };
    uint32_t colors_important{ 0 };

    // helper function for getting color depth
	uint16_t get_depth() const {
        return static_cast<uint16_t>(bit_count);
    }
};
#pragma pack(pop)

bool load_bmp(const char* path, Image<RGB8b>& img)
{
	std::ifstream file(path, std::ios::binary);
	if(!file) {
		std::cerr << "Error opening file '" << path << "'" << std::endl;
		return false;
	}

	BMPFileHeader bmp_file_header;
	BMPInfoHeader bmp_info_header;

	file.read(reinterpret_cast<char*>(&bmp_file_header), sizeof(bmp_file_header));
	if(bmp_file_header.file_type != 0x4D42) {
		std::cerr << "Error: Invalid file format. Expected BMP." << std::endl;
		return false;
	}

	file.read(reinterpret_cast<char*>(&bmp_info_header), sizeof(bmp_info_header));

	// does not support any other types except for 8-bit BGR
	if(bmp_info_header.bit_count != 24)
		return false;

	// The BMP format requires that the image data is aligned on a 4 byte boundary
	// We will use the width to determine how many bytes are needed to hold one row of the image data
	// We need to add padding bytes to ensure that each row is aligned on a 4 byte boundary
	int padding = (4 - (bmp_info_header.width * bmp_info_header.get_depth() / 8) % 4) % 4;

	// Jump to the beginning of the image data
	file.seekg(bmp_file_header.offset_data, file.beg);

	img = Image<RGB8b>(bmp_info_header.width, bmp_info_header.height);

	int idx = 0;
	for(int y = img.height()-1; y >= 0; y--) { 
		for(int x = 0; x < img.width(); x++) {
			file.read(reinterpret_cast<char*>(&img[y][x].b), 1);
			file.read(reinterpret_cast<char*>(&img[y][x].g), 1);
			file.read(reinterpret_cast<char*>(&img[y][x].r), 1);
		}
		if (padding != 0) {
			file.seekg(padding, std::ios_base::cur);
		}
	}
	return true;
}

bool save_bmp(const char* path, const Image<RGB8b>& img)
{
	// The BMP format requires that the image data is aligned on a 4 byte boundary
	// We will use the width to determine how many bytes are needed to hold one row of the image data
	// We need to add padding bytes to ensure that each row is aligned on a 4 byte boundary
	int padding = (4 - (img.width() * 3) % 4) % 4;

	int data_size = img.height() * (img.width()*3 + padding);
	BMPFileHeader bmp_file_header;
	bmp_file_header.file_type = 0x4D42;
	bmp_file_header.file_size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + data_size;
	bmp_file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

	BMPInfoHeader bmp_info_header;
	bmp_info_header.size = sizeof(BMPInfoHeader);
	bmp_info_header.width = img.width();
	bmp_info_header.height = img.height();
	bmp_info_header.planes = 1;
	bmp_info_header.bit_count = 24;
	bmp_info_header.compression = 0;
	bmp_info_header.size_image = data_size;
	bmp_info_header.x_pixels_per_meter = 0;
	bmp_info_header.y_pixels_per_meter = 0;
	bmp_info_header.colors_used = 0;
	bmp_info_header.colors_important = 0;

	std::ofstream file(path, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file '" << path << "'" << std::endl;
		return false;
	}

	file.write(reinterpret_cast<const char*>(&bmp_file_header), sizeof(bmp_file_header));
	file.write(reinterpret_cast<const char*>(&bmp_info_header), sizeof(bmp_info_header));

	for (int y = bmp_info_header.height - 1; y >= 0; --y) {
		for (int x = 0; x < bmp_info_header.width; ++x) {
			file.write(reinterpret_cast<const char*>(&img[y][x].b), 1);
			file.write(reinterpret_cast<const char*>(&img[y][x].g), 1);
			file.write(reinterpret_cast<const char*>(&img[y][x].r), 1);
		}
		if (padding != 0) {
			file.seekp(padding, std::ios_base::cur);
		}
	}

	return true;
}
