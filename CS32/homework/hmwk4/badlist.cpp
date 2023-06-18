// Aaron Chien
// 405498016
void removeBad(list<Restaurant*>& li)
// li is a list data structure of restaurant pointers
{
    list<Restaurant*>::iterator it;
    // create an iterator called it pointing to the list of restaurant pointers
    for (it = li.begin(); it != li.end(); it++)
    {
        if ((*it)->stars() <= 2)
        // since the iterator acts like a pointer pointing to resturant pointers
        // you would deference the iterator to get the resturant pointer
        // then deference that restaurant pointer to get the values
        {
            delete *it;
            // iterator is like a pointer pointing to a restaurant pointer 
            // you delete the deferenced iterator to delete the pointer 
            it = li.erase(it);
            // C++ erase is deleting that object and pusing it into vector int destroyedOnes 
            it--;
        }
    }
}