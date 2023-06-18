// Aaron Chien
// 405498016
void removeBad(vector<Restaurant*>& v)
{
    vector<Restaurant*>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
    {
        if ((*it)->stars() <= 2)
        {
            delete *it;
            it = v.erase(it);
            it--;
        }
    }
}
// erase should just remove it from the container 
// once erased statically variable gets deleted out of range
// when something is dynamcalliy allocated, it is your responsibility to delete it 
