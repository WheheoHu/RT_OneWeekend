//
// Created by Wheheohu on 5/29/24.
//
#include <iostream>
#include <fstream>
#include "Image_Render.h"
#include <spdlog/spdlog.h>


#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType{0x4D42};
    uint32_t bfSize{0};
    uint16_t bfReserved1{0};
    uint16_t bfReserved2{0};
    uint32_t bfOffBits{0};
};

struct BMPInfoHeader {
    uint32_t biSize{0};
    int32_t biWidth{0};
    int32_t biHeight{0};

    uint16_t biPlanes{1};
    uint16_t biBitCount{0};

    uint32_t biCompression{0};
    uint32_t biSizeImage{0};

    int32_t biXPelsPerMeter{0};
    int32_t biYPelsPerMeter{0};

    uint32_t biClrUsed{0};
    uint32_t biClrImportant{0};
};
#pragma pack(pop)

bool BMP_Image_Render::render(const char *filename, uint32_t image_width, uint32_t image_height) const {
    // Ensure framebuffer size matches width and height
    if (framebuffer.size() != static_cast<size_t>(image_width * image_height)) {
        spdlog::error("Framebuffer size does not match specified dimensions.");
        return false;
    }

    std::vector<uint8_t> bmp_pixel_data(image_width*image_height*3);

    // Convert Eigen::Vector3f data to RGB format expected by BMP
    for (int y = 0; y < image_height; ++y) {
        for (int x = 0; x < image_width; ++x) {
            int framebuffer_index = y * image_width + x;
            int bmp_index = ((image_height - 1 - y) * image_width + x) * 3;

            vec3_color color = framebuffer[framebuffer_index];
            bmp_pixel_data[bmp_index] = static_cast<uint8_t>(color.z() ); // B
            bmp_pixel_data[bmp_index + 1] = static_cast<uint8_t>(color.y() ); // G
            bmp_pixel_data[bmp_index + 2] = static_cast<uint8_t>(color.x() ); // R
        }
    }

    // Create BMP file and info headers
    BMPFileHeader fileHeader = {};
    BMPInfoHeader infoHeader = {};

    fileHeader.bfType = 0x4D42; // 'BM'
    fileHeader.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    fileHeader.bfSize = fileHeader.bfOffBits + static_cast<uint32_t>(bmp_pixel_data.size());

    infoHeader.biSize = sizeof(BMPInfoHeader);
    infoHeader.biWidth = image_width;
    infoHeader.biHeight = image_height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 24; // 24 bits per pixel (RGB)
    infoHeader.biCompression = 0; // BI_RGB

    infoHeader.biXPelsPerMeter=2835;
    infoHeader.biYPelsPerMeter=2835;

    infoHeader.biSizeImage = static_cast<uint32_t>(bmp_pixel_data.size());

    std::ofstream file(filename, std::ios_base::binary);
    if (!file) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return false;
    }

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    file.write(reinterpret_cast<const char*>(bmp_pixel_data.data()), bmp_pixel_data.size());



    file.close();

    return true;
}

BMP_Image_Render::BMP_Image_Render(const std::vector<vec3_color> &framebuffer) : framebuffer(framebuffer) {}

