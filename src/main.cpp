#include <iostream>
#include <string>
#include <any>
#include <parse.h>
int main(int argc, char const *argv[])
{
    std::string file = "/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/Annotations/2010_003970.xml";
    Parse parse;
    parse.parse(file);
    return 0;
}
