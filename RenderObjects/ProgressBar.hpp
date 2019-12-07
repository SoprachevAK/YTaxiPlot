//
// Created by Andrei Soprachev on 2019-12-08.
//

#ifndef YANDEXTAXIPLOT_PROGRESSBAR_HPP
#define YANDEXTAXIPLOT_PROGRESSBAR_HPP

#include "../Interfsaces/RenderObject.hpp"
#include "../Primitives/Rect.hpp"

//пример с прогрес баром
class ProgressBar : RenderObject
{
public:
  ProgressBar(Rect rect, int color, float p = 0);

  void draw() override;

  Rect rect_; //где рисовать
  int color_;
  float p_; //процент заполнения
};

#endif //YANDEXTAXIPLOT_PROGRESSBAR_HPP
