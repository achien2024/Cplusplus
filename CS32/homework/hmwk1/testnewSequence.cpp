// Aaron Chien

#ifndef TESTNUM_N  // In case you haven't already defined the name TESTNUM
#define TESTNUM_N 1
#endif

#if TESTNUM_N == 1

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    s.insert(0, 62);
    s.insert(1, 63);
    s.insert(2, 64);
    s.insert(3, 63);
    s.insert(4, 66);
    assert(s.remove(63) == 2);
    assert(s.size() == 3);
    ItemType x;
    assert(s.get(0, x)  &&  x == 62);
    assert(s.get(1, x)  &&  x == 64);
    assert(s.get(2, x)  &&  x == 66);
}

#elif TESTNUM_N == 2

// aaron is on this one

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s1;
    s1.insert(0, 45);
    s1.insert(0, 54);
    Sequence s2;
    s2.insert(0, 81);
    s1.swap(s2);
    assert(s1.size() == 1  &&  s1.find(81) == 0);
    assert(s2.size() == 2  &&  s2.find(45) == 1  &&  s2.find(54) == 0);
}

#elif TESTNUM_N == 3

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    s.insert(0, "dosa");
    s.insert(1, "pita");
    s.insert(2, "");
    s.insert(3, "matzo");
    assert(s.find("") == 2);
    s.remove("dosa");
    assert(s.size() == 3  &&  s.find("pita") == 0  &&  s.find("") == 1  &&
                s.find("matzo") == 2);

}

#elif TESTNUM_N == 4

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1  &&  s.find(42) == 0);
    cout << "Passed all tests" << endl;
}

#elif TESTNUM_N == 5

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    for (int i = 0; i < DEFAULT_MAX_ITEMS - 1; i++)
    {
        s.insert(5);
    }

    s.insert(6);

    ItemType x;

    s.get(159, x);
    cout << s.size() << endl;
    cout << x << endl;
    
    s.erase(159);
    cout << s.size() << endl;
    s.get(159, x);
    cout << x << endl;
    s.get(158, x);
    cout << x << endl;
}

#elif TESTNUM_N == 6

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.insert(0, 3) == 0);
    assert(s.insert(1, 5) == 1);
    assert(s.insert(2, 7) == 2);
    assert(s.insert(3, 2) == 3);
    assert(s.insert(4, 1) == 4);
    s.insert(4);
}

#elif TESTNUM_N == 7

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.insert(0, 3) == 0);
    assert(s.insert(1, 5) == 1);
    assert(s.insert(2, 7) == 2);
    assert(s.insert(3, 2) == 3);
    assert(s.insert(4, 1) == 4);
    s.insert(4);
}

#elif TESTNUM_N == 8

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

// testing swap function
int main()
{
    Sequence s;
    Sequence a;
    assert(a.insert(5) == 0);
    assert(a.insert(5, 20) == -1);
    assert(a.insert(1, 30) == 1);
    assert(a.insert(4) == 0);
    cout << "next" << endl;
    a.swap(s);
    assert(a.size() == 0);
    assert(s.size() == 3);
    assert(a.empty());
    assert(!s.empty());
}

#elif TESTNUM_N == 9

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 24;

       // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v) != -1);

    // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);

       // When two Sequences' contents are swapped, their capacities are
       // swapped as well:
    a.swap(b);
    assert(a.insert(v) == -1);
    assert(b.insert(v) != -1);

}

#elif TESTNUM_N == 10

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence a(3);   // a can hold at most 1000 items
    Sequence b(4);      // b can hold at most 5 items

    a.insert(1);
    a.insert(3);
    a.insert(5);
    // a.insert(6);
    cout << a.size() << endl;

    b.insert(10);
    b.insert(20);
    b.insert(23);
    b.insert(89);

    cout << b.size() << endl;

    a = b;
    cout << a.size() << endl;
    cout << b.size() << endl;
    assert(a.size() == 4);
    assert(b.size() == 4);
}

#elif TESTNUM_N == 11

// using ItemType = std::string
#include "newSequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    s.insert(0, "lavash");
    s.insert(0, "tortilla");
    assert(s.size() == 2);
    ItemType x = "injera";
    assert(s.get(0, x) && x == "tortilla");
    assert(s.get(1, x) && x == "lavash");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

#else

// using ItemType = unsigned long
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

#endif