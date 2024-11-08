//
// Created by bob on 4/3/20.
//
// Updated by bob on 3/13/23.
//

#ifndef LINEARLIST_H
#define LINEARLIST_H

#include <cstdint>
#include <stdexcept>

template <typename ListType>
struct CDListNode {
    ListType
        datum;
    CDListNode<ListType>
        *next,
        *prev;
};

template <typename ListType>
class CDList {
public:
        
    //=========================================================================
    //--------------------------- common operations ---------------------------
    //=========================================================================

    //=========================================================================
    // LinearList()
    //  constructor
    //

    CDList() {

        head = nullptr;     // as discussed in the slides
        cur = nullptr;
        count = 0;
    }

    //=========================================================================
    // LinearList(LinearList<ListType> &l)
    //  copy constructor
    //

        CDList(CDList<ListType> &l) {
            CDListNode<ListType>
                *ptr,
                *tmp=l.head,
                **prev = &head;

            cur = nullptr;
            // count once for each node in existing list
            for (uint32_t i=0;i<l.count;i++) {
                // make a new node
                ptr = new CDListNode<ListType>;

                // copy one value from existing list
                ptr->datum = tmp->datum;

                // attach new node to end of new list
                *prev = ptr;

                // move pointer (to pointer) to end of new list
                prev = &((*prev)->next);

                // move to next node in existing list
                tmp = tmp->next;
            }

            // point last node to first node
            ptr->next = head;

            // set all back pointers
            prev = head;
            for (uint32_t i=0;i<l.count;i++) {
                ptr = ptr->next;
                ptr->prev = prev;
            }

            count = l.count;
        }

    //=========================================================================
    // ~LinearList()
    //  destructor
    //

    ~CDList() { clear(); }

    //=========================================================================
    // uint32_t size()
    //  return size of list (number of nodes)
    //

    uint32_t size() { return count; }

    //=========================================================================
    // bool isEmpty()
    //  return true if list is empty, false otherwise
    //

    bool isEmpty() { return count == 0; }

    //=========================================================================
    // void clear()
    //  remove all nodes from list, reset head and count
    //
    // Notes:
    // - uses a counted loop instead of looking for the nullptr. that way, if
    //   this is changed to a circular list (which has no null pointers), the
    //   code won't be affected.
    //

    void clear() {
        CDListNode<ListType>
            *tmp;

        for (int i=0;i<count;i++) {
            tmp = head->next;           // remember second node in the list
            delete head;                // remove the first node
            head = tmp;                 // second node moves to front
        }

        head = nullptr;                 // all nodes removed, reset list
        count = 0;
        cur = nullptr;
    }

    //=========================================================================
    //----------------------- list-specific operations ------------------------
    //=========================================================================

    //=========================================================================
    // uint32_t search(const ListType &key)
    //  search for key in the list
    //
    // Parameter:
    //  key - what to look for
    //
    // Returns:
    //  - index of first occurrence if key exists in the list
    //  - throws a domain_error exception if key is not in the list
    //

    uint32_t search(const ListType &key) {
        CDListNode<ListType>
            *tmp = head;                // start at head of list

        for (uint32_t i=0;i<count;i++) {     // step through the list
            if (key == tmp->datum) {     // if key found, stop and return index
                cur = tmp;
                return i;
            }
            tmp = tmp->next;            // walk to next node
        }

        // if we get here, the key was not in the list
        throw std::domain_error("key not found");
    }

    //=========================================================================
    // ListType &operator[](int32_t pos)
    //  return reference to element at given position, works like array []
    //
    // Parameter:
    //  pos - position in the list to access
    //
    // Returns:
    //  - reference to specified element in the list
    //  - throws a domain_error exception if pos is invalid (< 0 or >= count)
    //

    ListType &operator[](int32_t pos) {
        CDListNode<ListType>
            *tmp = head;                // start at head of list

        if (pos < -count || pos >= count) {
            throw std::domain_error("Invalid index");
        }

        if (pos < 0) {
            for (int32_t i=0;i>-pos;i--) {
                tmp = tmp->prev;
            }
        } else {
            for (int32_t i=0;i<pos;i++) {        // step through the list
                tmp = tmp->next;            // walk to next node
            }
        }

        return tmp->datum;              // return reference;
    }

    //=========================================================================
    // void map(void (*fp)(ListType &))
    //  apply given function to each element in the list
    //
    // Parameter:
    //  fp - pointer to function to call
    //

    void map(void (*fp)(ListType &)) {
        CDListNode<ListType>
            *tmp = head;                // start at head of list

        for (int i=0;i<count;i++) {     // step through the list
            (*fp)(tmp->datum);          // call the function, pass the datum
            tmp = tmp->next;            // walk to next node
        }
    }

    //=========================================================================
    // void insert(uint32_t pos,const ListType &d)
    //  insert element into the list
    //
    // Parameters:
    //  pos - position of new element; subsequent elements shifted
    //    d - value to be inserted
    //
    // Notes:
    //  - throws a domain_error exception if pos is invalid (> count)
    //  - predecessor work is done by pointing to the pointers. this allows all
    //    positions in the list to be treated identically, without regard to
    //    whether it is the list object or a node pointing to the new node.
    //    conceptually the walking process is the same.
    //

    void insert(uint32_t pos, const ListType &d) {
        CDListNode<ListType>
            *ptr,
            **pred,
            *successor;

        // step 0: validate pos
        if (pos > count) {
            throw std::domain_error("Invalid index");
        }

        // step 1: allocate new node and place datum
        ptr = new CDListNode<ListType>;
        ptr->datum = d;

        if (count == 0) {
            // make the node point to itself forwards and backwards
            ptr->next = ptr->prev = ptr;

            // set the head pointer
            head = ptr;

            // update the count
            count++;

            // done
            return;
        }

        // step 2: find the predecessor
        pred = &head;
        for (int i=0;i<pos;i++)
            pred = &((*pred)->next);	// walk to next pointer
        // find the node after the new node
        successor = *pred;

        // step 3: copy predecessor's next pointer to new node
        ptr->next = *pred;
        // new node points backwards to predecessor
        ptr->prev = successor->prev;

        // step 4: predecessor points to new node
        *pred = ptr;
        // successor points to new node
        successor->prev = ptr;

        // step 5: update count
        count++;
    }

    //=========================================================================
    // void remove(uint32_t pos)
    //  remove element from the list
    //
    // Parameter:
    //  pos - position of element to be removed; subsequent elements shifted
    //
    // Notes:
    //  - throws a domain_error exception if pos is invalid (>= count)
    //  - predecessor work is done by pointing to the pointers. this allows all
    //    positions in the list to be treated identically, without regard to
    //    whether it is the list object or a node pointing to the new node.
    //    conceptually the walking process is the same.
    //

    void remove(uint32_t pos) {
        CDListNode<ListType>
            *ptr,
            **pred,
            *successor;

        // step 0: validate pos
        if (pos >= count) {
            throw std::domain_error("Invalid index");
        }
        if (count==1) {
            // remove the node
            delete head;

            // reset head and cur
            head = cur = nullptr;

            // update the count
            count--;

            // done
            return;
        }

        // step 1: find the predecessor
        pred = &head;
        for (int i=0;i<pos;i++)
            pred = &((*pred)->next);

        // step 2: remember node to be deleted
        ptr = *pred;
        // find the node after the node to be deleted
        successor = ptr->next;
        // if we are removing the current node, set cur to nullptr
        if (cur == ptr) {
            cur = nullptr;
        }

        // step 3: copy ntbd's pointer to predecessor... pointing around ntbd
        *pred = ptr->next;
        // successor points backwards to predecessor
        successor->prev = ptr->prev;

        // step 4: delete the node
        delete ptr;

        // step 5: update count
        count--;
    }

    ListType& first() {
        if (count==0) {
            throw std::runtime_error("tried to access first of empty list.");
        }
        cur = head;
        return cur->datum;
    }

    ListType& last() {
        if (count==0) {
            throw std::runtime_error("tried to access last of empty list.");
        }
        cur = head->prev;
        return cur->datum;
    }

    bool isFirst() {
        if (cur==nullptr) return false;
        return cur==head;
    }

    bool isLast() {
        if (cur==nullptr) return false;
        return cur==head->prev;
    }

    ListType& next() {
        if (cur==nullptr) {
            throw std::runtime_error("tried to access next of empty list.");
        }
        cur = cur->next;
        return cur->datum;
    }

    ListType& prev() {
        if (cur==nullptr) {
            throw std::runtime_error("tried to access prev of empty list.");
        }
        cur = cur->prev;
        return cur->datum;
    }

    ListType& current() {
        if (cur==nullptr) {
            throw std::runtime_error("tried to access current of empty list.");
        }
        return cur->datum;
    }

private:
    CDListNode<ListType>
        *head,
        *cur;
    int32_t
        count;
};

#endif //LINEARLIST_H
