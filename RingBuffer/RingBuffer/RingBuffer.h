#pragma once

#include <iostream>

using namespace std;

template<typename T>
class RingBufferFirst {
public:
	RingBufferFirst(const int& buffer_size_)
		: buffer_size(buffer_size_) {
		ring_buffer = new T[buffer_size];
	}
	~RingBufferFirst();
private:
	const int buffer_size;
	T* ring_buffer;
};
