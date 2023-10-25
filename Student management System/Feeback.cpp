#include<iostream>
using namespace std;
#include<string>

class Feedback
{
	private:
		string feedback;
	public:
		
		void leaveFeedback()
		{
			char choice;
			cout<<"Do you want to leave Feedback "<<endl;
			cin>>choice;
			if(choice=='y' || choice=='Y')
			{
				cout<<"Enter your feedback "<<endl;
				cin>>feedback;
				cout<<"Thank you for your feedback "<<endl;
				
			}
			else
			exit(1);
			
		}
		void showFeedback()
		{
			cout<<" Feedback : "<<feedback<<endl;
		}
};
