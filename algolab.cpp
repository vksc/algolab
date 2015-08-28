// algolab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <vector>
#include <list>
#include <map>
#include <functional>
#include <iterator>
#include <string>
#include <sstream>

#include "sorting.h"
#include "quiz.h"
#include "data.h"

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

	friend std::ostream& operator << (std::ostream& ostr, const test_data& v);
};

bool operator < (const test_data& rhs, const test_data& lhs)
{
	return rhs.key < lhs.key;
}

bool operator > (const test_data& rhs, const test_data& lhs)
{
	return rhs.key > lhs.key;
}

std::ostream& operator << (std::ostream& ostr, const test_data& v)
{
	ostr << v.key;

	if (v.data)
		ostr << v.data;

	return ostr;
}

void test_sorting()
{
	using test_values = std::vector<test_data>;

	test_values v = { { 5, 'a' }, 2, 4, { 5, 'c' }, 7, 6, 1, 3};
	print(v);
	sort::bubble_sort(v.begin(), v.end());

	//sort::insertion_sort(v.begin(), v.end(), std::greater<>());
	//sort::quick_sort(v.begin(), v.end());
	sort::shell_sort(v.begin(), v.end());// , [](const test_data& v1, const test_data& v2) { return v1.key < v2.key;  });

	print(v);
}

void test_quiz()
{
	using test_values = std::vector<test_data>;

	test_values b1 = { 9, 5, 0, 0, 0, 0 };
	test_values b2 = { 12, 6, 3, 1 };

	print(b1, true);
	print(b2);
	quiz::inplace_merge_sorted(b1.begin(), std::next(b1.begin(), 2), b1.end(), b2.begin(), b2.end(), std::greater<test_values::value_type>());
	print(b1);

	test_values b3 = { 9, 5 };
	test_values b4 = { 12, 6, 3, 1 };
	test_values b5;
	quiz::my_merge_sorted(b3.begin(), b3.end(), b4.begin(), b4.end(), std::back_inserter(b5), std::greater<test_values::value_type>());

	print(b5, true);

	std::string s1 = "hello dumb code !";
	std::wstring s2 = L"Vasya was here today";

	quiz::reverse_words(s1.begin(), s1.end(), ' ');
	std::cout << s1 << '\n';

	quiz::reverse_words(s2.begin(), s2.end(), L' ');
	std::wcout << s2 << '\n';
}

template <typename Node, typename level_map>
void get_tree_levels(const Node& node, int level, int pos, int dir, level_map& lm)
{
	if (lm[level].empty())
		lm[level].insert(0, 170, ' ');

	std::ostringstream stm;
	stm << node.data;
	std::cout << level << " * " << node.data << '\n';
	lm[level].insert(pos, stm.str());

	if (node.left)
		get_tree_levels(*node.left, level + 1, dir <= 0 ? pos - 8 : pos - 3, dir ? dir : -1, lm);
	if (node.right)
		get_tree_levels(*node.right, level + 1, dir >= 0 ? pos + 8 : pos + 3, dir ? dir : 1, lm);

	std::cout << std::endl;
}

template <bool presort = true, typename FwdIt>
void balance_bst_data(FwdIt first, FwdIt last)
{
	if (first == last)
		return;

	if (presort)
		std::sort(first, last);

	size_t len = std::distance(first, last);
	auto mid = std::next(first, (len / 2));

	if (mid == last)
		return;

	auto first2 = mid + 1;
	auto l2 = std::distance(first, mid);
	std::cout << *mid << std::endl;
	first = std::rotate(first, mid, first2);

	balance_bst_data<false>(first, first + l2);
	balance_bst_data<false>(first2, last);
}

void test_data()
{
	using intree = data::bintree<int>;
	std::vector<int> v1, v2;

	v1 = { 5, 3, 7, 1, 4, 6, 8, 10, 12 };
	
	intree tree;
	for (auto i : v1)
		tree.addNode(i);

	tree.visit([](const intree::node& root)
	{
		std::map<int, std::string> lm;
		get_tree_levels(root, 0, 50, false, lm);

		for (size_t i = 0; i < lm.size(); ++i)
		{
			std::cout << lm[i] << std::endl;
		}

	});

	v2 =  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	//v2 = v1;
	intree tree2;

	balance_bst_data(v2.begin(), v2.end());
	for (auto i : v2)
		tree2.addNode(i);

	tree2.visit([](const intree::node& root)
	{
		std::map<int, std::string> lm;
		get_tree_levels(root, 0, 50, false, lm);

		for (size_t i = 0; i < lm.size(); ++i)
		{
			std::cout << lm[i] << std::endl;
		}

	});
}

int main(int argc, char* argv[])
{
	try
	{
		test_sorting();
		test_quiz();
		test_data();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}


	return 0;

}
