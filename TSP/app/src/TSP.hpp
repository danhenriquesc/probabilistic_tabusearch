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
      float distances[MAX_CITIES][MAX_CITIES];

      void ReadFile();
      void ClearFileHeader();
      void PrintCities();
      int Nint(double x);
      double Distance(ProbabilisticTabuSearch::City*, ProbabilisticTabuSearch::City*);
      void CalculateDistances();
      void PrintDistances();
  };
}
