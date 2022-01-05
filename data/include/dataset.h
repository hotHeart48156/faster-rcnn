#pragma once
#include <string>
#include <torch/torch.h>
#include <vector>
#include"parse.h"
enum Mode
{
    Train,
    Test
};
namespace
{
    using Example=torch::data::Example<torch::Tensor,std::map<std::string,std::string>>;
    struct CovDataset : torch::data::Dataset<CovDataset,torch::data::Example<torch::Tensor,std::map<std::string,std::string>>>
    {
    private:
        torch::Tensor images_;
        torch::Tensor targets_;
        Mode mode_;
        std::string data;
        std::string file_splited_path;
        std::vector<std::string> xml_files_name;
        Parse parse;

    public:
        explicit CovDataset(const std::string data, const std::string file_splited_path, Mode mode = Mode::Train);
        Example get(size_t index) override;
        torch::optional<size_t> size() const override;
        std::pair<torch::Tensor, torch::Tensor> read_data(std::string data_xml_files, const std::string file_splited_path, size_t index);
        // return image and labels
        const torch::Tensor &images() const;
        const torch::Tensor $targets() const;
    };

};