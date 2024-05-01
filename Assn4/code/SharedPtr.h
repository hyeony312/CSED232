#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <iostream>
#include <cassert>

template<typename ObjectType>
void Deallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Object" << std::endl;
	delete ptr;
}

template<typename ObjectType>
void ArrayDeallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Array" << std::endl;
	delete[] ptr;
}

template<typename T>
using DeallocatorFuncType = void (T*);

// SharedPtr
template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc = Deallocator<ObjectType> >
class SharedPtr
{
private:
	ObjectType* m_object;
	int* m_ref_counter;

	// ======= ADD CODE HERE IF NEEDED =========
				
public:
	////////////////////////////////////////////
	// Constructors & destructor
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	SharedPtr() : m_object(nullptr), m_ref_counter(nullptr) {}
	explicit SharedPtr(ObjectType* object) : m_object(object), m_ref_counter(new int(1)) {}

	~SharedPtr()
	{
		if (m_object!=nullptr)
		{
			--(*m_ref_counter);
			if (*m_ref_counter == 0)
			{
				Dealloc(m_object);
				delete m_ref_counter;
			}
		}
	}

	////////////////////////////////////////////
	// Assignment operator
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	SharedPtr& operator=(const SharedPtr& ptr)
	{
		if (this != &ptr)
		{
			if (m_object!=nullptr)
			{
				--(*m_ref_counter);
				if (*m_ref_counter == 0)
				{
					Dealloc(m_object);
					delete m_ref_counter;
				}
			}

			m_object = ptr.m_object;
			m_ref_counter = ptr.m_ref_counter;
			++(*m_ref_counter);
		}
		return *this;
	}


	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	// operator*

	// ======= ADD CODE HERE IF NEEDED =========
	ObjectType& operator *() { return *m_object; }
	const ObjectType& operator *() const { return *m_object; }
	ObjectType* operator ->() { return m_object; }
	const ObjectType* operator ->() const { return m_object; }


	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	// ======= ADD CODE HERE IF NEEDED =========
	ObjectType& operator[](int index)
	{
		return m_object[index];
	}
	ObjectType& operator[](int index) const
	{
		return m_object[index];
	}

	////////////////////////////////////////////
	// Type casting operators
	////////////////////////////////////////////
	// operator ObjectType const*() const
	// operator ObjectType*()
	
	// ======= ADD CODE HERE IF NEEDED =========
	operator ObjectType* ()
	{
		return m_object;
	}
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif
