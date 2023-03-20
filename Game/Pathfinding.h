#pragma once

#include <tuple>
#include <queue>
#include <unordered_map>
#include <utility>

using Location = std::tuple<int, int>;

namespace std
{
	template<> struct hash<Location>
	{
		std::size_t operator()(const Location& id) const noexcept
		{
			return std::get<0>(id) ^ std::get<0>(id);
		}
	};
}

using PQElement = std::pair<int, Location>;

struct PriorityQueue
{
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

	inline bool empty() const { return elements.empty(); }

	inline void put(Location item, int priority) { elements.emplace(priority, item); }

	Location get()
	{
		Location best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

