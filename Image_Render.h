//
// Created by Wheheohu on 5/29/24.
//

#ifndef RT_ONEWEEKEND_IMAGE_RENDER_H
#define RT_ONEWEEKEND_IMAGE_RENDER_H

#include <vector>
#include "RT_Weekend.h"

class Image_Render {
public:
    virtual bool render(const char *filename, uint32_t image_width, uint32_t image_height) const = 0;
};



class BMP_Image_Render : public Image_Render {
public:
    explicit BMP_Image_Render(const std::vector<vec3_color> &framebuffer);

    bool render(const char *filename, uint32_t image_width, uint32_t image_height) const override;

private:
    std::vector<vec3_color>  framebuffer;

};

#endif //RT_ONEWEEKEND_IMAGE_RENDER_H
