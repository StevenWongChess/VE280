#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"
using namespace std;

enum MEMBERSHIP{PLATINUM, GOLD, SILVER, REGULAR};
const string membership[4] = {"platinum", "gold", "silver", "regular"};

class line{
public:
	int timestamp;
	string name;
	MEMBERSHIP status;
	int duration;
};

MEMBERSHIP tran(string str);

int main(int argc, char const *argv[])
{
	Dlist<line> *queue_arr = new Dlist<line>[4];
	int line_count;
	cin >> line_count;
	line *list = new line[line_count];
	for(int i = 0; i < line_count; i++){
		string tmp = "";
		cin >> list[i].timestamp >> list[i].name >> tmp >> list[i].duration;
		list[i].status = tran(tmp);
		// cout << list[i].timestamp << list[i].name << list[i].status << list[i].duration << endl;
		queue_arr[tran(tmp)].insertBack(&list[i]);
	}

	int tick = 0;
	int time_end = 0;
	while(true){
		cout << "Starting tick #" << tick << endl;
		for(int i = 0; i < line_count; i++){
			if (&list[i] != nullptr && list[i].timestamp == tick){
				cout << "Call from " << list[i].name << " a " << membership[list[i].status] << " member\n";
			}
		}
		bool busy = (tick < time_end);
		if(!busy){
			int terminate = 0;
			for(int i = 0; i < 4; i++){
				if(!queue_arr[i].isEmpty()){
					line *tmp = queue_arr[i].removeFront();
					cout << "Answering call from " << tmp->name << endl;
					time_end = tick + tmp->duration;
					// delete tmp;
					break;
				}
				else{
					terminate++;
				}
			}
			if(terminate == 4){
				break;
			}
		}		
		tick ++;
	}
	delete[] list;
	delete[] queue_arr; 
	return 0;
}

MEMBERSHIP tran(string str){
	for(int i = 0; i < 4; i++){
		if (str == membership[i]){
			return static_cast<MEMBERSHIP>(i);
		}
	}
	cout << "error in input format\n";
	return PLATINUM;
}





