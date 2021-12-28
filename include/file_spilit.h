#include <random>
#include <string>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

std::string vec_to_string(std::vector<std::string> vec)
{
    std::string result;
    for (auto c : vec)
    {
        result.append(c + "\n");
    }
    return result;
}

class SpiliFiles
{
private:
    std::string files_path;
    std::string splited_file_path;
    std::vector<std::string> all_file_name;
    std::vector<std::string> train_files;
    std::vector<std::string> test_files;

    void list_all_file()
    {
        for (auto &p : fs::directory_iterator(files_path))
        {
            all_file_name.push_back(p.path().filename().generic_string());
        }
    }
    void spilit_file()
    {
        list_all_file();
        for (auto file : all_file_name)
        {
            std::rand() % 10 > 3 ? train_files.push_back(file) : test_files.push_back(file);
        }
        std::cout << train_files.size() << " " << test_files.size();
    }

public:
    SpiliFiles(std::string xml_dir, std::string splited_file_path);
    ~SpiliFiles();

    void write_file()
    {
        std::ofstream files;
        files.open(splited_file_path + "train.txt", std::ios_base::out);
        if (files.is_open())
        {
            files << vec_to_string(train_files).data()<<std::endl;
            files.flush();
            files.close();
        }

        files.open(splited_file_path + "test.txt", std::ios_base::out);
        if (files.is_open())
        {
            files << vec_to_string(test_files).data() << std::endl;
        }
    }
};

SpiliFiles::SpiliFiles(std::string xml_dir, std::string splited_file_path)
    : files_path(xml_dir), splited_file_path(splited_file_path)
{
    if (!fs::exists(splited_file_path + "train.txt") && !fs::exists(splited_file_path + "test.txt"))
    {
        spilit_file();
        write_file();
    }
}

SpiliFiles::~SpiliFiles()
{
}
