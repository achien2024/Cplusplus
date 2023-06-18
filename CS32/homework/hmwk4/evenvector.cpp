// Aaron Chien
// 405498016

void removeEven(vector<int>& v)
{
    vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
    {
        if (*it % 2 == 0)
        {
            it = v.erase(it);
            it--;
        }
    }
}