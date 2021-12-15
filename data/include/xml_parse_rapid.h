#pragma once
#include "voc_xml_data_model.h"
#include<string>
namespace
{

    class XmlParseRapid
    {
    private:
    Annotation annotation;

    public:
        XmlParseRapid(/* args */);
        ~XmlParseRapid();
        void parse(std::string path);
    };

}