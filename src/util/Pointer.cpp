#include <Pointer.hpp>

#include <Memory.hpp>

template <typename T>
Pointer<T>::Pointer(T* pointer, uint32_t size)
{
	this->pointer = pointer;

	this->size = size;
}

template <typename T>
Pointer<T>::Pointer(uint32_t size) : Pointer(new T[size](), size)
{

}

template <typename T>
Pointer<T>::~Pointer()
{

}

template <typename T>
T* Pointer<T>::get()
{
	return this->pointer;
}

template <typename T>
uint32_t Pointer<T>::getSize()
{
	return this->size;
}

template <typename T>
T Pointer<T>::operator[](uint32_t index) const
{
	return this->pointer[index];
}

template <typename T>
T& Pointer<T>::operator[](uint32_t index)
{
	return this->pointer[index];
}

template <typename T>
T& Pointer<T>::operator*()
{
	return *this->pointer;
}

template class Pointer<uint32_t>;
template class Pointer<Memory>;
template class Pointer<unsigned char>;