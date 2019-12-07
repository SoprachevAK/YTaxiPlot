//
// Created by Andrei Soprachev on 2019-12-08.
//

#ifndef YANDEXTAXIPLOT_PLOT_HPP
#define YANDEXTAXIPLOT_PLOT_HPP

#include <vector>

#include "../../../../Library/Mobile Documents/com~apple~CloudDocs/Polytech/C++/3Сем/Курсач/YandexTaxiPlot/Primitive/Rect.hpp"
#include "../../../../Library/Mobile Documents/com~apple~CloudDocs/Polytech/C++/3Сем/Курсач/YandexTaxiPlot/Interface/RenderObject.hpp"
#include "PlotLine.hpp"

typedef long long int time_;

//график
class Plot : public RenderObject
{
public:
  Plot(time_ statT, time_ endT, Rect rect);

  void draw() override; //draw plot and all lines

  void setStartTime(time_ t);
  void setEndTime(time_ t);
  void addLine(PlotLine line);
  void changeRect(Rect rect);

private:

  time_ startTime_;
  time_ endTime_;
  std::vector<PlotLine> lines_;
  Rect rect_;
};

#endif //YANDEXTAXIPLOT_PLOT_HPP
