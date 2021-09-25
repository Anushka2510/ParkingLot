#include<bits/stdc++.h>
using namespace std;

class Vehicle{
	private:
		string reg_no;
		int age;
		int slot_no;
		
	public:
		
		Vehicle(string reg, int age, int slot){
			this->reg_no = reg;
			this->age = age;
			this->slot_no = slot;
		}
		
		string get_reg(){
			return reg_no;
		}
		
		int get_age(){
			return age;
		}
		
		int get_slot(){
		    return slot_no;
		}
		
		void print(){
			cout << "\n	Reg_No	:	" << reg_no;
			cout << "\n	Age	:	" << age;
			cout << "\n	Slot_No	:	" << slot_no;
		}
};
	
	
	
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

string find_reg(string command){
	int n = command.size();
	string reg = "";
	
	int space;
	for(space=n-1; command[space]!=' '; space--);
	
	for(int i=space+1; i<n; i++)
		reg = reg + command[i];
		
	return reg;
}

int find_age(string command){
	int n = command.size();
	int age = 0;
	
	int space;
	for(space=n-1; command[space]!=' '; space--);
	
	for(int i=space+1; i<n; i++)
		age = age*10 + int(command[i]-48);
		
	return age;
}		
	
int find_slot(string command){
	int n = command.size();
	int slot = 0;
	
	int space;
	for(space=n-1; command[space]!=' '; space--);
	
	for(int i=space+1; i<n; i++)
		slot = slot*10 + int(command[i]-48);
		
	return slot;
}	

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////




string find_slot_given_age(vector<Vehicle> cars, int SIZE, int age){
	string ans = "";
	
	for(int i=0; i<SIZE; i++){
		if(cars[i].get_age() == age){
			
			int slot = cars[i].get_slot();
			ostringstream oss;
			oss << slot;
			
			ans = ans + oss.str();
			ans = ans + ",";
		}
	}
	
	ans = ans.substr(0, ans.size()-1);
	return ans;
}


string find_reg_given_age(vector<Vehicle> cars, int SIZE, int age){
	vector<string> ans;
	
	for(int i=0; i<SIZE; i++){
		if(cars[i].get_age() == age){
			
			string reg = cars[i].get_reg();
			ans.push_back(reg);
			
		}
	}
	
	string result = "";
	int n = ans.size();
	
	if(n==0)
		return result;
		
	for(int i=0; i<n-1; i++)
		result = result + "\"" + ans[i] + "\"" + ",";
	
	result = result + "\"" + ans[n-1] + "\"";
	return result;
}



int find_slot_given_reg(vector<Vehicle> cars, int SIZE, string reg){
	for(int i=0; i<SIZE; i++){
		string temp = cars[i].get_reg();
		
		int ans = temp == reg;
		if(ans == 1)
			return cars[i].get_slot();
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////




pair<string, int> find_reg_age(string command){
	int n = command.size();
	string reg = "";
	int age = 0;
	
	int space;
	for(space=n-1; command[space]!=' '; space--);
			
	for(int i=space+1; i<n; i++)
		age = age*10 + int(command[i]-48);
		
	for(space=5; command[space]!=' '; space++);
	for(int i=5; i<space; i++)
		reg = reg + command[i];
		
	return make_pair(reg, age);
}


int create_slots(string command){
	int n = command.size();
	int space;
	for(space=n-1; command[space]!=' '; space--);
	
	int size = 0;
	for(int i=space+1; i<n; i++)
		size = size*10 + int(command[i]-48);
		
	return size; 
}
		

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


bool compare(string command, string str[], int N){
	int n = command.size();
	
	for(int k=0; k<N; k++){
		int m = str[k].size();
		bool temp = false;
		
		for(int i=0; i<n; i++){
			if(command.substr(i, m) == str[k]){
				temp = true;
				break;
			}
		}
		
		if(temp == false) return false;
	}
	return true;
}


int main(){
	
	int next = 1;
	set<int> empty;
	empty.insert(next);
	
	string cmd;
	getline(cin, cmd);
	
    int MAX_SIZE = create_slots(cmd);
    vector<Vehicle> cars(MAX_SIZE, {"", 0, 0});
    
    cout << "Created parking of " << MAX_SIZE << " slots" << endl;

	bool flag = true;
	
	string v1[1] = {"Park"};
	string v2[1] = {"Leave"};
	
	string v31[2] = {"Slot", "driver"};
	string v32[2] = {"Slot", "car"};
	string v4[2] = {"Vehicle", "driver"};
	
	
	while(flag){
		
		string command;
		getline(cin, command);

		if(compare(command, v1, 1)){
			
			if(next > MAX_SIZE){
				cout << endl;
				continue;
			}
		  pair<string, int> reg_age = find_reg_age(command);
			
			string reg = reg_age.first;
			int age = reg_age.second;
			int slot = *empty.begin();
			
			Vehicle car(reg, age, slot);
			cars[slot-1] = car;
			
			cout << "Car with vehicle registration number \"" << reg <<"\" has been parked at slot number " << slot << endl;
			
			empty.erase(slot);
			if(next == slot) next++;
			if(next <= MAX_SIZE) empty.insert(next);
		}
		
		else if(compare(command, v2, 1)){
      int slot = find_slot(command);
			Vehicle car("", 0, 0);
			
			if(cars[slot-1].get_slot() == 0){
				cout << "Slot already vacant" << endl;
				continue;
			}
			
			cout << "Slot number " << slot << " vacated, the car with vehicle registration number \"" << cars[slot-1].get_reg() << "\" left the space, the driver of the car was of age " << cars[slot-1].get_age() << endl;
			
			cars[slot-1] = car;
			empty.insert(slot);
		}
		
		else if(compare(command, v31, 2)){
      int age = find_age(command);
			string all_slot_no = find_slot_given_age(cars, next, age);
			cout << all_slot_no << endl;
		}
		
		else if(compare(command, v32, 2)){
      string reg = find_reg(command);
			int slot = find_slot_given_reg(cars, next, reg);
			
			if(slot == 0) cout << endl;
			else cout << slot << endl;
		}	
		
		else if(compare(command, v4, 2)){
			int age = find_age(command);
			string all_reg_no = find_reg_given_age(cars, next, age);
			cout << all_reg_no << endl;
		}
		
		else if(command[0] == 'X' || command[0] == 'x') flag = false;
	}
	return 0;
}
