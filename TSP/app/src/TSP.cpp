#ifndef PTS_TSP_H_
#define PTS_TSP_H_

#include <iostream>

#include <sstream>
#include "TSP.hpp"
#include "City.hpp"
#include "Logger.hpp"
#include "Config.hpp"

#define TSPLIB_FILE_HEADER_LINES 6
#define TSPLIB_FILES_PATH string(REPOSITORY_PATH) + "TSP/InstancesTSPLIB/"

using namespace std;

namespace ProbabilisticTabuSearch
{
  // PUBLIC
  TSP::TSP(string filename)
  {
    numberOfCities = 0;
    instanceFilename = TSPLIB_FILES_PATH + filename;
    ReadFile();
    PrintCities();
  }

  // PRIVATE
  void TSP::ReadFile()
  {
    ProbabilisticTabuSearch::Logger::Log(
      "Start to read",
      ("File " + instanceFilename),
      ProbabilisticTabuSearch::Logger::WARNING
    );

    file.open(instanceFilename);

    ClearFileHeader();

    string line;
    int a;
    double b, c;

    while( getline(file, line) )
    {
      if (line == "EOF") break;

      istringstream iss(line);
      iss >> a >> b >> c;

      ProbabilisticTabuSearch::City *city = new ProbabilisticTabuSearch::City(b, c);
      cities[a] = city;

      ++numberOfCities;
    }
  } 

  void TSP::ClearFileHeader()
  {
    ProbabilisticTabuSearch::Logger::Log(
      "Clearing headers",
      ("File " + instanceFilename),
      ProbabilisticTabuSearch::Logger::WARNING
    );

    string line;
    for(int i = 0; i < TSPLIB_FILE_HEADER_LINES; i++)
    {
      getline(file, line);
    }
  }

  void TSP::PrintCities()
  {
    for(int i = 1; i <= numberOfCities; i++)
    {
      ProbabilisticTabuSearch::Logger::Log(
        "Print City",
        ("ID #" + to_string(i) + " | X: " + to_string(cities[i]->x) +  " | Y: " + to_string(cities[i]->y)),
        ProbabilisticTabuSearch::Logger::DEBUG
      );
    }
  }
}

#endif // PTS_TSP_H_