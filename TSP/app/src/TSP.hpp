#include <string>
#include <fstream>
#include "Config.hpp"

using namespace std;

namespace ProbabilisticTabuSearch
{
  class City;

  class TSP
  {
    public:
      TSP(string);
      
    private:
      string instanceFilename;
      ifstream file;
      ProbabilisticTabuSearch::City *cities[MAX_CITIES];
      int numberOfCities;

      void ReadFile();
      void ClearFileHeader();
      void PrintCities();
  };
}
