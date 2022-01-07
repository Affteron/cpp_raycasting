#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cassert>

//DEBUG
#include <bitset>
#include <sstream>


/**
 * @brief Pack color's RGBA value in HEX value. For example:
 * @param r red channel value
 * @param g green channel value
 * @param b blue channel value
 * @param a alpha channel value
 * @return uint32_t color's value in HEX
 */
uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255) {
    /** 
     * For example:
     * r = 50 << 24 = 0b0000_0000_0000_0000_0000_0000_0011_0010 << 24 = 0b0011_0010_0000_0000_0000_0000_0000_0000 = 0x32000000
     * g = 100 << 16 = 0b0000_0000_0000_0000_0000_0000_0110_0100 << 16 = 0b0000_0000_0110_0100_0000_0000_0000_0000 = 0x00640000
     * b = 200 << 8 = 0b0000_0000_0000_0000_0000_0000_1100_1000 << 8 = 0b0000_0000_0000_0000_1100_1000_0000_0000 = 0x0000C800
     * a = 255 = 0b0000_0000_0000_0000_0000_0000_1111_1111 = 0x000000FF
     * return 0x32000000 + 0x00640000 + 0x0000C800 + 0x000000FF = 0x3264C8FF
     */
    return (r << 24) + (g << 16) + (b << 8) + a;
}

/**
 * @brief Unpack color's HEX value in RGBA value
 * 
 * @param color ref to hex value
 * @param r ref to red channel value
 * @param g ref to green channel value
 * @param b ref to blue channel value
 * @param a ref to alpha channel value
 */
void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) {
    /**
     * For example:
     * color = 0x3264C8FF
     * r = 0x3264C8FF >> 24 & 255 = 0b0011_0010_0110_0100_1100_1000_1111_1111 >> 24 & 0b0000_0000_0000_0000_0000_0000_1111_1111 = 0b0011_0010
     * g = 0x3264C8FF >> 16 & 255 = 0b0011_0010_0110_0100_1100_1000_1111_1111 >> 16 & 0b0000_0000_0000_0000_0000_0000_1111_1111 = 0b0110_0100
     * b = 0x3264C8FF >> 8 & 255 = 0b0011_0010_0110_0100_1100_1000_1111_1111 >> 8 & 0b0000_0000_0000_0000_0000_0000_1111_1111 = 0b1100_1000
     * a = 0x3264C8FF >> 0 & 255 = 0b0011_0010_0110_0100_1100_1000_1111_1111 >> 24 & 0b0000_0000_0000_0000_0000_0000_1111_1111 = 0b1111_1111
     */                             
    r = (color >> 24) & 255;
    g = (color >> 16) & 255;
    b = (color >>8) & 255;
    a = (color >> 0) & 255;
}

/**
 * @brief Save image to PPM (P6) format on disk
 * 
 * @param filename path to output file
 * @param image ref to image's buffer
 * @param w image width 
 * @param h image heigth
 */
void drop_ppm_image(const std::string filename, const std::vector<uint32_t> &image, const size_t w, const size_t h) {
    /**
     * Code of PPM file's example:
     * 
     * P6                       <-- Format (magic number)
     * # Some comment           <-- Comment
     * 3 2                      <-- Image Size (Width&Heigth)
     * 255                      <-- Max color's value
     * !@#$%^&*()_+|{}:"<       <-- Each three symbol equale RGB value.
     */
    assert(image.size() == w * h);
    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << w << " " << h << "\n255\n";
    for (size_t i = 0; i < h * w; i++) {
        uint8_t r, g, b, a;
        unpack_color(image[i], r, g, b, a);
        ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
    }
    ofs.close();
}

int main() {
    // Image width
    const size_t win_w = 512;
    // Image heigth
    const size_t win_h = 512;
    // Image buffer, initialized  to red
    std::vector<uint32_t> framebuffer(win_w*win_h, 255);

    // Fill the screen with color gradient
    for(size_t j = 0; j < win_h; j++) {
        for(size_t i = 0; i < win_w; i++) {
            uint8_t r = 255 * j / float(win_h);
            uint8_t g = 255 * i / float(win_h);
            uint8_t b = 0;
            framebuffer[i + j * win_w] = pack_color(r, g, b);
        }
    }

    drop_ppm_image("./out.ppm", framebuffer, win_w, win_h);

    return 0;
}