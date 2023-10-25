#include<iostream>
using namespace std;
class Teachers{
	string name;
	string email;
	string pass;
	string course;
	
	public:
	Teachers(){
		name="\0";
		email="\0";
		pass="\0";
		course="\0";
	}
	void set_name(string str){
		name=str;
		set_ID(str);
	}
	void set_ID(string str){
		bool check=false;
		string s3="@nu.edu.pk";
		string s2="123$";
		char s1[10];
		int j=0;
		for(int i=0;check==false;i++)
			if(str[i]=='.' || str[i]==' '){
				for(int j=i+1,k=0;str[j]!=' ' && str[j]!='\0';j++,k++)
					s1[k]=str[j];
				check=true;
			}
		pass=s1+s2;
		email=s1+s3;	
	}
	void set_course(string str){
		course=str;
	}
	string get_name(){
		return name;
	}
	string get_course(){
		return course;
	}
	string get_email(){
		return email;
	}
	string get_pass(){
		return pass;
	}
	void display(){
		cout<<"Name: "<<name<<endl;
		cout<<"email: "<<email<<endl;
		cout<<"Instructor of course: "<<course<<endl;
	}
};
