#ifndef VECTOR_H
#define VECTOR_H

#include <iterator>
#include <memory>
#include <exception>
#include <iostream>

template <class T>
class Vector
{
public:
// Member types

	typedef T value_type;
	typedef size_t size_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef std::reverse_iterator <iterator> reverse_iterator;
	typedef std::reverse_iterator <const_iterator> const_reverse_iterator;

//Constructors
	//Default constructor
	Vector() { create(); }

	//Fill constructor
	explicit Vector(size_type n, const T& val = T{}) { create(n, val); }

	//Copy constructor
	Vector(const Vector& vec) { create(vec.begin(), vec.end()); }

//Destructor
	~Vector() { uncreate(); }

//Member functions
	//vector::operator= copy version
	Vector& operator=(const Vector& vec)
	{
		if (&vec != this)
		{
			uncreate();
			create(vec.begin(), vec.end());
		}
		return *this;
	}

	//vector::operator= move version
	Vector& operator=(Vector&& vec) noexcept
	{
		if (&vec != this)
			uncreate();

		std::swap(vec.data, data);
		std::swap(vec.avail, avail);
		std::swap(vec.limit, limit);
	}

	//vector::push_back
	void push_back(const T& val)
	{
		if (avail == limit)
			grow();
		unchecked_append(val);
	}

	//vector::operator[]
	T& operator[](size_type i)
	{
		try {
			if (i > size() || i < 0) throw std::out_of_range("reached limit of the operator[]");
		}
		catch (const std::out_of_range& e)
		{
			std::cout << e.what();
			exit(0);
		}

		return data[i];
	}
	const T& operator[](size_type i) const
	{
		try {
			if (i > size() || i < 0) throw std::out_of_range("reached limit of the operator[]");
		}
		catch (const std::out_of_range& e)
		{
			std::cout << e.what();
			exit(0);
		}

		return data[i];
	}

	//vector::size
	size_type size() const { return avail - data; }

	//vector::capacity
	size_type capacity() const { return limit - data; }

	//vector::empty
	bool empty() const
	{
		if (data == nullptr)
			return true;
		return false;
	}

	//vector::begin
	iterator begin() { return data; }
	//vector::cbegin
	const_iterator begin() const { return data; }

	//vector::end
	iterator end() { return limit; }
	//vector::cend
	const_iterator end() const { return limit; }

	//vector::rbegin
	iterator rbegin()
	{
		iterator it = limit;
		return --it;
	}
	//vector::crbegin
	const_iterator rbegin() const
	{
		iterator it = limit;
		return --it;
	}

	//vector::rend
	iterator rend()
	{
		iterator it = data;
		return ++it;
	}
	//vector::crend
	const_iterator rend() const
	{
		iterator it = data;
		return ++it;
	}

	//vector::front
	T& front()
	{
		return *data;
	}

	//vector::back
	T& back()
	{
		iterator it = avail;
		return *(--it);
	}

	//vector::at
	T& at(size_type pos)
	{
		try {
			if (size() <= pos || pos < 0) throw std::out_of_range("Out of range");
		}
		catch (const std::out_of_range& e)
		{
			std::cout << e.what();
			exit(0);
		}

		return data[pos];
	}

	//vector::reserve
	void reserve(size_type new_cap)
	{
		if (new_cap > capacity())
		{
			iterator new_data = alloc.allocate(new_cap);
			iterator new_avail = std::uninitialized_copy(data, avail, new_data);
			uncreate();
			data = new_data;
			avail = new_avail;
			limit = data + new_cap;
		}
	}

	//vector::clear
	void clear()
	{
		iterator new_data = alloc.allocate(capacity());
		size_type cap = capacity();
		uncreate();
		limit = new_data + cap;
		data = avail = new_data;
	}

	//vector::pop_back()
	void pop_back()
	{
		iterator it = avail;
		alloc.destroy(--it);
		avail = it;
	}

	//vector::shrink_to_fit
	void shrink_to_fit()
	{
		limit = avail;
	}

	//vector::resize
	void resize(size_type count, value_type value = T())
	{
		if (count < size())
		{
			size_type new_size = count;
			iterator new_data = alloc.allocate(new_size);
			iterator new_avail = std::uninitialized_copy(data, data + count, new_data);
			iterator new_limit = new_data + capacity();

			uncreate();

			data = new_data;
			avail = new_avail;
			limit = new_limit;
		}
		else if (count > size())
		{
			size_type new_size = count;
			iterator new_data = alloc.allocate(new_size);
			iterator it = std::uninitialized_copy(data, avail, new_data);
			std::uninitialized_fill(it, new_data + new_size - 1, value);
			iterator new_avail = new_data + new_size;
			iterator new_limit;
			if (capacity() < new_avail - new_data)
			{
				new_limit = new_avail;
			}
			else
			{
				new_limit = new_data + capacity();
			}
			uncreate();

			data = new_data;
			avail = new_avail;
			limit = new_limit;
		}
	}

//Non-member overloaded functions
	//operator ==
	/*bool operator==(const Vector &vec1, const Vector &vec2)
	{
		return vec1 == vec2
	}*/
private:
	iterator data;
	iterator avail;
	iterator limit;

	std::allocator<T> alloc;

	void create()
	{
		data = avail = limit = nullptr;
	}
	void create(size_type n, const T& val)
	{
		data = alloc.allocate(n);
		limit = avail = data + n;
		std::uninitialized_fill(data, limit, val);
	}
	void create(const_iterator i, const_iterator j)
	{
		data = alloc.allocate(j - i);
		limit = avail = std::uninitialized_copy(i, j, data);
	}

	void uncreate()
	{
		if (data)
		{
			iterator it = avail;
			while (it != data)
				alloc.destroy(--it);
			alloc.deallocate(data, limit - data);
		}
		data = limit = avail = nullptr;
	}

	void grow()
	{
		size_type new_size;
		new_size = std::max(2 * (limit - data), ptrdiff_t(1));

		iterator new_data = alloc.allocate(new_size);
		iterator new_avail = std::uninitialized_copy(data, avail, new_data);

		uncreate();

		data = new_data;
		avail = new_avail;
		limit = data + new_size;
	}
	void unchecked_append(const T& val)
	{
		alloc.construct(avail++, val);
	}
};

#endif