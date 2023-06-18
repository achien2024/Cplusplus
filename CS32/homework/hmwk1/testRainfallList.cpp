// Aaron Chien

#ifndef TESTNUM_R  // In case you haven't already defined the name TESTNUM
#define TESTNUM_R 1
#endif

#if TESTNUM_R == 1

#include "Sequence.h"
#include "RainfallList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    RainfallList x;

    assert(x.add(10));
    assert(x.add(5));
    assert(x.add(300));
    assert(x.add(250));
    assert(!x.remove(50));
    assert(x.maximum() == 300);
    assert(x.remove(300));
    assert(x.remove(250));
}

#elif TESTNUM_R == 2

#include "Sequence.h"
#include "RainfallList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    RainfallList x;

    assert(x.add(10));
    assert(x.add(5));
    assert(x.add(300));
    assert(x.add(250));
    assert(x.minimum() == 5);
    assert(x.maximum() == 300);    
}

#elif TESTNUM_R == 3

#include "newSequence.h"
#include "RainfallList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    RainfallList x;

    assert(x.minimum() == NO_RAINFALLS);
    assert(x.maximum() == NO_RAINFALLS);
    assert(!x.add(500));
    assert(!x.add(-50));

    // x.m_rainfall.dump();
    
}

#else

#include "newSequence.h"
#include "RainfallList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    RainfallList x;

    assert(x.add(10));
    assert(x.add(5));
    assert(x.add(300));
    assert(x.add(250));
    cout << x.minimum() << endl;
    assert(x.minimum() == 5);
    assert(x.maximum() == 300);    
}
#endif