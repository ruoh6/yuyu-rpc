#ifndef UNIQUE_ID_H
#define UNIQUE_ID_H

#include <cstdint>
#include <string>

namespace yuyu {
    namespace _detail {
        constexpr unsigned char encoding_table[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0,
            0, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
            26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 0, 0, 0, 0, 37,
            0, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
            53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 0, 0, 0, 0, 0 };

        constexpr char decoding_table[] = 
            " 0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ_"
            "abcdefghijklmnopqrstuvwxyz";

        constexpr uint64_t next_interim(uint64_t current, size_t char_code) {
            return (current << 6) | encoding_table[(char_code <= 0x7F) ? char_code : 0];
        }

        constexpr uint64_t atom_val(const char* cstr, uint64_t interim = 0xF) {
            return (*cstr == '\0') ?
                interim:
                atom_val(cstr + 1,
                        next_interim(interim, static_cast<size_t>(*cstr)));

        }
    }

    template<size_t Size>
    constexpr uint64_t UniqueId(char const (&str)[Size]) {
        static_assert(Size <= 11, "only 10 characters are allowed");
        return static_cast<uint64_t>(_detail::atom_val(str));
    }

    inline std::string DecodeUniqueId(const uint64_t x) {
        std::string result;
        result.reserve(11);
        bool read_chars = ((x & 0xF00000000000000) >> 60) == 0xF;
        uint64_t mask = 0xFC0000000000000;
        for (int bitshift = 54; bitshift >= 0; bitshift -= 6, mask >>= 6) {
            if (read_chars)
                result += _detail::decoding_table[(x & mask) >> bitshift];
            else if (((x & mask) >> bitshift) == 0xF)
                read_chars = true;
        }

        return result;
    }
}
#endif
