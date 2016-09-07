#include <iostream>
#include <vector>
using namespace std;


template <typename T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &);
	T pop();
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};

template <typename T>
stack<T>::stack() : array_(nullptr), array_size_(0), count_(0){};

template <typename T>
size_t stack<T>::count() const{ return count_; }

template <typename T>
void stack<T>::push(T const &a){
	if (array_ == nullptr){ array_ = new T[1]; array_[0] = a; count_++; array_size_ = count_*sizeof(T); }
	else { T *p = new T[count_]; 
	for (int i = 0; i < count_; i++) p[i] = array_[i];
	delete[] array_;
	count_++; array_size_ = count_*sizeof(T);
	array_ = new T[count_];
	for (int i = 0; i < (count_ - 1); i++) array_[i] = p[i]; delete[] p;
	array_[count_-1] = a;
	}
}

template <typename T>
T stack<T>::pop(){ if (!count_) throw("stack pust");
else { count_--; array_size_ = count_*sizeof(T);
	   T *p = new T[count_];
	   for (int i = 0; i < count_; i++) p[i] = array_[i];
	   T x = array_[count_];
	   delete[] array_;
	   array_ = new T[count_];
	   for (int i = 0; i < count_; i++) array_[i] = p[i];
	   return x;
	}
}
