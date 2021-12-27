#include <voc_xml_data_model.h>
#include <parse.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    
    Parse parse;
    auto result = parse.parse("/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/Annotations/2008_002037.xml");
    if (result.has_value())
    {
        std::cout <<result.value();
    }
    return 0;
}
