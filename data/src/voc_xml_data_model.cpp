#include"voc_xml_data_model.h"
#include <rttr/registration>
RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<Object>("Object")
        .constructor<>()
        .property("filename", &Object::name)
        .property("folder", &Object::xmax)
        .property("occluded", &Object::xmin)
        .property("pose", &Object::ymax)
        .property("objects", &Object::ymin)
        .property("diffcult", &Object::diffcult);
    registration::class_<Size>("Size")
        .constructor<>()
        .property("depth", &Size::depth)
        .property("width", &Size::width)
        .property("height", &Size::height);

    registration::class_<Annotation>("Annotation")
        .constructor<>()
        .property("filename", &Annotation::filename)
        .property("folder", &Annotation::folder)
        .property("occluded", &Annotation::occluded)
        .property("size", &Annotation::size)
        .property("objects", &Annotation::objects)
        .property("segmented", &Annotation::segmented)
        .property("occluded", &Annotation::occluded)
        .property("pose", &Annotation::pose);
}