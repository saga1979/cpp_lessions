#ifndef ARRAY1_H
#define ARRAY1_H

#include <iostream>

using std::ostream;
using std::istream;

class Array {
	friend ostream &operator<<(ostream &, const Array &);
	friend istream &operator >> (istream &, Array &);
public:
	Array(int = 10);                   // default constructor
	Array(const Array &);              // copy constructor
	~Array();                            // destructor
	int getSize() const;                 // return size
	const Array &operator=(const Array &); // assign arrays
	bool operator==(const Array &) const;  // compare equal

										   // Determine if two arrays are not equal and
										   // return true, otherwise return false (uses operator==).
	bool operator!=(const Array &right) const
	{
		return !(*this == right);
	}

	int &operator[](int);              // subscript operator
	const int &operator[](int) const;  // subscript operator
	static int getArrayCount();          // Return count of 
										 // arrays instantiated.
private:
	int size; // size of the array
	int *ptr; // pointer to first element of array
	static int arrayCount;  // # of Arrays instantiated
};

#endif
