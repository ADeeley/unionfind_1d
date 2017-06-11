#include "percolate.h"
#include "tests.h"

using namespace std;


int main() {
	int trials = 50000;
	int gridSize = 5;
	clock_t t = clock();
	PercolationStats p = PercolationStats(gridSize, trials);
	t = clock() - t;
	cout << trials << " trials took " << (float) (t / CLOCKS_PER_SEC) 
	 << " seconds for a grid size " << gridSize << '\n';
	return 0;
}