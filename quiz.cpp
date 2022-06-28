#include "quiz.h"

SP::quiz::FILE_OPERATE SP::quiz::initFileList() {
    DIR* dp;
    struct dirent* dirp;
    if ( nullptr == (dp = opendir(mStrFilePath.c_str())) ) {
        std::cout<<"Open File "<<mStrFilePath<<" fail, Pleae recheck the file path!"<<std::endl;
        return OPEN_DIR_FAIL;
    }
    while((dirp = readdir(dp)) != NULL) {
        if( dirp->d_name[0] == '.' ) {
            continue;
        }
        if( dirp->d_type == DT_REG ) {
        FILE_NAME newFile(dirp->d_name);
            //std::cout << "get new file:" << newFile << std::endl;
            mVecFileList.push_back(newFile);
        }
    }
    return NO_ERR;	
}


SP::quiz::FILE_OPERATE SP::quiz::getRandomFile(FILE_NAME& o_fileName){
	if ( 0 == mVecFileList.size() ) {
		return EMPTY_DATA;
	}
	int fileNums = mVecFileList.size();
	int choosedFile = rand() % fileNums;
	o_fileName = mVecFileList[choosedFile];
	cout<<"Choose "<<choosedFile<<" as a rand num in "<<fileNums<<",file is "<<o_fileName<<endl;
	return NO_ERR;
}


SP::quiz::SENTENCE SP::quiz::getRandomSentence(const FILE_NAME& i_fileName) {
	if ( mMapDictionary.find(i_fileName) != mMapDictionary.end() ) {
		int wordSums = mMapDictionary[i_fileName].size();
		int idx = rand() % wordSums;
		return mMapDictionary[i_fileName][idx].first;
	}
	else {
		std::vector<pair<string, int>> newFileWord;
		ifstream fileStream(i_fileName.c_str());
		if (!fileStream) {
			cout<<"Open File "<<i_fileName<<" fail, Pleae recheck the file path!"<<endl;
			return "";
		}
		cout<<"Open File "<<i_fileName<<" successfully!"<<endl;
		SENTENCE line = "";
		while ( !fileStream.eof() ) {
			getline(fileStream, line);
			if(line.empty())
				continue;
			newFileWord.push_back(make_pair(line,1));
		}
		mMapDictionary[i_fileName] = newFileWord;
	}
	return getRandomSentence(i_fileName);
}

int SP::quiz::getRandomNumber(vector<int>& i_list) {
	if(0 == i_list.size()) {
		return -1;
	}
	int sum = i_list.size();
	int randonNum = rand() % sum;
	return i_list[randonNum];
}
