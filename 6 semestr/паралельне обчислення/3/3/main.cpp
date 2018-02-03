#include <iostream>
#include <algorithm>
#include <atomic>
#include <vector>
#include <thread>
#include <ctime>

void sum(std::vector<int>::iterator &beg, std::vector<int>::iterator &end, std::atomic <int> &res)
{
	for (auto i = beg; i < end; i++)
		res += *i;
}
int calculateSum(std::vector <int> &array)
{
	std::atomic <int> result(0);
	std::vector <std::thread> threadArray;

	int threadsAmount = std::thread::hardware_concurrency();
	int step = array.size() / threadsAmount;
	int rest = array.size() % threadsAmount;

	for (int i = 0; i < threadsAmount; i++)
		threadArray.push_back(std::thread(sum, array.begin() + step * i, array.begin() + step * (i + 1), std::ref(result)));
	if (rest != 0)
		threadArray.push_back(std::thread(sum, array.begin() + (array.end() - array.begin() - rest), array.end(), std::ref(result)));

	std::for_each(threadArray.begin(), threadArray.end(), [](std::thread &t){ t.join(); });

	return result.load();
}

void quantity(std::vector<int>::iterator &beg, std::vector<int>::iterator &end, std::atomic <int> &res, std::function <bool(int)> condition)
{
	for (auto i = beg; i < end; i++)
		if (condition(*i))
			++res;
}
int calculateQuantity(std::vector <int> &array, std::function <bool(int)> condition)
{
	std::atomic <int> result(0);
	std::vector <std::thread> threadArray;

	int threadsAmount = std::thread::hardware_concurrency();
	int step = array.size() / threadsAmount;
	int rest = array.size() % threadsAmount;

	for (int i = 0; i < threadsAmount; i++)
		threadArray.push_back(std::thread(quantity, array.begin() + step * i, array.begin() + step * (i + 1), std::ref(result), condition));
	if (rest != 0)
		threadArray.push_back(std::thread(quantity, array.begin() + (array.end() - array.begin() - rest), array.end(), std::ref(result), condition));

	std::for_each(threadArray.begin(), threadArray.end(), [](std::thread &t){ t.join(); });

	return result.load();
}

/*min & max with indices*/
void minAndMax(std::vector <int> &array, int beg, int end, std::atomic <int> &minPos, std::atomic <int> &maxPos)
{

	for (int i = beg; i < end; i++)
	{

		int prev_value_max = maxPos.load();
		int prev_value_min = minPos.load();
		/*CAS loop*/
		while (array.at(prev_value_max) < array.at(i) && !maxPos.compare_exchange_strong(prev_value_max, i));
		while (array.at(prev_value_min) > array.at(i) && !minPos.compare_exchange_strong(prev_value_min, i));

	}
}
std::pair <int, int> findMinAndMax(std::vector <int> &array)
{
	std::atomic <int> minPos(0), maxPos(0);
	std::vector <std::thread> threadArray;

	int threadsAmount = std::thread::hardware_concurrency();
	int step = array.size() / threadsAmount;
	int rest = array.size() % threadsAmount;

	for (int i = 0; i < threadsAmount; i++)
		threadArray.push_back(std::thread(minAndMax, array, step * i, step * (i + 1), std::ref(minPos), std::ref(maxPos)));
	if (rest != 0)
		threadArray.push_back(std::thread(minAndMax, array, array.size() - rest, array.size(), std::ref(minPos), std::ref(maxPos)));
	std::for_each(threadArray.begin(), threadArray.end(), [](std::thread &t){ t.join(); });

	return std::make_pair <int, int>(minPos.load(), maxPos.load());
}

/*checksum using xor*/
void checksum(std::vector<int>::iterator &beg, std::vector<int>::iterator &end, std::atomic <int> &res)
{
	for (auto i = beg; i < end; i++)
		res ^= *i;
}
int calculateChecksum(std::vector <int> &array)
{
	std::atomic <int> result(0);
	std::vector <std::thread> threadArray;

	int threadsAmount = std::thread::hardware_concurrency();
	int step = array.size() / threadsAmount;
	int rest = array.size() % threadsAmount;

	for (int i = 0; i < threadsAmount; i++)
		threadArray.push_back(std::thread(checksum, array.begin() + step * i, array.begin() + step * (i + 1), std::ref(result)));
	if (rest != 0)
		threadArray.push_back(std::thread(checksum, array.begin() + (array.end() - array.begin() - rest), array.end(), std::ref(result)));

	std::for_each(threadArray.begin(), threadArray.end(), [](std::thread &t){ t.join(); });

	return result.load();
}

int main()
{
	std::srand(std::time(nullptr));

	//std::vector <int> array;// {1, 2, 3, 4, 220, -228, 5, 6, 7, 8, 9, 10};
	/*for (int i = 0; i < 100000; i++)
		array.push_back(i);*/

	std::vector <int> array(100000);
	std::generate(array.begin(), array.end(), std::rand);

	std::cout << "Sum: " << calculateSum(array) << std::endl;

	std::cout << "Quantity: " << calculateQuantity(array, [=](int i){ return i < 502; }) << std::endl;

	auto res = findMinAndMax(array);
	std::cout << "Min value index: " << res.first << std::endl
			  << "Max value index: " << res.second << std::endl;

	std::cout << "Checksum: " << calculateChecksum(array) << std::endl;

	system("pause");
	return 0;
}
