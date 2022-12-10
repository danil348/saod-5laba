#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <chrono>

using namespace std;

struct Passenger
{
	string name;

	bool inFirst;
	bool inSecond;

	int firstPlace = 0;
	int secondPlace = 0;

	int serviceTime;
	bool serviced = false;
};

class queue
{
public:
	queue(int size);
	void insert(Passenger value);
	void increase();
	Passenger remove();
	Passenger peekFront();
	bool isEmpty();
	int Size();
	void display();
	void resetTime() {
		this->time = 0;
	}
	int getTime();
	void increaseTime();
	void move(int value) {
		if (arr[front].inFirst) {
			while (arr[front].firstPlace != value + 1) {
				front++;
				if (front == size) {
					front = 0;
				}
			}
		}
		else {
			while (arr[front].secondPlace != value + 1) {
				front++;
				if (front == size) {
					front = 0;
				}
			}
		}
	}
	void servised() {
		arr[front].serviced = true;
	}
private:
	int time;
	int size;
	Passenger* arr;
	int front;
	int rear;
	int items;
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream file;
	string filename;
	queue passengers1(5);
	queue passengers2(4);

	cout << "Введите название файла для ввода: ";
	cin >> filename;
	file.open(filename);
	while (!file.eof())
	{
		Passenger passenger;
		file >> passenger.name;
		file >> passenger.inFirst;
		file >> passenger.inSecond;
		file >> passenger.firstPlace;
		file >> passenger.secondPlace;
		file >> passenger.serviceTime;

		if (passenger.inFirst == true) {
			passengers1.insert(passenger);
			if (passenger.inSecond == true) {
				Passenger passengertmp;
				passengertmp.name = passenger.name;
				passengertmp.inFirst = passenger.inFirst;
				passengertmp.inSecond = passenger.inSecond;
				passengertmp.firstPlace = passenger.firstPlace;
				passengertmp.secondPlace = passenger.secondPlace;
				passengertmp.serviceTime = passenger.serviceTime;
				passengers2.insert(passengertmp);
			}
		}
		else {
			passengers2.insert(passenger);
		}
	}

	cout << "первая очередь: ";
	passengers1.display();
	cout << "вторая очередь: ";
	passengers2.display();
	cout << endl;


	while (true)
	{
		if (passengers2.isEmpty() == true && passengers1.isEmpty() == true) {
			break;
		}


		if (passengers1.peekFront().serviceTime == passengers1.getTime() && passengers1.isEmpty() == false) {

			cout << "первая очередь: ";
			passengers1.display();


			int tmp = passengers1.peekFront().firstPlace;
			passengers1.servised();
			cout << passengers1.remove().name << " обслужен\n";
			if (passengers1.Size() > 1) {
				passengers1.move(tmp);
			}
			passengers1.resetTime();


		}


		if (passengers2.peekFront().serviceTime == passengers2.getTime() && passengers2.isEmpty() == false) {

			cout << "вторая очередь: ";
			passengers2.display();


			int tmp = passengers2.peekFront().secondPlace;
			passengers2.servised();
			cout << passengers2.remove().name << " обслужен\n";
			if (passengers2.Size() > 1) {
				passengers2.move(tmp);
			}
			passengers2.resetTime();

		}

		if (passengers1.getTime() == 0 && passengers2.getTime() == 0 &&
			passengers1.peekFront().name == passengers2.peekFront().name) {
			passengers2.servised();
			passengers2.remove();
		}

		passengers1.increaseTime();
		passengers2.increaseTime();
	}


	cout << "первая очередь\n";
	passengers1.display();
	cout << "\nвторая очередь\n";
	passengers2.display();
}

int queue::getTime()
{
	return this->time;
}

void queue::increaseTime() {
	this->time += 1;
}

queue::queue(int size)
{
	this->size = size;
	arr = new Passenger[size];
	front = 0;
	rear = -1;
	items = 0;
	time = 0;
}

void queue::insert(Passenger value)
{
	if (items == size) {
		increase();
	}
	arr[++rear] = value;
	items++;
}

void queue::increase()
{
	// выделение памяти под увеличенный массив
	Passenger* tmp = new Passenger[size + 5];

	// перенос значений из старого массива
	for (int i = 0; i < items; i++)
	{
		tmp[i] = arr[i];
	}

	size += 5;

	delete[] arr;
	arr = tmp;
}

Passenger queue::remove()
{
	Passenger tmp = arr[front++];
	if (front == size) {
		front = 0;
	}
	items--;
	return tmp;
}

Passenger queue::peekFront()
{
	return arr[front];
}

bool queue::isEmpty()
{
	return items == 0;
}

int queue::Size()
{
	return items;
}

void queue::display()
{
	if (isEmpty() == true) {
		cout << "очередь пустая";
	}
	else {
		for (int i = 0; i < size; i++) {
			if (arr[i].serviced == false) {
				if (i == size - 1) {
					if (arr[i].inFirst == true) {
						cout << "№" << arr[i].firstPlace << " " << arr[i].name << " (" << arr[i].serviceTime << ")";
					}
					else {
						cout << "№" << arr[i].secondPlace << " " << arr[i].name << " (" << arr[i].serviceTime << ")";
					}
				}
				else {
					if (arr[i].inFirst == true) {
						cout << "№" << arr[i].firstPlace << " " << arr[i].name << " (" << arr[i].serviceTime << ") -- ";
					}
					else {
						cout << "№" << arr[i].secondPlace << " " << arr[i].name << " (" << arr[i].serviceTime << ") -- ";
					}
				}
			}
		}
		cout << endl;
	}
}
