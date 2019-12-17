#include "details.hpp"
#include <fstream>
#include <stdexcept>

sf::Vector2<long int> getInfo(boost::filesystem::directory_entry &entry)
{
  std::ifstream in(entry.path().string());
  if (!in.is_open())
  {
    throw std::invalid_argument("Incorrect name of file\n");
  }

  sf::Vector2<long int> element;

  in >> element.x;
  in >> element.y;


  return element;
}


