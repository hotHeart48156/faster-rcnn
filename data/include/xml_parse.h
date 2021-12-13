#include <expat.h>
namespace{

class XmlParse
{
private:
    const char* path="";
public:
    XmlParse(const char* path);
    void parse();
   
};


}