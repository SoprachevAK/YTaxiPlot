//
// Created by Andrei Soprachev on 2019-12-08.
//

#ifndef YANDEXTAXIPLOT_PLOTLINE_HPP
#define YANDEXTAXIPLOT_PLOTLINE_HPP

#include <vector>
#include <string>

#include "../../Primitives/Point.hpp"
#include "../../Primitives/Rect.hpp"
#include "../../Interfsaces/RenderObject.hpp"

typedef long long int time_;

//линия на графике
class PlotLine
{
public:
  PlotLine(std::string xName, std::string yName, std::string lineName, int color, std::vector<Point> points);

  void draw(time_ start, time_ end, Rect rect); //нарисовать линию от и до в заданном прямоугольнике

private:
  std::string xName_;
  std::string yName_;
  std::string lineName_;
  int color_;
  std::vector<Point> points_;
};

#endif //YANDEXTAXIPLOT_PLOTLINE_HPP
