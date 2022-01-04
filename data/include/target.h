#pragma once
#include "voc_xml_data_model.h"
#include <vector>
struct Target
{
    std::vector<BndBox> boxs_size;
    std::vector<double> areas;

    float** to_number() {
        float** result;
        int i=0;
        for(auto size : boxs_size){
            float size[]={size.xmax,size.xmin,size.ymax,size.ymin};
            result[i]=size;
            
        }
    }
    Target number_to_target(**float numbers) {}
};
