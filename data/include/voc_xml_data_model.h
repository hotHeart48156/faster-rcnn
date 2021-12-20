#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <rttr/registration>
#include <rttr/type>
using namespace std;
using namespace rttr;
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
    RTTR_ENABLE();
    // RTTR_REGISTRATION_FRIEND;
};

// std::ostream &
// operator<<(std::ostream &os, const Annotation &annotation)
// {
//     return os << "filename: " << annotation.filename << std::endl
//               << "folder: " << annotation.folder << endl
//               << "objects[0].name: " << annotation.objects[0].name << endl
//               << "objects[0].diffcult:" << annotation.objects[0].diffcult << endl
//               << "objects[0].occluded:" << annotation.objects[0].occluded << endl
//               << "objects[0].xmax:" << annotation.objects[0].xmax << endl
//               << "objects[0].xmin:" << annotation.objects[0].xmin << endl
//               << "objects[0].ymax:" << annotation.objects[0].ymax << endl
//               << "objects[0].ymin:" << annotation.objects[0].ymin << endl
//               << "occluded:" << annotation.occluded << endl
//               << "segmented:" << annotation.segmented << endl
//               << "size.depth:" << annotation.size.depth << endl
//               << "size.height:" << annotation.size.height << endl
//               << "size.width:" << annotation.size.width << endl;
// }