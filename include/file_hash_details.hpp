#pragma once
#include <file_hash_region.hpp>
#include <string>
#include <vector>

class file_hash_details
{
public:
    std::string file_name;
    u32 file_size;
    u32 FileSize;
    std::vector<file_hash_region*> hash_regions;

    file_hash_details(std::string fileName, u32 fileSize, std::vector<file_hash_region*> regions) : file_name(fileName), file_size(fileSize), hash_regions(regions)
    {}
};
