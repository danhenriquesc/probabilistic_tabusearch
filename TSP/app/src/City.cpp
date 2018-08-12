#ifndef PTS_CITY_H_
#define PTS_CITY_H_

#include "City.hpp"
#include "Logger.hpp"

using namespace std;

namespace ProbabilisticTabuSearch
{
  // PUBLIC
  City::City(double coord_x, double coord_y)
  {
    ProbabilisticTabuSearch::Logger::Log(
      "Create City",
      ("X = " + to_string(coord_x) + " and Y = " + to_string(coord_y)),
      ProbabilisticTabuSearch::Logger::VERBOSE
    );

    x = coord_x;
    y = coord_y;
  }
}

#endif // PTS_CITY_H_