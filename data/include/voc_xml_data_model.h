#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <rttr/registration>
#include <vector>
#include <rttr/type>
// #include<rtt>
struct BndBox
{
    double xmax;
    double xmin;
    double ymax;
    double ymin;

    RTTR_ENABLE()
};
BndBox get_bndbox_instance(rttr::type type_box, bool &ok)
{
    BndBox box;
    box.xmax = type_box.get_property_value("xmax").to_double();
    box.xmin = type_box.get_property_value("xmin").to_double();
    box.ymax = type_box.get_property_value("ymax").to_double();
    box.ymin = type_box.get_property_value("ymin").to_double();
    ok = true;
    return box;
}
bool operator==(BndBox const &lhs, BndBox const &rhs)
{
    return std::tie(lhs.xmax, lhs.xmin, lhs.ymax, lhs.ymin) ==
           std::tie(rhs.xmax, rhs.xmin, rhs.ymax, rhs.ymin);
}

struct Object
{
    std::string name;
    std::string diffcult;
    std::string occluded;
    BndBox bndbox;
    std::string pose;
    void set_bndbox(BndBox box)
    {
        bndbox = box;
        std::cout << "set_bndbox invoke" << box.xmax << " " << box.xmin;
    }
    RTTR_ENABLE()
};
Object get_object_instance(rttr::type type_object, bool &ok)
{
    Object object;
    object.name = type_object.get_property_value("name").to_string();
    object.diffcult = type_object.get_property_value("diffcult").to_int();
    object.occluded = type_object.get_property_value("occluded").to_int();
    // object.bndbox = get_bndbox_instance(type_object.get_property("bndbox"));
    object.name = type_object.get_property_value("name").to_string();
    ok = true;
    return object;
}
// REFL_AUTO(
//     type(Object), field(name), field(xmin), field(ymax), field(ymin), field(diffcult), field(occluded), field(pose))

bool operator==(Object const &lhs, Object const &rhs)
{
    return std::tie(lhs.diffcult, lhs.name, lhs.occluded, lhs.pose) ==
           std::tie(rhs.diffcult, rhs.name, rhs.occluded, rhs.pose);
}

struct ImgSize
{
    double depth;
    double height;
    double width;
    RTTR_ENABLE()
};
ImgSize get_imgsize_instance(rttr::variant v_size, bool &ok)
{
    ImgSize size;
    std::cout<<"cover oopp";

    // size.depth = v_imgsize.get_type().get_property_value("depth").to_double();
    // size.height = v_imgsize.get_type().get_property_value("height").to_double();
    // size.width = v_imgsize.get_type().get_property_value("width").to_double();
    ok = true;
    return size;
}
// REFL_AUTO(
//     type(Size), field(depth), field(height), field(width))
bool operator==(ImgSize const &lhs, ImgSize const &rhs)
{
    return std::tie(lhs.depth, lhs.height, lhs.width) == std::tie(rhs.depth, rhs.height, rhs.width);
}

struct Annotation
{
    std::string filename;
    std::string folder;
    std::string occluded;
    std::string pose;
    int diffcult;
    std::vector<Object> objects;
    ImgSize size;
    int segmented;
    Annotation *get_instance()
    {
        std::cout << "get_instance invoke";
        return this;
    }
    void insert_object(Object object)
    {
        std::cout << "insert object invoke";
        objects.push_back(object);
    }
    void set_size(ImgSize img_size)
    {
        std::cout << "set size invoke";
        size = img_size;
    }

    RTTR_ENABLE()
};
Annotation get_annotation_instance(rttr::type type_annotation, bool &ok)
{
    Annotation annotation;
    annotation.folder = type_annotation.get_property_value("folder").to_string();
    annotation.filename = type_annotation.get_property_value("filename").to_string();
    annotation.occluded = type_annotation.get_property_value("occluded").to_string();
    annotation.pose = type_annotation.get_property_value("pose").to_string();
    annotation.segmented = type_annotation.get_property_value("segmented").to_int();
    annotation.folder = type_annotation.get_property_value("folder").to_string();
    ok = true;
    return annotation;
}
bool operator==(Annotation const &lhs, Annotation const &rhs)
{
    return lhs.filename == rhs.filename;
}

RTTR_REGISTRATION
{
    rttr::type::register_converter_func(get_bndbox_instance);
    rttr::type::register_converter_func(get_imgsize_instance);
    rttr::type::register_converter_func(get_object_instance);
    rttr::type::register_converter_func(get_annotation_instance);

    rttr::registration::class_<BndBox>("BndBox")
        .constructor<>()
        .property("xmax", &BndBox::xmax)
        .property("ymax", &BndBox::ymax)
        .property("xmin", &BndBox::xmin)
        .property("ymin", &BndBox::ymin);
    rttr::registration::class_<Object>("Object")
        .constructor<>()
        .property("name", &Object::name)
        .property("pose", &Object::pose)
        .property("diffcult", &Object::diffcult)
        .property("bndbox", &Object::bndbox)
        .method("set_bndbox", &Object::set_bndbox);

    rttr::registration::class_<ImgSize>("ImgSize")
        .constructor<>()
        .property("depth", &ImgSize::depth)
        .property("width", &ImgSize::width)
        .property("height", &ImgSize::height);
    rttr::registration::class_<Annotation>("Annotation")
        .constructor<>()
        .property("filename", &Annotation::filename)
        .property("folder", &Annotation::folder)
        .property("objects", &Annotation::objects)
        .property("size", &Annotation::size)
        .property("segmented", &Annotation::segmented)
        .property("diffcult", &Annotation::diffcult)
        .property("occluded", &Annotation::occluded)
        .method("get_instance", &Annotation::get_instance)
        .method("insert_object", &Annotation::insert_object)
        .method("set_size", &Annotation::set_size);
}

std::ostream &
operator<<(std::ostream &os, const Annotation &annotation)
{
    return os << "filename: " << annotation.filename << ::std::endl
              << "folder: " << annotation.folder << ::std::endl
              << "objects[0].name: " << annotation.objects[0].name << ::std::endl
              << "objects[0].diffcult:" << annotation.objects[0].diffcult << ::std::endl
              << "objects[0].xmax:" << annotation.objects[0].bndbox.xmax << ::std::endl
              << "objects[0].xmin:" << annotation.objects[0].bndbox.xmin << ::std::endl
              << "objects[0].ymax:" << annotation.objects[0].bndbox.ymax << ::std::endl
              << "objects[0].ymin:" << annotation.objects[0].bndbox.ymin << ::std::endl
              << "occluded:" << annotation.occluded << ::std::endl
              << "segmented:" << annotation.segmented << ::std::endl
              << "size.depth:" << annotation.size.depth << ::std::endl
              << "size.height:" << annotation.size.height << ::std::endl
              << "size.width:" << annotation.size.width << ::std::endl;
}
