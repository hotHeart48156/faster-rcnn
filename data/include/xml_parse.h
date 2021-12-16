#pragma once
#include <expat.h>
#include <string>
#include<vector>
// #pragma execution_character_set("utf-8")
// namespace
// {
struct Object
{
    std::string name;
    float xmax;
    float xmin;
    float ymax;
    float ymin;
    int diffcult;
    int occluded;
    std::string pose;
};
struct Size
{
    int depth;
    int height;
    int width;
};

struct Annotation
{
    std::string filename;
    std::string folder;
    std::string occluded;
    std::string pose;
    int diffcult;
    std::vector<Object> objects;
    int segmented;
    Size size;
};
static Annotation annotation;

class XmlParse
{
private:
    XML_Parser parser=XML_ParserCreate("UTF-8");;

public:
    XmlParse();
    ~XmlParse();
    void parse(const char *path);
};

// }