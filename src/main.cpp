#include<iostream>
#include<torch/torch.h>
#include<torchvision/models/alexnet.h>
#include<expat.h>
#include<dataset.h>
int main(int argc, char const *argv[])
{
    torch::Tensor tensor=torch::rand({4,6});
    std::cout<<tensor;
    return 0;
    

}
