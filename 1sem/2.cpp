#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<map>
#include<cctype>

struct Stats{
	int count;
	std::string word;
};

std::string prepare(std::string word){
	std::string result;
	std::transform(word.begin(), word.end(), result.begin(), ::tolower);
	if(ispunct(result.back())){
		result.pop_back();
	}
	return result;
}

int main(){
	std::map<std::string, int> words;
	std::ifstream file("file.txt");
	if (file.is_open()){
		std::string word;
		while(!file.eof()){
			file >> word;
			word = prepare(word);
			if(words.find(word) == words.end()){
				words[word] = 1;
			}
			else{
				words[word]++;
			}
		}
		std::vector<Stats> s;
		s.resize(0);
		for(const auto&[word, count] : words){
			s.emplace_back(count, word);
		}
	}
}
