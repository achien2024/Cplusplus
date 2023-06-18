// Aaron Chien
// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    int z = n - 1;
    if (z >= 0)
    {
        if (somePredicate(a[z]))
        {
            return allTrue(a, n - 1);
        }
        else
        {
            return false;
        }
    }
    // recursively iterate through the array and keep returning true until n-1 is < 0 or the function returns false when predicate fails
    else
    {
        return true;
    }
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const string a[], int n)
{
    if (n > 0)
    {
        if (somePredicate(a[n-1]))
        {
            return (1 + countTrue(a, n-1));
            // keep adding 1 everytime it passes predicate
        }
        else
        {
            return (countTrue(a, n-1));
            // simply skip that number and don't count it, should return 0 
        }
    }
    else
    {
        return 0;
        // base case when n runs out 
    }
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    // fail case
    if (n <= 0)
    {
        return -1;
    }

    // base case 
    if (somePredicate(*a))
    {
        return 0;
    }
    
    // go to the next one and check that position 
    int count = firstTrue(a + 1, n-1);
    if (count == -1)
    {
        return -1;
    }
    else
    {
        return count + 1;
    }
}

// Return the subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
// that no strings are to be considered to be in the array, return -1.
int positionOfMax(const string a[], int n)
{
    // fail case 
    if (n <= 0)
    {
        return -1;
    }
    // base case
    if (n == 1)
    {
        return 0;
    }
    // break the problem into smaller problems 
    // return the start of the array, the first index and compare it to the next one 
    int i = positionOfMax(a, n - 1);
    int prev = n-1;
    // compare it to the previous one 
    if (a[prev] > a[i])
    {
        return prev;
    }
    else
    {
        return i;
    }
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
 // For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then the function should return true if a2 is
//    "sonia" "ketanji" "samuel"
// or
//    "sonia" "elena" "elena"
// and it should return false if a2 is
//    "sonia" "samuel" "ketanji"
// or
//    "john" "ketanji" "ketanji"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
    // base case
    if (n2 <= 0)
    {
        return true;
    }

    // fail case
    if (n1 < 0)
    {
        return false;
    }

    // if the two elements in the array are the same, move them both down and check that one as well
    if (*a1 == *a2)
    {
        n2 = n2 - 1;
        n1 = n1 - 1;
        return contains(a1+1, n1, a2+1, n2);
    }
    else
    // simply move the a1 down instead of moving both 
    {
        n1 = n1 - 1;
        return contains(a1+1, n1, a2, n2);
    }
}