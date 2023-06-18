#include <iostream>
#include "Sequence.h"
#include <cassert>
using namespace std;

int main() {
    cout << "TEST 1" << endl;
    Sequence test1;
    assert(test1.empty());
    assert(test1.size() == 0);
    // testing empty and size 
    cout << endl;

    cout << "TEST 2 " << endl;
    Sequence test2;
    assert(test2.insert(1, "z") == -1);
    // testing for invalid positions
    assert(test2.insert(0, "z") == 0);
    // testing insert
    assert(test2.insert(1, "i") == 1);
    cout << endl;

    cout << "TEST 3 " << endl;
    Sequence test3;
    assert(test3.insert("b") == 0);
    assert(test3.insert("d") == 1);
    assert(test3.insert("c") == 1);
    assert(test3.insert("a") == 0);
    cout << endl;

    cout << "TEST 4 " << endl;
    Sequence test4;
    assert(test4.insert(0, "i") == 0);
    assert(test4.insert(1, "want") == 1);
    assert(test4.insert(2, "to") == 2);
    assert(test4.insert(3, "sleep") == 3);
    assert(test4.insert("sleep") == 1);
    assert(test4.insert("sleep") == 1);
    assert(test4.insert("sleep") == 1);
    // I sleep sleep sleep want to sleep
    cout << endl;
    assert(test4.erase(1));
    // I sleep sleep want to sleep
    cout << endl;
    assert(test4.remove("sleep") == 3);
    // I want to
    cout << endl;

    cout << "TEST 5 " << endl;
    Sequence test5;
    assert(test5.insert(0, "i") == 0);
    assert(test5.insert(1, "am") == 1);
    assert(test5.insert(2, "getting") == 2);
    assert(test5.insert(3, "boba") == 3);
    assert(test5.insert("sleep") == 4);
    assert(test5.insert("sleep") == 4);
    assert(test5.insert("sleep") == 4);
    ItemType x;
    assert(test5.get(3, x) && x == "boba");
    assert(test5.get(6, x) && x == "sleep");
    assert(test5.find("sleep") == 4);
    cout << endl;
    // i am getting boba sleep sleep sleep 
    assert(test5.set(4, "to"));
    assert(test5.set(5, "celebrate"));
    assert(test5.set(6, "life"));
    assert(test5.find("sleep") == -1);
    cout << endl;
    // i am getting boba to celebrate life

    cout << "TEST 6" << endl;
    // Copy Construcor
    Sequence test6(test5);
    assert(test6.insert("am") == 0);
    // am i am getting boba to celebrate life
    cout << endl;
    // i am getting boba to celebrate life
    cout << endl;

    cout << "SWAP TEST" << endl;
    // Swap
    // a b c d
    cout << endl;
    // i want to
    cout << endl;
    test3.swap(test4);
    // i want to
    cout << endl;
    // a b c d
    cout << endl;
    assert(test4.insert("e") == 4);
    // a b c d e
    cout << endl;
    // i want to 
    cout << endl;

    cout << "ASSIGNMENT OPERATOR" << endl;
    // Assignment operator 
    test1 = test5;
    // i am getting boba to celebrate life
    cout << endl;
    assert(test1.insert(3, "tiger") == 3);
    // i am getting tiger boba to celebrate life
    cout << endl;
    // i am getting boba to celebrate life
    cout << endl;

    cout << "SUBSEQUENCE" << endl;
    // Subsequence
    Sequence test7;
    test7.insert(0, "bo");
    test7.insert(1, "boba");
    test7.insert(2, "bobo");
    test7.insert(3, "boba");
    test7.insert(4, "boba");
    test7.insert(5, "bo");
    test7.insert(6, "bo");
    test7.insert(7, "bo");
    test7.insert(8, "bo");
    test7.insert(9, "boba");
    test7.insert(10, "bobo");
    test7.insert(11, "boba");
    test7.insert(12, "bo");

    Sequence test8;
    test8.insert(0, "bo");
    test8.insert(1, "bo");
    test8.insert(2, "boba");
    test8.insert(3, "bobo");

    assert(subsequence(test7, test8) == 7);

    Sequence test9;
    assert(subsequence(test9, test8) == -1);
    assert(subsequence(test8, test9) == -1);
    cout << endl;

    cout << "CONCATREVERSE" << endl;
    // concatereverse
    // z i
    cout << endl;
    // i want to
    cout << endl;
    Sequence test10;
    concatReverse(test2, test3, test10);
    // i z to want i
    cout << endl;

    concatReverse(test2, test3, test2);
    // i z to want i 
    cout << endl;

    concatReverse(test3, test3, test3);
    // to want i to want i 
    cout << endl;

    cout << "all test cases passed!" << endl;
}