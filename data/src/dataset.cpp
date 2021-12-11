#include"dataset.h"
#include <torch/serialize/input-archive.h>
#include<expat.h>
namespace {
    constexpr int KTrainSize=200;
    constexpr int KTestSize=200;
    constexpr int KRows=300;
    constexpr int KCol=300;

    // torch::Tensor CVtoTensor(){}
    std::pair<torch::Tensor,torch::Tensor> read_data(const std::string &root,bool train){

    }
    // CovDataset::CovDataset(const std::string &root, Mode mode = Mode::Train){
    //  auto data=read_data(root,mode=Mode::Train);
    //  auto image=std::move(data.first);
    //  auto targets=std::move(data.second);
    // }

//    torch::data::Example<> CovDataset::get(size_t index){

//    }
   
}
