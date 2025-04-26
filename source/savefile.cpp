#include <savefile.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace savefile {
    bool load_metadata(fs::path dream_path, string &metadata)
    {
        fs::path meta_path = dream_path / "dream_land_meta.json";
        //cout << fs::absolute(meta_path) << endl;
        if(fs::exists(meta_path) && fs::is_regular_file(meta_path)){
            ifstream meta_data_file(meta_path);
            stringstream buffer;
            buffer << meta_data_file.rdbuf();
            metadata = buffer.str();
            meta_data_file.close();
            return true;
        }
        return false;
    }

    u32 read_32_from_metadata(fs::path dream_path, string name){
        string metadata;
        if(load_metadata(dream_path, metadata)) {
            regex rgx("[\'\"]" + name + "[\'\"]: (\\d+)");

            smatch matches;

            if(regex_search(metadata, matches, rgx)) {
                return stoi(matches[1].str());
            }
            else {
                cout << "name not found in metadata" << endl;
            }
        }
        else {
        cout << "metadata not found" << endl;
        }
        return 0;
    }

    string read_string_from_metadata(fs::path dream_path, string name){
        string metadata;
        if(load_metadata(dream_path, metadata)) {
            regex rgx("[\'\"]" + name + "[\'\"]: '([[:graph:]]+)'");

            smatch matches;

            if(regex_search(metadata, matches, rgx)) {
                return matches[1].str();
            }
            else {
                cout << "name not found in metadata" << endl;
            }
        }
        else {
        cout << "metadata not found" << endl;
        }
        return 0;
    }

    size_t read_player_count(fs::path dream_path)
    {
        return (size_t)read_32_from_metadata(dream_path, "mMtPlayerVillagersNum");
    }

    string read_island_name(fs::path dream_path)
    {
        return read_string_from_metadata(dream_path, "mMtVNm");
    }

    bool is_file_size(fs::path file, size_t size)
    {
        return fs::file_size(file) == size;
    }

    void decrypt_pair(fs::path data_path, fs::path header_path, fs::path data_path_out)
    {
        fstream data_file, header_file;

        size_t data_size = fs::file_size(data_path);
        size_t header_size = sizeof(GSaveVersion);
        u8 *data = new u8[data_size];
        GSaveVersion header;

        data_file.open(data_path, ios::in | ios::binary);
        data_file.read((char *)data, data_size);
        data_file.close();

        header_file.open(header_path, ios::in | ios::binary);
        header_file.read((char *)&header, header_size);
        header_file.close();

        SaveCrypto::Crypt(header, data, data_size);

        fstream decrypted_data_file;
        decrypted_data_file.open(data_path_out, ios::out | ios::binary | ios::trunc);
        decrypted_data_file.write((char *)data, data_size);
        decrypted_data_file.close();

        delete data;
    }

    void encrypt_pair(fs::path data_path, fs::path header_path_out, fs::path data_path_out, u32 tick)
    {
        fstream data_file;

        size_t data_size = fs::file_size(data_path);
        size_t header_size = sizeof(GSaveVersion);

        u8 *data = new u8[data_size];
        GSaveVersion header;

        data_file.open(data_path, ios::in | ios::binary);
        data_file.read((char *)data, data_size);
        data_file.close();

        memcpy(&header, data, sizeof(GSaveVersion) - sizeof(header.headerCrypto));

        SaveCrypto::RegenHeaderCrypto(header, tick);
        SaveCrypto::Crypt(header, data, data_size);

        fstream encrypted_data_file, encrypted_header_file;
        encrypted_data_file.open(data_path_out, ios::out | ios::binary | ios::trunc);
        encrypted_data_file.write((char *)data, data_size);
        encrypted_data_file.close();

        encrypted_header_file.open(header_path_out, ios::out | ios::binary | ios::trunc);
        encrypted_header_file.write((char *)&header, header_size);
        encrypted_header_file.close();

        delete data;
    }

    void calc_file_hash(fs::path data_path, u16 revision)
    {
        std::string filename = data_path.filename().generic_string();

        fstream data_file;

        size_t data_size = fs::file_size(data_path);
        u8 *data = new u8[data_size];

        data_file.open(data_path, ios::in | ios::binary);
        data_file.read((char *)data, data_size);
        data_file.close();


        file_hash_details *fhd = revision_checker::hash_info[revision].find_file_hash_details(filename);
        if (fhd != nullptr) {
            for(auto &hashregion : fhd->hash_regions) {
                MurmurHash3::Update(data, hashregion->hash_offset, hashregion->get_begin_offset(), hashregion->size);
            }
        }
        else {
            std::cout << "WARNING: Couldn't find hash details for file \"" << filename << "\"" << std::endl;
        }

        data_file.open(data_path, ios::out | ios::binary | ios::trunc);
        data_file.write((char *)data, data_size);
        data_file.close();
    }

    void decrypt_batch(fs::path in_path, fs::path out_path, bool *g_players)
    {
        // snapshot dir_entries in case in_path and out_path are the same
        std::vector<std::filesystem::path> dir_entries{};
        for (auto const& dir_entry : fs::directory_iterator(in_path))
        {
            dir_entries.push_back(dir_entry.path());
        }
        for (auto const& dir_entry : dir_entries)
        {
            if(fs::is_directory(dir_entry)){
                string folder_name = util::get_folder_name(dir_entry);
                //match the digits in Villager0 to Villager7
                regex rgx("Villager(\\d)");
                smatch matches;
                //if its a player that needs to be dumped
                if(regex_search(folder_name, matches, rgx) && g_players[stoi(matches[1].str())]) {
                    fs::path new_out_path = out_path / folder_name;
                    fs::create_directories(new_out_path);
                    decrypt_batch(dir_entry, new_out_path, g_players);
                }
            }

            else if(dir_entry.extension() == ".dat" && dir_entry.filename().generic_string().find("Header") == string::npos) {
                fs::path data_path(out_path / dir_entry.filename());
                if(dir_entry != data_path) {
                    if (fs::exists(data_path)) {
                        fs::remove(data_path);
                    }
                    fs::copy_file(dir_entry, data_path);
                }
                if(dir_entry.filename() != "landname.dat") {
                    fs::path header_path(in_path / (dir_entry.stem().generic_string() + "Header.dat"));
                    //cout << dir_entry.path().generic_string() << endl;
                    //cout << data_path.generic_string() << endl;
                    if(fs::exists(header_path)){
                        decrypt_pair(dir_entry, header_path, data_path);
                        //if same directory, we need to delete the header file after decryption
                        if(dir_entry == data_path) {
                            fs::remove(header_path);
                        }
                    }
                }
            }
        }
    }

    void encrypt_batch(fs::path in_path, fs::path out_path, u32 tick, u16 revision)
    {
        // snapshot dir_entries in case in_path and out_path are the same
        std::vector<std::filesystem::path> dir_entries{};
        for (auto const& dir_entry : fs::directory_iterator(in_path))
        {
            dir_entries.push_back(dir_entry.path());
        }
        for (auto const& dir_entry : dir_entries)
        {
            if(fs::is_directory(dir_entry)){
                fs::path new_out_path = out_path / util::get_folder_name(dir_entry);
                fs::create_directories(new_out_path);
                encrypt_batch(dir_entry, new_out_path, tick, revision);
            }

            else if(dir_entry.extension() == ".dat" && dir_entry.filename().generic_string().find("Header") == string::npos) {
                fs::path data_path(out_path / dir_entry.filename());
                if(dir_entry != data_path) {
                    if (fs::exists(data_path)){
                        fs::remove(data_path);
                    }
                    fs::copy_file(dir_entry, data_path);
                }
                if(dir_entry.filename() != "landname.dat") {
                    fs::path header_path(out_path / (dir_entry.stem().generic_string() + "Header.dat"));
                    calc_file_hash(data_path, revision);
                    encrypt_pair(data_path, header_path, data_path, tick);
                }
            }
        }
    }

    void check_players(ifstream &dream_file, u32 account_offset, bool *g_players) {
        for (u8 player = 0; player < 8; player++) {
            u64 offset = player * 0x48;
            u128 account_uid = 0;
            util::read_data(dream_file, dream_header_difference + account_offset + offset, &account_uid, 0x10);
            if (account_uid != 0) g_players[player] = true;
        }
    }

    vector<fs::path> get_player_folders(fs::path folder, bool *g_players) {
        vector<fs::path> player_folders;
        for (u8 player = 0; player < 8; player++) {
            if(g_players[player]) {
                player_folders.push_back(fs::path(folder / ("Villager" + to_string(player))));
            }
        }
        return player_folders;
    }

    int check_file_header_info_compatibility(revision_checker::file_header_info info_1, revision_checker::file_header_info info_2){
        int difference = (info_1.major - info_2.major);
        if(difference < 0) return -1;
        if(difference > 0) return 1;
        return 0;
    }
}
