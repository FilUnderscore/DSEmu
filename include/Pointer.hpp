#ifndef INCLUDE_POINTER_HPP_
#define INCLUDE_POINTER_HPP_

#include <cstdint>

using namespace std;

template <typename T>
class Pointer
{
public:
	Pointer(T* pointer, uint32_t size);

	Pointer(uint32_t size);
	
	~Pointer();

	T* get();

	uint32_t getSize();

	T operator[](uint32_t index) const;

	T& operator[](uint32_t index);	

	T& operator*();

private:
	T* pointer;

	uint32_t size;
};

#endif