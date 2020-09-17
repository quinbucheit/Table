/*
*	An abstract data type representing a table of values with functionality for appending
*	rows and columns, modifying the contents of specified cells, extracting a sub-table
*	and applying a specified operation to all values in the table.
*
*	Header file for the Table class.
*
*	Author: Quintin Bucheit
*/
#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include <iostream>

using namespace std;

template <typename T>
class Table {

	/*
		Overloaded stream insertion operator that allows client code to output a table in
		the same way that primitive type values are outputted.
	*/
	template <typename U>
	friend ostream& operator<<(ostream&, const Table<U>&);

	/*
		Overloaded addition operator that providesan intuitive syntax for updating all of
		the values in a table according to the given function f.
		
			Example:
				cout << t + square;
	*/
	template <typename U>
	friend Table<U>& operator+(Table<U>&, U(*f)(U));

public:
	// Constructor
	Table(int r, int c);
	
	// Overloaded constructor that uses n for both rows and columns
	Table(int n = 5);
	
	// Copy Constructor
	Table(const Table&);
	
	// Overloaded assignment operator
	Table& operator=(const Table&);
	
	// Destructor.
	~Table();

	/*
		Overloaded function call operator that takes two integer arguements indicating
		the row and column of a cell in the table and returns a reference to the value
		at that position.
	*/
	T& operator()(int r, int c) const;

	/*
		Overloaded function call operator that takes four integer arguements representing
		the top-left and bottom-right corners of a subtable and returns a reference to 
		that subtable without modifying the original.
		
		tlr = top-left row, tlc = top-left column
		brr = bottom-right row, brc = bottom-right column
	*/
	Table& operator()(int tlr, int tlc, int brr, int brc) const;

	/*
		Returns a reference to a table obtained by appending t onto the bottom of the
		table calling this function.
	*/
	Table& append_rows(const Table& t) const;
	
	/*
		Returns a reference to a table obtained by appending t onto the right of the
		table calling this function.
	*/
	Table& append_cols(const Table& t) const;

	// returns rows
	int get_rows() const;
	// returns cols
	int get_cols() const;
private:
	T** table;
	int rows;
	int cols;

	void alloc(); // allocates table memory
	void dealloc(); // deallocates table memory
};
#endif
