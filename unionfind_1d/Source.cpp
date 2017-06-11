#include "percolate.h"
#include "tests.h"

using namespace std;


int main() {
	int n = 5;
	Percolates grd = Percolates( n );
	int num = 6;
	while ( true ) {
		grd.open( rand() % 24 + 0 );
		grd.print_grid();
		if ( grd.does_percolate() )
			break;
	}
	run_tests();
	return 0;
}