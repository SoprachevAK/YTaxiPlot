//
// Created by Andrei Soprachev on 2019-12-08.
//

#ifndef YTAXIPLOT_TEXT_HPP
#define YTAXIPLOT_TEXT_HPP

#include <string>

#include "../Interfsaces/RenderObject.hpp"
#include "../Primitives/Rect.hpp"


enum align
{
  left,
  center
};

class Text : RenderObject
{
public:
  Text(std::string text, int color = 0, float fontSize = 12, align align = align::left);

  void draw() override;

  float fontSize_;
  int color_;
  std::string text_;
  align align_;

};

#endif //YTAXIPLOT_TEXT_HPP
