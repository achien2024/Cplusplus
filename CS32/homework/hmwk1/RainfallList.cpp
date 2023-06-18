// Aaron Chien

#include "RainfallList.h"
#include <iostream>

RainfallList::RainfallList()
// constructor for RainfallList class 
// didn't initialize anything since for each class of Rainfalllist, the maximum value it can hold is 160
{
    
}

bool RainfallList::add(unsigned long rainfall)
// function for adding in rain observations
{
    if (rainfall >= 0 && rainfall <= 400)
    // if the rainfall observation is valid, insert it into m_rainfall Sequence class
    {
        // m_rainfall.insert(m_rainfall.size(), rainfall);
        m_rainfall.insert(rainfall);
        return true;
    }
    else
    {
        return false;
    }
}

bool RainfallList::remove(unsigned long rainfall)
// function to remove something from the sequence of m_rainfall class
{
    return (m_rainfall.erase(m_rainfall.find(rainfall)));
    // m_rainfall.find(rainfall) finds the position where rainfall is
    // .erase() would then take that position and remove it from the sequence
    // .erase() returns true if the value was removed
    // if the rainfall was non-existent, the find would be -1, and erase would see -1 and return false 
    // since -1 is not a valid position
}

int RainfallList::size() const
// returns the size of the sequence of m_rainfall 
{
    return m_rainfall.size();
}

unsigned long RainfallList::minimum() const
// returns the minimum value of the sequence
{
    if (m_rainfall.empty())
    // if the rainfall is empty, return NO_RAINFALLS
    {
        return NO_RAINFALLS;
    } 
    else
    {
        ItemType x;
        // initialize an ItemType (insigned long) variable
        m_rainfall.get(0, x);
        // retrieve the 0 index value in sequence since we used insert functions to insert values
        // the entire thing should be ordered least to greatest
        // get would store the element at position 0 into x 
        return x;
        // return x
    }
}

unsigned long RainfallList::maximum() const
{
    if (m_rainfall.empty())
    {
        return NO_RAINFALLS;
    } 
    else
    {
        ItemType x;
        // initialize an ItemType (insigned long) variable
        m_rainfall.get(m_rainfall.size() - 1, x);
        // retrieve the last index value in sequence since we used insert functions to insert values
        // the entire thing should be ordered least to greatest
        // get would store the element at the last position into x 
        return x;
    }
}