#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

struct Sector {
	int parent;
	int ID;
	bool isOpen = false;
	int treeSize = 1;
	Sector( int i ) :
		ID{ i }, parent{ i } {};
};

class Grid {
public:
	Grid( int sz ) :
		gridSize{ sz } {
		for ( int i = 0; i < ( gridSize * gridSize ); i++ )
			grid.push_back( new Sector( i ) );
		// Add virtual sectors to the end of the vector
		grid.push_back( new Sector( gridSize*gridSize ) );
		grid.push_back( new Sector( (gridSize*gridSize)+1 ) );
	}

	// Methods
	Sector* get_sector( int );
	Sector* get_sector_by_coordinates( int, int );
	Sector* operator[]( const int );
private:
	vector<Sector*> grid;
	const int gridSize;
};

class Percolation {
public:
	Percolation( int sz ) :
		grid{ Grid( sz ) }, totalSectors{ sz*sz }, gridSize {
		sz
	} {}

	// Methods
	int get_root( int );
	void unite( int, int );
	bool find( int, int );
	void print_grid();
	void open( int );
	bool does_percolate();
	
	// Variables
	Grid grid;
	const int totalSectors;
	const int gridSize;
};

class PercolationStats {
public:
	PercolationStats( int, int );
	double mean();
	double stddev();
	double confidenceLo();
	double confidenceHi();
	// test methods
	void print_stats();
	
private:
	vector<double>results;
};