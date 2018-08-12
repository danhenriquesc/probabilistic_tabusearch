#ifndef PTS_LOGGER_H_
#define PTS_LOGGER_H_

#include <iostream>
#include "Logger.hpp"
#include "Config.hpp"

using namespace std;

namespace ProbabilisticTabuSearch
{
  void Logger::Log(string title, string message, Levels level)
  {
    if (level <= LOG_LEVEL)
    {
      cout << "[" + title + "] " << message << endl;
    }
  } 
}

#endif // PTS_LOGGER_H_