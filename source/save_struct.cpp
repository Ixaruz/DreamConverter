#include <save_struct.hpp>

namespace save_struct
{
    //expect sorted vector
    u16 get_clamped_revision(std::vector<u16> const& vec, u16 revision)
    {
        //clamp to lowest and highest revision
        if (vec.front() > revision) { return vec.front(); }
        if (vec.back() < revision) { return vec.back(); }

        auto it = std::upper_bound(vec.begin(),
                                vec.end(),
                                revision);

        return *(std::prev(it));

    }

    int count_upgrades(std::vector<u16> const& vec, u16 revision_in, u16 revision_out)
    {
        revision_in = get_clamped_revision(vec, revision_in);
        revision_out = get_clamped_revision(vec, revision_out);

        auto it_in = std::find(vec.begin(), vec.end(), revision_in);
        auto it_out = std::find(vec.begin(), vec.end(), revision_out);

        return std::distance(it_in, it_out);
    }

}
