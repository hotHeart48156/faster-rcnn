#include <voc_xml_data_model.h>
#include <parse.h>
#include <iostream>

// struct test
// {
//     int a, b, c, d;
//     RTTR_ENABLE()
// };
// RTTR_REGISTRATION
// {
//     rttr::registration::class_<test>("test")
//         .constructor<>()
//         .property("a", &test::a)
//         .property("b", &test::b)
//         .property("c", &test::c)
//         .property("d", &test::d);
// }

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
