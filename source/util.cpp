#include <util.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace util {
	void set_bit(void *buffer, int bit_offset, bool value) {
		if((*((char *)buffer + bit_offset / 8) >> (bit_offset % 8) & 1) != value)
			*((char *)buffer + bit_offset / 8) ^= 1 << (bit_offset % 8);
	}

    void read_32(ifstream &file, u32 offset, u32 &value) {
        file.seekg(offset, ios::beg);
        file.readsome((char *)&value, sizeof(u32));
    }

	void read_32(void *buffer, u32 offset, u32 &value){
		read_data(buffer, offset, &value, sizeof(u32));
	}

    void write_32(ofstream &file, u32 offset, u32 value) {
        file.seekp(offset, ios::beg);
        file.write((char *)&value, sizeof(u32));
    }

	void write_32(void *buffer, u32 offset, u32 value){
		write_data(buffer, offset, &value, sizeof(u32));
	}

    void read_data(ifstream &file, u32 offset, void *value, u32 size) {
		if(value != nullptr) {
			file.seekg(offset, ios::beg);
			file.readsome((char *)value, size);
		}
    }

	void read_data(void *buffer, u32 offset, void *value, u32 size) {
		memcpy(value, (char *)buffer + offset, size);
    }

    void write_data(ofstream &file, u32 offset, void *value, u32 size) {
		if(value != nullptr) {
			file.seekp(offset, ios::beg);
			file.write((char *)value, size);
		}
    }

	void write_data(void *buffer, u32 offset, void *value, u32 size) {
		memcpy((char *)buffer + offset, value, size);
    }

	string get_folder_name(fs::path path)
	{
		if(fs::is_directory(path)){
			return path.generic_string().substr(path.generic_string().find_last_of('/') + 1);
		}
		return path.parent_path().generic_string().substr(path.parent_path().generic_string().find_last_of('/') + 1);
	}
}