// algolab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <utility>
#include <vector>
#include <list>
#include <functional>
#include <iostream>
#include <algorithm>

namespace sort
{
	template <typename FwdIt, typename Compare = std::less<typename std::iterator_traits<FwdIt>::value_type>>
	void bubble_sort(FwdIt first, FwdIt last, Compare lessThan = Compare())
	{
		if (first == last)
			return;

		--last;

		for (auto i = first, i_last_unsorted = last; i != last; ++i, --i_last_unsorted)
		{	// Outer cycle is used just as a counter for N-size array: 0...N-1
			for (auto j = first, j_next = j; j != i_last_unsorted; ++j)
			{	// Find the biggest item in the remaining portion of array.
				// i_last is used as an upper bound of 'unsorted' data.
				j_next++;

				if (lessThan(*j_next, *j)) 
				{
					std::iter_swap(j, j_next);
				}
			}
		}
	}

	template<class FwdIt, class Compare = std::less<typename std::iterator_traits<FwdIt>::value_type>>
	void insertion_sort(FwdIt first, FwdIt last, Compare lessThan = Compare())
	{
		for (auto i = first; i != last; ++i)
		{
			auto insertion_pos = std::upper_bound(first, i, *i, lessThan);
			std::rotate(insertion_pos, i, std::next(i, 1));
		}
	}

	template<typename FwdIt, typename PivotFunction, typename Compare>
	void quick_sort(FwdIt first, FwdIt last, PivotFunction pfn, Compare lessThan)
	{
		// Note that std::search uses an improved implementation, which can select quicksearch, heapsort or insertion sorting depending on data amount.
		if (first == last)
			return;

		auto i_pivot = pfn(first, last);
		auto pivot = *i_pivot;
		
		auto partitioner1 = [&pivot, &lessThan](const std::iterator_traits<FwdIt>::value_type& v)->bool
		{	return lessThan(v, pivot); };

		auto partitioner2 = [&pivot, &lessThan](const std::iterator_traits<FwdIt>::value_type& v)->bool
		{	return !lessThan(pivot, v); };

		// Divide sorted interval on two partitions according to given predicate
		auto middle1 = std::partition(first, last, partitioner1);
		
		// For 'upper' interval, use partition to move pivot value(s) to the middle1 position (i.e. placed at interval's start). 
		// As a result, we will have following partition: begin,...,middle1, middle2,....end.
		// And following intervals will be processed recursively: [begin, middle1), [middle2, end).
		auto middle2 = std::partition(middle1, last, partitioner2); 

		quick_sort(first, middle1, pfn, lessThan);
		quick_sort(middle2, last, pfn, lessThan);
	}

	template<typename FwdIt, typename Compare>
	void quick_sort(FwdIt first, FwdIt last, Compare lessThan)
	{
		if (first == last)
			return;

		auto pivotFn = [](FwdIt b, FwdIt e)->FwdIt
		{	return	std::next(b, std::distance(b, e) / 2);	};

		quick_sort(first, last, pivotFn, lessThan);
	}

	template<class FwdIt>
	void quick_sort(FwdIt first, FwdIt last)
	{
		quick_sort(first, last, std::less<typename std::iterator_traits<FwdIt>::value_type>());
	}

	template<typename RanIt, typename Compare = std::less<typename std::iterator_traits<RanIt>::value_type>>
	void shell_sort(RanIt first, RanIt last, Compare lessThan = Compare())
	{
		if (first == last)
			return;

		for (auto d = std::distance(first, last) / 2; d != 0; d /= 2) 
			for (RanIt i = std::next(first, d); i != last; ++i) 
				for (RanIt j = i; std::distance(first, j) >= d && lessThan(*j, *std::prev(j, d)); j = std::prev(j, d))
					std::swap(*j, *std::prev(j, d));
	}
}

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

