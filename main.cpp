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
	tmp->readJsonFile();
	int i = 0;
	while(i++ < 19){
		SP::quiz::FILE_NAME choosedFile="";
		(void)tmp->getRandomFile(choosedFile);
		cout<<"**************No."<<i<<"******************"<<endl;
		string sentence = tmp->getRandomSentence(filePath+choosedFile);
		cout<<"*   "<<sentence<<"    *"<<endl;
		cout<<endl;
		cout<<"[Y/N]                                     "<<endl;
		char c;
		cin.get(c);
		if('y' == c || 'Y' ==c){
        	        cout<<"Congrates!!"<<endl;
			tmp->updateMap(filePath+choosedFile, sentence, -1);
	        }
        	else{
               		cout<<"Sorry~"<<endl;
			tmp->updateMap(filePath+choosedFile, sentence, 1);
	        }
        	cout<<"******Press enter to next WORD...*********"<<endl;
	        std::cin.ignore(1);
        	cin.get();
	}
	(void)tmp->generateNewJsonFile();
	delete tmp;
	return 0;
}
