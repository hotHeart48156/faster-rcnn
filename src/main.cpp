#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <iostream>
#include <map>
#include <string>
#include<any>
// #include<experimental/any>
void read(rapidxml::xml_node<char> *node)
{
    std::map<char*, std::string> result;
    result.insert("aacc","aacc");
    for (; node != NULL;)
    {
        if (node->first_node() != nullptr)
        {
            node = node->first_node();
        }
    }

    if (node->next_sibling() != nullptr)
    {
        node = node->next_sibling();
    }

    if (node->parent() != nullptr)
    {
        node = node->parent();
    }
}

int main(int argc, char const *argv[])
{
    char *file = "/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/Annotations/2010_003970.xml";
    rapidxml::file<> file_doc(file);
    // std::cout<<doc.data()[0]<<std::endl;
    rapidxml::xml_document<> doc;
    doc.parse<0>(file_doc.data());
    auto node = doc.first_node()->first_node();
    for (auto n = node; n != NULL; n = n->next_sibling())
    {
        std::cout << n->name() << n->value();
    }

    return 0;
}
