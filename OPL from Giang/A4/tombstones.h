//
//  tombstones.h
//
//  Created by Hilton Carboo and Muhammad Muneeb on 4/3/18.
//  Copyright © 2018 BlaqCo. All rights reserved.
//
#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__

using namespace std;

// pointer template
template <class T> class Pointer;

// Tombstone template
template <class T> class Tombstone;

// method for memory leak.
void MLerror()
{
    cout<<"A Memory Leak Excepted!"<<endl;
    exit(1);
}

// for Dangling reference
void DRerror()
{
    cout<<"There is Dangling Reference Excepted!"<<endl;
    exit(1);
}


template <class T>
class Tombstone
{
public:
    // counting reference for a Tombstone
    int referenceCounting;
    // pointer value to a actual address
    T* value;
    // bool var to check tombstones is still being used or not
    bool rip;
    // initializing constructor for tombstone
    Tombstone<T>()
    {
        referenceCounting = 0;
        value = NULL;
        rip = false;
    }
};


template <class T>
class Pointer
{
public:
    // Initialized pointer to Tombstone
    Tombstone <T> *ptr;
    Pointer<T>(){
        // default constructor
        ptr = new Tombstone<T>();
        // won't be usable while initializing
        ptr->rip = true;
    }
    Pointer<T>(Pointer<T>& y)
    {
        // copy constructor
        // y is referring to the pointer
        if(y.ptr->rip) {
            DRerror();
    // when y is not used, that means the dangling reference is being accessed
        }
        ptr = y.ptr;
        if(ptr->referenceCounting != 0) ptr->referenceCounting++;
    }
    Pointer<T>(T* x)
    {
        //  constructor bootstrapping
        ptr = new Tombstone<T>();
        ptr->value = x;
        ptr->rip = false;
        if(x != NULL){
            ptr->referenceCounting = 1;
        }
        else{
            ptr->referenceCounting = 0;
        }
    }
    
    // argument should always be a call to new
    ~Pointer<T>()
    {
        // destructor
        ptr->referenceCounting--;  // just delete a one of the pointer
        if(ptr->referenceCounting == 0 && !ptr->rip){
            MLerror();
        // if rip is false and counting is zero than there is a memory leak
        }
        ptr = NULL;
    }
    
    T& operator*() const{
        // dereferencing
        if(ptr->referenceCounting==0){
            MLerror();
        // if reference counting reaches to 0 which indicates we are running in to a memory leak excp
        }
        else if(ptr->rip == true){
            // if rip is true than there is a dangling reference except
            DRerror();
        }else{
            return *(ptr->value); //else return the actual value of it
        }
        
    }
    T* operator->() const{
        // field dereferencing
        if(ptr->referenceCounting==0){
            MLerror();
            // if reference counting reaches to 0 which indicates we are running in to a memory leak excp
        }
        else if(ptr->rip == true){
            DRerror();        // if rip is true than there is a dangling reference excp
        }else{
            return ptr->value; //else return the actual value of it
        }
        
    }
    Pointer<T>& operator=(const Pointer<T>& t){     // assignment
        ptr->referenceCounting--;
        if(ptr->referenceCounting == 0){
            MLerror();
    // if reference counting reaches to 0 which indicates we are running in to a memory leak excp
        }
        ptr = t.ptr;
        ptr->referenceCounting++; // reference count incrementing
        if(ptr->rip){
            DRerror();  // if rip is true than there is a dangling reference except
        }
        return *this;
    }
    
    friend void free(Pointer<T>& t){
        // delete pointed-at object
        if(t.ptr->rip)
        {
            DRerror();    // if rip is true than there is a dangling reference except
        }else{
            delete t.ptr->value; // delete pointer of obj
            t.ptr->rip = true; // set tombstone pointer to true
        }
    }
    
    // This is essentially the inverse of the new inside the call to
    // the bootstrapping constructor. It should delete the pointed-to
    // object (which should in turn call its destructor).
    // equality comparisons:
    bool operator==(const Pointer<T>& t) const{
        if(ptr->rip|| (t.ptr->rip)){
            DRerror(); // if rip is true than there is a dangling reference except
        }
        else{
            return ptr->value == (t.ptr->value);
        }
        
    }
    bool operator!=(const Pointer<T>& t) const{
        if(ptr->rip|| (t.ptr->rip)){
            DRerror(); // if rip is true than there is a dangling reference except
        }
        else{
            return ptr->value != (t.ptr->value);
        }
    }
    
    bool operator==(const int n) const
    {
        return ptr->value == NULL && n == 0;
    }
    // return true if pointer is 0 or null
    bool operator!=(const int n) const{
        return !(ptr->value == NULL && n == 0);
    }
    // return false if pointer is 0 or null
    
};


template <class T>
bool operator==(const int n, const Pointer<T>& t)
{ return t == n; }

template <class T>
bool operator!=(const int n, const Pointer<T>& t)
{ return t != n; }

#endif
