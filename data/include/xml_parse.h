#include <expat.h>
#include <string>
namespace
{
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
        std::string image_name;
        std::string folder;
        Object object;
        int segmented;
        Size size;


    };

    
    
    

    class XmlParse
    {
    private:
        Annotation annotation;
        XML_Parser parser;
    public:
        XmlParse();
        ~XmlParse();
        void parse(const char *path);
    };

}