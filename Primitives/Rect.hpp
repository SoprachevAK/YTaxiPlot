//
// Created by Andrei Soprachev on 2019-12-08.
//

#ifndef YANDEXTAXIPLOT_RECT_HPP
#define YANDEXTAXIPLOT_RECT_HPP

#include "Point.hpp"

//прямоугольник
class Rect
{
  Rect(Point ld, Point ru);
  Rect(int xd, int yd, int xu, int yu);

  Point ld; //left down
  Point ru; //right up

};

#endif //YANDEXTAXIPLOT_RECT_HPP
