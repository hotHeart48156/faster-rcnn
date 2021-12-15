#include<string>
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
    Object object;
    int segmented;
    Size size;
};