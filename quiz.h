#include <algorithm>
#include <string>

#pragma once

namespace quiz
{
	// http://www.fulcrumweb.com.ua/archives/1018
	template <typename RanIt, typename Compare = std::less<typename std::iterator_traits<RanIt>::value_type>>
	void inplace_merge_sorted(RanIt first1, RanIt lastSorted, RanIt last1, RanIt first2, RanIt last2, Compare comp = Compare())
	{
		if (first2 == last2)
			return;

		if (first1 == last1)
			throw std::invalid_argument("Source container is empty.");

		size_t szdata1 = std::distance(first1, lastSorted);
		size_t sz1 = std::distance(first1, last1);
		size_t szmerging = std::distance(lastSorted, last1);

		if (szdata1 >= sz1)
			throw std::invalid_argument("No space for merging in a source container.");

		size_t sz2 = std::distance(first2, last2);
		if (sz2 > szmerging)
			throw std::invalid_argument("Second container is too big for merging.");

		using RevIt = std::reverse_iterator<RanIt>;
		
		RevIt i1(lastSorted);
		RevIt rlast1(first1);

		RevIt i2(last2);
		RevIt rlast2(first2);

		RevIt insertion(last1);

		//
		while (insertion != rlast1 && (i1 != rlast1 || i2 != rlast2))
		{
			RevIt next_data;

			if (i1 != rlast1 && i2 != rlast2)
				next_data = comp(*i2, *i1) ? i1++ : i2++;
			else if (i1 == rlast1)
				next_data = i2++;
			else
				next_data = i1++;

			*insertion = *next_data;
			insertion++;
		}
	}

	// http://www.fulcrumweb.com.ua/archives/4447
	// However, there is std::merge which is preferable due to checking of input ranges for sorting and other error handling
	template <typename RanIt, typename OutIt, typename Compare = std::less<typename std::iterator_traits<RanIt>::value_type>>
	void my_merge_sorted(RanIt first1, RanIt last1, RanIt first2, RanIt last2, OutIt out, Compare comp = Compare())
	{
		// no error handling

		auto i1 = first1;
		auto i2 = first2;

		while (i1 != last1 || i2 != last2)
		{
			RanIt next_data;

			if (i1 == last1)
				next_data = i2++;
			else
				if (i2 == last2)
					next_data = i1++;
				else
					next_data = comp(*i1, *i2) ? i1++ : i2++;

			*out++ = *next_data;
		}
	}

	template <typename FwdIt, typename value_type = std::iterator_traits<FwdIt>::value_type value_type>
	void reverse_words(FwdIt first, FwdIt last, const value_type& separator)
	{
		if (first == last)
			return;

		for (FwdIt from = first, to = std::find(from, last, separator); from != last; to = std::find(from, last, separator))
		{
			std::reverse(from, to);
			
			if (to == last)
			{
				std::reverse(first, last);
				from = last;
			}
			else
				from = std::next(to, 1);
		}		
	}
}