namespace save_struct {
    template<class T>
    std::unique_ptr<T> create_save_struct(std::map<u16, std::function<std::unique_ptr<T>(u8*)>> constructors,
                                                u16 revision,
                                                u8* data)
    {
        auto it = constructors.find(revision);
        if (it != constructors.end()) {
            return it->second(data);
        }
        return nullptr; // or throw an exception if type is not found
    }

    template<class T>
    std::unique_ptr<T> get_save_struct(std::map<u16, std::function<std::unique_ptr<T>(u8*)>> constructors,
                                       std::vector<u16> const& revisions,
                                       u8 *data,
                                       u16 revision_in,
                                       u16 revision_out)
    {
        std::unique_ptr<T> save_struct_out = create_save_struct<T>(constructors,
                                                                   get_clamped_revision(revisions, revision_in),
                                                                   data);
        // for loop; count towards 0 (no upgrade/downgrade left to do)
        for(int i = count_upgrades(revisions, revision_in, revision_out);
            i != 0;
            i-=i/std::abs(i)
            )
        {
            //revision_out > revision_in
            if (i > 0)
                save_struct_out = save_struct_out->upgrade();
            else if (i < 0)
                save_struct_out = save_struct_out->downgrade();
        }
        return save_struct_out;
    }
}
