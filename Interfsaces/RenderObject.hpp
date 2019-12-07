//
// Created by Andrei Soprachev on 2019-12-08.
//

#ifndef YANDEXTAXIPLOT_RENDEROBJECT_HPP
#define YANDEXTAXIPLOT_RENDEROBJECT_HPP



//от сюда наследуются все отрисовываемые объекты
class RenderObject
{
public:
  virtual void draw();
  bool isEnable_;
};

#endif //YANDEXTAXIPLOT_RENDEROBJECT_HPP
