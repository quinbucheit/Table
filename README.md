# Table
An abstract data type representing a table of values with functionality for appending row and columns, modifying the contents of specified cells, extracting a sub-table, and applying a specified operation to all values in the table. Demonstrates understanding of class templates, dynamic memory allocation, and operator overloading in C++.

Technical details:

1. Client code can construct a Table object by specifying the number of rows and columns, or by specifying a single integer if both dimensions are the same. 

2. The stream insertion (leftshit) operator is overloaded so that client code can output a table in the same way that primitive type values are outputted; for example:
    Table<int> table(3, 5);
    ...
    cout << table << endl;
Assume that cell (0, 0) is in the top-left corner of the table.
  
3. The function call operator is overloaded to take two integer arguements indicating the row and column of a cell in the table. The function returns a reference to the value at that position. This allows client code to modify table entries with a natural syntax that is similar to array bracket notation. For example, to assign the value 10 to the cell in row 3, column 4, one would write:
    table(3, 4) = 10;
This is equivalent to:
    table.operator()(3, 4) = 10;
    
4.
