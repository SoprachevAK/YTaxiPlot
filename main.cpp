#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/filesystem.hpp>


struct vector2li
{
  long int x;
  long int y;
};

float width = 4000;

void draw(std::vector<vector2li> v)
{

  sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

  int maxX = std::max_element(v.begin(), v.end(), [](const vector2li& e1, const vector2li& e2){return e1.x < e2.x;})->x;
  int maxY = std::max_element(v.begin(), v.end(), [](const vector2li& e1, const vector2li& e2){return e1.y < e2.y;})->y;
  int minY = std::min_element(v.begin(), v.end(), [](const vector2li& e1, const vector2li& e2){return e1.y < e2.y;})->y;


  long int startX = v[0].x;
  int deltaX = maxX - startX;
  int deltaY = maxY - minY;

  std::vector<sf::Vertex> vert;
  for (int i = 0; i < v.size() - 1; ++i)
  {

    vert.push_back(sf::Vector2f((v[i].x - startX) * width / deltaX , 1000 - (v[i].y - minY) * 1000/deltaY));
    vert.push_back(sf::Vector2f((v[i + 1].x - startX) * width / deltaX, 1000 - (v[i + 1].y - minY)* 1000/deltaY));

  }

  std::cout << "\n\n";
  for (auto & i : vert)
  {
    //std::cout << i.position.x << " " << i.position.y << "\n";
  }


  std::vector<sf::Vertex> vertToDraw = vert;
  float offset = 0;
  while (window.isOpen())
  {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
      offset -= 1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
      offset += 1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
    {
      width += 1;
      offset -=  offset / width;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
    {
      width -= 1;
      offset += offset / width;
    }




    vert.clear();
    for (int i = 0; i < v.size() - 1; ++i)
    {

      vert.push_back(sf::Vector2f((v[i].x - startX) * width / deltaX + offset, 1000 - (v[i].y - minY) * 1000/deltaY));
      vert.push_back(sf::Vector2f((v[i + 1].x - startX) * width / deltaX + offset, 1000 - (v[i + 1].y - minY)* 1000/deltaY));

    }
    std::vector<sf::Vertex> vertToDraw = vert;



    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();


    window.draw(&vertToDraw[0], vert.size(), sf::Lines);
    window.display();
  }

}


int main()
{
  std::vector<vector2li> t;

  std::string path = boost::filesystem::current_path().string() + "/snapShot/";
  std::cout << path << "\n";
  for (const auto & entry : boost::filesystem::directory_iterator(path))
  {
    //std::cout << entry.path().string() << "\n";
    std::ifstream file(entry.path().string());
    long int time = 0;
    file >> time;
    //std::cout << time << " ";
    int price = 0;
    file >> price;
    //std::cout << price << "\n";

    auto v2li = vector2li{time, price};

    //std::cout << v2li.x << " " << v2li.y  << "\n";
    //std::cout << std::asctime(std::localtime(&time)) << " " << price << "\n";

    if(v2li.x > 10)
      t.push_back(v2li);

    file.close();
  }

  std::sort(t.begin(), t.end(), [](vector2li lhs, vector2li rhs) { return lhs.x < rhs.x;});



  std::vector<vector2li> t2;
  for(int i = 5; i < t.size() - 5; i++)
  {
    long int s = (t.at(i-4).y + t.at(i-3).y + t.at(i-2).y + t.at(i-1).y + t.at(i).y + t.at(i+1).y + t.at(i+2).y + t.at(i+3).y + t.at(i+4).y)/9;
    t2.push_back(vector2li{t.at(i).x, s});
  }


  draw(t);
  draw(t2);
  return 0;
}
