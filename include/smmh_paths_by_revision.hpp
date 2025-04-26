#pragma once
#include <revision_checker.hpp>
#include <cstdio>

using namespace std;

namespace smmh_paths_by_revision{
    const string relative_path = "Smmh";

    string revision_string(revision_checker::file_header_info fhi);

    string game(revision_checker::file_header_info fhi);
}
