#include "percolate.h"
#include "tests.h"

using namespace std;

void run_trial( int gridSize, int trials ) {
	clock_t t = clock();
	PercolationStats p = PercolationStats( gridSize, trials );
	t = clock() - t;
	cout << trials << " trials took " << (float)( t / CLOCKS_PER_SEC )
		<< " seconds for a grid size " << gridSize << '\n'
		<< "Mean: " << p.mean() << '\n'
		<< "Standard Deviation: " << p.stddev() << '\n'
		<< "95% confidence interval: [" << p.confidenceHi() << ',' << p.confidenceLo() << "]\n";
	p.print_stats();
}
void trial1() {

	run_trial( 500, 5 );
	run_trial( 1000, 5 );
	run_trial( 2000, 5 );
	run_trial( 4000, 5 );
	run_trial( 8000, 5 );
	run_trial( 16000, 5 );
	run_trial( 32000, 5 );
	run_trial( 64000, 5 );
	run_trial( 128000, 5 );
}

void trial2() {
	run_trial( 5, 20 );
	run_trial( 10, 20 );
	run_trial( 20, 20 );
	run_trial( 40, 20 );
	run_trial( 80, 20 );
	run_trial( 160, 20 );
	run_trial( 320, 20 );
	run_trial( 640, 20 );
	run_trial( 1280, 20 );

	
	run_trial( 10000, 20 );
}

int main() {
	run_trial( 5, 10 );

	return 0;
}