#pragma once
#include <algorithm>
long long min3(long long a, long long b, long long c) {
	return std::min(a, std::min(b, c));
}