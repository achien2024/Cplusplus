// Aaron Chien

#include "newSequence.h"
#include <iostream>
#include <string>

Sequence::Sequence(int x)
// constructor, initialize the array size and set our private member array to dynamically 
// allocate to a new array
    // since we are dynamically allocating to an array, we set a pointer to point to it 
// set the size to 0 too
{
    m_cap = x;
    m_array = new ItemType[m_cap];
    m_size = 0;
}

Sequence::Sequence()
// default constructor, if no argument is given, just set the size to the max size possible
{
    m_cap = DEFAULT_MAX_ITEMS;
    m_array = new ItemType[m_cap];
    m_size = 0;
}

bool Sequence::empty() const
{
    if (m_size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (0 <= pos && pos <= m_size && m_size < m_cap)
    {
        for (int i = m_size; i > pos; i--)
        {
            *(m_array + i) = *(m_array + i - 1);
        }
        *(m_array + pos) = value;
        m_size++;
        return pos;
    }
    else
    {
        return -1;
    }
}

int Sequence::insert(const ItemType& value)
{
    int p = m_size;
    // make p the m_size if value is not the smallest value
    for (int i = 0; i < m_size; i++)
    // creating a for loop to iterate through the array
    {
        if (value <= *(m_array + i))
        {
            p = i;
            break;
            // exit out of the for loop 
        }
    } 

    return insert(p, value);  
}

bool Sequence::erase(int pos)
// when you use the new keyword, it's in those situations where you need to worry about deleting
// i did not expilicity create anything so I do not need to worry about deleting anything 
{
    if (0 <= pos && pos < m_size)
    {
        for (int i = pos; i <= m_size; i++)
        {
            *(m_array + i) = *(m_array + i+1);
        }
        // delete *(m_array + m_size - 1);
        // *(m_array + m_size - 1) = NULL;
        // you cannot delete any variable, only pointers
        // can only delete stuff you dynamically allocated
        // *(m_array + m_size - 1) = NULL;
        // change the last position to nothing
        m_size--;
        return true;
    } 
    else
    {
        return false;
    }
}

int Sequence::remove(const ItemType& value)
// so we wouldn't want to use pointers and references for ints and other objects built in
// this is because they are small, so they don't take up a lot of space
// and having a system of pointers and ints would become very stressful for the developer reading the code
// since Sequence is an array of ints 180, that can take a large amount of memory so when there are functions
// that return the class, it's best to use pointers and addresses 
{
    int num_items_removed = 0;
    for (int i = 0; i < m_size; i++)
    {
        if (*(m_array + i) == value)
        {
            erase(i);
            // m_size--;
            // erase decrements m_size already
            i--;
            num_items_removed++;
        }
    }

    return num_items_removed;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (0 <= pos && pos < m_size)
    {
        value = *(m_array + pos);
        return true;
    }
    else 
    {
        return false;
    }
}

bool Sequence::set(int pos, const ItemType& value) 
{
    if (0 <= pos && pos < m_size)
    {
        *(m_array + pos) = value;
        return true;
    }
    else
    {
        return false;
    }
}

int Sequence::find(const ItemType& value) const
{
    int p = -1;
    for (int i = 0; i < m_size; i++)
    {
        if (*(m_array + i) == value)
        {
            p = i;
        }
    }
    return p;
}

void Sequence::swap(Sequence &other)
{
    int temp_mSize, temp_arrSize;
    temp_arrSize = m_cap;
    temp_mSize = m_size;
    // creating temp variables to switch the size of the array and the capacity of the array

    m_cap = other.m_cap;
    m_size = other.m_size;
    // set our own size and capacity to the other's

    other.m_cap = temp_arrSize;
    other.m_size = temp_mSize;
    // set the other's capacity and size to our's

    // switches the size of the array and the size of the max items it can hold

    ItemType* temp_m_array;
    temp_m_array = other.m_array;
    other.m_array = m_array;
    m_array = temp_m_array;
    // what this program is doing is that it's swapping pointers, not arrays
    // so it just switches to what it's pointing to
}

Sequence::Sequence(const Sequence& other)
// copy constructor
{
    m_cap = other.m_cap;
    // copies the capacity to the other's capacity 
    m_size = other.m_size;
    // since other and this are both Sequence class, I am able to access the other's m_size private member
    m_array = new ItemType[m_size];
    // using new so that when we destruct this, we can delete it
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }
}

Sequence& Sequence::operator= (const Sequence& rhs)
// when you do the equal sign, when the value gets swapped over, you want to return something
    // you can return a copy, but it will be inefficient 
    // you wouldn't want to use a ptr because you want this to resolve to the value/object you assign over 
        // other equal signs do not work this way 
// *, &, value
// we do not want to do value here because it is impossible to pass by value 
    // if you do value, it will be copied repeatedly and will constantly call the =
    // this causes an infinite loop as Sequence Sequence::operator= will call the = again when it encounters =
    // when it sees =, it will call = again
// we can use * and pointers, it just more annoying and more likely to have errors
// return_type class::fun_name(parameters)
// in this case of overloading operators, the fun_name is operator=
{
    if (this != &rhs)
    {
        Sequence temp(rhs);
        // was trying to copy a const Sequence into an unsigned long by doing ItemType temp(rhs)
            // basically you were trying to convert a const data type into a different data type which wouldn't work in this case
        // delete[] m_array;
        swap(temp);
        // delete temp not needed as it will automaticall call the manually created destructor 
    }

    return *this;
    // statically assigned local variables only typically use &
    // if you plan on returning something large, use a pointer 
        // & *, **
        // you treat the & like a normal object
        // using a reference type is used for parameters 
}

Sequence::~Sequence()
// destructor
{
    delete[] m_array;
    // because it is a ptr to an array, you do not need to use a for loop
        // when it sees this, it will deallocate everything in the array 
    // if you have an array of ptrs, you need to loop through the array and delete each ptr
        // if you have a 2D array of ptrs, you need to use a for loop 
}