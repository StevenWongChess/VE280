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
	string status;
	int duration;
};

int main(int argc, char const *argv[])
{
	Dlist<line> *queue_arr = new Dlist<line>[4];
	int line_count;
	cin >> line_count;
	line *list = new line[line_count];
	for(int i = 0; i < line_count; i++){
		cin >> list[i].timestamp >> list[i].name
			>> list[i].status >> list[i].duration;
		queue_arr[0].insertBack(&list[i]);
		cout << "Call from " << list[i].name << " a " << list[i].status << " silver member\n";
	}

	if(!busy){
		for(int i = 0; i < 4; i++){
			if(!queue_arr[i].isEmpty()){
				queue_arr[i].removeFront();
				break;
			}
		}
	}		
	else{
		
	}

	
	return 0;

}







