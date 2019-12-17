#ifndef SFMLTEST_PLOT_HPP
#define SFMLTEST_PLOT_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "details.hpp"

class Plot
{
public:
  Plot(vecPoint &points, int width, int height);

private:
  void draw();
  void drawLine();
  sf::Vector2f getMousePos();
  float getIntersect(float pos);
  void reDraw();
  void updateKeyEvent(sf::Event ev);
  void update();


  void onMouseWheelMove(sf::Event ev);

  float offset_;
  float scale_;
  vecPoint points_;
  int width_;
  int height_;
  sf::RenderWindow *window_;
};

#endif