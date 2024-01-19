#include<iostream>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

using namespace std;

void readFilee(vector<int>& num){
	cout << "请输入文件名：" << endl;
	string fileName ;
	cin >> fileName;

 	char buffer[256] = {'\0'};   //初始化为‘\0'方便判断结束
    ifstream in(fileName);
    if (!in.is_open())
    {
        cout << "未找到相关文件!"; exit(1);
    }
    while (!in.eof())
    {
        in.read(buffer, 100);
    }

	int count = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
    {        
        count++;
        if (buffer[i] == ' ' || buffer[i] == '\n')
        {
            int number=0;
            count--;
            for (int j = 1; j <= count; j++)
            {
                number += (buffer[i - j]-'0') * (pow(10,j-1));                           
            }
            num.push_back(number);
            // cout << number << endl;
 
            count = 0;
        }
    }

	cout << endl << "文件内容为：" << endl;
	for (int i : num){
		cout<<i<<" ";
	}
	cout<<endl;

}
// string md5(string mes);
// int main(){
//     string s ="iloveyou";
//     // cout << md5(s);
//     md5(s);

//     int len = s.length();
//     int padLength = 16 - len % 16; //需要填充多少个字符  
//     for(int i = len; i < padLength + len; i ++){
//     	s.push_back(padLength);
// 	}
//     md5(s);
    

// }