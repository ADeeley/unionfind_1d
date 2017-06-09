#include <iostream>
#include <vector>

using namespace std;

/*
The rows of the grid of size Gridsize-1 are selected first. The columns follow
	  cols 1-4
row 1 [][][][]
row 2 [][][][]
row 3 [][][][]
row 4 [][][][]

*/

struct Sector {
	int parent = -1;
	int ID;
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
	void unite( int idA, int idB );
	bool find( int idA, int idB );
	void print_grid();
	int get_root( int a );
private:
	int gridSize;
};

int Percolates::get_root( int a ) {
	// returns the root note of sector a
	while ( !( grid[a]->parent == -1 ) )
		a = grid[a]->parent;

	return a;
}
void Percolates :: unite( int idA, int idB ) {
	// Unites the sectors with index idA and idB
	// first find the root sectors of idA and idB
	idA = get_root( idA );
	idB = get_root( idB );
	// If idA and idB do not share a root, then make the root of idB the root of idA
	if ( !( idA == idB ) )
		grid[idA]->parent = idB;
}

void Percolates::print_grid() {
	int i = 0;
	for ( int r = 0; r < gridSize; r++ ) {
		for ( int c = 0; c < gridSize; c++ ) {
			cout << '[' << grid[i]->ID << "]:" << grid[i]->parent << '\t';
			i += 1;
		}
		cout << '\n';
	}
	cout << '\n';
}

bool Percolates::find( int idA, int idB ) {
	// Returns true if intA and intB share a root node
	idA = get_root( idA );
	idB = get_root( idB );

	if ( idA == idB )
		return true;
	else
		return false;

}

int main() {
	int n = 5;
	Percolates grd = Percolates( n );
	/*
	cout << grd[5]->ID << ',' << grd.get_sector_by_coordinates( 1, 1 )->ID << '\n';
	cout << grd[14]->ID << ',' << grd.get_sector_by_coordinates( 3,2 )->ID << '\n';
	*/
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
		

	return 0;
}