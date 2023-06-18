// Aaron Chien
// 405498016
void removeEven(list<int>& li)
{
    list<int>::iterator it;
    // when you derefence an iterator, you get the value
    // li.begin() and li.end() are pointing, not giving the values so you wouldn't dereference 
    for(it = li.begin(); it != li.end(); it++)
    {
        if (*it % 2 == 0)
        {
            it = li.erase(it);
            it--;
        }
    }
}