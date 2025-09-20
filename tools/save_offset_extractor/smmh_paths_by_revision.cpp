#include "smmh_paths_by_revision.hpp"

namespace smmh_paths_by_revision{
    string revision_string(revision_checker::file_header_info fhi) {
        char revision_string[64];
        sprintf(revision_string, "%d_%d.byml", fhi.minor, fhi.major);
        return string(revision_string);
    }

    string game(revision_checker::file_header_info fhi) {
        return relative_path + "/S00_" + revision_string(fhi);
    }
}
