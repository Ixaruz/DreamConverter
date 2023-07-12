#pragma once
#include <file_hash_details.hpp>
#include <map>
#include <algorithm>

class file_hash_info
{
public:
    std::map<u32, file_hash_details*> list;

    file_hash_info(std::vector<file_hash_details*> hashSets) {
        for(file_hash_details *fhd : hashSets) {
            list[fhd->file_size] = fhd;
        }
    }

    file_hash_details* find_file_hash_details(std::string fileName) {
        for (auto it = list.begin(); it != list.end(); ++it)
            if (it->second->file_name == fileName)
                return it->second;

        return nullptr;
    }
};
