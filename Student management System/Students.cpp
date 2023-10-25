
class Students{
	private:
	string name;
	string r_no;
	string email;
	string pass;
	int nofcourse;
	Courses registeredcourse;
	int quizscore;
	string quizname;
	
	public:
	Students(){
		name="\0";
		email="\0";
		pass="\0";
		r_no="\0";
		nofcourse=0;
		quizscore=0;
		quizname="\0";
	}
	string get_quizname(){
		return quizname;
	}
	void set_quizname(string str){
		quizname=str;
	}
	void set_quizscore(int i){
		quizscore+=i;
	}
	int get_quizscore(){
		return quizscore;
	}
	void set_name(string str){
		this->name=str;
		set_pass(str);
	}
	void set_r_no(string str){
		r_no=str;
		set_email(str);
	}
	void set_pass(string str){
		string domain="123$";
		char s[15];
		int len=0;
		for(int i=0;str[i]!=' ' && str[i]!='\0';i++){
			len++;
			s[i]=str[i];
		}
		if(len<4)
			s[3]=0;
		pass=s+domain;
			
	}
	void set_email(string str){
		string domain="@nu.edu.pk";
		char s[7];
		s[0]='i';
		s[1]=str[0];
		s[2]=str[1];
		for(int i=3,j=4;str[j]!='\0';i++,j++)
			s[i]=str[j];
		email=s+domain;
	}
	Courses get_registeredcourse(){
		return registeredcourse;
	}
	void set_nofcourse(int x){
		nofcourse=++x;
	}
	int get_nofcourse(){
		return nofcourse;
	}
	string get_email(){
		return email;
	}
	string get_pass(){
		return pass;
	}
	string get_name(){
		return name;
	}
	string get_r_no(){
		return r_no;
	}
	bool Addcourse(string str,string str2){
		int len=0;
		for(int i=0;registeredcourse.get_course(i)!="0";i++){
			if(str==registeredcourse.get_course(i))
				return 0;
			len++;
		}
		registeredcourse.set_course(str,len);
		registeredcourse.set_ID(str2,len);
		nofcourse++;
		return 1;
	}
	bool Removecourse(){
		int x;
		cout<<"Please select course that u want to remove from registered courses: "<<endl;
		registeredcourse.display();
		cin>>x;
		while(x>nofcourse || x<1){
			cout<<"Please enter a valid choice: ";
			cin>>x;
		}
		for(int i=x-1;i<nofcourse;i++){
			if(!i+1>=nofcourse){
				registeredcourse.set_course(registeredcourse.get_course(i+1),i);
				registeredcourse.set_ID(registeredcourse.get_ID(i+1),i);
			}
			else{
				registeredcourse.set_course("0",i);
				registeredcourse.set_ID("0",i);
			}
		}
		nofcourse--;
		return 1;
	}
	void student_attendance(){
		cout<<"ATTENDANCE OVERVIEW"<<endl;
		for(int i=0;i<nofcourse;i++)
			cout<<i+1<<") "<<registeredcourse.get_course(i)<<": "<<registeredcourse.get_attendance(registeredcourse.get_course(i),nofcourse)<<endl;
	}
	void display(){
		cout<<"-----------------------------"<<endl;
		cout<<".........Student Profile....."<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Email: "<<email<<endl;
		cout<<"No of registered courses: "<<nofcourse<<endl;
		cout<<"Registered courses...."<<endl;
		registeredcourse.display();
	}
};
