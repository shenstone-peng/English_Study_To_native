#include <map>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
typedef std::string FILE_NAME;
typedef std::vector<FILE_NAME> FILE_NAME_LIST;
std::map<FILE_NAME, vector<string> > dictionary;
 
typedef enum _FILE_OPERATE
{
    NO_ERR = 0,
    ILEGAL_FORMAT,
    OPEN_DIR_FAIL,
}FILE_OPERATE;


bool isFilePath(const std::string& i_filePath){
        return true;
}

FILE_NAME getRandomFile(FILE_NAME_LIST& i_fileList) {
    if ( 0 == i_fileList.size() )
        return "";
    int fileNums = i_fileList.size();
    int choosedFile = rand() % fileNums;
    return i_fileList[choosedFile];
}

std::string getRandomSentence(FILE_NAME& chooseFile) {
    if ( dictionary.find(chooseFile) != dictionary.end() ) {
        int wordSums = dictionary[chooseFile].size();
        int idx = rand() % wordSums;
        return dictionary[chooseFile][idx];
    }
    else {
	 std::vector<string> newFileWord;
        ifstream fileStream(chooseFile.c_str());
        if (!fileStream)
        {
            cout<<"Open File "<<chooseFile<<" fail, Pleae recheck the file path!"<<endl;
            return "";
        }
	cout<<"Open File "<<chooseFile<<endl;
        string line = "";
        while ( !fileStream.eof() ) {
            getline(fileStream, line);
	    if(line.empty())continue;
            newFileWord.push_back(line);
        }
        dictionary[chooseFile] = newFileWord;
    }
    return getRandomSentence(chooseFile);
}

int getFileList(const std::string& i_filePath, FILE_NAME_LIST& o_fileList){
    if ( !isFilePath(i_filePath) ) {
        return ILEGAL_FORMAT;
    }
    DIR* dp;
    struct dirent* dirp;
    if ( nullptr == (dp = opendir(i_filePath.c_str())) ) {
        std::cout<<"Open File "<<i_filePath<<" fail, Pleae recheck the file path!"<<std::endl;
        return OPEN_DIR_FAIL;
    }
    while((dirp = readdir(dp)) != NULL) {
        if( dirp->d_name[0] == '.' ) {
            continue;
        }
        if( dirp->d_type == DT_REG ) {
        FILE_NAME newFile(dirp->d_name);
            //std::cout << "get new file:" << newFile << std::endl;
            o_fileList.push_back(newFile);
        }
    }
    return NO_ERR;
}
int main(int argc, char *argv[]) {
    unsigned int seed = time(0);
    srand(seed);

    std::string filePath;
    if (argc != 2)
    {
            std::cout<<"Please Enter Input File Path And Name:"<<std::endl;
            std::cin>>filePath;
    }
    else
    {
        filePath = argv[1];
    }
    FILE_NAME_LIST englishPath;
    int err = getFileList(filePath, englishPath);
    if ( err != NO_ERR) {
        std::cout<<"something wrong, err:"<<err<<std::endl;
    }
    int i = 0;
    while(i < 20) {
        FILE_NAME quizFile = getRandomFile(englishPath);
        quizFile = filePath + quizFile;
	std::cout<<"This time we will test "<<quizFile<<std::endl;
	cout<<endl;
	cout<<endl;
	std::string quizWord = getRandomSentence(quizFile);
	std::cout<<"     "<<quizWord<<std::endl;
	cout<<endl;
	cout<<endl;
	std::cout << "Press the enter key to continue ...";
	std::cin.get();
	++i;
    }
    return err;
}
