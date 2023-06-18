// Aaron Chien
#ifndef TESTNUM_S  // In case you haven't already defined the name TESTNUM
#define TESTNUM_S 4
#endif

#if TESTNUM_S == 1

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    s.insert(0, "a");
    s.insert(1, "b");
    s.insert(2, "e");
    s.insert(3, "b");
    s.insert(4, "c");
    assert(s.remove("b") == 2);
    assert(s.size() == 3);
    std::string x;
    assert(s.get(0, x)  &&  x == "a");
    std::cout <<  "x is: " << x << std::endl;
    assert(s.get(1, x)  &&  x == "e");
    assert(s.get(2, x)  &&  x == "c");
}

#elif TESTNUM_S == 2

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s1;
    s1.insert(0, "paratha");
    s1.insert(0, "focaccia");
    Sequence s2;
    s2.insert(0, "roti");
    s1.swap(s2);
    assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
                s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
}

#elif TESTNUM_S == 3

#include "Sequence.h"
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

#elif TESTNUM_S == 4

#include "Sequence.h"
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

#elif TESTNUM_S == 5

#include "Sequence.h"
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

    int x;

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

#elif TESTNUM_S == 6

#include "Sequence.h"
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

#elif TESTNUM_S == 7

#include "Sequence.h"
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

#elif TESTNUM_S == 8

#include "Sequence.h"
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

#elif TESTNUM_S == 9

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

// testing erase function
int main()
{
    Sequence s;
    s.insert("a");
    s.insert("b");
    s.insert("c");
    s.insert("a");
    s.insert("a");
    s.insert("b");
    s.insert("c");
    s.insert("a");
    s.insert("c");
    s.insert("a");
    assert(s.remove("a") == 5);
    assert(s.size() == 5);

}

#elif TESTNUM_S == 10

// using ITEMTYPE = std::string

#include "Sequence.h"
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

#elif TESTNUM_S == 11

// using itemtype = unsigned long
#include "Sequence.h"
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

#elif TESTNUM_S == 12

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

// testing swap function
int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.size() == 0);
    assert(s.insert(4, 5) == -1);
    assert(s.insert(1) == 1);
    assert(s.insert(2) == 2);
    assert(s.insert(1) == 3);
    assert(s.)

}

#else

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