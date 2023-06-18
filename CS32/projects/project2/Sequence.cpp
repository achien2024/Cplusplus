// Aaron Chien
#include "Sequence.h"
// #include "newSequence.h"
#include <iostream>
#include <string>

Sequence::Sequence()
// constructor for class Sequence, intializes the m_size to 0
// m_size will be tracking the size of the array in sequence 
{
    m_size = 0;
    HEAD = nullptr;
    TAIL = nullptr;
}

// copy constructor
Sequence::Sequence(const Sequence& other)
{
    m_size = 0;
    HEAD = nullptr;
    TAIL = nullptr;
    // needed to initialize all of this because if you do not, will have weird stuff
    // when you call the insert, you point to your own head, but your head is not pointing to anything
    Node* pointer;
    int p = 0;
    for (pointer = other.HEAD; pointer != nullptr; pointer = pointer->next)
    {
        insert(p, pointer->var);
        p++;
    }
}

bool Sequence::empty() const
// function to test if the Sequence is empty, sees if the size is 0
// const because it does not affect the any of the class member variables
{
    if (m_size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Sequence::size() const
// function to return the size of the sequence aka the array
// const because it just returns the size, does not affect any of the private member variables 
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
// insert function
{
    if (0 <= pos && pos <= m_size)
    // if the position inserted is greater or equal to 0
    // and if the position inserted is less than or equal to the size of the array
    {
        Node* item = new Node();
        // 
        Node* m_temp;
        item->var = value;
        // 
        if (m_size == 0)
        // if this is the first item
        {
            HEAD = item;
            TAIL = item;
            item->next = nullptr;
            item->prev = nullptr;
        }
        else if (pos == 0)
        // inserting at position 0
        {
            m_temp = HEAD;
            // A C, want B A C
            item->next = m_temp;
            // set B's next to point to A
            item->prev = nullptr;
            // set B's previous to null since it's in the front
            m_temp->prev = item;
            // set A's previous to B now instead of null
            HEAD = item;
            // set the head to the B instead of A
        } 
        else if (pos == m_size)
        // if pos is the size, than that means to add that item at the tail (the end)
        {
            m_temp = TAIL;
            // point the temp ptr to TAIL
            item->next = nullptr;
            // set the next ptr of node to NULL since now it should go nowhere
            item->prev = m_temp;
            // set the prev ptr of node to temp ptr (the last item) since it is no longer the last item 
            TAIL = item;
            // set TAIL to point to the last item
            m_temp->next = item;
            // fix the last item previously to now point to the next item 
        }
        else
        {
            m_temp = HEAD;
            for(int i = 1; i < pos && m_temp != nullptr; i++)
            // for(Node* pointer = HEAD; pointer != nullptr; pointer = pointer->next)
            {
                m_temp = m_temp->next;
                // set m_temp to be the node before the added node
                // A C and we want to put B between A and C
                // set m_temp to be A
            }

            item->prev = m_temp;
            // set B prev to A
            item->next = m_temp->next;
            // set B next to C
            m_temp->next->prev = item;
            // from A go to C
            // and set C prev to B
            m_temp->next = item;
            // set A next to B
        }
        m_size++;
        // increment size because you inserted a value, so the size of the array increases
        // this is to track the size of the array 
        return pos;
        // return the position the value was inserted
    }
    else
    // if any of the conditions fail, return -1
    {
        return -1;
    }
}

int Sequence::insert(const ItemType& value)
{
    int p = m_size;
    // if value is not the smallest item, insert it at the end
    int i = 0;
    // value to keep track of position
    for (Node* pointer = HEAD; pointer != nullptr; pointer = pointer->next)
    // creating a for loop to iterate through the array
    {
        if (value <= pointer->var)
        {
            p = i;
            // the position is i-1 since it will increment by 1 s
            break;
            // exit out of the for loop 
        }
        i++;
        // increment p by 1 to track the position we should be at 
    } 
    
    return insert(p, value);  
}

bool Sequence::erase(int pos)
{
    if (0 <= pos && pos < m_size)
    // if pos is <= 0 and lower than the size of the array, meaning that it's an actual position in the array
    {
        Node* pointer;
        // if the list has one item only
        if (m_size == 1 && pos == 0)
        {
            pointer = HEAD;
            HEAD = nullptr;
            TAIL = nullptr;
            delete pointer;
        }
        // if it's at the head
        else if (pos == 0 && m_size != 1)
        {
            pointer = HEAD;
            pointer->next->prev = nullptr;
            HEAD = pointer->next;
            // you do not need to do pointer->next = null
            // when you delete this, it deletes the entire address of that variable, but it doesn't cause a chain reaction
            delete pointer;
        }
        else if (pos == m_size -  1)
        {
            pointer = TAIL;
            pointer->prev->next = nullptr;
            TAIL = pointer->prev;
            delete pointer;
        }
        else
        {
            pointer = HEAD;
            for (int i = 0; pointer != nullptr && i < pos; pointer = pointer->next)
            {
                i++;
            }
            pointer->prev->next = pointer->next;
            pointer->next->prev = pointer->prev;
            delete pointer;
        }
        m_size--;
        return true;
    }
    else
    {
        return false;
    }
}

int Sequence::remove(const ItemType& value)
{
    int num_items_removed = 0;
    // counter to keep track of the number of items removed
    int i = 0;
    // counter to keep track of which position to delete 
    Node* ptr = HEAD;
    // ptr is head trying to delete
    // ptr is tail trying to delete 
    while (ptr != nullptr)
    // for (ptr = HEAD; ptr != nullptr; ptr = ptr->next, i++)
    // loop through the array

    // only edge case to worry about is the head and tail
    // and another edge case of deleting the head 

    // when deleting the head, move the ptr forward so it knows where the next position is 
    // when deleting the tail, move the ptr forward which is null so 

    {
        if (ptr->var == value)
        // if the element at i equals the value
        // call the erase function in order to remove it and increment the counter
        {
            ptr = ptr->next;
            erase(i);
            num_items_removed++;
            // erase takes care of special cases like 1 items
            // m_size--;
            // erase decrements m_size already
        }
        else
        {
            ptr = ptr->next;
            // you need to move the ptr forward
            i++;
        }
            // ptr = ptr->prev;
            // "start the loop again code"
                // this is causing your code to be slow 
            // THE COMMENTS BELOW IS WHAT YOU DID AT 2AM!
            // so the issue here is that if we have only item here and that item gets erased
            // we set ptr = HEAD which is nullptr
            // ptr->next points to nothing so it will give you a segmentation error
            // we set ptr = HEAD to restart the array
    }

    return num_items_removed;
    // return the number of items removed
    // if nothing was removed, then just return 0 
}

bool Sequence::get(int pos, ItemType& value) const
// const because the get function does not change Sequence at all
{
    if (0 <= pos && pos < m_size)
    // if pos is greater or equal to 0 and STRICTLY less than the size of array
    // then this is a valid position and we put the element at position into value 
    {
        int i = 0;
        Node* pointer;
        // create a node pointer
        for(pointer = HEAD; pointer != nullptr && i < pos; pointer = pointer->next)
        // set the pointer to head and iterate through the list until you're at the position 
        {
            i++;
            // increment i to keep track of the loop
        }
        value = pointer->var;
        // set the value to the pointer's value
        return true;
    }
    else 
    {
        return false;
    }
}

bool Sequence::set(int pos, const ItemType& value) 
{
    if (0 <= pos && pos < m_size)
    // if position is a valid position
    {
        int i = 0;
        Node* pointer;
        // create node pointer
        for(pointer = HEAD; pointer != nullptr && i < pos; pointer = pointer->next)
        // set pointer to HEAD and iterate through the list
        {
            i++;
            // increment i to keep track of the loop
        }
        pointer->var = value;
        // change the pointer's value 
        return true;
    }
    else
    {
        return false;
    }
}

int Sequence::find(const ItemType& value) const
// const because it does not change anything of Sequence, just retrieves value 
{
    int p = -1;
    // make p = -1 if it does not find value
    int i = 0;
    // tracker for loop
    Node* pointer;
    // create a Node pointer
    for(pointer = HEAD; pointer != nullptr; pointer = pointer->next)
    // iterate through the linked list
    {
        i++;
        // increment i 
        if (pointer->var == value)
        // is the variable equals that value
        // then we have found the value, and we take i - 1 as the position 
        {
            p = i - 1;
            break;
        }
    }

    return p;
}

void Sequence::swap(Sequence &other)
{
    // swap the head and tail pointers 
    Node* temp_ptr;
    temp_ptr = HEAD;
    HEAD = other.HEAD;
    other.HEAD = temp_ptr;

    temp_ptr = TAIL;
    TAIL = other.TAIL;
    other.TAIL = temp_ptr;

    int temp_size;
    temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
}

Sequence::~Sequence()
{
    Node* pointer;
    // int p = 0;
    int iter = m_size;
    for(int p = 0; p < iter; p++)
    {
        erase(0);
    }
    /*
    for(pointer = HEAD; pointer != nullptr; pointer = pointer->next)
    {
        erase(p);
    }
    */
}

Sequence& Sequence::operator= (const Sequence& rhs)
{
    if (this != &rhs)
    {
        Sequence temp(rhs);
        // was trying to copy a const Sequence into an unsigned long by doing ItemType temp(rhs)
            // basically you were trying to convert a const data type into a different data type which wouldn't work in this case
        // delete[] m_array;
        swap(temp);
        // delete temp not needed as it will automaticall call the manually created destructor 
    }

    return *this;
    // statically assigned local variables only typically use &
    // if you plan on returning something large, use a pointer 
        // & *, **
        // you treat the & like a normal object
        // using a reference type is used for parameters 
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq2.size() < seq1.size() && !seq2.empty())
    {
        int p = 0;
        // position tracker
        int c = 0;
        int r = -1;
        // returner if seq2 is not found in se1
        ItemType x1, x2;
        while(p < seq1.size())
        {
            seq1.get(p, x1);
            seq2.get(c, x2);
            if (x1 == x2)
            {
                c++;
                // seq2.get(c, x2);
            }
            else
            {
                while (c > 0)
                // while c is above 0, i want to decrement c and p so that 
                // x2 goes back to the beginning
                // x1 goes back to the last time they were not equa 
                {
                    p--;
                    c--;
                }
                // seq2.get(p, x2);
            }
            if (c == seq2.size())
            // once c is the size of seq2, then it means that it iterated through the entire list
            // of seq2 and it was found in seq1
            {
                r = p - (seq2.size() - 1);
                // so r becomes the first position where the sequence begins
                // r = position of the last item in seq2 in seq1 minus seq2's size - 1
                    // 1 is there to account that size is one greater than position 
                break;
                // break out of the while statement 
            }
            p++;
        }
        return r;
    }
    else
    {
        return -1;
    }
}

/*
void Sequence::dump() const
{
    Node* ptr = HEAD;
    while(ptr != nullptr)
    {
        std::cerr << ptr->var << std::endl;
        ptr = ptr->next;
    }
}
*/


void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    int total_size;
    total_size = seq1.size() + seq2.size();
    int i = 0;
    // integer to keep position of where to insert in result
    int s1, s2; 
    // integer to get position of seq1 and seq2 values
    s1 = seq1.size() - 1;
    // variable to get the last position of seq1
    s2 = seq2.size() - 1;
    // variable to get the last position of seq2
    ItemType x;
    // x value for get

    Sequence temp;
    while (i < seq1.size())
    {
        seq1.get(s1, x);
        temp.insert(i, x);
        s1--;
        i++;
    }
    while (i < total_size)
    {
        seq2.get(s2, x);
        temp.insert(i, x);
        s2--;
        i++;
    }
    result = temp;
}
