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
 	mVecNeedUpdateFile.push_back(o_fileName);	
	//cout<<"Choose "<<choosedFile<<" as a rand num in "<<fileNums<<",file is "<<o_fileName<<endl;
	return NO_ERR;
}
SP::quiz::FILE_OPERATE SP::quiz::updateMap(const string& filename, const string& sentence, int var) {
	if(mMapDictionary.find(filename) == mMapDictionary.end()) {
		cout<<"error not find"<<endl;
		return NO_ERR;
	}
	for(auto it = mMapDictionary[filename].begin(); it != mMapDictionary[filename].end(); ++it) {
		if(it->first == sentence){
			cout<<"before:"<<it->second<<endl;
			it->second += var;
			if(it->second <0){
				it->second = 0;
			}
			cout<<"after:"<<it->second<<endl;
		}
	}
	return NO_ERR;
}
SP::quiz::FILE_OPERATE SP::quiz::generateNewJsonFile(){
	Json::Reader reader;
	Json::Value root;
	string jsonfilename="tmp.json";
	for(auto it =mMapDictionary.begin(); it != mMapDictionary.end(); ++it) {
		string file_name = it->first;
		vector<pair<string, int>> data = it->second;
		Json::Value single_file;
		single_file["filename"] = file_name;
		Json::Value sentence_array;
		//cout<<"test:"<<file_name<<endl;
		for(auto single_data : data){
			Json::Value item;
			item["Num"] = single_data.second;
			item["Sentence"]=single_data.first;
			//item["Num"] = 10;
			sentence_array.append(item);
		}
		Json::Value tmp;
		tmp["sentence"]=sentence_array;
		Json::Value tmp2;
		tmp2.append(single_file);
		tmp2.append(tmp);
		root.append(tmp2);

	}
	
	Json::FastWriter writer;
	string strWrite = writer.write(root);
	ofstream ofs;
	ofs.open(jsonfilename);
	ofs << strWrite;
	ofs.close();
	return NO_ERR;
}
SP::quiz::FILE_OPERATE SP::quiz::readJsonFile() {
	Json::Reader reader;
	Json::Value root;
	ifstream is;
	is.open("tmp.json");
	if(reader.parse(is, root, false)) {
		unsigned int len = root.size();
//		cout<<"here:"<<len<<endl;
		for(auto i = 0; i < len; i++) {
				string filename = root[i][0]["filename"].asString();
				cout<<"Alanasy file "<<filename<<" success!"<<endl;
				Json::Value sen = root[i][1]["sentence"];
				unsigned int len_sen = sen.size();
				vector<pair<string,int>> tmpData;
				for(auto j =0;j<len_sen;++j) {
//					cout<<"len_sen:"<<len_sen<<endl;
					string tmp_sen = sen[j]["Sentence"].asString();
					int weighed = sen[j]["Num"].asInt();
					tmpData.push_back(make_pair(tmp_sen, weighed));
				}
				mMapDictionary[filename]=tmpData;
		}	
	}
	else{
		cout<<"something wrong"<<endl;}

			return NO_ERR;
			
	}
SP::quiz::SENTENCE SP::quiz::getRandomSentence(const FILE_NAME& i_fileName) {
	if ( mMapDictionary.find(i_fileName) != mMapDictionary.end() ) {
		vector<int> tmp;
		getWeighedVec(mMapDictionary[i_fileName], tmp);
		int wordSums = mMapDictionary[i_fileName].size();
		int idx = getRandomNumber(tmp);
		return mMapDictionary[i_fileName][idx].first;
	}
	else {
		std::vector<pair<string, int>> newFileWord;
		ifstream fileStream(i_fileName.c_str());
		if (!fileStream) {
			cout<<"Open File "<<i_fileName<<" fail, Pleae recheck the file path!"<<endl;
			return "";
		}
	//	cout<<"Open File "<<i_fileName<<" successfully!"<<endl;
		SENTENCE line = "";
		while ( !fileStream.eof() ) {
			getline(fileStream, line);
			if(line.empty())
				continue;
			newFileWord.push_back(make_pair(line,10));
		}
		mMapDictionary[i_fileName] = newFileWord;
	}
	Json::Reader reader;
	return getRandomSentence(i_fileName);
}
void SP::quiz::getWeighedVec(vector<pair<string, int>>& i_list, vector<int>& o_list) {
	o_list.clear();
	int idx = 0;
	for(auto data : i_list) {
		for(auto i = 0; i < data.second; ++i) {
			o_list.push_back(idx);
		}
		idx++;
	}
}
int SP::quiz::getRandomNumber(vector<int>& i_list) {
	if(0 == i_list.size()) {
		return -1;
	}
	int sum = i_list.size();
	int randonNum = rand() % sum;
	return i_list[randonNum];
}
