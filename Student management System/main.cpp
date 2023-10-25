#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<ctime>
#include "Feeback.cpp"
#include "Courses.cpp"
#include "Teachers.cpp"
#include "Students.cpp"
#include "user.cpp"
#include "Bank.cpp"
using namespace std;

class GoogleClassroomSystem{
	protected:
	Courses course;
	Bank bank[11];
	Teachers teacher[11];
	Students student[216];
	Quiz* quiz=NULL;
	Answers ans[11][3];
	string quiz_ans[4];
	user User;
	
	public:
	
	void readdatafromcsvfile(){
		cout<<"Starting the system....."<<endl;
		ifstream inputFile("data.csv");
		if (!inputFile.is_open()) {
			cout << "Failed to open file!" << endl;
			exit(0);
	    	}
	    	string line;
	   	const int ROWS = 1; // Maximum number of rows 
	   	int row = 0;
	    
	   	int n=0; //for rows;
	    	int j=0; //for col;
	    	int k=0; 
	    	while (getline(inputFile, line)) {
	      		  if (row >= ROWS) {
		 		   cout << "Maximum number of rows exceeded!" << endl;
		  		   break;
	       		  }
		stringstream lineStream(line);
		string cell;
		while (getline(lineStream, cell, ',')) 
			{
				if(n==0 && j>2){
					course.set_course(cell,j-3);
				}
				if(n==1 && j>2){
					course.set_ID(cell,j-3);
				}
				if(n==2 && j>2){
					teacher[j-3].set_name(cell);
					teacher[j-3].set_course(course.get_course(j-3));
				}
				if(n>3 && n<220){
					if(j==1)
						student[n-4].set_r_no(cell);
					if(j==2)
						student[n-4].set_name(cell);
					if(j>2)
						if(cell=="1"){
							student[n-4].set_nofcourse(student[n-4].get_nofcourse());
							student[n-4].get_registeredcourse().set_course(course.get_course(j-3),student[n-4].get_nofcourse()-1);
							student[n-4].get_registeredcourse().set_ID(course.get_ID(j-3),student[n-4].get_nofcourse()-1);
						}
				}
				j++;		
			}
		k=0;
		j=0;
		n++;
		}
		inputFile.close();
				
		string s1[11]={"1) Programming Fundamentals","2) Object Oriented Programming","3) Introduction To Computing","4) Data Structures","5) Analysis of Algorithms","6) Software Requirements Engineering","7) Research Methodology","8) Big Data Analysis","9) Artificial Intelligence","10) Deep Learning","11) Digital Image Processing"};
		string s2[3]={"Topic 1:","Topic 2:","Topic 3:"};
		string s3[3]={"MCQs:","True/False:","Descriptive Questions:"};
		
		ifstream inputFile2("QuestionBank.csv");
		if (!inputFile2.is_open()) {
			cout << "Failed to open file!" << endl;
			exit(0);
	    	}
	    	line;
	   	row = 0;
		int course=0;
		int t=0;
		k=5;
		n=0;
		int m=0; //for mcq
		char toremove=',';
		int o=0;
	    	while (getline(inputFile2, line)) {
	      		  if (row >= 724) {
		 		   cout << "Maximum number of rows exceeded!" << endl;
		  		   break;
	       		  }
		stringstream lineStream(line);
		string cell;
		while (getline(lineStream, cell, ',')) 
			{
				for(int i=0;i<11;i++)
					if(cell==s1[i]){
						bank[i].set_coursename(cell);
						course++;
						t=0;
						k=5;
						continue;
						}
				for(int i=0;i<3;i++)
					if(cell==s2[i]){
						t++;
						m=0;
						continue;
					}
				if(course!=0 && t!=0){
					if(bank[course-1].topic[t-1].topicname=="0"){
						string y;
						getline(inputFile2,y);
						for(int i=0;y[i]!='\0';i++)
							if(y[i]==',')
								y[i]='\0';
						bank[course-1].topic[t-1].topicname=y;
					}
				}
				for(int i=0;i<3;i++)
					if(s3[i]==cell){
						k=i;
						n=0,m=0,o=0;
						continue;
					}
				if(k==0){
						if(n==1 || n==6)
							bank[course-1].topic[t-1].mcq.str[m]=cell;
						else if(n!=0)
							bank[course-1].topic[t-1].mcq.option[o++]=cell;
						if(n==4)
							m++;
					n++;		
				}
				else if(k==1){
					if(n!=0)
						bank[course-1].topic[t-1].tf.str[m++]=cell;
					n++;
				}
				else if(k==2){
					if(n==1 || n==2)
						bank[course-1].topic[t-1].question.str[m++]=cell;
					n++;
				}
					
						
			}
		row++;
		}
		inputFile2.close();
		
		ifstream inputFile3("Answers.csv");
		if (!inputFile3.is_open()) {
			cout << "Failed to open file!" << endl;
			exit(0);
	    	}
		line="\0";
	   	row = 0;
		int i=0;
		j=0;
		n=0;
		k=0;
	    	while (getline(inputFile3, line)) {
	      		  if (row >= 209) {
		 		   cout << "Maximum number of rows exceeded!" << endl;
		  		   break;
	       		  }
		stringstream lineStream(line);
		string cell;
		while (getline(lineStream, cell, ',')) 
			{
				if(cell==s1[i]){	
					i++;
					j=0;
				}
				else{
					if(cell==s3[0]){
						n=0;
						j++;
						k=1;
					}
					else if(cell==s3[1]){
						k=2;
						n=0;
					}
					if(n!=0){
						if(k==1)
							ans[i-1][j-1].mcq_ans[n-1]=cell;
						if(k==2)
							ans[i-1][j-1].tf_ans[n-1]=cell;
					}
				}
				n++;
			}
			row++;
		}
		inputFile3.close();
 	}
 	
 	void login(){
		User.null();
 		int n;
 		cout<<"Select who you are...."<<endl;
 		cout<<"----------------------"<<endl;
 		cout<<"Press 1 for student.."<<endl;
 		cout<<"Press 2 for teacher..."<<endl;
 		cout<<"----------------------"<<endl;
 		cin>>n;
 		cout<<"----------------------"<<endl;
 		bool check=false;
 		if(n==1 || n==2)
 			check=true;
 		while(check==false){
 			cout<<"Please enter valid input: ";
 			cin>>n;
 			if(n==1 || n==2)
 				check=true;
 		}
 		if(n==1){
 			if(!student_verify())
 				cout<<"failed to login"<<endl;
 		}
 		else{
 			if(!teacher_verify())
				cout<<"failed to login"<<endl;
 		}
 	}
 	bool student_verify(){
 		string s1,s2;
 		cin.ignore();
 		cout<<"Please enter your email (Example:i191961@nu.edu.pk): ";
 		getline(cin,s1);
 		cout<<"Please enter your password (Example: Firstname123$): ";
 		getline(cin,s2);
 		bool check;
 		for(int i=0;i<216;i++){
 			check=true;
 			if(s1!=student[i].get_email())
 				check=false;
 			if(s2!=student[i].get_pass())
 				check=false;
 			if(check==true){
 				User.user_student=&student[i];
 				break;
 			}
 		}
 		if(check==true){

 			bool ch=false;
			while(ch==false){
				int x;
				cout<<"----------------------------------------------"<<endl;
				cout<<"Student MainMenu"<<endl;
				cout<<"----------------------------------------------"<<endl;
				cout<<"1) Check your student Profile? "<<endl;
				cout<<"2) Do you want to register for a new course? "<<endl;
				cout<<"3) Do you want to drop a course? "<<endl;
				cout<<"4) Do you want to Submit an Assignment? "<<endl;
				cout<<"5) Do you want to take a Quiz? "<<endl;
				cout<<"6) Do you want to see Assignment score? "<<endl;
				cout<<"7) Do you want to see Quiz score? "<<endl;

				
				cout<<"8) Do you want to see attendance? "<<endl;
				cout<<"9) Do you want to logout? "<<endl;
				cout<<"10) Do you want to exit the program? "<<endl;
				cout<<"----------------------------------------------"<<endl;
				cin>>x;
				cout<<"----------------------------------------------"<<endl;
				switch(x){
					case 1: User.user_student->display();break;
					case 2: if(User.user_student->get_nofcourse()==7){
							cout<<"Max courses already registered"<<endl;
							break;
						}
						else{
							cout<<"List of available courses...."<<endl;
							int x;
							course.display();
							cin>>x;
							if(User.user_student->Addcourse(course.get_course(x-1),course.get_ID(x-1)))
								cout<<"Registered Succesfully"<<endl;
							else
								cout<<"Course already registered"<<endl;
							break;
						}
					case 3: if(User.user_student->get_nofcourse()==0){
							cout<<"No courses registered"<<endl;
							break;
						}
						else{
							if(User.user_student->Removecourse())
								cout<<"Course dropped successfully"<<endl;break;
						}		
					case 4:  if(quiz==NULL){
 							cout<<"No Assignment has been assigned yet"<<endl;
 						}
 						else{
 						bool ch3=false;
 						for(int i=0;i<User.user_student->get_nofcourse();i++){
 							if(User.user_student->get_registeredcourse().get_course(i)==quiz->course){
 								ch3=true;
 								takeQuiz();
 							}
 						}
 						if(ch3==false)
 								cout<<"A new Assignment has been assigned but you are not registered in the course, please register into the course "<<quiz->course<<" to give the quiz"<<endl;
 						}
 						break;	
 					case 5:  if(quiz==NULL){
 							cout<<"No Assignment has been assigned yet"<<endl;
 						}
 						else{
 						bool ch3=false;
 						for(int i=0;i<User.user_student->get_nofcourse();i++){
 							if(User.user_student->get_registeredcourse().get_course(i)==quiz->course){
 								ch3=true;
 								takeQuiz();
 							}
 						}
 						if(ch3==false)
 								cout<<"A new Assignment has been assigned but you are not registered in the course, please register into the course "<<quiz->course<<" to give the quiz"<<endl;
 						}
 						break;		
					case 6: QuizStats();break;
					case 7: QuizStats();break;

					
					case 8: User.user_student->student_attendance();break;
					case 9:	login();
						ch=true;break;
					case 10: ch=true;break;
					default: cout<<"Please enter a valid choice"<<endl;break;
				}
			}
 			return 1;
 		}
 		else{
 			return 0;
 		}
 	}
 	bool teacher_verify(){
 		string s1,s2;
 		cin.ignore();
 		cout<<"Please enter your email (Example:Firstname@nu.edu.pk): ";
 		getline(cin,s1);
 		cout<<"Please enter your password (Example: Firstname123$): ";
 		getline(cin,s2);
 		bool check;
 		for(int i=0;i<11;i++){
 			check=true;
 			if(s1!=teacher[i].get_email())
 				check=false;
 			if(s2!=teacher[i].get_pass())
 				check=false;
 			if(check==true){
 				User.user_teacher=&teacher[i];
 				break;
 			}
 		}
 		if(check==true){
 			bool ch=false;
			while(ch==false){
				int x;
				cout<<"----------------------------------------------"<<endl;
				cout<<"Teacher MainMenu"<<endl;
				cout<<"----------------------------------------------"<<endl;
				cout<<"1) See your profile? "<<endl;
				cout<<"2) Generate an Assignment? "<<endl;
				cout<<"3) Generate a Quiz? "<<endl;
				cout<<"4) See Assignment analytics? "<<endl;
				cout<<"5) See Quiz analytics? "<<endl;
				
				cout<<"6) See attendance sheet? "<<endl;
				cout<<"7) Do you want to logout?"<<endl;
				cout<<"8) Do you want to exit the system?"<<endl;
				cout<<"----------------------------------------------"<<endl;
				cin>>x;
				cout<<"----------------------------------------------"<<endl;
				switch(x){
					case 1: User.user_teacher->display();break;
					case 2: QuizGenerate();break;
					case 3: QuizGenerate();break;
					
					case 4: QuizAnalytics();break;
					case 5: QuizAnalytics();break;
					
					case 6: attendancesheet();break;
					case 7: login();
						ch=true;break;
					case 8: ch=true;break;
					default: cout<<"Please enter a valid choice"<<endl;break;
					
				}
			}
 			return 1;
 		}
 		else{
 			return 0;
 		}

 	}
 	bool QuizGenerate(){
 		int n;
		for(int i=0;i<11;i++)
			if(User.user_teacher->get_course()==teacher[i].get_course())
				n=i;
		int x;
		cout<<"COURSE:: "<<teacher[n].get_course()<<endl;
		cout<<"Select topic: "<<endl;
		for(int j=0;j<3;j++)
			cout<<j+1<<") "<<bank[n].topic[j].topicname<<endl;
		cin>>x;
		bool check=false;
		while(check==false){
			if(x==1 || x==2 || x==3){
				check=true;
				AssignQuiz(n,x-1);
			}
		}
		cout<<"The Assigments detail is as follow: "<<endl;
		cout<<"----------------------------------"<<endl;
		cout<<"Topic Name: "<<bank[n].topic[x-1].topicname<<endl;
		cout<<"----------------------------------"<<endl;
		cout<<"-------------------------------"<<endl;
		cout<<" PART A ) "<<endl;
		cout<<"-------------------------------"<<endl;
		for(int i=0;i<2;i++){
			cout<<i+1<<") "<<quiz->mcq.str[i]<<endl;
			for(int j=0;j<4;j++)
				cout<<quiz->mcq.option[j]<<endl;
		}
		cout<<"-------------------------------"<<endl;
		cout<<" PART B ) "<<endl;
		cout<<"-------------------------------"<<endl;
		for(int k=0;k<2;k++)
			cout<<k+1<<") "<<quiz->tf.str[k]<<endl;
		cout<<"-------------------------------"<<endl;
		cout<<" PART C) Descriptive Questions "<<endl;
		cout<<"-------------------------------"<<endl;
		for(int k=0;k<2;k++)
			cout<<k+1<<") "<<quiz->question.str[k]<<endl;
		char s;
		cout<<"------------------------------"<<endl;
		cout<<"Please confirm the details (Y): ";
		cin>>s;
		if(s=='y' || s=='Y')
			cout<<"Assignment has been assigned"<<endl;
		else
			QuizGenerate();
		return 1;
 	}
 	void AssignQuiz(int course,int topic){
 		cin.ignore();
 		quiz=new Quiz;
 		quiz->course=teacher[course].get_course();
 		quiz->mcq=bank[course].topic[topic].mcq;
 		quiz->tf=bank[course].topic[topic].tf;
 		quiz->question=bank[course].topic[topic].question;
 		int j=0;
 		for(int i=0;i<4;i++){
 			if(i<2)
 				quiz_ans[i]=ans[course][topic].mcq_ans[i];
 			else
 				quiz_ans[i]=ans[course][topic].tf_ans[j++];
 		}
 		cout<<"Please enter time limit in mins to attempt the quiz: ";
 		cin>>quiz->time;
 	}
 	void takeQuiz(){
	 		cout<<"You have "<<quiz->time<<" mins to attempt the Assignment"<<endl;
			string ans[6];
			cout<<"-------------------------------"<<endl;
			cout<<" PART A ) MCQs "<<endl;
			cout<<"-------------------------------"<<endl;
			cin.ignore();
			for(int i=0,j=0;i<8;i++){
				if(i==0 || i==4)
					cout<<quiz->mcq.str[j++]<<"(1)"<<endl;
				cout<<quiz->mcq.option[i]<<endl;
	 		}
	 		cout<<"Please enter correct option (a,b,c,d): ";
	 		getline(cin,ans[0]);
	 		cout<<"Please enter correct option (a,b,c,d): ";
	 		getline(cin,ans[1]);
			cout<<"-------------------------------"<<endl;
			cout<<" PART B ) True/False "<<endl;
			cout<<"-------------------------------"<<endl;
	 		for(int i=0;i<2;i++){
	 			cout<<quiz->tf.str[i]<<"(1)"<<endl;
	 			cout<<"Please enter T/F: ";
	 			getline(cin,ans[i+2]);
	 		}
			cout<<"-------------------------------"<<endl;
			cout<<" PART C) Descriptive Questions "<<endl;
			cout<<"-------------------------------"<<endl;
	 		for(int i=0;i<2;i++){
	 			cout<<quiz->question.str[i]<<endl;
	 			getline(cin,ans[i+4]);
	 		}
	 		cout<<"You have successfully given the Assignment!!"<<endl;
			for(int i=0;i<4;i++)
				if(quiz_ans[i]==ans[i])
					User.user_student->set_quizscore(1);
			int len=0;
			while(ans[4][len]!='\0')
				len++;
			if(len>100)
				User.user_student->set_quizscore(3);
			else if(len>50)
				User.user_student->set_quizscore(2);
			else if(len>10)
				User.user_student->set_quizscore(1);
			len=0;
			while(ans[5][len]!='\0')
				len++;
			if(len>100)
				User.user_student->set_quizscore(3);
			else if(len>50)
				User.user_student->set_quizscore(2);
			else if(len>10)
				User.user_student->set_quizscore(1);
			User.user_student->set_quizname(quiz->course);
			for(int i=0;i<User.user_student->get_nofcourse();i++)
				if(quiz->course==User.user_student->get_registeredcourse().get_course(i))
					User.user_student->get_registeredcourse().set_attendance(i);
 	}
 	void QuizStats(){
 		if(User.user_student->get_quizname()=="\0")
 			cout<<"You have not submit an assignment yet"<<endl;
 		else{
 			cout<<"----------RESULT--------------"<<endl;
 			cout<<"Course Name: "<<User.user_student->get_quizname()<<endl;
 			cout<<"Score: "<<User.user_student->get_quizscore()<<"/10"<<endl;
 		}
 	}
 	bool attendancesheet(){
 		ofstream outputFile;
 		outputFile.open("Attendance.txt");
 		
 		if(!outputFile.is_open()){
 			cout<<"File could not be opened"<<endl;
 			return 1;
 		}
 		string input;
 		input="Attendance sheet of course : "+User.user_teacher->get_course()+"\n";
 		outputFile<<input;
 		for(int i=0;i<216;i++)
 			for(int j=0;j<11;j++)
 				if(student[i].get_registeredcourse().get_course(j)==User.user_teacher->get_course()){
 					input=student[i].get_name()+" : "+student[i].get_registeredcourse().get_attendance(j)+"\n";
 					outputFile<<input;
 				}
 		outputFile.close();
 		cout<<"Data written into file sucessfully"<<endl;
 		return 1;
 		
 					
 	}
 	bool QuizAnalytics(){
 		ofstream outputFile;
 		outputFile.open("AssignmentAnalytics.txt");
 		
 		if(!outputFile.is_open()){
 			cout<<"File could not be opened"<<endl;
 			return 1;
 		}
 		float avg=0;
 		float total=0;
 		for(int i=0;i<216;i++)
 			for(int j=0;j<11;j++)
 				if(student[i].get_registeredcourse().get_course(j)==User.user_teacher->get_course()){
 						avg+=student[i].get_quizscore();
 						if(student[i].get_quizscore()!=0)
 							total++;
 				}
 		string input;
 		input="COURSE:: "+User.user_teacher->get_course()+"\n";
 		outputFile<<input;
 		for(int i=0;i<216;i++)
 			for(int j=0;j<11;j++)
 				if(student[i].get_registeredcourse().get_course(j)==User.user_teacher->get_course()){
					input=student[i].get_name()+" score: "+to_string(student[i].get_quizscore())+"\n";
					outputFile<<input;	
				}
		input="Assignment average is: "+to_string(avg/total)+"/10\n";
		outputFile<<input;
 		outputFile.close();
 		cout<<"Data written into file sucessfully"<<endl;
 		return 1;
 	}	
 			
 	
};
int main(){
	GoogleClassroomSystem exam;
	exam.readdatafromcsvfile();
	exam.login();
	Feedback Fb;
	Fb.leaveFeedback();
}
