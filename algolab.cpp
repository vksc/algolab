// algolab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <vector>
#include <list>

#include "sorting.h"

template <bool horz = true, typename T>
void print(const T& container)
{
	char delim = horz ? ' ' : '\n';

	for (auto i : container)
	{
		std::cout << i << delim;
	}

	std::cout << std::endl;
}

template <typename FwdIt, bool horz = true>
void print(FwdIt first, FwdIt middle, FwdIt last)
{
	char delim = horz ? ' ' : '\n';

	for (auto i = first; i != middle; ++i)
	{
		std::cout << *i << delim;
	}
	
	std::cout << " <---> " << delim;
	for (auto i = middle; i != last; ++i)
	{
		std::cout << *i << delim;
	}

	std::cout << std::endl;
}

struct test_data
{
	int key;
	char data;

	test_data(int k) : key(k), data(0) {}
	test_data(int k, char c) : key(k), data(c) {}
};

bool operator < (const test_data& rhs, const test_data& lhs)
{
	return rhs.key < lhs.key;
}

bool operator > (const test_data& rhs, const test_data& lhs)
{
	return rhs.key > lhs.key;
}

template <typename ostream_t>
ostream_t& operator << (ostream_t& ostr, const test_data& v)
{
	ostr << v.key;

	if (v.data)
		ostr << v.data;

	return ostr;
}

int _tmain(int argc, _TCHAR* argv[])
{

	using test_values = std::vector<test_data>;

	test_values v = { { 5, 'a' }, 2, 4, { 5, 'c' }, 7, 6, 1, 3};
	print(v);

	//sort::bubble_sort(v.begin(), v.end());
	//sort::insertion_sort(v.begin(), v.end(), std::greater<>());
	//sort::quick_sort(v.begin(), v.end());
	sort::shell_sort(v.begin(), v.end());// , [](const test_data& v1, const test_data& v2) { return v1.key < v2.key;  });

	print(v);

	return 0;
}

