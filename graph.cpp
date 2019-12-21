#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "details.hpp"
#include "plot.hpp"

const int screenWidth = 1300;
const int screenHeight = 1000;

void graph()
{
  vecPoint vec;

  std::cout << "start\n";

  std::string path = boost::filesystem::current_path().string() + "/snapShot/";
  std::cout << "calculate\n";

  int filesCount = 0;
  int processedFilesCount = 0;
  int tempFile = 0;
  for (auto & entry: boost::filesystem::directory_iterator(path))
  {
    filesCount++;
  }


  for (auto & entry: boost::filesystem::directory_iterator(path))
  {
    if(filesCount / 10.0f < tempFile)
    {
      processedFilesCount += tempFile;
      std::cout << 1.0f * processedFilesCount / filesCount << "\n";
      tempFile = 0;
    }
    tempFile ++;
    point pointFromPath = getInfo(entry);
    if (pointFromPath.x > 10)
    {
      vec.push_back(pointFromPath);
    }
  }

  std::sort(vec.begin(), vec.end(), [](point &elem1, point &elem2)->bool
      {return elem1.x < elem2.x;});


  std::cout << "Enter interpolation step: ";
  size_t step = 10;
  std::cin >> step;
  while (step < 2 || step * 2 > vec.size())
  {
    std::cout << "Error, step must be > 2 and < data size / 2\nEnter interpolation step: ";
    std::cin >> step;
  }

  vecPoint vecForDraw;


  for (size_t i = step; i < vec.size() - step - 1; i++)
  {
    long int sum = 1;
    for (size_t j = i - step; j < i + step; j++)
    {
      sum += vec.at(j).y;
    }
    vecForDraw.emplace_back(vec.at(i - step).x, sum / (step * 2 - 1));
  }
  Plot plot(vecForDraw, screenWidth, screenHeight);
}

