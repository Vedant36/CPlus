#include <iostream>
#include <vector>
using namespace std;

class Group{
public:
	int *data;
	int pin, size;
	vector<int> loop;
	Group(int _size = 256){
		pin = 0;
		size = _size;
		data = new int[_size];
		for(int i=0; i<size; ++i) data[i]=0;
	}
	~Group(){delete[] data;}
	void show();
	void clear();
	void run(int, string);
};

void Group::clear(){
	for(int i=0; i<size; ++i) data[i]=0;
}
void Group::show(){
	for (int i = 0; i < size; ++i){
		cout << (int)data[i];
		cout << ((i==pin)?"<":" ");
		if (!((i+1)%32)) cout << endl;
	}
}
void Group::run(int size, string line){
	while(){

	}
}

int main()
{
	Group basic(128);

	cout << "BrainFuck 1.0.0 (default, Sep  8 2020, 02:06:59)\n"
			 << "[G++ (Ubuntu 9.3.0-10ubuntu2) 9.3.0] :: Cabbage Corp. on linux\n"
			 << "Type h for more information and q to quit\n";

	while(true){
		cout << "brainfuck> ";
		string line;
		getline(cin, line);
		// cout << "<" 
		// 		<< (int)line[0] << "|" 
		// 		<< line << ">";
		switch(line[0]){
			case 'q': return 0;
			case 'c': basic.clear();break;
			case 'd': basic.show();break;
			case 'r':{
				int size = line.size();
				cout << size;
				basic.run(size, line.substr(2>size?size:2,size-1));
				break;
			}
		}
	}
}