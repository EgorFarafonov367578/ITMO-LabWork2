#pragma once
#include <cinttypes>
#include <iostream>



struct uint2022_t {
    // implement
private:
    uint8_t arr[253];
public:
    uint8_t get(int place) const {
        if ((arr[place / 8] & (1 << (place % 8))) != 0) {
            return 1;
        } else {
            return 0;
        }
    }
    void put(int place, uint8_t value) {
        arr[place / 8] = arr[place / 8] & (255 - (1 << (place % 8)));
        arr[place / 8] = arr[place / 8] | (value << (place % 8));
    }
    uint2022_t() {
        for (int i = 0; i < 253; i++)
        {
            arr[i] = 0;
        }
    }
    uint2022_t(const uint2022_t& ob)
    {
        for (int i = 0; i < 253; i++)
        {
            arr[i] = ob.arr[i];
        }
    }
    void operator=(const uint2022_t& ob)
    {
        for (int i = 0; i < 253; i++)
        {
            arr[i] = ob.arr[i];
        }
    }
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator >= (const uint2022_t& lhs, const uint2022_t& rhs);

bool operator <= (const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
