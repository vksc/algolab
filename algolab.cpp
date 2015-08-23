// algolab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <vector>
#include <list>
#include <functional>
#include <iterator>

#include "sorting.h"
#include "quiz.h"

template <bool horz = true, typename T>
void print(const T& container, bool start_section = false)
{
	if (start_section)
		std::cout << "----------------------\n";

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

void test();

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		test();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}


	return 0;

}

void test()
{
	using test_values = std::vector<test_data>;

	test_values v = { { 5, 'a' }, 2, 4, { 5, 'c' }, 7, 6, 1, 3};
	print(v);

	//sort::bubble_sort(v.begin(), v.end());
	//sort::insertion_sort(v.begin(), v.end(), std::greater<>());
	//sort::quick_sort(v.begin(), v.end());
	sort::shell_sort(v.begin(), v.end());// , [](const test_data& v1, const test_data& v2) { return v1.key < v2.key;  });

	print(v);

	test_values a1 = { 2, 3, 5, 7, 9, 0, 0, 0, 0 };
	test_values a2 = { 1, 3, 8, 12 };
	
	print(a1, true);
	print(a2);
	quiz::inplace_merge_sorted(a1.begin(), std::next(a1.begin(), 5), a1.end(), a2.begin(), a2.end());

	print(a1);

	/*test_values b1 = { 9, 7, 5, 3, 2, 0, 0, 0, 0 };
	test_values b2 = { 12, 8, 3, 1 };
*/
	test_values b1 = { 9, 5, 0, 0, 0, 0 };
	test_values b2 = { 12, 6, 3, 1 };

	print(b1, true);
	print(b2);
	quiz::inplace_merge_sorted(b1.begin(), std::next(b1.begin(), 2), b1.end(), b2.begin(), b2.end(), std::greater<>());
	print(b1);

	test_values b3 = { 9, 5};
	test_values b4 = { 12, 6, 3, 1 };
	test_values b5;
	quiz::my_merge_sorted(b3.begin(), b3.end(), b4.begin(), b4.end(), std::back_inserter(b5), std::greater<>());

	print(b5, true);
}

