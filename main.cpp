#include "quiz.h"


int main(int argc, char *argv[]){
	std::string filePath;
   	if (argc != 2)
    	{
            std::cout<<"Please Enter Input File Path And Name:"<<std::endl;
            std::cin>>filePath;
    	}
    	else {
        	filePath = argv[1];
    	}
	SP::quiz* tmp = new SP::quiz(filePath);
	(void)tmp->initFileList();
	int i = 0;
	while(i++ < 20){
		SP::quiz::FILE_NAME choosedFile="";
		(void)tmp->getRandomFile(choosedFile);
		cout<<tmp->getRandomSentence(filePath+choosedFile)<<endl;
		cout<<endl;
		cout<<"************Y/N***************************"<<endl;
		char c;
		cin.get(c);
		if('y' == c || 'Y' ==c){
        	        cout<<"Congrates!!"<<endl;
	        }
        	else{
               		cout<<"Sorry~"<<endl;
	        }
        	std::cout<<"Press enter to next WORD..."<<endl;
	        std::cin.ignore(1);
        	cin.get();
	}
	delete tmp;
	return 0;
}
