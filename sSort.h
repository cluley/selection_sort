#pragma once

#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <future>

namespace own {
	template <class It>
	void min_element(It begin, It end, std::promise<It> prom)
	{
		if (begin == end) {
			prom.set_value(end);
			return;
		}

		auto smallest = begin;
		++begin;

		for (; begin != end; ++begin) {
			if (*begin < *smallest)
				smallest = begin;
		}
		prom.set_value(smallest);
	}
}

template<class It>
void sSort(It begin, It end)
{
	if (begin == end) return;

	for (auto i = begin; i != end; ++i) {
		std::promise<It> prom;
		std::future<It> ft_min = prom.get_future();
		auto ft = std::async(own::min_element, i, end, std::move(prom));

		ft.wait();

		std::iter_swap(i, ft_min.get());
	}
}