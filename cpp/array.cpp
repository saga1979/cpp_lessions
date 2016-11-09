#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#include <iomanip>

using std::setw;

#include <cstdlib>
#include <cassert>
#include "array.h"

// Initialize static data member at file scope
int Array::arrayCount = 0;   // no objects yet

							 // Default constructor for class Array (default size 10)
Array::Array(int arraySize)
{
	size = (arraySize > 0 ? arraySize : 10);
	ptr = new int[size]; // create space for array
	assert(ptr != 0);    // terminate if memory not allocated
	++arrayCount;          // count one more object

	//memset(ptr, 0, sizeof(int)*size);
	for (int i = 0; i < size; i++)
		ptr[i] = 0;          // initialize array
}

// Copy constructor for class Array
// must receive a reference to prevent infinite recursion
Array::Array(const Array &init) : size(init.size)
{
	ptr = new int[size]; // create space for array
	assert(ptr != 0);    // terminate if memory not allocated
	++arrayCount;          // count one more object

	for (int i = 0; i < size; i++)
		ptr[i] = init.ptr[i];  // copy init into object
}

// Destructor for class Array
Array::~Array()
{
	delete[] ptr;            // reclaim space for array
	--arrayCount;             // one fewer objects
}

// Get the size of the array
int Array::getSize() const { return size; }

// Overloaded assignment operator
// const return avoids: ( a1 = a2 ) = a3
const Array &Array::operator=(const Array &right)
{
	if (&right != this) {  // check for self-assignment

						   // for arrays of different sizes, deallocate original
						   // left side array, then allocate new left side array.
		if (size != right.size) {
			delete[] ptr;         // reclaim space
			size = right.size;     // resize this object
			ptr = new int[size]; // create space for array copy
			assert(ptr != 0);    // terminate if not allocated
		}

		for (int i = 0; i < size; i++)
			ptr[i] = right.ptr[i];  // copy array into object
	}

	return *this;   // enables x = y = z;
}

// Determine if two arrays are equal and
// return true, otherwise return false.
bool Array::operator==(const Array &right) const
{
	if (size != right.size)
		return false;    // arrays of different sizes

	for (int i = 0; i < size; i++)
		if (ptr[i] != right.ptr[i])
			return false; // arrays are not equal

	return true;        // arrays are equal
}

// Overloaded subscript operator for non-const Arrays
// reference return creates an lvalue
int &Array::operator[](int subscript)
{
	// check for subscript out of range error
	assert(0 <= subscript && subscript < size);

	return ptr[subscript]; // reference return
}

// Overloaded subscript operator for const Arrays
// const reference return creates an rvalue
const int &Array::operator[](int subscript) const
{
	// check for subscript out of range error
	assert(0 <= subscript && subscript < size);

	return ptr[subscript]; // const reference return
}

// Return the number of Array objects instantiated
// static functions cannot be const 
int Array::getArrayCount() { return arrayCount; }

// Overloaded input operator for class Array;
// inputs values for entire array.
istream &operator >> (istream &input, Array &a)
{
	for (int i = 0; i < a.size; i++)
		input >> a.ptr[i];

	return input;   // enables cin >> x >> y;
}

// Overloaded output operator for class Array 
ostream &operator<<(ostream &output, const Array &a)
{
	int i;

	for (i = 0; i < a.size; i++) {
		output << setw(12) << a.ptr[i];

		if ((i + 1) % 4 == 0) // 4 numbers per row of output
			output << endl;
	}

	if (i % 4 != 0)
		output << endl;

	return output;   // enables cout << x << y;
}
