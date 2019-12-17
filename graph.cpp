#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "details.hpp"
#include "plot.hpp"

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

  vecPoint vecForDraw;

  size_t step = 4;
  for (size_t i = step; i < vec.size() - step - 1; i++)
  {
    long int sum = 0;
    for (size_t j = i - step; j < i + step; j++)
    {
      sum += vec.at(j).y;
    }
    vecForDraw.emplace_back(vec.at(i - step).x, sum / (step * 2 - 1));
  }
  Plot plot(vecForDraw, 1300, 1000);
}

