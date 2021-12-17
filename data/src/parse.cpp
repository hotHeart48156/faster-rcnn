#include "parse.h"
#include <string>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <rapidxml/rapidxml_print.hpp>
#include <rttr/registration>
#include "voc_xml_data_model.h"
// namespace
// {
    Parse::Parse()
    {
    }

    Parse::~Parse()
    {
    }
    enum NodeType
    {
        HaveChild,
        HaveSibling,
        HaveParent
    };
    std::pair<rapidxml::xml_node<char> *, NodeType> search_all(rapidxml::xml_node<char> *node)
    {
        if (node->first_node() != NULL)
        {
            node = node->first_node();
            return {node, NodeType::HaveChild};
        }
        if (node->next_sibling() != NULL)
        {
            node = node->next_sibling();
            return {node, NodeType::HaveSibling};
        }
        if (node->parent() != NULL)
        {
            auto parent_node = node->parent();
            node = node->parent()->next_sibling();
            return {parent_node, NodeType::HaveParent};
        }
    }

    rttr::type handle_object(rttr::type *annotation, std::pair<rapidxml::xml_node<char> *, NodeType> node_type, rapidxml::xml_node<char> *root_node)
    {
        auto object_property = annotation->get_property(node_type.first->name());
        auto object = rttr::type::get<Object>();
        while (object_property && node_type.second != NodeType::HaveParent)
        {
            node_type = search_all(root_node);
            auto object_property = object.get_property(node_type.first->name());
            if (object_property)
            {
                object_property.set_value(object, node_type.first->value());
            }
        }
        return object;
    }
    rttr::type handle_size(rttr::type *annotation, std::pair<rapidxml::xml_node<char> *, NodeType> node_type, rapidxml::xml_node<char> *root_node)
    {
        auto size_property = annotation->get_property(node_type.first->name());
        auto size = rttr::type::get<Size>();
        while (size_property && node_type.second != NodeType::HaveParent)
        {
            node_type = search_all(root_node);
            auto size_property = size.get_property(node_type.first->name());
            if (size_property)
            {
                size_property.set_value(size, node_type.first->value());
            }
        }
        return size;
    }
    void Parse::parse(std::string path)
    {
        auto xml_content = rapidxml::file(path.c_str());
        rapidxml::xml_document<> xml_document;
        xml_document.parse<0>(xml_content.data());
        auto root_node = xml_document.first_node();
        rttr::type annotation = rttr::type::get<Annotation>();
        for (; root_node != NULL;)
        {
            auto node_type = search_all(root_node);
            auto property = annotation.get_property(node_type.first->name());
            if (property)
            {
                if (property.get_name() == "object")
                {
                    auto object = handle_object(&annotation, node_type, root_node);
                    property.set_value(annotation, object);
                }
                if (property.get_name() == "size")
                {
                    auto size = handle_size(&annotation, node_type, root_node);
                    property.set_value(annotation, size);
                }

                property.set_value(annotation, node_type.first->value());
            }
        }
    }
// }