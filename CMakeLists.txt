cmake_minimum_required(VERSION 3.14)
project(YandexTaxiPlot)

set(CMAKE_CXX_STANDARD 14)

add_executable(YandexTaxiPlot
        main.cpp
        Interfsaces/RenderObject.hpp
        Primitives/Canvas.hpp
        Primitives/Point.hpp
        Primitives/Rect.hpp
        RenderObjects/ProgressBar.hpp
        RenderObjects/Text.hpp
        RenderObjects/Plot/Plot.hpp
        RenderObjects/Plot/PlotLine.hpp
        )