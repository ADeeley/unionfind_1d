#include "percolate.h"

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
	while ( !( grid[a]->parent == -1 ) ) {
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
		grid[a]->parent = b;
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
			cout << open << '\t';
			i += 1;
		}
		cout << '\n';
	}
	cout << '\n';
}

void Percolation::open(int index) {
	// Opens the sector a and unites it with any adjacent sectors.
	grid[index]->isOpen = true;


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
	
	// If the site is on the top or bottom rows, set it's root to a virtual sector
}

bool Percolation::does_percolate() {
	// Returns true if any of the sectors on row 0 share roots with any sectors on the 
	// bottom row
	for ( int i = 0; i < gridSize; i++ ) {
		for ( int j = ( gridSize*gridSize ) - gridSize; j < gridSize*gridSize; j++ ) {
			if ( find( i, j ) )
				return true;
		}
	}
	return false;
}

// -------------- PercolationStats Methods ------------

PercolationStats::PercolationStats(int n, int trials) {
	srand( time( NULL ) ); // Initialise random with a seed based upon the current time
	int sectorsOpened = 0 ;
	Percolation *p;

	for ( int t = 0; t < trials; t++ ) {
		p = new Percolation( n );
		while ( true ) {
			p->open( rand() % (n*n) );
			sectorsOpened += 1;
			if ( p->does_percolate() ) {
				//cout << "Percolated at " << sectorsOpened << " sectors.\n";
				//p->print_grid();
				results.push_back( sectorsOpened );
				sectorsOpened = 0;
				break;
			}
		}
	}
}

void PercolationStats::print_stats() {
	for ( int i : results )
		cout << i << ',';
	cout << '\n';
}