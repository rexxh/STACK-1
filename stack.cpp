#include <iostream>
using namespace std;

template <typename T>
class stack
{
public:
	stack();
	stack(const stack&);
	size_t count() const;
	void push(T const &);
	T pop();
	~stack();
	stack& operator=(const stack&);
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};

template<typename T>
stack<T>& stack<T>::operator=(const stack& b){
	//if (this != &b){
	//	delete[] array_;
	//	count_ = b.count_;
	//	array_size_ = b.array_size_;
	//	array_ = new T[count];
	//	copy(b.array_, b.array_ + count_, array_);
	//}
	cout << "!!!!!!!" << endl;
	return *this;
}

template <typename T>
stack<T>::stack() : array_(nullptr), array_size_(0), count_(0){};

template <typename T>
stack<T>::stack(const stack& x) : array_size_(x.array_size_), count_(x.count_){
	array_ = new T[array_size_];
	for (int i = 0; i < count_; i++) array_[i] = x.array_[i];
}

template <typename T>
stack<T>::~stack(){
	delete[] array_;
}

template <typename T>
size_t stack<T>::count() const{ return count_; }

template <typename T>
void stack<T>::push(T const &a){
	if (array_ == nullptr){
		array_ = new T[1]; array_[0] = a;
		count_++; array_size_++;
	}
	else{
		if (count_ == array_size_){
			T *p = array_;
			array_ = new T[array_size_ * 2];
			for (int i = 0; i < count_; i++) array_[i] = p[i];
			delete[]p;
			array_size_ *= 2;
		}
		array_[count_] = a;
		count_++;
	}
}

template <typename T>
T stack<T>::pop(){
	if (count_ == 0) throw("stack pust");
	else {
		count_--;
		return array_[count_];
	}
}


void main()
{
	stack<int> s1;
	s1.push(1); s1.push(2); s1.push(3);
	cout << s1.pop() << endl; cout << s1.pop() << endl; cout << s1.pop() << endl;
	s1.push(1); s1.push(2); s1.push(3);
	stack<int> s2 = s1;
	cout << s2.pop() << endl; cout << s2.pop() << endl; cout << s2.pop() << endl;
	cout << s1.count() << endl;
	cout << s1.pop() << endl; cout << s1.pop() << endl; cout << s1.pop() << endl;
	system("pause");
}
