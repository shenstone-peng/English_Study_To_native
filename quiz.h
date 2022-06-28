#ifndef SPQUIZ
#define SPQUIZ
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
namespace SP {
    
class quiz {
public:
    typedef std::string FILE_NAME;
    typedef std::vector<FILE_NAME> FILE_NAME_LIST;
    typedef std::string SENTENCE;
    typedef int NUM;
    typedef enum _FILE_OPERATE
    {
        NO_ERR = 0,
        ILEGAL_FORMAT,
        OPEN_DIR_FAIL,
	EMPTY_DATA,
    }FILE_OPERATE;
    public:
    quiz(const string& i_filepath):mStrFilePath(i_filepath){
        std::cout<<"new quiz from path ["<<i_filepath<<"]"<<endl;
        unsigned int seed = time(0);
        srand(seed);
    }
    FILE_OPERATE initFileList();
    
    FILE_OPERATE getRandomFile(FILE_NAME& o_fileName);
    
    SENTENCE getRandomSentence(const FILE_NAME& i_fileName);
    
    int getRandomNumber(vector<int>& i_list);
    bool isFilePath(const std::string& i_filepath);
    

    
private:
    std::string mStrFilePath;
    std::map<FILE_NAME, vector<pair<SENTENCE, NUM>>> mMapDictionary;
    FILE_NAME_LIST mVecFileList;
};


}//end namespace


#endif //SPQUIZ
