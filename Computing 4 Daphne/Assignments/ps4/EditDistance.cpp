#include "EditDistance.hpp"
ED::ED(std::string s1, std::string s2) {
	string1 = s1;
	string2 = s2;
	size_string1 = string1.length();
	size_string2 = string2.length();
	opt = new int*[size_string1 + 1];
	for (int i=0; i<(size_string1 + 1); i++) {
		opt[i]= new int[size_string2 + 1];
	}
}


int ED::penalty(char a, char b) {
	return (a == b ? 0 : 1);
}

int ED::min(int a, int b, int c) {
	return std::min(std::min(a, b),c);
}

int ED::OptDistance() {
	int score = 0;
	for (int i=size_string1; i>=0; i--) { //fill in the column base
		opt[i][size_string2] = score;
		score += 2;
		for (int j = size_string2; j>=0; j--) {//fill in the row base	
			opt[size_string1][j-1] = opt[size_string1][j]+2;
		}
	}
	//fill in all the table
	for (int i = size_string1-1; i>=0; i--) {
		for (int j = size_string2-1; j>=0; j--) {
			opt[i][j] = min(opt[i+1][j+1] + penalty(string1[i],string2[j]), opt[i][j+1]+2, opt[i+1][j]+2);
		}
	}
	return opt[0][0];
}

std::string ED::Alignment() {
	int i = 0, j = 0, k= 0;
	std::string align;
	std::string str="s s 0\n";

	k = (size_string1 > size_string2) ? size_string1 : size_string2;

	for (int n=0; n<k; n++) {
		if (string1[i]==string2[j] && opt[i][j] == opt[i+1][j+1]) {
			str[0]=string1[i];
			str[2]=string2[j];
			str[4]='0';
			align += str;
			i++;
			j++;
		} else if (string1[i]!=string2[j] && opt[i][j] == opt[i+1][j+1]+1) {
			str[0]=string1[i];
			str[2]=string2[j];
			str[4]='1';
			align += str;
			i++;
			j++;
		} else if (opt[i][j] == opt[i+1][j] + 2){
			str[0]=string1[i];
			str[2]='-';
			str[4]='2';
			align += str;
			i++;
		} else if (opt[i][j] == opt[i][j+1] + 2) {
			str[0]='-';
			str[2]=string2[j];
			str[4]='2';
			align += str;
			j++;
		}
	}
	while ((i < size_string1) && (j < size_string2)) {
		str[0] = string1[i];
		str[2] = string2[j];
		str[4] = '0';
		align += str;
		i++;
		j++;
	}
	while (i < size_string1) {
		str[0]=string1[i];
		str[2]='-';
		str[4]='2';
		align += str;
		i++;
	}
	while (j < size_string2) {
		str[0] = '-';
		str[2] = string2[j];
		str[4] = '2';
		align += str;
		j++;
	}
	return align;
}

