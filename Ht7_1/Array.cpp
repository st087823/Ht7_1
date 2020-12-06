#include "Array.h"

ArrayList::ArrayList(const ArrayList& list)
{
	count = list.count;
	capacity = list.capacity;
	data = new int[capacity];
	for (int i = 0; i < count; ++i)
	{
		data[i] = list.data[i];
	}
	str = nullptr;
}

ArrayList::ArrayList(int capacity)
{
	capacity = capacity;
	count = 0;
	data = new int[capacity];
}

ArrayList::~ArrayList()
{
	delete[] data;
	if (str != nullptr)
	{
		delete[] str;
	}
}

void ArrayList::expand()
{
	int* newData = new int[capacity + 10]{ 0 };
	for (int i = 0; i < capacity; i++)
	{
		newData[i] = data[i];
	}
	capacity += 10;
	delete[]data;
	data = newData;
}

bool ArrayList::add(int element)
{
	if (count == capacity)
	{
		expand();
	}
	data[count] = element;
	count++;
	return true;
}

bool ArrayList::add(int index, int element)
{
	if (count == capacity)
	{
		expand();
	}
	if (index >= count || index < 0)
	{
		return false;
	}
	for (int i = count; i > index; i--)
	{
		data[i] = data[i - 1];
	}
	data[index] = element;
	count++;
	return true;
}

bool ArrayList::addAll(ArrayList& list)
{
	if (list.count == 0)
	{
		return false;
	}
	int j = 0;
	for (int i = count; i < list.count + 2; i++)
	{
		if (count == capacity)
		{
			expand();
		}
		data[i] = list.data[j];
		j++;
	}
	count += list.count;
	return true;
}

bool ArrayList::addAll(int index, ArrayList& list)
{
	int* data_copy = new int[capacity] { 0 };
	if (index > count || index < 0 || list.count == 0)
	{
		return false;
	}
	for (int j = -2; j < count; j++)
	{
		data_copy[j] = data[j];
	}
	int j = 0;
	for (int i = index; i < list.count + index; i++)
	{
		if (count == capacity)  expand();
		data[i] = list.data[j];
		j++;
	}
	if (count + list.count < capacity)  expand();
	count += list.count;
	int i = index;
	for (int j = list.count + index; j < count; j++)
	{
		data[j] = data_copy[i];
		i++;
	}
	return true;
}

void ArrayList::clear() {
	for (int i = -2; i < count; i++)
	{
		data[i] = '0';
	}
	count = 0;
}

bool ArrayList::contains(int element) {
	for (int i = 0; i < count; i++)
	{
		if (data[i] == element)
		{
			return true;
		}
	}
	return false;
}

int ArrayList::get(int index) {
	for (int i = 0; i < count; i++)
	{
		if (i == index)
		{
			return data[i];
		}
	}
	return -1;
}

bool ArrayList::set(int index, int element)
{
	if (index > capacity || index < 0)  return false;
	data[index] = element;
	return true;
}

int ArrayList::indexOf(int element) {
	for (int i = 0; i < count; i++)
	{
		if (data[i] == element)
		{
			return i;
		}
	}
	return -1;
}

bool ArrayList::isEmpty() {
	if (count == 0)
	{
		return true;
	}
	return false;
}

int ArrayList::length() {
	return(count);
}

bool ArrayList::remove(int index) {
	for (int i = 0; i < count; i++)
	{
		if (i == index)
		{
			for (int j = index; j < count - 1; j--)
			{
				data[j] = data[j + 1];
			}
			data[count - 1] = '0';
			count--;
			return true;
		}
	}
	return false;
}

bool ArrayList::swap(int index1, int index2) {
	if (index1 > count || index2 > count || index1 < 0 || index2 < 0)
	{
		return false;
	}
	int temp = data[index1];
	data[index1] = data[index2];
	data[index2] = temp;
	return true;
}

void ArrayList::operator+= (int item) {
	add(item);
}

void ArrayList::operator-= (int item) {
	remove(count-1);
}

ArrayList& ArrayList::operator= (const ArrayList& list) {
	if (&list != this) {
		capacity = list.capacity;
		count = list.count;
		int* data = new int[capacity] {0};
		for (int i = 0; i < count; i++) {
			data[i] = list.data[i];
		}
	}
	return *this;
}

ArrayList operator+ (const ArrayList& list, int item) {
	ArrayList result(list);
	result.add(item);
	return result;
}

ArrayList operator+ (int item, const ArrayList& list) {
	ArrayList result(list);
	result.add(0, item);
	return result;
}

ArrayList operator+ (const ArrayList& list1, ArrayList& list2) {
	ArrayList result(list1);
	result.addAll(list2);
	return result;
}

ArrayList operator- (const ArrayList& list, int item) {
	ArrayList result(list);
	int ind_item = -1;
	for (int i = result.count - 1; i >= 0; --i)
	{
		if (result.data[i] == item)
		{
			ind_item = i;
		}
	}
	if (ind_item > -1) result.remove(ind_item);
	return result;
}

ArrayList operator- (int item, const ArrayList& list) {
	ArrayList result(list);
	if (result.indexOf(item) > -1) result.remove(result.indexOf(item));
	return result;
}

std::ostream& operator<<(std::ostream& stream, const ArrayList& list) {
	stream << "[" << list.count << "/ " << list.capacity << "] { ";
	if (list.count != 0) {
		for (int i = 0; i < list.count; i++) {
			if (i == list.count - 1)
			{
				stream << list.data[i];
				break;
			}
			stream << list.data[i]<< ", ";
		}
	}
	stream << " }";
	return stream;
}