#include <random>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
auto files_path = "./VOCdevkit/2012/Annotation";
int ramdom = std::rand();
std::vector<std::string> all_file_name;
std::vector<std::string> train_files;
std::vector<std::string> test_files;

void listAllFile()
{
    for (auto &p : fs::directory_iterator(files_path))
    {
        all_file_name.push_back(p.path().filename());
    }
    
}


int main(int argc, char const *argv[])
{

    return 0;
}
