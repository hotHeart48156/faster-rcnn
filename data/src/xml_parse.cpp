#include "xml_parse.h"
#include <expat.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
// namespace
// {
// using namespace std;
static void XMLCALL
startElememt(void *data, const XML_Char *element, const XML_Char **attrs)
{
    std::cout << "att" << attrs[0];
    if (!strcmp(element, "filename"))
    {
        std::cout << "att" << attrs[0];
        std::string filename = attrs[3];
        auto file = fopen("./result.txt", "w");
        fwrite(filename.c_str(), filename.length(), 1, file);
        //  annotation.filename = attrs[1];

        // std::wstring cc=filename;
        //  std::cout<<"filename"<<(int *)data;
        // std::cout << attrs[4]<<*attrs;
        // for(std::string cc : attrs[3]){
        //     std::cout<<cc;
        // }
    }
    if (!strcmp(element, "xmax"))
    {
        //  annotation.object.xmax = std::(attrs[4]);
        std::cout << element;
    }
    // if (!strcmp(element, "xmin"))
    // {
    //      annotation.object.xmin = std::stof(attrs[1]);
    // }
    // if (!strcmp(element, "ymax"))
    // {
    //      annotation.object.ymax = std::stof(attrs[1]);
    // }
    // if (!strcmp(element, "ymin"))
    // {
    //      annotation.object.ymin = std::stof(attrs[1]);
    // }
    // if (!strcmp(element, "difficult"))
    // {
    //      annotation.diffcult = std::stoi(attrs[1]);
    // }
    // if (!strcmp(element, "occluded"))
    // {
    //      annotation.occluded = attrs[1];
    // }

    // if (!strcmp(element, "segmented"))
    // {
    //      annotation.segmented = std::stof(attrs[1]);
    // }
    // if (!strcmp(element, "depth"))
    // {
    //      annotation.size.depth = std::stof(attrs[1]);
    // }
    // if (!strcmp(element, "height"))
    // {
    //      annotation.size.height = std::stof(attrs[1]);
    // }
    // if (!strcmp(element, "width"))
    // {
    //      annotation.size.width = std::stof(attrs[1]);
    // }
}
static void XMLCALL
endElement(void *data, const XML_Char *element) {}
void value(void *data, const char *name, int len)
{

    // std::cout<<data<<name<<len;
}
XmlParse::XmlParse()
{
    // XmlParse::parser = XML_ParserCreate("utf-8");
    XML_SetElementHandler(XmlParse::parser, startElememt, endElement);
    XML_SetCharacterDataHandler(XmlParse::parser, value);
}
void XmlParse::parse(const char *path)
{
    std::stringstream xml_content;
    std::fstream file;
    file.open(path);
    xml_content << file.rdbuf();
    auto xml_content_string = xml_content.str();
    auto xml_content_erase_space = xml_content_string.erase(0, xml_content_string.find("\t\n\v\f\r "));
    std::cout << xml_content_erase_space;
    std::string test = "<filename>ggff</filename>";
    int done = 0;
    XML_Parse(XmlParse::parser, test.c_str(), test.length(), 1);
    // std::cout << "done" << done;
}
XmlParse::~XmlParse()
{
    XML_ParserFree(XmlParse::parser);
}
// }
