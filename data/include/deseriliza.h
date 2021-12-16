#pragma once
#include<string>
namespace
{
    class Object;
    


    template<class Object> class A;
    class Deserilize
    {
    private:
    public:
        template<typename Object>
        Deserilize(Object *object,std::string data);
        ~Deserilize();
    };

}
