#include<iostream>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

// #include "rsatool.h"

using namespace std;


//判断素数
 int IsPrime(int n)
{
	 int temp = (int)sqrt(n);
	for (int i = 2; i <= temp; i++)
	{
		if (n % i == 0) return 0;//n不是素数的话返回0
	}
	return 1;//n是素数的话返回1
}

//选取两个素数
void InputPrime(int &p, int &q)
{
	int P, Q;
	cout << "请输入两个不相等的大素数: p,q" << endl;
	cin >> P >> Q;
		do
		{  
			while (IsPrime(Q) != 1)
			{
				cout << Q << "不满足是素数，请重新输入大素数: q" << endl;
				cin >> Q;
			}

			while (IsPrime(P) != 1)
			{
				cout << P << "不满足是素数，请重新输入大素数: p" << endl;
				cin >> P;
			}

			while(P==Q)
			{
				cout << "p,q不能相等，请重新输入两个大素数: p, q" << endl;
				cin >> P >> Q;	
			}


		} while (IsPrime(P) !=1||IsPrime(Q)!=1||Q==P);	
	
	p = P;
	q = Q;
	
}

//计算n和n的欧拉函数值
void N(int p , int q, int &n,int &Euler_n)
{
	n = p * q;
	Euler_n = (p - 1) * (q - 1);
}

//求两个数的最大公约数
int GreatestCommonDivisor(int a, int b) 
{
	int t;
	if (a < b) 
	{
		// 交换两个数，使大数放在a的位置上。
		t = a;
		a = b;
		b = t;
	}
	while (b != 0)
	{
		// 利用辗转相除法，直到b为0为止。
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}

//选取e
void E(int Euler_n,int &e)
{
	e = rand() % (Euler_n - 1) + 1; //e取值是1<e<Euler_n  即 [2,Euler_n]范围内的随机数
	do  // gcd(e,Euler_n)=1  ，e与Euler_n互素，最大公约数=1
	{
	e = rand() % (Euler_n - 1) + 1; //e取值是1<e<Euler_n  即 [2,Euler_n]范围内的随机数
	} while (GreatestCommonDivisor(Euler_n , e)!=1);//当e与Euler_n最大公约数!=1时，循环不断地刷新e的值
}

//求逆元d
void D(int e,int Euler_n ,int &d)
{
	int Sign_of_Inverse_Element=0;//判断是否求出逆元的标志：Sign_of_Inverse_Element。当Sign_of_Inverse_Element=1，则求出了逆元
	do
	{
		for (int i = 1; i <Euler_n; i++)
		{
			if ((i * e) % Euler_n == 1)
			{
				Sign_of_Inverse_Element = 1; //Sign_of_Inverse_Element=1时表面求出了逆元d
				d = i;
			}
		}
	} while (Sign_of_Inverse_Element !=1);

}

//对于明文m的加密   (这里认为m是由输入字符转成的二进制的十进制值)
void Encrypt_key(string m, int e,int n, vector<int>& C)
{
	for(char t : m){
		int product = 1;//product表示m自身不断相乘的积  
	   	for (int i = 1; i <= e; ++i)//用e来控制m的指数
			{ product = (product * (t-'a'+1)) % n; }//注意不要忘记%n  
		C.push_back(product);
	}
}

//对密文c的解密
void Decrypt_key(vector<int> C, int d, int n, string& show)
{
	for(int t : C){
		int product = 1;//product表示c自身不断相乘的积
		for (int i = 1; i <= d; ++i)//用d来控制c的指数
			{product = (product * t) %n;}//注意不要忘记%n
		show.push_back(product+'a'-1);
	}
}


//Bob制作公钥和私钥
void Make_PublicKey_And_PrivateKey(int &p , int &q, int& n,  int& e,int& d)
{
	int p1, q1, n1, Euler_n1, e1, d1;
	//Bob制作公钥的过程
	InputPrime(p1, q1);//选取两个素数
	p = p1;
	q = q1;

	N(p1, q1, n1, Euler_n1); //计算n和  n的欧拉函数值Euler_n
	n = n1;

	E(Euler_n1, e1);//选取e
	e = e1;
    cout << "公钥:{ e=" << e1 << ", n=" << n1 << "} " << endl;
	
	//Bob制作公钥的过程
	D(e1, Euler_n1, d1);//求逆元d
	d = d1;
	cout << "私钥:{ d=" << d1 << ", n=" << n1 << "} " << endl<<endl;
	
}



//Bob解开密文
void Bob_Decode_Ciphertext_From_Alice( int n,  int d,vector<int>& C)
{	
	string show;
	
	cout << "解密后的明文为： ";
	Decrypt_key(C, d, n, show);
	// cout<<d<<n<<endl;
	cout<<endl;
	for(char t : show){
		cout << t << "";
	}
	cout<<endl;
}

void readFile_rsa(string& mes)//读取文件
{
	cout << "请输入文件名：" << endl;
	string fileName ;
	cin >> fileName;
	FILE* fp = fopen(fileName.c_str(), "r+");
	if (fp == nullptr) {
		cout << "未找到相关文件" << endl;
		return;
	}
	else {
		cout << "成功打开文件" << endl;
	}
	char ch;
	int pos = 0;
	while ((ch = fgetc(fp)) != EOF) {
		mes+=ch;
	}
	cout << endl << "文件内容为：" << endl;
	cout << mes << endl;
	fclose(fp);
}
 

 
void saveFile_rsa(string s)//保存文件
{
	string fileName;
	cout << endl << "请输入保存信息的文件名：" << endl;
	cin >> fileName;
	FILE* fp = fopen(fileName.c_str(), "w+");
	if (fp == nullptr) {
		cout << endl << "保存文件失败" << endl;
		return;
	}
	else {
		cout << endl << "保存成功!" << endl;
	}
	fprintf(fp, "%s", s.c_str());
	fclose(fp);
	
}

void readFile_int(vector<int>& num){
	cout << "请输入文件名：" << endl;
	string fileName ;
	cin >> fileName;

 	ifstream fin(fileName);
	int idata;
    while (fin >> idata)
    {  
        num.push_back(idata);
    }   

	cout << endl << "文件内容为：" << endl;
	for (int i : num){
		cout<<i<<" ";
	}
	cout<<endl;

}

void saveFile_int(vector<int> v){
	string fileName;
	cout << "信息已加密(RSA)!" << endl;
	cout << "请将密文写进文件，比如'key.txt'/'promise.txt':" << endl;
	cin >> fileName;
	ofstream f(fileName);
    for (int item : v) {
        f<<item<<" ";
    }
	cout << "已经将密文写进" <<  fileName << "中了,可以在当前目录中找到它" << endl;
}


// void keyDown()//按键处理
// {
// 	int p, q ;
// 	int d;
// 	int n, e;  //公钥
// 	vector<int> C; //密文串
// 	string mes;  //明文

// 	cout<<"请选择模式：1、加密明文，2、解密密文，0、退出程序。\n填写数字序号：";
// 	int userkey = 0;
// 	cin >> userkey;
// 	switch (userkey) {
// 		case 1:
// 			Make_PublicKey_And_PrivateKey(p, q, n, e, d); //输入密钥
// 			readFile(mes);  
// 			Encrypt_key(mes, e, n, C);//加密

// 			cout << "发送的密文：";
// 			for(int t : C){
// 				cout << t << "  ";
// 			}
// 			saveFile_int(C);
// 			//INIT
// 			mes = "";
// 			C={0};
// 			break;
// 		case 2:
// 			readFile_int(C);
// 			Bob_Decode_Ciphertext_From_Alice(n,d,C);
// 			break;
// 		case 0:
// 			exit(0);
// 			break;
// 	}
	
// }

// int main()
// {
// 	while(1){
// 		keyDown();
// 	}
// 	return 0;

// }


