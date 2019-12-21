#include <iostream>
#include "plot.hpp"

const int offsetTop = 100;
const int offsetBotton = 50;

int maxX = 0;
int maxY = 0;
int minX = 0;
int minY = 0;

sf::CircleShape circle;
sf::Text priceText;
sf::Text dateText;
const int circleR = 10;

Plot::Plot(vecPoint &points, int width, int height) :
  points_(points),
  width_(width),
  height_(height),
  scale_(4)
{
  window_ = new sf::RenderWindow(sf::VideoMode(width_, height_), "Price plot");

  maxX = points_.back().x;
  minX = points_.front().x;

  maxY = std::max_element(points_.begin(), points_.end(), [](const point &e1, const point &e2)
  {
    return e1.y < e2.y;
  })->y;

  minY = std::min_element(points_.begin(), points_.end(), [](const point &e1, const point &e2)
  {
    return e1.y < e2.y;
  })->y;

  circle = sf::CircleShape(circleR);
  circle.setFillColor(sf::Color::Red);

  sf::Font font;
  font.loadFromFile("Arial.ttf");
  priceText = sf::Text("-", font);
  priceText.setFillColor(sf::Color::White);

  dateText = sf::Text("-", font);
  dateText.setFillColor(sf::Color::White);
  draw();
}


void Plot::draw()
{

  const float FPS = 60.0f; //The desired FPS. (The number of updates each second).

  sf::Clock clock;

  sf::Event ev;
  while (window_->isOpen())
  {
    //Wait until 1/60th of a second has passed, then update everything.
    if (clock.getElapsedTime().asSeconds() >= 1.0f / FPS)
    {
      update();
      clock.restart();
    } else //Sleep until next 1/60th of a second comes around
    {
      sf::Time sleepTime = sf::seconds((1.0f / FPS) - clock.getElapsedTime().asSeconds());
      sleep(sleepTime);
    }

    //Handle input
    while (window_->pollEvent(ev))
    {
      updateKeyEvent(ev);

    }
  }
}


sf::Vector2f Plot::getMousePos()
{
  auto pos = sf::Mouse::getPosition(*window_);
  auto wSize = window_->getSize();
  return sf::Vector2f{1.0f * pos.x * width_ / wSize.x, 1.0f * pos.y * width_ / wSize.y};
}

sf::Vector2<long> Plot::getIntersect(float pos)
{
  for (int i = 0; i < points_.size(); ++i)
  {
    float p = static_cast<float>(points_.at(i).x - minX) * scale_ * (width_) / (maxX - minX) + offset_;
    if(p > pos)
    {
      return points_.at(i);

    }
  }
  return sf::Vector2<long>(0, -404);
}

void Plot::drawLine()
{
  std::vector<sf::Vertex> mouseMovedLine;

  float posX = getMousePos().x;


  mouseMovedLine.emplace_back(sf::Vector2f(posX, height_ - offsetBotton), sf::Color::Red);
  mouseMovedLine.emplace_back(sf::Vector2f(posX, offsetTop), sf::Color::Red);

  auto intersect = getIntersect(posX);
  int h = height_ - offsetTop - offsetBotton;
  float posY =  -offsetBotton + height_ - static_cast<float>(intersect.y - minY) * h / (maxY - minY);


  priceText.setString(std::to_string((int)intersect.y) + " rub");
  priceText.setPosition(posX - circleR - 30, offsetTop - 50);
  window_->draw(priceText);

  dateText.setString(std::asctime(std::localtime(&intersect.x)));
  dateText.setPosition(posX - circleR - 150, offsetTop - 90);
  window_->draw(dateText);

  circle.setPosition(posX - circleR, posY - circleR);
  window_->draw(circle);
  window_->draw(&mouseMovedLine[0], mouseMovedLine.size(), sf::Lines);
}

void Plot::reDraw()
{
  window_->clear();

  std::vector<sf::Vertex> vertex;

  for (size_t i = 0; i < points_.size() - 1; i++)
  {
    int h = height_ - offsetTop - offsetBotton;

    sf::Vector2f point1;
    point1.x = static_cast<float>(points_.at(i).x - minX) * scale_ * (width_) / (maxX - minX) + offset_;
    point1.y = -offsetBotton + height_ - static_cast<float>(points_.at(i).y - minY) * h / (maxY - minY);
    sf::Vector2f point2;
    point2.x = static_cast<float>(points_.at(i + 1).x - minX) * scale_ * (width_) / (maxX - minX) + offset_;
    point2.y = -offsetBotton + height_ - static_cast<float>(points_.at(i + 1).y - minY) * h / (maxY - minY);

    vertex.emplace_back(point1, sf::Color::Green);
    vertex.emplace_back(point2, sf::Color::Green);
  }
  window_->draw(&vertex[0], vertex.size(), sf::Lines);


  drawLine();


  //window_->draw(&axis[0], axis.size(), sf::Lines);
  window_->display();
}

bool pressedLeft = false;
bool pressedRight = false;
int mouseDelta = 0;
float zoomSpeed = 0.1;

int moveDir()
{
  return pressedLeft ? -1 : pressedRight ? 1 : 0;
}

void onKeyPressed(sf::Event ev)
{
  if (ev.key.code == sf::Keyboard::Key::Right)
    pressedRight = true;
  if (ev.key.code == sf::Keyboard::Key::Left)
    pressedLeft = true;
}

void onKeyReleased(sf::Event ev)
{
  if (ev.key.code == sf::Keyboard::Key::Right)
    pressedRight = false;
  if (ev.key.code == sf::Keyboard::Key::Left)
    pressedLeft = false;
}

void Plot::onMouseWheelMove(sf::Event ev)
{
  mouseDelta += ev.mouseWheel.delta;
}

void Plot::updateKeyEvent(sf::Event ev)

{
  switch (ev.type)
  {
    case sf::Event::KeyPressed:
      onKeyPressed(ev);
      break;
    case sf::Event::KeyReleased:
      onKeyReleased(ev);
      break;
    case sf::Event::MouseWheelMoved:
      onMouseWheelMove(ev);
      break;
    case sf::Event::Closed:
      window_->close();
      break;
  }
}

void Plot::update()
{
  offset_ -= moveDir() * 10;

  if (mouseDelta != 0)
  {
    float scaleAfter = std::clamp(scale_ + mouseDelta * zoomSpeed, 1.0f, 10.0f);
    offset_ += (getMousePos().x - offset_) * ((scale_ * 1.0 / scaleAfter) - 1);
    scale_ = scaleAfter;
    mouseDelta = 0;
  }

  offset_ = std::clamp(offset_, -width_ * (scale_ - 1), .0f);

  reDraw();
}


