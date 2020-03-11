
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<map>
#include<cctype>
//using namespace std;

//создаем структуру слово+число раз, которое оно встретилось в тексте
struct Stats {
	std::string word;
	int count;
};

//создаем функцию логического типа (true/false) для сравнения элемнтов типа Stats (про них написано выше)
//сравнение происходит по второму параметру - числу раз, которое встретилось слово
bool cmp(Stats x, Stats y) {
	return(x.count > y.count);
}

//функция, которая принимает слово и "готовит" его
std::string prepare(std::string& word) {
	std::transform(word.begin(), word.end(), word.begin(), ::tolower); //приводим слова к нижнему регистру
	
	//если на конце слова есть символ пунктуации, он обрезается 
	if (ispunct(word.back())) { 
		word.pop_back();
	}
	return word;
}

int main() {
	int N;
	std::cin >> N;

	//создаем словарь words
	std::map<std::string, int> words;
	
	//открываем файл file.txt как file
	std::ifstream file("file.txt");

	if (file.is_open()) {
		std::string word; //создаем строку word
		while (!file.eof()) {
			file >> word; //пробегаем по файлу по "словам" - элементам, разделенных пробелами
			word = prepare(word); //готовим слова для обработки в словарь и записи
			if (words.find(word) == words.end()) { //если в словаре еще нет этого слова кладем его значение равное 1
				words[word] = 1;
			}
			else {
				words[word]++; //если в словаре слово уже есть, увеличиваем его кол-во в словаре на 1
			}
		}

		std::vector<Stats> s(words.size()); //создаем вектор (массив) s типа Stats раземром по кол-ву слов массива
		int i = 0;
		for (const auto& [word, count] : words) //пробегаем по всем словам из словаря и записываем всю инфу в массив
		{
			s[i].count = count;
			s[i].word = word;
			i++;
		}
		sort(s.begin(), s.end(), cmp); //сортируем массив от начала до конца с помощью написанной функции сравнения

		//выводим N самых частовстречаемых слов
		for (int i = 0; i < N; ++i)
		{
			std::cout << s[i].word << " " << s[i].count << "\n";
		}
			
	}
	else {
		std::cout << "file ne otkrilsya";
	}
}
