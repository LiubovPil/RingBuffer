// Done by Liubov Piliagina

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class RingBufferOneSide {
public:
	RingBufferOneSide(const size_t& buffer_size_)
		: buffer_size(buffer_size_), buffer_pos(0), ring_buffer(NULL){
		ring_buffer = new T[buffer_size];
	}
	size_t GetRingBufferTotalSize() const {
		return buffer_size;
	}
	T& GetFromRingBuffer(int pos_) const {
		return ring_buffer[pos_];
	}
	void AddToRingBuffer(T value_) {
		ring_buffer[buffer_pos++] = value_;

		if (buffer_pos == buffer_size)
			buffer_pos = 0;
	}
	~RingBufferOneSide() {
		delete[] ring_buffer;
	}
private:
	const size_t buffer_size;
	size_t buffer_pos;
	T* ring_buffer;
};

template<typename T>
class RingBufferTwoSide {
public:
	RingBufferTwoSide(const size_t& buffer_size_)
		: buffer_size(buffer_size_), head(0), tail(0),
		is_full(false), ring_buffer(NULL) {
		ring_buffer = new T[buffer_size];
	}
	size_t GetRingBufferTotalSize() const {
		return buffer_size;
	}
	bool IsEmpty() const {
		return ((tail - head) == 0 && !is_full);
	}
	void PushBack(T value_) {
		if (is_full)
			throw runtime_error("Ring buffer is full");

		ring_buffer[tail++] = value_;
		
		CheckBorder(tail);

		is_full = tail == head;
	}
	T& PopBack() {
		if (IsEmpty())
			throw runtime_error("Ring buffer is empty");

		tail--;
		CheckBorder(tail);

		return ring_buffer[tail];
	}
	void PushFront(T value_) {
		if (is_full)
			throw runtime_error("Ring buffer is full");
		
		head--;
		CheckBorder(head);

		ring_buffer[head] = value_;

		is_full = tail == head;
	}
	T& PopFront() {
		if (IsEmpty())
			throw runtime_error("Ring buffer is empty");

		T& value = ring_buffer[head++];
		CheckBorder(head);

		return value;
	}
	~RingBufferTwoSide() {
		delete[] ring_buffer;
	}
private:
	const size_t buffer_size;
	int head;
	int tail;
	bool is_full;
	T* ring_buffer;

	void CheckBorder(int& border) {
		if (border == buffer_size)
			border = 0;
		else if (border < 0)
			border = buffer_size - 1;
	}
};


int main()
{
	/*RingBufferOneSide<string> alphabet(5);
	
	alphabet.AddToRingBuffer("Zz");
	alphabet.AddToRingBuffer("Aa");
	alphabet.AddToRingBuffer("Cc");
	alphabet.AddToRingBuffer("Ff");
	alphabet.AddToRingBuffer("Dd");

	size_t size = alphabet.GetRingBufferTotalSize();
	
	for (size_t i = 0; i < size; ++i) {
		cout << alphabet.GetFromRingBuffer(i) << ", ";
	}
	alphabet.AddToRingBuffer("Ee");
	cout << endl;

	for (size_t i = 0; i < size; ++i) {
		cout << alphabet.GetFromRingBuffer(i) << ", ";
	}*/

	RingBufferTwoSide<int> num(10);

	num.PushBack(0);
	num.PushBack(1);
	num.PushBack(2);
	num.PushFront(9);
	num.PushFront(8);
	num.PushFront(7);
	num.PushFront(6);

	cout << num.PopBack() << endl;
	cout << num.PopBack() << endl;
	cout << num.PopBack() << endl;
	cout << num.PopBack() << endl;

	num.PushBack(9);
	num.PushBack(0);
	num.PushBack(1);
	num.PushBack(2);
	num.PushBack(3);

	cout << num.PopFront() << endl;
	cout << num.PopFront() << endl;

	num.PushFront(7);
	num.PushFront(6);
	num.PushFront(5);
	num.PushFront(4);
	cout << num.PopFront() << endl;

}

