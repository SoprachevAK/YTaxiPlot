//
// Created by Andrei Soprachev on 2019-12-08.
//

#ifndef YANDEXTAXIPLOT_CANVAS_HPP
#define YANDEXTAXIPLOT_CANVAS_HPP

#include <vector>
#include "../Interfsaces/RenderObject.hpp"

//это полотно -- текущий экран отрисоваки (вообще их можно нагенерить сколько угодно), их можно включать и выключать
class Canvas
{
public:
  void draw();

  void addRenderObject(RenderObject obj);

  void enable();
  void disable();

private:
  std::vector<RenderObject> objects;
  bool isEnable_;
};

#endif //YANDEXTAXIPLOT_CANVAS_HPP