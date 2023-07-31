#pragma once

#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <future>

namespace own {
	void min_element(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::promise<std::vector<int>::iterator> prom)
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

void sSort(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	if (begin == end) return;

	for (auto i = begin; i != end; ++i) {
		std::promise<std::vector<int>::iterator> prom;
		std::future<std::vector<int>::iterator> ft_min = prom.get_future();
		auto ft = std::async(own::min_element, i, end, std::move(prom));

		ft.wait();

		std::iter_swap(i, ft_min.get());
	}
}