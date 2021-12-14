#include "xml_parse.h"
#include <expat.h>
#include <iostream>
#include <cstring>
namespace
{
    static void XMLCALL
    startElememt(void *data, const XML_Char *element, const XML_Char **attrs)
    {
        
    }
    static void XMLCALL
    endElement(void *data, const XML_Char *element) {}
    void value(void *data, const char *name, int len) {}
    XmlParse::XmlParse()
    {
        XmlParse::parser = XML_ParserCreate(NULL);
        XML_SetElementHandler(parser, startElememt, endElement);
        XML_SetCharacterDataHandler(parser, value);
    }
    void XmlParse::parse(const char *path)
    {

        char data[1024] = {};
        FILE *xml_file = fopen(path, "r");
        size_t len = fread(&data, sizeof(char), 1024, xml_file);
        while (data != NULL && len > 0)
        {
            XML_Parse(parser, data, strlen(data), XML_TRUE);
            size_t len = fread(&data, sizeof(char), 1024, xml_file);
        }
    }
    XmlParse::~XmlParse()
    {
        XML_ParserFree(XmlParse::parser);
    }
}