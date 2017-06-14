#include "percolate.h"
#include <algorithm>

using namespace std;

/*
The rows of the grid of size Gridsize-1 are selected first. The columns follow
	  cols 0-4
row 0 [][][][][]
row 1 [][][][][]
row 2 [][][][][]
row 3 [][][][][]
row 4 [][][][][]

*/

// ---------- Sector definitions ---------------
Sector* Grid::get_sector( int i ) {
	return grid[i];
}

Sector* Grid::get_sector_by_coordinates( int row, int col ) {
	return grid[( row*(gridSize) ) + col];
}

Sector* Grid::operator[](const int index){
	return grid[index];
}

// ---------- Percolates definitions ------------

int Percolation::get_root( int a ) {
	// Returns the root note of sector a.
	// Returns a if a is its own root
	/*
	while ( !( grid[a]->parent == -1 ) ) {
		a = grid[a]->parent;
	}
	*/

	while ( !( grid[a]->parent == a ) ) {
		grid[a]->parent = grid[grid[a]->parent]->parent;
		a = grid[a]->parent;
	}
	return a;
}
void Percolation :: unite( int a, int b ) {
	// Unites the sectors with index a and b.
	// First find the parent sectors of a and b. 
	a = get_root( a );
	b = get_root( b );
	// If a and b do not share a parent, then make b the parent of a.
	if ( !( a == b ) ) {
		if ( grid[a]->treeSize < grid[b]->treeSize ) {
			grid[a]->parent = b;
			grid[b]->treeSize += grid[a]->treeSize;
		}
		else {
			grid[b]->parent = a;
			grid[a]->treeSize += grid[b]->treeSize;
		}
		//cout << "United " << a << " and " << b << '\n';
	}
}

bool Percolation::find( int a, int b ) {
	// Returns true if a and a share a root node
	a = get_root( a );
	b = get_root( b );

	if ( a == b )
		return true;
	else
		return false;
}

void Percolation::print_grid() {
	// Prints a grid representation showing each sector's ID and it's parent
	/*
	int i = 0;
	char open;
	for ( int row = 0; row < gridSize; row++ ) {
		for ( int col = 0; col < gridSize; col++ ) {
			open = ( grid[i]->isOpen ) ? 'o' : 'x';
			cout << open << '[' << grid[i]->ID << "]:" << grid[i]->parent << ' ';
			i += 1;
		}
		cout << '\n';
	}
	cout << '\n';
	*/
	int i = 0;
	char open;
	for ( int row = 0; row < gridSize; row++ ) {
		for ( int col = 0; col < gridSize; col++ ) {
			open = ( grid[i]->isOpen ) ? 'o' : 'x';
			cout << open << ',';
			i += 1;
		}
		cout << '\n';
	}
	/*
	cout << '\n';
	int i = 0;
	char open;
	for ( int row = 0; row < gridSize; row++ ) {
		for ( int col = 0; col < gridSize; col++ ) {
			cout << grid[i]->treeSize << '\t';
			i += 1;
		}
		cout << '\n';
	}
	cout << '\n';
	*/
}

void Percolation::open(int index) {
	// Opens the sector a and unites it with any adjacent sectors.

	grid[index]->isOpen = true;

	// If the site is on the top or bottom rows, set it's root to a virtual sector
	if ( index < gridSize )
		unite( index, (gridSize*gridSize));

	if ( index > (gridSize*gridSize)-gridSize && index < (gridSize*gridSize))
		unite( index, (gridSize*gridSize)+1 );
	// Unite with adjacent sectors

	if ( index>0 ) // left
		if (!((index)%gridSize == 0 )) // checks for column overflow
			if ( grid[index-1]->isOpen )
				unite( index, index - 1 );

	if ( index < gridSize*gridSize - 1 ) // right
		if (!((index+1)%gridSize == 0 )) // checks for column overflow
			if ( grid[index + 1]->isOpen )
				unite( index, index + 1 );

	if ( index - gridSize >= 0 ) // up
		if ( grid[index - gridSize]->isOpen )
			unite( index, index - gridSize );

	if ( index + gridSize < gridSize*gridSize ) // down
		if ( grid[index + gridSize]->isOpen )
			unite( index, index + gridSize );
	

}

bool Percolation::does_percolate() {
	// Returns true if any of the sectors on row 0 share roots with any sectors on the 
	// bottom row
	/*
	for ( int i = 0; i < gridSize; i++ ) {
		if ( grid[i]->isOpen ) {
			for ( int j = ( gridSize*gridSize ) - gridSize; j < gridSize*gridSize; j++ ) {
				if ( grid[j]->isOpen ) {
					if ( find( i, j ) )
						return true;
				}
			}
		}
	}
	return false;
	*/
	if ( find( gridSize*gridSize, gridSize*gridSize + 1 ) )
		return true;
	return false;
}

// -------------- PercolationStats Methods ------------

PercolationStats::PercolationStats(int n, int trials) {
	srand( time( NULL ) ); // Initialise random with a seed based upon the current time
	double numOpened = 0 ;
	Percolation *p = new Percolation(n);
	vector<int> choices;
	for ( int i = 0; i < p->totalSectors; i++ ) choices.push_back( i );

	for ( int t = 0; t < trials; t++ ) {

		// generate unique random numbers with each number only being generated once
		std::random_shuffle( choices.begin(), choices.end());
		cout << "Choices: " << choices.size() << '\n';
		for( int i : choices ){
			p->print_grid();
			cout << "Num opened: " << numOpened << " Opened sector " << i << '\n';
			p->open( i );
			numOpened += 1;
			cout << "does percolate: " << p->does_percolate() << '\n';
			if ( p->does_percolate() ) {
				cout << "Percolated at " << numOpened << " sectors.\n";
				//p->print_grid();
				results.push_back( numOpened/p->totalSectors );
				cout << "Per: " << numOpened << ',' << p->totalSectors << ',' << numOpened/(p->totalSectors) << '\n';
				numOpened = 0;
				break;
				
			}
		}
		p = new Percolation( n );
	}
}

double PercolationStats::mean() {
	// Returns the mean of the results as a double
	double sum = 0;

	for ( double n : results )
		sum += n;

	return sum / results.size();
}

double PercolationStats::stddev() {
	// Returns the standard deviation of the results
	double m = mean();
	double squaredDifference = 0;

	// work out the variance
	for ( double n : results )
		squaredDifference += pow( ( n - m ), 2 );
	double variance = squaredDifference / ( results.size() -1 );

	return sqrt( variance );
}

double PercolationStats::confidenceHi() {
	return mean() - (( 1.96*stddev() ) / sqrt(results.size()));
}

double PercolationStats::confidenceLo() {
	return mean() + (( 1.96*stddev() ) / sqrt(results.size()));
}

void PercolationStats::print_stats() {
	for ( double i : results )
		cout << i << ',';
	cout << '\n';
}