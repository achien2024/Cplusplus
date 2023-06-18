// Aaron Chien
#include "Sequence.h"
// #include "newSequence.h"
#include <iostream>
#include <string>

Sequence::Sequence()
// constructor for class Sequence, intializes the m_size to 0
// m_size will be tracking the size of the array in sequence 
{
    m_size = 0;
}

bool Sequence::empty() const
// function to test if the Sequence is empty, sees if the size is 0
// const because it does not affect the any of the class member variables
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
// function to return the size of the sequence aka the array
// const because it just returns the size, does not affect any of the private member variables 
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
// insert function
{
    if (0 <= pos && pos <= m_size && m_size < DEFAULT_MAX_ITEMS)
    // if the position inserted is greater or equal to 0
    // and if the position inserted is less than or equal to the size of the array
    // and the size is STRICTLY less than the max size (160), continue
        // cannot be equan to or else it will go beyond the array boundaries
    {
        for (int i = m_size; i > pos; i--)
        // start at the end of the array and as long as it's greater than the position, decrement
        // basically go from the end of the array to the position
        // i is the size because we want to put something in position size + 1 since we are increasing the array when inserting
        {
            *(m_array + i) = *(m_array + i - 1);
            // move everything down 1 after the position
            // take the position and move the previous value there 
        }
        *(m_array + pos) = value;
        // move the value into the array's position
        m_size++;
        // increment size because you inserted a value, so the size of the array increases
        // this is to track the size of the array 
        return pos;
        // return the position the value was inserted
    }
    else
    // if any of the conditions fail, return -1
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
        /*
        for (int n = 0; n < m_size; n++)
        // creating a for loop to iterate through the array
        {
            if(value <= *(m_array + i) && *(m_array + i) < *(m_array + n))
            // using the two for loops, we compare each value to itself amd see if 
            // the value is smaller or equal to that value
            // and if ith's value is STRICTLY smaller than every nth's value
                // not <= because we want the first index where i is the smallest value, so cannot be equal
            {
                p = i;
                // make p the position where value is <= to ith's value and where i is the smallest value
                // with value's constraint
            }
        }
        */
    } 

    return insert(p, value);  
    // what this statement is doing:
        // int i = insert(p, value);
        // return i;

    // doing return insert(p, value) is weird
    // why is that when I just do insert(p, value)
    // we need to return the value at each step 
    // we need to return the value back to the function it is in 
}

bool Sequence::erase(int pos)
// when you use the new keyword, it's in those situations where you need to worry about deleting
// i did not expilicity create anything so I do not need to worry about deleting anything 
{
    if (0 <= pos && pos < m_size)
    // if pos is <= 0 and lower than the size of the array, meaning that it's an actual position in the array
    {
        for (int i = pos; i < m_size - 1; i++)
        // loop through the from the the position of the value and move the element next to it down 
        // 
        {
            *(m_array + i) = *(m_array + i+1);
        }
        // you cannot delete any variable, only pointers
        // can only delete stuff you dynamically allocated
        // *(m_array + m_size - 1) = NULL;
        // change the last position to nothing
        m_size--;
        // decrement the size to keep track of it 
        return true;
    } 
    else
    {
        return false;
    }
}

int Sequence::remove(const ItemType& value)
{
    int num_items_removed = 0;
    // counter to keep track of the number of items removed
    for (int i = 0; i < m_size; i++)
    // loop through the array
    {
        if (*(m_array + i) == value)
        // if the element at i equals the value
        // call the erase function in order to remove it and increment the counter
        {
            erase(i);
            i--;
            // m_size--;
            // erase decrements m_size already
            num_items_removed++;
        }
    }

    return num_items_removed;
    // return the number of items removed
    // if nothing was removed, then just return 0 
}

bool Sequence::get(int pos, ItemType& value) const
// const because the get function does not change Sequence at all
{
    if (0 <= pos && pos < m_size)
    // if pos is greater or equal to 0 and STRICTLY less than the size of array
    // then this is a valid position and we put the element at position into value 
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
    // if position is a valid position
    {
        *(m_array + pos) = value;
        // turn that position's element into value 
        return true;
    }
    else
    {
        return false;
    }
}

int Sequence::find(const ItemType& value) const
// const because it does not change anything of Sequence, just retrieves value 
{
    int p = -1;
    // make p = -1 if it does not find value
    for (int i = 0; i < m_size; i++)
    // loop through the array and see where an element's array equals value
    // if it equals value, turn p into that position and return it
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
    int m_temp;
    // intialize a temporary variable to switch the sizes
    ItemType temp;
    // initialize a temporary ItemType variable to switch the classes's array
    if (m_size < other.m_size)
    // if the size of the class is less than the size of the other's class
    // loop through the other since it would have more values that would have to transfer
    // transfer each element in the class to temp, even if it's empty
    // turn class's array into the other's array
    // turn other's array into the class's array using temp 
    {
        for (int i = 0; i < other.m_size; i++)
        {
            temp = *(m_array + i);
            *(m_array + i) = *(other.m_array + i);
            *(other.m_array + i) = temp;
        }
    } 
    else if (m_size > other.m_size)
    // if the size of the class is greater than the size of the other's class
    // loop through the  classsince it would have more values that would have to transfer
    // transfer each element in the other's to temp, even if it's empty
    // turn other class's array into the class's array
    // turn class's array into the other's array using temp  
    {
        for (int i = 0; i < m_size; i++)
        {
            temp = *(other.m_array + i);
            *(other.m_array + i) = *(m_array + i);
            *(m_array + i) = temp;
        }
    }

    m_temp = m_size;
    m_size = other.m_size;
    other.m_size = m_temp;
    // transfering the sizes of arrays
}