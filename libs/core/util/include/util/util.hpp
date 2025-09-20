#pragma once

#include <types.hpp>

#include <filesystem>
#include <fstream>
#include <ctime>
#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <functional>

using namespace std;
namespace fs = std::filesystem;

namespace util
{
    void set_bit(void *buffer, int bit_offset, bool value);

    void read_32(ifstream &file, u64 offset, u32 &value);

    void read_32(void *buffer, u64 offset, u32 &value);

    void write_32(ofstream &file, u64 offset, u32 value);

    void write_32(void *buffer, u64 offset, u32 value);

    void read_data(ifstream &file, u64 offset, void *value, u64 size);

    void read_data(void *buffer, u64 offset, void *value, u64 size);

    void write_data(ofstream &file, u64 offset, void const *value, u64 size);

    void write_data(void *buffer, u64 offset, void const *value, u64 size);

    string get_folder_name(fs::path path);
}
