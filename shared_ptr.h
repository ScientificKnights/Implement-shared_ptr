#ifndef _SHARED_PTR_H
#define _SHARED_PTR_H

template<typename> class shared_ptr;

template<typename T>
class shared_ptr {
private:
	size_t* count_ptr = NULL;
	T* m_ptr = NULL;
public:
	shared_ptr()
		:m_ptr(NULL), count_ptr(new size_t(0)) {
	}
	explicit shared_ptr(T* ptr)
		:m_ptr(ptr), count_ptr(new size_t(1)) {
	}
	shared_ptr(const shared_ptr& hp)
		:m_ptr(hp.m_ptr), count_ptr(hp.count_ptr) {
		(*count_ptr)++; //引用计数加1 
	}
	shared_ptr& operator=(shared_ptr& hp) {
		//https://www.codeproject.com/Articles/15351/Implementing-a-simple-smart-pointer-in-c
		//https://blog.csdn.net/liushengxi_root/article/details/80598430
		if (this != hp) {
			if (--(*count_ptr) == 0) {
				delete m_ptr;
				delete count_ptr;
			}
			m_ptr = hp.m_ptr;
			count_ptr = hp.count_ptr;
			++(*count_ptr);
		}
		return *this;
	}
	~shared_ptr() {
		--(*count_ptr);
		if ((*count_ptr) == 0) {
			delete m_ptr;
			delete count_ptr;
		}
	}
	size_t use_count() { return (*count_ptr); }
	T& operator*() { return *m_ptr; }
	T* operator->() { return m_ptr; }
};

#endif
