//
// Created by Andrei Soprachev on 2019-12-10.
//

#ifndef SFMLTEST_PLOT_HPP
#define SFMLTEST_PLOT_HPP

#include <vector>
#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>

struct vector2li
{
  long int x;
  long int y;
};

class Plot
{
public:
  Plot(std::vector<vector2li> points_, sf::Rect<sf::Vector2i> rect_);

private:
  std::vector<sf::Vertex> allLines;

};

#endif //SFMLTEST_PLOT_HPP
