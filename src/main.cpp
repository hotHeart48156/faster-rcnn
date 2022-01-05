// #include <voc_xml_data_model.h>
// #include <parse.h>
#include <iostream>
// #include "file_spilit.h"
#include <torch/torch.h>
#include<vector>
// #include<ten>
// #include<tensorflow/c/tf_tensor.h>
// #include<tensorflow/core/platform/>
int main(int argc, char const *argv[])
{

    // int64_t * tt;
    // tt[0]=1;
    // tt[1]=2;
    // int64_t tt[10]={1,2,3,4,5,6,};
    std::vector<int64_t> tt = {
        1,
        2,
        3,
        4,
        5,
        6,
    };
    struct test{
        int a,b;
    };
    test t={1,2};
    std::vector<torch::Tensor> tensor_arrary={torch::tensor(1,torch::kInt64),torch::tensor(2,torch::kInt64)};
    auto d = torch::from_blob(tensor_arrary.data(), {2}, torch::kInt64);
    auto c = torch::randn({1, 100});
    std::cout << d<<" tt "<<d[0];
    // Parse parse;
    // auto result = parse.parse("/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/Annotations/2008_002037.xml");
    // if (result.has_value())
    // {
    //     std::cout <<result.value();
    // }
    // return 0;

    // SpiliFiles spilit("/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/Annotations/","/home/ubuntu/program/faster-rcnn/");
}
