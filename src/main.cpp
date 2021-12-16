#include <iostream>
#include <string>
#include <any>
// #include <xml_parse_rapid.h>
// #include <dataset.h>
#include<opencv2/core.hpp>
#include<torch/torch.h>
int main(int argc, char const *argv[])
{
    auto tensor=torch::rand({3,3});
    std::cout<<tensor;
    // Annotation annotation;
    // std::string file = "/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/Annotations/2010_003970.xml";
    // XmlParseRapid parse;
    // auto annotation=parse.parse(file);
    // std::cout<<annotation;
    return 0;
}
