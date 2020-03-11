#include<algorithm>
#include<iostream>
#include<vector>
#include<string>

bool cmp(std::string x, std::string y){
	if (x.size() < y.size()){
		return(true);
	}
	else if(x.size() == y.size() && x <= y){
		return(true);
	}
	else{
		return(false);
	}
}

int main(){
	int n;
	std::cin>>n;
	std::vector<std::string>array;
	array.resize(n);
	for(int i = 0; i < n; i++){
		std::string elem;
		std::cin>>elem;
		array[i] = elem;
	}
	std::sort(array.begin(), array.end(), cmp);
	for(int i = 0; i < n; i++){
		std::cout<<array[i]<< " ";
	}
	
}
