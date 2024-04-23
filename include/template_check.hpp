#pragma once
#include <types.hpp>
#include <util.hpp>
#include <revision_checker.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace template_check {

    enum class error {
        none,
        missing_files,
        wrong_revision,
        not_enough_players,
    };

    struct result {
        error error_type;
        string additional_info;
    };
        
    class template_check {
    private:
        fs::path templ_path;
        bool *g_players = nullptr;
        bool personalfound[8] = { false };
        result res = { error::none, "" };
        bool revision_found = false;
        revision_checker::file_header_info _file_header_info;

        void check_players();

    public:
        template_check(filesystem::path template_path, bool* players) {
            templ_path = fs::path(template_path);
            g_players = players;
        }
        
        result check_template_files(bool is_sub_dir = false);
        
        result check_template_files(fs::path file_path, bool is_sub_dir = false);

        revision_checker::file_header_info get_file_header_info() { return _file_header_info;}
    };
}