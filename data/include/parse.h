#pragma once
#include "voc_xml_data_model.h"
#include <rttr/type>
#include <optional>
#include<iostream>
#include<rapidxml/rapidxml.hpp>
#include<rapidxml/rapidxml_utils.hpp>
// namespace
// {
class Parse
{
private:
public:
    rttr::type annotation=rttr::type::get_by_name("Annotation");
    Parse(/* args */);
    ~Parse();
    std::optional<Annotation> parse(std::string path);
};
// int parse(std::string path){
//     rapidxml::file<> file(path.c_str());
//     rapidxml::xml_document<> doc;
//     doc.parse<0>(file.data());
//     rapidxml::xml_node<> *root = doc.first_node();
//     Annotation annotation;
//     std::cout<<root->name();
//     annotation.folder=root->first_node("folder")->value();
//     annotation.filename=root->first_node("filename")->value();
//     annotation.segmented=(int)root->first_node("segmented")->value();

//     return 0;
// }
