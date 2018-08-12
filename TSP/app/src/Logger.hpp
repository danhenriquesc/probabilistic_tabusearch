#include <string>

using namespace std;

namespace ProbabilisticTabuSearch
{
  class Logger
  {
    public:
      enum Levels
      {
        OFF,
        WARNING,
        VERBOSE,
        DEBUG
      };

      static void Log(string, string, Levels = VERBOSE);
  };
}
