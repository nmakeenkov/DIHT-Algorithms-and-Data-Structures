#include"Net.h"
#include<iostream>

int main() {
	std::ios_base::sync_with_stdio(false);
	Net<long long> a;
	std::cin >> a;
	a.runPreflowPush(0, a.getV() - 1);
	std::cout << a;
	return 0;
}