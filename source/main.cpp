#include <iostream>
#include <filesystem>
#include <convert_dream.hpp>

using namespace std;
namespace fs = std::filesystem;

void print_usage()
{
    cout << 
    "Usage: DreamConverter.exe {TemplatePath} {DreamPath}\n"
    ;
}

int main(int argc, char **argv)
{
    
    if(argc != 3) {
        print_usage();
        return 0;
    }

    fs::path template_path(argv[1]);
    fs::path dream_path(argv[2]);

    convert_dream dream_converter(template_path, dream_path);
    //cout << fs::absolute(TemplatePath) << endl << fs::absolute(DreamPath) << endl;

    return 0;
}