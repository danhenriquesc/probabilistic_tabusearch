#include <iostream>
#include "TSP.hpp"

int main(){
  ProbabilisticTabuSearch::TSP *tsp = new ProbabilisticTabuSearch::TSP("berlin52.tsp.txt");

  return 0;
}

