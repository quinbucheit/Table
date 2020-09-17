/*
*   An abstract data type representing a table of values with functionality for appending
*   rows and columns, modifying the contents of specified cells, extracting a sub-table
*   and applying a specified operation to all values in the table.
*
*	  Implementation file for table class.
*
*   Author: Quintin Bucheit
*/
#include <iomanip>
#include <cassert>
#include "table.h"

template <typename T>
Table<T>::Table(int r, int c) {
    this->rows = r;
    this->cols = c;
    alloc();
}

template <typename T>
Table<T>::Table(int n) {
    this->rows = n;
    this->cols = n;
    alloc();
}

template <typename T>
Table<T>::Table(const Table& t) {
    rows = t.rows;
    cols = t.cols;
    alloc();
}

template <typename T>
Table<T>& Table<T>::operator=(const Table& t) {
    if (this == &t) {
        return *this;
    }

    if (rows != t.rows || cols != t.cols) {
        dealloc();
        rows = t.rows;
        cols = t.cols;
        alloc();
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            table[i][j] = t.table[i][j];
        }
    }

    return *this;
}

template <typename T>
Table<T>::~Table() {
    dealloc();
}

template <typename T>
T& Table<T>::operator()(int r, int c) const {
    return table[r][c];
}

template <typename T>
Table<T>& Table<T>::operator()(int tlr, int tlc, int brr, int brc) const {
    Table<T>* t = new Table<T>((brr + 1) - tlr, (brc + 1) - tlc);
    t->alloc();

	// copies desired subset of the table calling this function into t's table
    for (int i = tlr, k = 0; i <= brr && k < t->rows; i++, k++) {
        for (int j = tlc, l = 0; j <= brc && l < t->cols; j++, l++) {
            t->table[k][l] = table[i][j];
        }
    }
    return *t;
}

template <typename T>
Table<T>& Table<T>::append_rows(const Table& t) const {
    assert(cols == t.cols);

    Table<T>* temp = new Table<T>(rows + t.rows, cols);
    temp->alloc();

    int i;
    int j;
	// copies content of table calling this function into temp's table
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            temp->operator()(i, j) = this->operator()(i, j);
        }
    }
	// appends content of t's table onto temp's table
    for (i = rows; i < temp->rows; i++) {
        for (j = 0; j < temp->cols; j++) {
            temp->operator()(i, j) = t(i - rows, j);
        }
    }
    return *temp;
}

template <typename T>
Table<T>& Table<T>::append_cols(const Table& t) const {
    assert(rows == t.rows);
    Table<T>* temp = new Table<T>(rows, cols + t.cols);
    temp->alloc();

    int i;
    int j;
	// copies content of table calling this function into temp's table
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            temp->operator()(i, j) = this->operator()(i, j);
        }
    }
	// appends content of t's table onto temp's table
    for (i = 0; i < temp->rows; i++) {
        for (j = cols; j < temp->cols; j++) {
            temp->operator()(i, j) = t(i, j - cols);
        }
    }
    return *temp;
}

template <typename T>
Table<T>& operator+(Table<T>& t, T(*f)(T)) {
    Table<T>* temp = new Table<T>(t.rows, t.cols);
    temp->alloc();

    int i, j;
	// copies content of t's table into temp's table
    for (i = 0; i < t.rows; i++) {
        for (j = 0; j < t.cols; j++) {
            temp->operator()(i, j) = t(i, j);
        }
    }
	// passes each item of temp's table to function f one at a time
    for (i = 0; i < temp->rows; i++) {
        for (j = 0; j < temp->cols; j++) {
            temp->operator()(i, j) = f(temp->operator()(i, j));
        }
    }

    return *temp;
}

template <typename T>
int Table<T>::get_rows() const {
    return rows;
}

template <typename T>
int Table<T>::get_cols() const {
    return cols;
}

template <typename T>
void Table<T>::alloc() {
    table = new T * [rows];
    for (int i = 0; i < rows; i++) {
        table[i] = new T[cols];
    }
}

template <typename T>
void Table<T>::dealloc() {
    for (int i = 0; i < rows; i++) {
        delete[]table[i];
    }
    delete[]table;
}

template <typename T>
ostream& operator<<(ostream& out, const Table<T>& t) {
    // w is the size of the columns in this table
    int w = out.width();

    for (int i = 0; i < t.rows; i++) {
        for (int j = 0; j < t.cols; j++) {
            // Has the effect of writing the table values right justified in columns
            // of size w.
            out << setw(w) << t(i, j) << " ";
        }
        out << endl;
    }
    return out;
}
