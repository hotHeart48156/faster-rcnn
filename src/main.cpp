#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <iostream>
#include <map>
#include <string>
#include <any>
#include <typeindex>
using namespace std;
std::map<std::string, std::any> result;
// void read(rapidxml::xml_node<char> *node)
// {
//     // result[""][""];

//     // result.insert(std::pair<std::string, std::string>("cs","cs"));
//     for (; node != NULL;)
//     {
//         if (node->first_node() != nullptr)
//         {
//             node = node->first_node();
//             // result.insert(std::pair<string, string>(node->name(), node->value()));
//             insert(node, std::pair<string, string>(node->name(), node->value()));
//             read(node);
//         }

//         if (node->next_sibling() != nullptr)
//         {
//             node = node->next_sibling();
//             insert(node, std::pair<string, string>(node->name(), node->value()));
//             read(node);
//         }

//         if (node->parent() != nullptr)
//         {
//             node = node->parent();
//             insert(node, std::pair<string, string>(node->name(), node->value()));
//             read(node);
//         }
//     }
// }

// void insert(rapidxml::xml_node<char> *node, std::pair<std::any, std::any> data)
// {
//     // rapidxml::xml_node<char> *parent_node;
//     std::vector<std::string> path;

//     for (; node != nullptr;)
//     {
//         if (node->parent() != nullptr)
//         {
//             node = node->parent();
//             path.push_back(node->name());
//         }
//     }

//     for (auto p : path)
//     {
//         if (!result.contains(p))
//         {
//             result.insert(std::pair<std::string, std::any>(p, NULL));
//         }
//     }

//     for (auto p : path)
//     {

//         // auto node = result[p].;
//         if (!result[p].has_value())
//         {
//             // node.insert(data);
//         }
//     }
// }

int main(int argc, char const *argv[])
{
    char file[] = "/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/Annotations/2010_003970.xml";
    rapidxml::file<> file_doc(file);
    // std::cout<<doc.data()[0]<<std::endl;
    rapidxml::xml_document<> doc;
    doc.parse<0>(file_doc.data());
    // auto node = doc.first_node()->first_node();
    // read(doc.first_node());
    return 0;
}
