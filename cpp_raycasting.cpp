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
     * r = 0x3264C8FF >> 24 & 255 = 0b0011_0010_0110_0100_1100_1000_1111_1111 >> 24 & 0b0000_0000_0000_0000_0000_0000_1111_1111 = 0b0000_0000_0000_0000_0000_0000_0011_0010
     * g = 0x3264C8FF >> 16 & 255 = 0b0011_0010_0110_0100_1100_1000_1111_1111 >> 16 & 0b0000_0000_0000_0000_0000_0000_1111_1111 = 0b0000_0000_0000_0000_0000_0000_0110_0100
     * b = 0x3264C8FF >> 8 & 255 = 0b0011_0010_0110_0100_1100_1000_1111_1111 >> 8 & 0b0000_0000_0000_0000_0000_0000_1111_1111 = 0b0000_0000_0000_0000_0000_0000_1100_1000
     * a = 0x3264C8FF >> 0 & 255 = 0b0011_0010_0110_0100_1100_1000_1111_1111 >> 24 & 0b0000_0000_0000_0000_0000_0000_1111_1111 = 0b0000_0000_0000_0000_0000_0000_1111_1111
     */                             
    r = (color >> 24) & 255;
    g = (color >> 16) & 255;
    b = (color >>8) & 255;
    a = (color >> 0) & 255;
}

int main() {
    // DEBUG
    int a = 50;
    int pow = 24;
    std::string a_binary = (std::bitset<32>(a)).to_string();
    std::string a_binary_w = (std::bitset<32>(a) << pow).to_string();
    
    unsigned long a_decimal = std::bitset<32>(a_binary).to_ulong();
    unsigned long a_decimal_w = std::bitset<32>(a_binary_w).to_ulong();
    
    std::stringstream ss;
    ss << std::hex << a_decimal_w;
    std::string a_hex (ss.str());

    std::cout << a_binary << std::endl;
    std::cout << a_binary_w << std::endl;
    std::cout << a_decimal << std::endl;
    std::cout << a_decimal_w << std::endl;
    std::cout << a_hex << std::endl;
    // DEBUG

    return 0;
}