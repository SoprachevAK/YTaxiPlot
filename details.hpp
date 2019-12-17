#ifndef SFMLTEST_DETAILS_HPP
#define SFMLTEST_DETAILS_HPP

#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using point = sf::Vector2<long int>;
using vecPoint = std::vector<point>;
using iteratorVec2li = vecPoint::iterator;

sf::Vector2<long int> getInfo(boost::filesystem::directory_entry &entry);

#endif
