#pragma once
#include "voc_xml_data_model.h"
// namespace
// {
    class Parse
    {
    private:
        Annotation annotation;
    public:
        Parse(/* args */);
        ~Parse();
        Annotation parse(std::string path);
    };

// }