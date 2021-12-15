#include <iostream>
#include <string>
#include <any>
#include <xml_parse.h>
#include <dataset.h>
int main(int argc, char const *argv[])
{
    // char file[] = "/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/Annotations/2010_003970.xml";
    char file[] = "/home/ubuntu/program/faster-rcnn/test.xml";

    XmlParse parse;
    parse.parse(file);
    // std::cout<<annotation.filename;
    return 0;
}
