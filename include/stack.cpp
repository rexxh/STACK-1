#ifndef stack_cpp
#define stack_cpp
#pragma once
#include <iostream>
//using namespace std;



template <typename T1, typename T2>
void construct(T1 * ptr, T2 const & value) {
	new(ptr)T1(value);
}

template <typename T>
void destroy(T * ptr) noexcept
{
	ptr->~T();
}

template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept
{
	for (; first != last; ++first) {
		destroy(&*first);
	}
}



template <typename T>
class allocator{
protected:
	allocator(size_t size = 0);
	~allocator();
	auto swap(allocator & other) -> void;
	allocator(allocator const &) = delete;
	auto operator =(allocator const &)->allocator & = delete;
	T * ptr_;
	size_t size_;
	size_t count_;
};

template <typename T>
allocator<T>::allocator(size_t size) : ptr_((T*)(operator new(size*sizeof(T)))), size_(size), count_(0){};

template<typename T>
allocator<T>::~allocator(){ destroy(ptr_,ptr_+count_); operator delete(ptr_); }

template<typename T>
auto allocator<T>::swap(allocator & other)->void{
	swap(ptr_, other.ptr_);
	swap(size_, other.size_);
	swao(count_, other.count_);
}



template <typename T>
class stack : private allocator<T>
{
public:
	stack(); /* noexcept */
	stack(const stack&); /* strong */
	~stack(); /* noexcept */
	size_t count() const; /* noexcept */
	void push(T const &); /* strong */
	const T& top(); /* strong */
	void pop(); /* strong */
	stack& operator=(const stack&); /* strong */
	bool empty(); /* noexcept */
};

/*template<typename T>
T* copy_mas(const T *p1, size_t c, size_t s){
	T *p2 = (T*)(operator new(s*sizeof(T)));
	try{ std::copy(p1, p1 + c, p2); }
	catch (...){ destroy(p2, p2 + c); operator delete(p2); throw; }
	return p2;
}*/

template <typename T>
stack<T>::stack() : allocator<T>(){};

template <typename T>
stack<T>::stack(const stack& x) : allocator<T>(x.size_){
	for (size_t i = 0; i < x.count_; i++) construct(allocator<T>::ptr_ + i, x.ptr_[i]);
	allocator<T>::count_ = x.count_;
};

template <typename T>
stack<T>::~stack(){}

template <typename T>
size_t stack<T>::count()const { return allocator<T>::count_; }

template <typename T>
void stack<T>::push(T const &a){
	if (allocator<T>::count_ == allocator<T>::size_){
		T *p = (T*)(operator new(sizeof(T)*(allocator<T>::size_ * 2 + (allocator<T>::count_ == 0))));
		for (size_t i = 0; i < allocator<T>::count_; i++) construct(p + i, allocator<T>::ptr_[i]);
		destroy(allocator<T>::ptr_, allocator<T>::ptr_ + allocator<T>::count_);
		operator delete(allocator<T>::ptr_);
		allocator<T>::ptr_ = p;
		allocator<T>::size_ = allocator<T>::size_ * 2 + (allocator<T>::count_ == 0);
	}
	allocator<T>::ptr_[allocator<T>::count_] = a;
	++allocator<T>::count_;
}

template <typename T>
const T& stack<T>::top(){
	if (allocator<T>::count_ > 0) return allocator<T>::ptr_[allocator<T>::count_ - 1];
	else throw("stack pust");
}

template <typename T>
void stack<T>::pop(){
	if (allocator<T>::count_> 0) --allocator<T>::count_;
	else throw("stack pust");
}

template<typename T>
stack<T>& stack<T>::operator=(const stack& b){
	if (this != &b){
		T *p = allocator<T>::ptr_;
		for(size_t i = 0; i < b.count_; i++) construct(allocator<T>::ptr_+i, b.ptr_[i]);
		//destroy(p, p + allocator<T>::count_);
		//operator delete(p);
		allocator<T>::count_ = b.count_;
		allocator<T>::size_ = b.size_;
	}
	return *this;
}

template<typename T>
bool stack<T>::empty(){ return(allocator<T>::count_ == 0); }

#endif
