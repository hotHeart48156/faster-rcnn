#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <refl.hpp>
#include <daw/json/daw_json_link.h>
#include <daw/daw_read_file.h>
struct Object
{
    std::string name;
    float xmax;
    float xmin;
    float ymax;
    float ymin;
    int diffcult;
    int occluded;
    std::string pose;
};
// REFL_AUTO(
//     type(Object), field(name), field(xmin), field(ymax), field(ymin), field(diffcult), field(occluded), field(pose))

bool operator==(Object const &lhs, Object const &rhs)
{
    // return lhs.name == rhs.name 
    // and lhs.xmax==lhs.xmax 
    // and lhs.ymax==rhs.ymax
    // and lhs.xmin==rhs.xmin
    // and lhs.ymin==rhs.ymin
    // and lhs.diffcult==rhs.diffcult
    // and lhs.occluded==rhs.occluded
    // and lhs.pose==rhs.pose
    // ;
    return std::tie(lhs.diffcult,lhs.name,lhs.xmax,lhs.xmin,lhs.ymax,lhs.ymin,lhs.occluded,lhs.pose)
    ==
    std::tie(rhs.diffcult,rhs.name,rhs.xmax,rhs.xmin,rhs.ymax,rhs.ymin,rhs.occluded,rhs.pose);
}
// namespace daw::json
// {
   
// }

struct ImgSize
{
    float depth;
    float height;
    float width;
};
// REFL_AUTO(
//     type(Size), field(depth), field(height), field(width))
bool operator==(ImgSize const &lhs, ImgSize const &rhs)
{
    return std::tie(lhs.depth,lhs.height,lhs.width)==std::tie(rhs.depth,rhs.height,rhs.width);
}
// namespace daw::json
// {
   
// }
struct Annotation
{
    std::string filename;
    std::string folder;
    std::string occluded;
    std::string pose;
    int diffcult;
    Object object;
    ImgSize size;
    int segmented;
};
bool operator==(Annotation const &lhs, Annotation const &rhs)
{
    return lhs.filename == rhs.filename;
}
namespace daw::json
{
    template <>
    struct json_data_contract<ImgSize>
    {
        static constexpr char const depth[] = "depth";
        static constexpr char const height[] = "height";
        static constexpr char const width[] = "width";

        using type = json_member_list<
            json_number<depth,float>
            ,json_number<height,float>
            ,json_number<width,float>
            >;

        static inline auto to_json_data(ImgSize const &value)
        {
            return std::forward_as_tuple(
                value.depth,
                value.height,
                value.width);
        }
    };
   

    template <>
    struct json_data_contract<Object>
    {
        static constexpr char const name[] = "name";
        static constexpr char const xmax[] = "xmax";
        static constexpr char const xmin[] = "xmin";
        static constexpr char const ymax[] = "ymax";
        static constexpr char const ymin[] = "ymin";
        static constexpr char const diffcult[] = "diffcult";
        static constexpr char const occluded[] = "occluded";
        static constexpr char const pose[] = "pose";
        using type = json_member_list<
            json_string<name>
            ,json_number<xmax,float>
            ,json_number<xmin,float>
            ,json_number<ymax,float>
            ,json_number<ymin,float>
            ,json_number<diffcult,int>
            ,json_number<occluded,int>
            ,json_string<pose>
            >;
        static inline auto to_json_data(Object const &value)
        {
            return std::forward_as_tuple(
                value.name,
                value.diffcult,
                value.occluded);
        }
    };
    
  
    template <>
    struct json_data_contract<Annotation>
    {
        static constexpr char const filename[] = "filename";
        static constexpr char const folder[] = "folder";
        static constexpr char const occluded[] = "occluded";
        static constexpr char const pose[] = "pose";
        static constexpr char const diffcult[] = "diffcult";
        static constexpr char const object[] = "object";
        static constexpr char const segmented[] = "segmented";
        static constexpr char const size[] = "size";


        using type = json_member_list<
            json_string<filename>
            ,json_string<folder>
            ,json_string<occluded>
            ,json_string<pose>
            ,json_number<diffcult,int>
            ,json_class<object,Object>
            ,json_class<size,ImgSize>
            ,json_number<segmented,int>
            >;

        static inline auto to_json_data(Annotation const &value)
        {
            return std::forward_as_tuple(
                value.filename,
                value.folder,
                value.occluded);
        }
    };
}


    
    


// REFL_AUTO(
//     type(Annotation), field(filename), field(folder), field(occluded), field(pose), field(objects), field(segmented), field(filename), field(size))

std::ostream &
operator<<(std::ostream &os, const Annotation &annotation)
{
    return os << "filename: " << annotation.filename << ::std::endl
              << "folder: " << annotation.folder << ::std::endl
            //   << "objects[0].name: " << annotation.object[0].name << ::std::endl
            //   << "objects[0].diffcult:" << annotation.object[0].diffcult << ::std::endl
            //   << "objects[0].occluded:" << annotation.object[0].occluded << ::std::endl
            //   << "objects[0].xmax:" << annotation.object[0].xmax << ::std::endl
            //   << "objects[0].xmin:" << annotation.object[0].xmin << ::std::endl
            //   << "objects[0].ymax:" << annotation.object[0].ymax << ::std::endl
            //   << "objects[0].ymin:" << annotation.object[0].ymin << ::std::endl
              << "occluded:" << annotation.occluded << ::std::endl
              << "segmented:" << annotation.segmented << ::std::endl;
            //   << "size.depth:" << annotation.size.depth << ::std::endl
            //   << "size.height:" << annotation.size.height << ::std::endl
            //   << "size.width:" << annotation.size.width << ::std::endl;
}

