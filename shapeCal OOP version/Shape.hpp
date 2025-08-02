#ifndef SHAPE_HPP
#define SHAPE_HPP

namespace TK 
{

    class Shape
    {
    public:
        virtual float getArea() const = 0;
        /*virtual void printStat() const = 0;*/
    };

};

#endif 