#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <utility>
#include <cmath>
#include <random>
#include <queue>
#include <cstring>
#include <algorithm>

#define N 1400
#define LIST_SIZE 100

enum Movement {move_opt2};

using namespace std;

typedef vector<int> sol;
typedef pair<double,double> point;

double fitness(sol);
double fitness(Movement,sol,int,int,int);
double distance(point, point);
sol constructive();
void printSolution(sol);
sol swap(sol, int, int);
sol opt2(sol, int, int);
int nint(double x);

map<int, point> points;
double distance_matrix[N+1][N+1];
sol currentSolution(N+1), bestSolution(N+1), initialSolution(N+1), bestCandidate(N+1);
int fitCurrentSolution, fitBestSolution, fitInitialSolution, fitBestCandidate;
//vector<vector<int> > tabuList(N+1, vector<int>((N+1),1));
int tabuList[N+1][N+1];

int main(){
	ifstream infile("fl1400.tsp.txt");
	string line;
	int a, it;
	double b, c;
	bool first;

	memset(tabuList, -(LIST_SIZE+1), sizeof(tabuList));
	// for(int i=1;i<=N;i++){
	// 	for(int j=1;j<=N;j++){
	// 		tabuList[i][j] = 0;
	// 	}

	// }

	for(int i=0; i<6;i++){
		getline(infile, line);
	}

	for(int i=1; i<=N;i++){
		getline(infile, line);
		istringstream iss(line);
    		
    	iss >> a >> b >> c;

    	points[a] = make_pair(b,c);
	}

	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			distance_matrix[i][j] = distance(points[i], points[j]);
		}
	}

	// ifstream ifl("tour.txt");
	// string l;
	// sol tour(N+1);
	// for(int i=1;i<=N;i++){
	// 	getline(ifl, l);
	// 	istringstream issl(l);
	// 	issl >> tour[i];
	// }
	// for(int i=1;i<=N;i++){
	// 	cout << tour[i] << " ";
	// }
	// cout << endl;
	// cout << fitness(tour) << endl;


	// exit(0);

	initialSolution = constructive();
	
	currentSolution = initialSolution;
	fitCurrentSolution = fitness(currentSolution);
	bestSolution = currentSolution;
	fitBestSolution = fitCurrentSolution;

	it = 0;
	fitBestCandidate = -1000000;
	int t_i, t_j;
	
	while(it < 2500000){
		first = true; //bestCandidate = NULL

		t_i = -1;
		t_j = -1;
		for(int i=1;i<=N;i++){
			for(int j=i+1;j<=N;j++){ //TODA VIZINHANÇA
				//if ( (it - tabuList[i][j] > LIST_SIZE) && ((first) || (fitness(opt2(currentSolution,i,j)) < fitBestCandidate)) ){
				if ( (it - tabuList[i][j] > LIST_SIZE) && ((first) || (fitness(move_opt2,currentSolution,fitCurrentSolution,i,j) < fitBestCandidate)) ){
					// cout << i << " | " << j << " | " << it << " - " << tabuList[i][j] << " > " << LIST_SIZE << endl;
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

		// cout << t_j << " | " << t_i << endl;
		tabuList[t_j][t_i] = it;
		tabuList[t_i][t_j] = it;
		// cout << "x" << endl;
		// cout << t_j << " | " << t_i << " | " << it-tabuList[t_j][t_i] << endl;

		it++;

		cout << it << " | " << fitBestSolution << endl;
		// cout << it << " | " << fitness(currentSolution) << endl;
		// cout << it << " | " << fitness(bestCandidate) << endl;
		//printSolution(bestSolution);
		// printSolution(currentSolution);
		// printSolution(bestCandidate);
	}

	cout << "FINALIZADO" << endl;
	cout << "CUSTO: " << fitBestSolution << endl;
	printSolution(bestSolution);
}

double fitness(sol S){
	double cost = 0;

	for(int i=1; i<N;i++){
		cost += distance_matrix[S[i]][S[i+1]];
	}

	cost += distance_matrix[S[N]][S[1]];

	return cost;
}

double fitness(Movement move,sol S,int fitness,int i,int j){
	int tmp[N];
	int removed = 0;
	int added = 0;
	double cost = 0;

	switch(move){
		case move_opt2:

			if(i > 1){
				removed += distance_matrix[S[i-1]][S[i]];
				added += distance_matrix[S[i-1]][S[j]];
			}
			else{
				removed += distance_matrix[S[N]][S[i]];
				added += distance_matrix[S[N]][S[j]];
			}

			if(j<N){
				removed += distance_matrix[S[j]][S[j+1]];
				added += distance_matrix[S[i]][S[j+1]];
			}
			else{
				removed += distance_matrix[S[j]][S[1]];
				added += distance_matrix[S[i]][S[1]];
			}

			cost = fitness - removed + added;

			break;
		default:
			cout << "MOVIMENTO INVALIDO" << endl;
	}
	
	return cost;
}

double distance(point p1, point p2){
	return nint(sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2)));
}

sol constructive(){
	sol solution(N+1);

	for(int i=1; i<=N;i++){
		solution[i] = i;
	}

	return solution;
}
void printSolution(sol S){
	cout << "Solution: " << endl;
	for(int i=1;i<=N;i++){
		cout << S[i] << " ";
	}
	cout << endl;
}

sol swap(sol S, int i, int j){
	int tmp = S[i];
	S[i] = S[j];
	S[j] = tmp;

	return S;
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

int nint(double x){
	return (int) (x+0.5);
}