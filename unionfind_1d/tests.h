#include <cassert>

using namespace std;

void test_get_sector() {
	Grid grid = Grid( 5 );
	assert( grid.get_sector( 0 )->ID == 0 );
	assert( grid.get_sector( 24 )->ID == 24 );
	assert( grid.get_sector( 5 )->ID == 5 );
	cout << "test_get_sector() ||PASS||\n";
}

void test_get_sector_by_coordinates() {
	Grid grid = Grid( 5 );
	assert( grid.get_sector_by_coordinates( 0, 0 )->ID == 0 );
	assert( grid.get_sector_by_coordinates( 4, 4 )->ID == 24 );
	assert( grid.get_sector_by_coordinates( 0, 4 )->ID == 4 );
	assert( grid.get_sector_by_coordinates( 4, 0 )->ID == 20 );
	cout << "test_get_sector_by_coordinates() ||PASS||\n"; }

void test_get_parent() {
	Percolates grid = Percolates( 5 );
	
	grid.open( 0 );
	grid.open( 5 );
	grid.open( 10 );
	grid.open( 15 );
	grid.open( 20 );
	//cout << "---------Root of 20: " << grid.get_root( 20 ) << '\n';
	assert( grid.get_root( 20 ) == grid.get_root(0) );
	assert( grid.get_root( 15 ) == grid.get_root(0) );
	assert( grid.get_root( 10 ) == grid.get_root(0) );
	assert( grid.get_root( 5 ) == grid.get_root(0) );
	grid.open( 4 );
	grid.open( 9 );
	grid.open( 14 );
	grid.open( 19 );
	grid.open( 24 );
	//cout << "---------Root of 20: " << grid.get_root( 20 ) << '\n';
	assert( grid.get_root( 4 ) == 4 );
	assert( grid.get_root( 9 ) == 4 );
	assert( grid.get_root( 14 ) == 4 );
	assert( grid.get_root( 19 ) == 4 );
	assert( grid.get_root( 24 ) == 4 );
}
void test_unite() {
	Percolates grid = Percolates( 5 );
	grid.unite( 0, 1 );
	grid.unite( 5, 0 );
	grid.unite( 4, 3 );
	grid.unite( 4, 9 );
	grid.unite( 20, 15 );
	grid.unite( 20, 21 );
	grid.unite( 24, 19 );
	grid.unite( 24, 23 );
	assert( grid.get_root( 0 ) == grid.get_root( 1 ) );
	assert( grid.get_root( 5 ) == grid.get_root( 0 ) );
	assert( grid.get_root( 4 ) == grid.get_root( 3 ) );
	assert( grid.get_root( 4 ) == grid.get_root( 9 ) );
	assert( grid.get_root( 20 ) == grid.get_root( 15 ) );
	assert( grid.get_root( 20 ) == grid.get_root( 21 ) );
	assert( grid.get_root( 24 ) == grid.get_root( 19 ) );
	assert( grid.get_root( 24 ) == grid.get_root( 23 ) );
}
void test_find() {
	Percolates grid = Percolates( 5 );
	grid.unite( 0, 1 );
	grid.unite( 5, 0 );
	grid.unite( 4, 3 );
	grid.unite( 4, 9 );
	grid.unite( 20, 15 );
	grid.unite( 20, 21 );
	grid.unite( 24, 19 );
	grid.unite( 24, 23 );
	assert( grid.find( 0, 1 ) );
	assert( grid.find( 5, 0 ) );
	assert( grid.find( 4, 3 ) );
	assert( grid.find( 4, 9 ) );
	assert( grid.find( 20, 15 ) );
	assert( grid.find( 20, 21 ) );
	assert( grid.find( 24, 19 ) );
	assert( grid.find( 24, 23 ) );
}
void test_open() {
	Percolates grid = Percolates( 5 );
	grid.open( 0 );
	grid.open( 5 );
	grid.open( 1 );
	assert( grid.grid[0]->isOpen );
	assert( grid.grid[5]->isOpen );
	assert( grid.grid[1]->isOpen );

}
void does_percolate() {
	Percolates *grid = new Percolates( 5 );
	grid->open( 0 );
	grid->open( 5 );
	grid->open( 10 );
	grid->open( 15 );
	grid->open( 20 );
	assert( grid->does_percolate() );
	delete grid;
	
	grid = new Percolates( 5 );
	grid->open( 4 );
	grid->open( 9 );
	grid->open( 14 );
	grid->open( 19 );
	grid->open( 24 );
	assert( grid->does_percolate() );
	delete grid;

	grid = new Percolates( 5 );
	grid->open( 0 );
	grid->open( 5 );
	grid->open( 7 );
	grid->open( 11 );
	grid->open( 12 );
	grid->open( 17 );
	grid->open( 18 );
	grid->open( 23 );
	assert( grid->does_percolate() );
	delete grid;

	grid = new Percolates( 5 );
	grid->open( 4 );
	grid->open( 9 );
	grid->open( 14 );
	grid->open( 19 );
	grid->open( 20 );
	assert( !(grid->does_percolate()) );
	delete grid;

}

void run_tests() {
	test_get_sector();
	test_get_sector_by_coordinates();
	test_get_parent();
	test_unite();
	test_find();
	test_open();
}