#include<iostream>
#include<string>
using namespace std;

class Courses{
	
	string* name;
	string* ID;
	char* attendance;
	
	public:
	Courses(){
		name=new string[11];
		ID=new string[11];
		attendance=new char[11];
		for(int i=0;i<11;i++){
			name[i]="0";
			ID[i]="0";
			attendance[i]='A';
		}
	}
	char get_attendance(string str,int x){
		int find=0;
		for(int i=0;i<x;i++)
			if(name[i]==str)
				find=i;
		return attendance[find];
	}
	char get_attendance(int x){
		return attendance[x];
	}
	void set_attendance(int x){
		attendance[x]='P';
	}
	void set_course(string name,int i){
		this->name[i]=name;
	}
	void set_ID(string ID,int i){
		this->ID[i]=ID;
	}
	string get_course(int i){
		return name[i];
	}
	string get_ID(int i){
		return ID[i];
	}
	void display(){
		for(int i=0; i<11 ;i++){
			if(name[i]!="0"){
				cout<<i+1<<") "<<name[i]<<endl;
				cout<<"Course ID: "<<ID[i]<<endl;
			}
			else if(name[i]=="0" && i==0)
				cout<<"No courses registered"<<endl;
		}
	}
};
