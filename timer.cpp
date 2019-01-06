#include <chrono>
#include <thread>
#include <iostream>

#include "timer.h"

int main()
{

	timer t; // ���岢����ʱ��
	for (int i = 0; i < 10; i++) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << i << " ";
	}
	std::cout << "\ntime elapsed:" << t.elapsed() << std::endl;
	
	return 0;
}