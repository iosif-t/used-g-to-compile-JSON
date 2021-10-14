#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include<math.h>


using namespace std;

#ifdef NULL
#undef NULL
#endif

bool mustPrint=false;

class Json;
class Key;
class Value;
class Object;
class True;
class False;
class Nil;
class Array;
class Str;
bool checkEqualObj(vector<Key> f,vector<Key> s);
bool checkEqualArr(vector<Value> f,vector<Value> s);
void printKeys(vector<Key> k);
void helpPrint(Value v);
void printArr(vector<Value> v);

int Tabs=0;

enum Type{
	STR,
	NUM,
	TRU,
	NIL,
	FALS,
	ARRAY,
	OBJECT,
	KEY
};


vector<Json> jsons;


class Value{
	
	public:
		Value(){this->dirty=false;}
		string strVal;	
		float numVal;
		bool boolVal;
		Type type;	
		string jsonname;
		vector<Value> myElem;
		vector<Key> keys;
		bool dirty;
		
		friend Value operator , (const Value& a,const Value& b);

		Value& operator [](const int& n){
			if(this->myElem.size()<n+1){
				Value v;
				this->myElem.push_back(v);
				return this->myElem.at(this->myElem.size()-1);
			}
			return this->myElem.at(n);
		}
		Value& help_overload(string n);

		Value& operator [](const string& n){
			return help_overload(n);
		}	
		void help_overload2(const Value &v);
		void operator += (const Value& v){
			help_overload2(v);
		}

		Value operator + (Value str){
			if(this->type==STR&&str.type==STR){
				Value newStr;
				newStr.strVal=this->strVal;
				newStr.strVal+=str.strVal;
				newStr.type=STR;
				return newStr;
			}
			else if(this->type==ARRAY&&str.type==ARRAY){
				Value newArr;
				newArr.type=ARRAY;
				newArr.myElem=this->myElem;
				for(int k=0;k<str.myElem.size();k++)
					newArr.myElem.push_back(str.myElem.at(k));
				return newArr;
			}
			else if(this->type==OBJECT&&str.type==OBJECT){
				Value newObj;
				newObj.type=OBJECT;
				newObj.keys=this->keys;
				for(int k=0;k<str.keys.size();k++)
					newObj.keys.push_back(str.keys.at(k));
				return newObj;
			}
			else if(this->type==NUM&&str.type==NUM){
				Value newNum;
				newNum.type=NUM;
				newNum.numVal=(this->numVal+str.numVal);
				return newNum;
			}
			cout << "Error,operands are not type of STRING,ARRAY,OBJECT,NUMBER"<<endl;
			exit(-1);
			
		}


		Value operator - (Value v){
			if(this->type==NUM&&v.type==NUM){
				Value newN;
				newN.type=NUM;
				newN.numVal=(this->numVal-v.numVal);
				return newN;
			}
			cout << "Error,operands are not type of NUMBER"<<endl;
			exit(-1);
		}
		Value operator * (Value v){
			if(this->type==NUM&&v.type==NUM){
				Value newN;
				newN.type=NUM;
				newN.numVal=(this->numVal*v.numVal);
				return newN;
			}
			cout << "Error,operands are not type of NUMBER"<<endl;
			exit(-1);
		}
		Value operator / (Value v){
			if(this->type==NUM&&v.type==NUM){
				Value newN;
				newN.type=NUM;
				newN.numVal=(this->numVal/v.numVal);
				return newN;
			}
			cout << "Error,operands are not type of NUMBER"<<endl;
			exit(-1);
		}
		Value operator % (Value v){
			if(this->type==NUM&&v.type==NUM){
				Value newN;
				newN.type=NUM;
				newN.numVal=fmod(this->numVal,v.numVal);
				return newN;
			}
			cout << "Error,operands are not type of NUMBER"<<endl;
			exit(-1);
		}
		Value operator < (Value v){
			if(this->type==NUM&&v.type==NUM){
				Value newN;
				if(this->numVal<v.numVal){
					newN.boolVal=true;
					newN.type=TRU;
					return newN;
				}
				newN.boolVal=false;
				newN.type=FALS;
				return newN;
			}
			cout << "Error,operands are not type of NUMBER"<<endl;
			exit(-1);
		}
		Value operator <= (Value v){
			if(this->type==NUM&&v.type==NUM){
				Value newN;
				if(this->numVal<=v.numVal){
					newN.boolVal=true;
					newN.type=TRU;
					return newN;
				}
				newN.boolVal=false;
				newN.type=FALS;
				return newN;
			}
			cout << "Error,operands are not type of NUMBER"<<endl;
			exit(-1);
		}
		Value operator > (Value v){
			if(this->type==NUM&&v.type==NUM){
				Value newN;
				if(this->numVal>v.numVal){
					newN.boolVal=true;
					newN.type=TRU;
					return newN;
				}
				newN.boolVal=false;
				newN.type=FALS;
				return newN;
			}
			cout << "Error,operands are not type of NUMBER"<<endl;
			exit(-1);
		}
		Value operator >= (Value v){
			if(this->type==NUM&&v.type==NUM){
				Value newN;
				if(this->numVal>=v.numVal){
					newN.boolVal=true;
					newN.type=TRU;
					return newN;
				}
				newN.boolVal=false;
				newN.type=FALS;
				return newN;
			}
			cout << "Error,operands are not type of NUMBER"<<endl;
			exit(-1);
		}

		Value operator && (Value v){
			if((this->type==TRU||this->type==FALS)&&(v.type==TRU||v.type==FALS)){
				Value newB;
				if(this->boolVal&&v.boolVal){
					newB.boolVal=true;
					newB.type=TRU;
					return newB;
				}
				newB.boolVal=false;
				newB.type=FALS;
				return newB;
			}
			cout << "Error,operands are not type of BOOL"<<endl;
			exit(-1);
		}
		Value operator || (Value v){
			if((this->type==TRU||this->type==FALS)&&(v.type==TRU||v.type==FALS)){
				Value newB;
				if(this->boolVal||v.boolVal){
					newB.boolVal=true;
					newB.type=TRU;
					return newB;
				}
				newB.boolVal=false;
				newB.type=FALS;
				return newB;
			}
			cout << "Error,operands are not type of BOOL"<<endl;
			exit(-1);
		}
		Value operator ! (){
			if(this->type==TRU||this->type==FALS){
				Value newB;
				if(!this->boolVal){
					newB.boolVal=true;
					newB.type=TRU;
					return newB;
				}
				newB.boolVal=false;
				newB.type=FALS;
				return newB;
			}
			cout << "Error,operands are not type of BOOL"<<endl;
			exit(-1);
		}
		friend ostream& operator<<(ostream &out,const Value j){
			if(j.dirty)
				return out;

			helpPrint(j);
			if(j.type==OBJECT){
				printKeys(j.keys);
			}
			else if(j.type==ARRAY){
				printArr(j.myElem);
			}
			return out;
		}
		Value operator == (Value v){
			if(this->type!=v.type){
				cout<<"ERROR dif types"<<endl;
				exit(-1);
			}
			Value newVal;
			newVal.type=FALS;
			newVal.boolVal=false;

			if(this->type==NUM&&v.type==NUM){
				if(this->numVal==v.numVal){
					newVal.type=TRU;
					newVal.boolVal=true;
				}
			}
			else if(this->type==STR&&v.type==STR){
				if(this->strVal==v.strVal){
					newVal.type=TRU;
					newVal.boolVal=true;
				}
			}			
			else if(this->type==TRU&&v.type==TRU){
					newVal.type=TRU;
					newVal.boolVal=true;
			}	
			else if(this->type==NIL&&v.type==NIL){
					newVal.type=TRU;
					newVal.boolVal=true;
			}			
			else if(this->type==OBJECT&&v.type==OBJECT){
				if(this->keys.empty()&&v.keys.empty()){
					 newVal.type=TRU;
					 newVal.boolVal=true;
				 }
				else if(checkEqualObj(this->keys,v.keys)){
					newVal.type=TRU;
					newVal.boolVal=true;
				}
			}
			else if(this->type==ARRAY&&v.type==ARRAY){
				if(this->myElem.empty()&&v.myElem.empty()){
					 newVal.type=TRU;
					 newVal.boolVal=true;
				 }
				else if(checkEqualArr(this->myElem,v.myElem)){
					newVal.type=TRU;
					newVal.boolVal=true;
				}				
			}
			return newVal;
		}
		Value operator != (Value v){
			if(this->type!=v.type){
				cout<<"ERROR dif types"<<endl;
				exit(-1);
			}
			Value newVal;
			newVal.type=FALS;
			newVal.boolVal=false;

			if(this->type==NUM&&v.type==NUM){
				if(this->numVal!=v.numVal){
					newVal.type=TRU;
					newVal.boolVal=true;
				}
			}
			else if(this->type==STR&&v.type==STR){
				if(this->strVal!=v.strVal){
					newVal.type=TRU;
					newVal.boolVal=true;
				}
			}			
			else if(this->type==TRU&&v.type==TRU){
					newVal.type=FALS;
					newVal.boolVal=false;
			}	
			else if(this->type==NIL&&v.type==NIL){
					newVal.type=FALS;
					newVal.boolVal=false;
			}			
			else if(this->type==OBJECT&&v.type==OBJECT){
				if(this->keys.empty()&&v.keys.empty()){
					 newVal.type=FALS;
					 newVal.boolVal=false;
				}
				else if(!checkEqualObj(this->keys,v.keys)){
					newVal.type=TRU;
					newVal.boolVal=true;
				}
			}
			else if(this->type==ARRAY&&v.type==ARRAY){
				if(this->myElem.empty()&&v.myElem.empty()){
					 newVal.type=FALS;
					 newVal.boolVal=false;
				 }
				else if(!checkEqualArr(this->myElem,v.myElem)){
					newVal.type=TRU;
					newVal.boolVal=true;
				}				
			}
			return newVal;
		}						
		
};





vector<Value> * temp=(vector<Value>*)0;
vector<Value> tmpArrayElements;




Value operator , (const Value& a,const Value& b){
	
	if(tmpArrayElements.empty()){
			if(mustPrint){
				helpPrint(a);
				if(a.type==OBJECT){
					printKeys(a.keys);
				}
				else if(a.type==ARRAY){
					printArr(a.myElem);
				}
				helpPrint(b);
				if(b.type==OBJECT){
					printKeys(b.keys);
				}
				else if(b.type==ARRAY){
					printArr(b.myElem);
				}
			}
			tmpArrayElements.push_back(a);
			tmpArrayElements.push_back(b);
			if(temp){
				temp->push_back(a);
				temp->push_back(b);	
			}
		}
	else{
		if(mustPrint){
			helpPrint(b);
			if(b.type==OBJECT){
				printKeys(b.keys);
			}
			else if(b.type==ARRAY){
				printArr(b.myElem);
			}
		}
		tmpArrayElements.push_back(b);
		if(temp){
			temp->push_back(b);
		}
	}
	return a;
}

string jsonName;

class Key:public Value{
	public:
		string key;
		Value key_value;
		Key(string name){
			this->strVal=name;
			this->key=name;
			this->type=KEY;
			this->jsonname=name;
		}
};


bool checkEqualArr(vector<Value> f,vector<Value> s){
	if(f.size()!=s.size())
		return false;
	for(int i=0;i<f.size();i++){

		if(f.at(i).type!=s.at(i).type)
			return false;
		if(f.at(i).dirty^s.at(i).dirty)
			return false;
		switch (f.at(i).type){
			case NUM:
				if(f.at(i).numVal!=s.at(i).numVal)
					return false;
			break;
			case STR:
				if(f.at(i).strVal!=s.at(i).strVal)
					return false;
			break;
			case OBJECT:
				return checkEqualObj(f.at(i).keys,s.at(i).keys);
			case ARRAY:
				return checkEqualArr(f.at(i).myElem,s.at(i).myElem);
			default:
			break;
		}
	}
	return true;	
}

bool checkEqualObj(vector<Key> f,vector<Key> s){
	if(f.size()!=s.size())
		return false;
	for(int i=0;i<f.size();i++){
		if(f.at(i).key!=s.at(i).key)
			return false;
		if(f.at(i).key_value.type!=s.at(i).key_value.type)
			return false;
		if(f.at(i).key_value.dirty^s.at(i).key_value.dirty)
			return false;
		switch (f.at(i).key_value.type){
			case NUM:
				if(f.at(i).key_value.numVal!=s.at(i).key_value.numVal)
					return false;
			break;
			case STR:
				if(f.at(i).key_value.strVal!=s.at(i).key_value.strVal)
					return false;
			break;
			case OBJECT:
				return checkEqualObj(f.at(i).key_value.keys,s.at(i).key_value.keys);
			
			case ARRAY:
				return checkEqualArr(f.at(i).key_value.myElem,s.at(i).key_value.myElem);
			default:
			break;
		}
	}
	return true;
}








Value& Value::help_overload(string n){
	bool passed;
	for(int k=0;k<this->keys.size();k++){
		if(this->keys.at(k).key==n)
			return this->keys.at(k).key_value;
		passed=true;
	}		
	if(passed){
		Key new_key(n);
		new_key.key_value.type=KEY;
		this->keys.push_back(new_key);
		return this->keys.at(this->keys.size()-1).key_value;
	}
			
	return this->keys.at(this->keys.size()-1).key_value; 
}

void Value::help_overload2(const Value & v){
	
	if(this->type==KEY){
		*this=v;
	}
	else{
		tmpArrayElements.clear();
		this->myElem.push_back(v);
		temp=&(this->myElem);
		
	}
}

class Json{
	public:
		string name;			
		Value val;
		Json(){this->name=jsonName;}
		Json(string name){	
			this->name=name;
			jsons.push_back(*this);	
	
		}
	
		Value& operator = (const Value& n){
			jsons.at(jsons.size()-1).val=n;
			jsons.at(jsons.size()-1).val.jsonname=jsons.at(jsons.size()-1).name;
			return jsons.at(jsons.size()-1).val;
		} 
};



class Str : public Value{
	public:	
		Str(string strVal){
			this->strVal=strVal.substr(1,strVal.size()-2);
			this->type=STR;
		}
};


class Number: public Value{
	public:
		Number(float numVal){
			this->type=NUM;
			this->numVal=numVal;	
		}
};

class True: public Value{
	public:
		True(){
			this->type=TRU;
			this->boolVal=true;
		}
};

class False: public Value{
	public:
		False(){
			this->type=FALS;
			this->boolVal=false;
		}
};

class Nil : public Value {
	public:
		Nil(){
			this->type=NIL;
		}
};




class Object: public Value{
	public:
		
		Object(){
			this->type=OBJECT;
		}
		Object(initializer_list<Value> j){
		
			for(auto i:j){
				
				if(i.type==KEY){
					
					Key k(i.jsonname);
					keys.push_back(k);
				}
				else{
					keys.at(keys.size()-1).key_value=i;
				
				}
			}
			this->type=OBJECT;	
		}
}; 

class Array : public Value {
	public:
		Array(){
			this->type=ARRAY;
		}
		 Array operator[](const Value &a) {
			if(tmpArrayElements.empty())
				this->myElem.push_back(a);
			else
				this->myElem=tmpArrayElements;
			tmpArrayElements.clear();	
			this->type=ARRAY; 
			return *this;
		} 
};



void printArr(vector<Value> v){
	Tabs++;
	int elemcounter=0;
	for(int i=0;i<v.size();i++){
		if(v.at(i).dirty)
			continue;
		for(int i=0;i<Tabs;i++){
				cout<<"\t";
		}
		cout<< "element #"<<elemcounter<< " ";
		elemcounter++;
		switch(v.at(i).type){
			case STR:			
				cout<<" - String : "<<v.at(i).strVal<<endl;				
				break;
			case NUM:
				cout<<" - Number : "<<v.at(i).numVal<<endl;
				break;
			case TRU:
				cout<<" - TRUE"<<endl;
				break;
			case FALS:
				cout<<" - FALSE"<<endl;
				break;
			case NIL:
				cout<<" - NULL"<<endl;
				break;
			case OBJECT:
				cout<<" - Object:"<<endl;
				 printKeys(v.at(i).keys);
				break;
			case ARRAY:
				cout<<" - Array:"<<endl;
				printArr(v.at(i).myElem);
				break;
			default : break;
		}
	}
	Tabs--;
	return;
}

void helpPrint(Value v){
	if(v.dirty)
		return;
	switch(v.type){
			case STR:
				cout<<v.strVal<<endl;
				break;
			case NUM:
				cout<<v.numVal<<endl;
				break;
			case TRU:
				cout<<"TRUE"<<endl;
				break;
			case FALS:
				cout<<"FALSE"<<endl;
				break;
			case NIL:
				cout<<"NULL"<<endl;
				break;
			case OBJECT:
				cout<<"Object:"<<endl;
				break;
			case ARRAY:
				cout<<"Array:"<<endl;
				break;
			default : break;
		}	
}



void printKeys(vector<Key> k){
	Tabs++;
	for(int i=0;i<k.size();i++){
		if(k.at(i).key_value.dirty)
			continue;
			for(int i=0;i<Tabs;i++){
				cout<<"\t";
			}
			switch(k.at(i).key_value.type){
			case STR:
				cout<<"Key named: "<<k.at(i).key<<" - String : "<<k.at(i).key_value.strVal<<endl;
				break;
			case NUM:
				cout<<"Key named: "<<k.at(i).key<<" - Number : "<<k.at(i).key_value.numVal<<endl;
				break;
			case TRU:
				cout<<"Key named: "<<k.at(i).key<<" - TRUE"<<endl;
				break;
			case FALS:
				cout<<"Key named: "<<k.at(i).key<<" - FALSE"<<endl;
				break;
			case NIL:
				cout<<"Key named: "<<k.at(i).key<<" - NULL"<<endl;
				break;
			case OBJECT:
				cout<<"Key named: "<<k.at(i).key<<" - Object:"<<endl;
				printKeys(k.at(i).key_value.keys);
				break;
			case ARRAY:
				cout<<"Key named: "<<k.at(i).key<<" - Array:"<<endl;
				printArr(k.at(i).key_value.myElem);
				break;
			default : break;
		}	
	}
	Tabs--;
	return;

}

void arrDirty(vector<Value> &arr);

void objDirty(vector<Key> &arr){
		
	for(int i=0;i<arr.size();i++){
		arr.at(i).dirty=true;
		switch(arr.at(i).key_value.type){
			case STR:
				arr.at(i).key_value.dirty=true;
				break;
			case NUM:
				arr.at(i).key_value.dirty=true;
				break;
			case TRU:
				arr.at(i).key_value.dirty=true;
				break;
			case FALS:
				arr.at(i).key_value.dirty=true;
				break;
			case NIL:
				arr.at(i).key_value.dirty=true;
				break;
			case OBJECT:
				arr.at(i).key_value.dirty=true;
				objDirty(arr.at(i).key_value.keys);
				break;
			case ARRAY:
				arr.at(i).key_value.dirty=true;
				arrDirty(arr.at(i).key_value.myElem);
				break;
			default : break;
		}	
	}
	return;
}

void arrDirty(vector<Value> & arr){
	for(int i=0;i<arr.size();i++){
		switch(arr.at(i).type){
			case STR:
				arr.at(i).dirty=true;
				break;
			case NUM:
				arr.at(i).dirty=true;
				break;
			case TRU:
				arr.at(i).dirty=true;
				break;
			case FALS:
				arr.at(i).dirty=true;
				break;
			case NIL:
				arr.at(i).dirty=true;
				break;
			case OBJECT:
				arr.at(i).dirty=true;
				objDirty(arr.at(i).keys);
				break;
			case ARRAY:
				arr.at(i).dirty=true;
				arrDirty(arr.at(i).myElem);
				break;
			default : break;
		}	
	}
	return;
}

class Delete{
	public:
	Delete(){}
	void operator + (Value& v){
		v.dirty=true;
		if(v.type==ARRAY)
			arrDirty(v.myElem);
		else if(v.type==OBJECT)
			objDirty(v.keys);
	}
};

Value IS_EMPTY(Value j){
	if(j.type==ARRAY){
		if(j.myElem.empty()||j.dirty)
			return True();
	}
	if(j.type==OBJECT){
		if(j.keys.empty()||j.dirty)
			return True();
	}
	return False();
}

Value TYPE_OF(Value j){
	switch(j.type){
		case STR:
			return Str("1string1");		
		case NUM:
			return Str("1number1");	
		case TRU:
			return Str("1boolean1");
		case FALS:
			return Str("1boolean1");	
		case NIL:
			return Str("1NULL1");	
		case OBJECT:
			return Str("1object1");
		case ARRAY:
			return Str("1array1");
		default : break;
	}	
	return Str("1KATS_KALA1");
}


Value HAS_KEY(Value v,string key){
	
	if(v.type==OBJECT){
		for(int i=0;i<v.keys.size();i++)
			if(v.keys.at(i).key==key&&!v.keys.at(i).dirty)
				return True();
	}
	return False();
}

Value SIZE_OF(Value v){
	if(v.type==ARRAY)
		return Number(v.myElem.size());
	if(v.type==OBJECT)
		return Number(v.keys.size());

	return Number(1);
}

#define PROGRAM_BEGIN int main(){

#define JSON(name) ;mustPrint=false;temp=(vector<Value>*)0;tmpArrayElements.clear();  jsonName=#name;Value name = Json(#name) 

#define STRING(strin)   Str(#strin) 

#define NUMBER(numee)   Number(numee) 

#define TRUE   True()

#define FALSE   False()

#define NULL  Nil()

#define KEY(name)  Key(#name) , false ? Value()  
 
#define OBJECT  Object

#define ARRAY  Array()

#define SET ;mustPrint=false; temp=(vector<Value>*)0;tmpArrayElements.clear();

#define ASSIGN =

#define ERASE ;mustPrint=false;temp=(vector<Value>*)0; tmpArrayElements.clear(); Delete() +

#define APPEND  +=  

#define PRINT ; mustPrint=true;temp=(vector<Value>*)0;tmpArrayElements.clear(); cout <<

#define PROGRAM_END  ;return 0;}