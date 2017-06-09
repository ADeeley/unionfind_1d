#include <iostream>
#include <vector>

using namespace std;

/*
The rows of the grid of size Gridsize-1 are selected first. The columns follow
	  cols 1-4
row 1 [][][][][]
row 2 [][][][][]
row 3 [][][][][]
row 4 [][][][][]
row 5 [][][][][]

*/

struct Sector {
	int parent = -1;
	int ID;
	bool isOpen = false;
	Sector( int i ) :
		ID{ i } {};

};

class Grid {
public:
	Sector* get_sector( int i ) {return grid[i];}
	Sector* get_sector_by_coordinates( int row, int col ) {
		return grid[( row*(gridSize-1) ) + col];
	}
	Grid( int sz ) :
		gridSize{ sz } {
		for ( int i = 0; i < ( gridSize * gridSize ); i++ )
			grid.push_back( new Sector( i ) );
	}
	Sector* operator[]( const int index );

private:
	vector<Sector*> grid;
	int gridSize;
};

Sector* Grid::operator[](const int index){
	return grid[index];

}

class Percolates {
public:
	Grid grid;
	Percolates( int sz ) :
		grid{ Grid( sz ) }, gridSize{ sz } {}
	int get_root( int a );
	void unite( int a, int b );
	bool find( int a, int b );
	void print_grid();
	void open( int a );
private:
	int gridSize;
};

int Percolates::get_root( int a ) {
	// Returns the root note of sector a.
	while ( !( grid[a]->parent == -1 ) )
		a = grid[a]->parent;

	return a;
}
void Percolates :: unite( int a, int b ) {
	// Unites the sectors with index a and b.
	// First find the root sectors of a and b. 
	a = get_root( a );
	b = get_root( b );
	// If a and b do not share a root, then make the root of b the root of a.
	if ( !( a == b ) ) {
		grid[a]->parent = b;
		cout << "United " << a << " and " << b << '\n';
	}
}

bool Percolates::find( int a, int b ) {
	// Returns true if a and a share a root node
	a = get_root( a );
	b = get_root( b );

	if ( a == b )
		return true;
	else
		return false;
}

void Percolates::print_grid() {
	int i = 0;
	for ( int row = 0; row < gridSize; row++ ) {
		for ( int col = 0; col < gridSize; col++ ) {
			cout << '[' << grid[i]->ID << "]:" << grid[i]->parent << '\t';
			i += 1;
		}
		cout << '\n';
	}
	cout << '\n';
}

void Percolates::open(int a) {
	// Opens the sector a and unites it with any adjacent sectors.
	grid[a]->isOpen = true;

	if ( a>0 ) // left
		if (!((a)%gridSize == 0 )) // checks for column overflow
			if ( grid[a-1]->isOpen )
				unite( a, a - 1 );

	if ( a < gridSize*gridSize - 1 ) // right
		if (!((a+1)%gridSize == 0 )) // checks for column overflow
			if ( grid[a + 1]->isOpen )
				unite( a, a + 1 );

	if ( a - gridSize > 0 ) // up
		if ( grid[a - gridSize]->isOpen )
			unite( a, a - gridSize );

	if ( a + gridSize < gridSize*gridSize ) // down
		if ( grid[a + gridSize]->isOpen )
			unite( a, a + gridSize );
}

int main() {
	int n = 5;
	Percolates grd = Percolates( n );
	/*
	cout << grd[5]->ID << ',' << grd.get_sector_by_coordinates( 1, 1 )->ID << '\n';
	cout << grd[14]->ID << ',' << grd.get_sector_by_coordinates( 3,2 )->ID << '\n';
	grd.print_grid();
	grd.unite( 4, 5 );
	grd.unite( 5, 6 );
	grd.unite( 7, 8 );
	grd.unite( 8, 9 );
	grd.unite( 4, 9 );
	grd.print_grid();
	
	cout << grd.find( 4, 8 ) << '\n';
	cout << grd.find( 4, 11 ) << '\n';
	cout << grd.find( 7, 9 ) << '\n';
	
	grd.open( 12 );
	grd.open( 13 );
	grd.open( 17 );
	grd.open( 11 );
	grd.open( 7 );
	grd.open( 14 );
	cout << "grd.open( 19 )\n";
	grd.open( 19 );
	cout << "grd.open( 20 )\n";
	grd.open( 20 );
	cout << "grd.open( 15 )\n";
	grd.open( 15 );
	cout << "grd.open( 10 )\n";
	grd.open( 10 );
	grd.print_grid();
	*/
	return 0;
}