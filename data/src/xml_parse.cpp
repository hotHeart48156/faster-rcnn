#include "xml_parse.h"
#include <expat.h>
#include <iostream>
#include<cstring>
namespace
{
  
    void start(void *data, const XML_Char *el, const XML_Char **attr)
    {
    }
    void end(void *data, const XML_Char *el) {}
    void value(void *data, const char *name, int len) {}
    XmlParse::XmlParse(const char *path)
    {
        path = path;
    }
    void XmlParse::parse()
    {

        XML_Parser parser = XML_ParserCreate(NULL);
        XML_SetElementHandler(parser, start, end);
        XML_SetCharacterDataHandler(parser, value);
        char data[1024] = {};
        FILE *xml_file = fopen(XmlParse::path, "r");
        size_t len=fread(&data, sizeof(char), 1024, xml_file);
        while (data!=NULL&&len>0)
        {
            XML_Parse(parser,data,strlen(data),XML_TRUE);
            size_t len=fread(&data, sizeof(char), 1024, xml_file);
        }
        XML_ParserFree(parser);
        
    }
}