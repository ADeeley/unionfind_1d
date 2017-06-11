#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

struct Sector {
	int parent = -1;
	int ID;
	bool isOpen = false;
	Sector( int i ) :
		ID{ i } {};
};

class Grid {
public:
	const int virtualSiteTopID = gridSize*gridSize + 1;
	const int virtualSiteBottomID = gridSize*gridSize + 2;

	Grid( int sz ) :
		gridSize{ sz } {
		for ( int i = 0; i < ( gridSize * gridSize ); i++ )
			grid.push_back( new Sector( i ) );
	}

	// Methods
	Sector* get_sector( int );
	Sector* get_sector_by_coordinates( int, int );
	Sector* operator[]( const int );

	// Variables
	Sector* virtualSiteTo = new Sector( virtualSiteTopID );
	Sector* virtualSiteBottom = new Sector( virtualSiteBottomID );
private:
	vector<Sector*> grid;
	const int gridSize;
};

class Percolation {
public:
	Percolation( int sz ) :
		grid{ Grid( sz ) }, gridSize{ sz } {}

	// Methods
	int get_root( int );
	void unite( int, int );
	bool find( int, int );
	void print_grid();
	void open( int );
	bool does_percolate();
	
	// Variables
	Grid grid;
private:
	int gridSize;
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
	vector<int>results;
};