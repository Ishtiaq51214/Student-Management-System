class MCQ{
	public:
	string str[2];
	string option[8];
	
	MCQ(){
		for(int i=0;i<2;i++)
			str[i]="\0";
		for(int i=0;i<8;i++)
			option[i]="\0";
	}
};
class TF{
	public:
	string str[2];
	
	TF(){
		for(int i=0;i<2;i++)
			str[i]="\0";
	}
};
class Cquestion{
	public:
	string str[2];
	Cquestion(){
		for(int i=0;i<2;i++)
			str[i]="\0";
	}
};
class Topic{
	public:
	string topicname;
	MCQ mcq;
	TF tf;
	Cquestion question;
	Topic(){
		topicname="0";
	}
	
};
class Quiz{
	public:
	string course;
	MCQ mcq;
	TF tf;
	Cquestion question;
	int time;
	Quiz(){
		course="\0";
	}
};
class Bank{
	string coursename;
	public:
	Topic topic[3];
	Bank(){
		coursename="\0";
	}
	void set_coursename(string str){
		coursename=str;
	}
	string get_coursename(){
		return coursename;
	}
};
class Answers{
	public:
	string mcq_ans[2];
	string tf_ans[2];
	Answers(){
		for(int i=0;i<2;i++)
			mcq_ans[i]="\0";
		for(int i=0;i<2;i++)
			tf_ans[i]="\0";
	}
};
