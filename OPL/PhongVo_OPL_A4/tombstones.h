#if not defined __TOMBSTONES_H__
#define __TOMBSTONES_H__


using namespace std;

template <class T> class Tombstone; // Tombstone template
template <class T> class Pointer;	// Pointer template

template <class T>
class Pointer {
public:
    Pointer<T>(){	// default constructor
		ptr = new Tombstone<T>();
        ptr->rip = true;
	}                            
    Pointer<T>(Pointer<T>& y){	// copy constructor
		if(y.ptr->rip) {
			cout<<"Dangling Reference Exception!"<<endl;
			exit(1);
		}
		ptr = y.ptr;
		if(ptr->referenceCounting != 0) ptr->referenceCounting++; 
	}
    Pointer<T>(T* x){	// bootstrapping constructor
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
    ~Pointer<T>(){	// destructor
		ptr->referenceCounting--;
		if(ptr->referenceCounting == 0 && !ptr->rip){
            cout<<"Memory Leak Exception!"<<endl;
			exit(1);
        }
        ptr = NULL;
	}

    T& operator*() const{	// dereferencing
		if(ptr->referenceCounting==0){
            cout<<"Memory Leak Exception!"<<endl;
			exit(1);
		}
		else if(ptr->rip == true){
			cout<<"Dangling Reference Exception!"<<endl;
			exit(1);
		}else{
            return *(ptr->value);
        }

	}
    T* operator->() const{	//field dereferencing
		if(ptr->referenceCounting==0){
            cout<<"Memory Leak Exception!"<<endl;
			exit(1);
		}
		else if(ptr->rip == true){
			cout<<"Dangling Reference Exception!"<<endl;
			exit(1);
		}else{
            return ptr->value;
        }

	}
    Pointer<T>& operator=(const Pointer<T>& t){		// assignment
        ptr->referenceCounting--;
        if(ptr->referenceCounting == 0){
            cout<<"Memory Leak Exception!"<<endl;
			exit(1);
		}
		ptr = t.ptr;
		ptr->referenceCounting++;
		if(ptr->rip){
			cout<<"Dangling Reference Exception!"<<endl;
			exit(1);
        }
		return *this; 
	}  
	
    friend void free(Pointer<T>& t){	//delete pointed-at object
        if(t.ptr->rip){
			cout<<"Dangling Reference Exception!"<<endl;
			exit(1);
        }else{
            delete t.ptr->value;
			t.ptr->rip = true;
        }
    }
		// 
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    // equality comparisons:
    bool operator==(const Pointer<T>& t) const{
		if(ptr->rip|| (t.ptr->rip)){
			cout<<"Dangling Reference Exception!"<<endl;
			exit(1);
		}
		else{
			return ptr->value == (t.ptr->value);		
		}

	}
    bool operator!=(const Pointer<T>& t) const{
		if(ptr->rip|| (t.ptr->rip)){
			cout<<"Dangling Reference Exception!"<<endl;
			exit(1);
		}
		else{
			return ptr->value != (t.ptr->value);	
		}
	}

    bool operator==(const int n) const{
		return ptr->value == NULL && n == 0;
	}
        // true if Pointer is null and int is zero
    bool operator!=(const int n) const{
        return !(ptr->value == NULL && n == 0);		
	}
        // false if Pointer is null and int is zero
	Tombstone <T> *ptr;
};

template <class T> 
class Tombstone {
public:
	int referenceCounting;	// reference counting for the Tombstone
	T* value;				// pointer of value to the actual address
	bool rip;				// boolean to check whether the tombstone is still unused or not
	Tombstone<T>(){			// constructor to initialize tombstone
        referenceCounting = 0;
        value = NULL;
        rip = false;
    }
};


template <class T>
bool operator==(const int n, const Pointer<T>& t) { 
	return t == n;
}
template <class T>
bool operator!=(const int n, const Pointer<T>& t) { 
	return t != n; 
}


#endif // __TOMBSTONES_H__
