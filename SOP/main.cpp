#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdlib>

#define MAX_EDGES 100
#define INFINITE 10000

enum Movement {move_opt2};

using namespace std;

typedef vector<int> sol;

sol constructive();
void printSolution(sol);
int fitness(sol);
int fitness(Movement,sol,int,int,int);
sol opt2(sol, int, int);

int N;
int TABU_LIST_SIZE;
int distances[MAX_EDGES][MAX_EDGES]; 
int tabulist[MAX_EDGES][MAX_EDGES];

sol currentSolution(N), bestSolution(N), initialSolution(N), bestCandidate(N);
int fitCurrentSolution, fitBestSolution, fitInitialSolution, fitBestCandidate;

// ./main filename
int main(int argc, char* argv[])
{

	// Loading input file
	string filename = argv[1];
	TABU_LIST_SIZE = atoi(argv[2]);
	ifstream infile(filename);

	// Reading Metadata
	string line;
	for(int i=0; i<4; i++)
	{
		getline(infile, line);
		cout << line << endl;
	}
	getline(infile, line);
	getline(infile, line);
	getline(infile, line);

	// Reading dimension
	getline(infile, line);
	istringstream iss(line);
	iss >> N;
	
	// Reading distances
	for(int i=0; i<N; i++)
	{
	 	getline(infile, line);
	 	istringstream iss(line);
    		
     	for(int j=0; j<N; j++)
     	{
     		iss >> distances[i][j];    		
     	}
	}

	// Initializing Tabu List
	memset(tabulist, -(TABU_LIST_SIZE+1), sizeof(tabulist));
	
	// Generating Initial Solution
	initialSolution = constructive();

	// Declaring and Starting TS variables
	int it = 0;
	int t_i, t_j;
	int fitMovement;
	bool first;

	currentSolution = initialSolution;
	fitCurrentSolution = fitness(currentSolution);
	bestSolution = currentSolution;
	fitBestSolution = fitCurrentSolution;
	
	while(it < 2500000){
		first = true; //bestCandidate = NULL
		fitBestCandidate = 1000000;

		t_i = -1;
		t_j = -1;
		for(int i=1;i<N-1;i++){
			for(int j=i+1;j<N-1;j++){ //TODA VIZINHANÇA
				fitMovement = fitness(move_opt2,currentSolution,fitCurrentSolution,i,j);

				if ( 
					(
						(it - tabulist[i][j] > TABU_LIST_SIZE) && 
						((first) || (fitMovement < fitBestCandidate))
					) ||
					fitMovement < fitBestSolution // Aspiração
				)

				{
					first = false;
					bestCandidate = opt2(currentSolution,i,j);
					fitBestCandidate = fitness(bestCandidate);
					t_i = i;
					t_j = j;
				}
			}
		}

		currentSolution = bestCandidate;
		fitCurrentSolution = fitBestCandidate;
		
		if(fitBestCandidate < fitBestSolution){
			bestSolution = bestCandidate;
			fitBestSolution = fitBestCandidate;
		}

		tabulist[t_j][t_i] = it;
		tabulist[t_i][t_j] = it;

		it++;

		cout << it << " | " << fitBestSolution << endl;
		// cout << it << " | " << fitness(currentSolution) << endl;
		// cout << it << " | " << fitness(bestCandidate) << endl;
		//cout << t_i << "x" << t_j << endl;
		//printSolution(bestCandidate);
	}

	cout << "FINALIZADO" << endl;
	cout << "CUSTO: " << fitBestSolution << endl;
	printSolution(bestSolution);

	return 0;
}

sol constructive(){
	sol solution(N);

	for(int i=0; i<N;i++)
	{
		solution[i] = i;
	}

	return solution;
}

void printSolution(sol S){
	cout << "Solution: " << endl;

	for(int i=0; i<N; i++)
	{
		cout << S[i] << " ";
	}

	cout << endl;
}

int fitness(sol S){
	int cost = 0;

	for(int i=0; i<N-1; i++)
	{
		if(distances[S[i]][S[i+1]] == -1)
		{
     		cost += INFINITE;
		} 
		else
		{
			cost += distances[S[i]][S[i+1]];
		}
	}

	for(int i=0; i<N-2; i++)
	{
		for(int j=i+2; j<N; j++)
		{
			if(distances[S[i]][S[j]] == -1)
			{
     			cost += INFINITE;
			}
		}
	}

	return cost;
}


int fitness(Movement move,sol S,int fit,int i,int j){
	int tmp[N];
	int removed = 0;
	int added = 0;
	int cost = 0;

	switch(move){
		case move_opt2:
			cost = fitness(opt2(S, i, j));

			break;
		default:
			cout << "MOVIMENTO INVALIDO" << endl;
	}
	
	return cost;
}


sol opt2(sol S, int i, int j){
	int tmp[N];

	int index = 0;
	for(int it = i; it<=j;it++){
		tmp[index++] = S[it];
	}

	index = 0;
	for(int it = j;it>=i;it--){
		S[it] = tmp[index++];
	}

	return S;
}