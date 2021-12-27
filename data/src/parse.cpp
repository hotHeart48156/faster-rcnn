#include "voc_xml_data_model.h"
#include <string>
#include "parse.h"
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <algorithm>
#include <rttr/type>
#include <optional>
#include <iostream>
Parse::Parse() {}
Parse::~Parse() {}

enum NodeType
{
    NEXT_PARENT,
    HAVE_CHILD,
    HAVE_SIBLING,
    END
};

std::pair<rapidxml::xml_node<> *, NodeType> next_node(rapidxml::xml_node<> *root)
{
    auto first_node_name = "";
    try
    {
        first_node_name = root->first_node()->name();
    }
    catch (...)
    {
        first_node_name = "";
    }
    if (std::strcmp(first_node_name, ""))
    {
        // std::cout << root->name() << "have first node" << std::endl;
        root = root->first_node();
        return {root, NodeType::HAVE_CHILD};
    }
    auto next_sibling_name = "";

    try
    {
        if (!(root->next_sibling() == nullptr))
        {
            next_sibling_name = root->next_sibling()->name();
        }
    }
    catch (...)
    {
        next_sibling_name = "";
    }
    if (std::strcmp(next_sibling_name, ""))
    {
        // std::cout << root->name() << "  have sibling" << std::endl;
        root = root->next_sibling();
        return {root, NodeType::HAVE_SIBLING};
    }
    auto next_parent_name = "";
    auto parent_name = "";
    // std::cout << "in parent" << std::endl;

    try
    {
        if (root->parent()->next_sibling() != nullptr)
        {
            next_parent_name = root->parent()->next_sibling()->name();
        }

        parent_name = root->parent()->name();
    }
    catch (...)
    {
        next_parent_name = "";
        parent_name = "next_parent_name";
    }
    if (std::strcmp(parent_name, ""))
    {
        if (root->parent()->next_sibling() != nullptr)
        {
            // std::cout << root->name() << "  have next parent" << root->parent()->next_sibling()->name() << std::endl;
            root = root->parent()->next_sibling();
            return {root, NodeType::NEXT_PARENT};
        }
        // std::cout << root->name() << "have end";
        return {root, NodeType::END};
    }
    return {root, NodeType::END};
}
Object parse_object(std::pair<rapidxml::xml_node<> *, NodeType> node, rttr::type annotation)
{
    assert(!(node.first->name() == "object"));
    node = next_node(node.first);
    rttr::type object = rttr::type::get<Object>();
    rttr::type bndbox = rttr::type::get<BndBox>();
    Object object_ins;
    BndBox bndbox_ins;
    for (; std::strcmp(node.first->name(), "difficult") && !std::strcmp(node.first->parent()->name(), "object");)
    {
        // (node.second == NodeType::NEXT_PARENT
        // std::cout << "object  " << node.first->name() << " " << node.first->value() << std::endl;
        if (!std::strcmp(node.first->name(), "actions"))
        {
            node.first = node.first->next_sibling();
            continue;
        }
        if (!std::strcmp(node.first->name(), "bndbox"))
        {
            // node = next_node(node.first);
            auto result = bndbox.get_property(node.first->name()).set_value(bndbox, std::atof(node.first->value()));
            // std::cout << "set success" << result << bndbox.get_property("xmax").get_value(bndbox).to_string() << bndbox.get_name() << std::endl;
            // std::cout << "bndbox" << node.first->name() << " " << node.first->value() << std::endl;
            node = next_node(node.first);
            bndbox.get_property(node.first->name()).set_value(bndbox_ins, std::atof(node.first->value()));
            // std::cout <<"bndbox"<< node.first->name() << " " << node.first->value() << std::endl;
            node = next_node(node.first);
            bndbox.get_property(node.first->name()).set_value(bndbox_ins, std::atof(node.first->value()));
            // std::cout << node.first->name() << " " << node.first->value() << std::endl;
            node = next_node(node.first);
            bndbox.get_property(node.first->name()).set_value(bndbox_ins, std::atof(node.first->value()));
            // std::cout << "bndbox end" << node.first->name() << " " << node.first->value() << std::endl;
            node = next_node(node.first);
            bndbox.get_property(node.first->name()).set_value(bndbox_ins, std::atof(node.first->value()));
            continue;
        }
        object.get_property(node.first->name()).set_value(object_ins, std::string(node.first->value()));
        node = next_node(node.first);
    }
    node = next_node(node.first);
    object.get_property(node.first->name()).set_value(object_ins, std::string(node.first->value()));

    object_ins.bndbox = bndbox_ins;
    std::cout << "bndbox" << bndbox_ins.xmax << " " << bndbox_ins.xmin << " " << bndbox_ins.ymax << " " << bndbox_ins.ymin;
    // annotation.get_method("insert_object").invoke(annotation.create(), object_ins);
    return object_ins;
}
ImgSize parse_size(std::pair<rapidxml::xml_node<> *, NodeType> node, rttr::type annotation)
{
    assert(!std::strcmp(node.first->name(), "size"));
    node = next_node(node.first);
    ImgSize img_size;
    rttr::type size = rttr::type::get<ImgSize>();
    for (; node.second != NodeType::NEXT_PARENT;)
    {
        size.get_property(node.first->name()).set_value(img_size, std::atof(node.first->value()));
        node = next_node(node.first);
    }
    // annotation.get_method("set_size").invoke(annotation.create(), img_size);
    return img_size;
}
std::optional<Annotation> Parse::parse(std::string path)
{
    rapidxml::file<> file(path.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(file.data());
    Parse::annotation = rttr::type::get_by_name("Annotation");
    rapidxml::xml_node<> *root = doc.first_node();
    Annotation annotation_instance;
    Object object;
    ImgSize size;
    auto result = next_node(root);
    for (; result.second != NodeType::END;)
    {
        if (!std::strcmp(result.first->name(), "object"))
        {
            object = parse_object(result, Parse::annotation);
        }
        if (!std::strcmp(result.first->name(), "size"))
        {
            size = parse_size(result, Parse::annotation);
        }
        if (!std::strcmp(result.first->name(), "source"))
        {
            result.first = result.first->next_sibling();
            continue;
        }

        annotation.get_property(result.first->name()).set_value(annotation_instance, std::string(result.first->value()));
        result = next_node(result.first);
        if (object.name != "")
        {
            annotation_instance.objects.push_back(object);
        }
        if (size.depth > 0)
        {
            annotation_instance.size = size;
        }
    }
    return annotation_instance;
    // return cc.convert<rttr::type::get_by_name("Annotation")>();
}
