// 对称加密：DES
// 公钥加密：RSA （数字签名）
// 哈希： MD5

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include<math.h>
#include<vector>

// #include "aestool.h"
// #include "rsatool.h"

using namespace std;

int n1=781,e1=297,d1=33; 
int n2=6541,e2=4163,d2=227;


void encrypt_aes(string& mes);
void decrypt_aes(string& mes);
void Make_PublicKey_And_PrivateKey(int &p , int &q, int& n,  int& e,int& d);
void Encrypt_key(string m, int e,int n, vector<int>& C);
void Decrypt_key(vector<int> C, int d, int n, string& show);
void saveFile_int(vector<int> v);
void readFile_int(vector<int>& num);
void readFile_rsa(string& mes);
void saveFile_rsa(string s);
string md5(string mes);

//用户A
bool Alice_encrypt(){
    string key = "akhvsrmfsyzibetagmhmademjkliddpq";  //密钥
    vector<int> C1,C2;  //密文
    string mes;  //明文
    string digest;  //摘要

    cout << "------用户A加密明文------" << endl;
    //生成密文文件test.txt
    encrypt_aes(mes);

    cout << endl <<"------用户A加密对称密钥key------" << endl;
    //加密后的会话密钥  key.txt
    Encrypt_key(key,e2,n2,C1);
    saveFile_int(C1);
    
    //哈希+数字签名  promise.txt
    cout << "------用户A对明文做哈希处理------" << endl;
    digest = md5(mes);
    Encrypt_key(digest,d1,n1,C2);
    saveFile_int(C2);
    return true;
}
//用户B
bool Bob_decrypt(){
    vector<int> C1,C2;  //密文
    string key;
    string mes;  //明文
    string digest;  //摘要
    string digest1;  //新产生的摘要


    // 私钥对会话密钥进行解密 key.txt
    cout << "------用户B对会话密钥进行解密------" << endl;
    readFile_int(C1);
    Decrypt_key(C1,d2,n2,key);
    cout << "解得的密钥为:" << endl;
    cout << key << endl;

    //对得到的密文进行解密  test.txt
    cout << "------用户B对得到的密文进行解密------" << endl;
    decrypt_aes(mes);

    //数字签名解密 promise.txt
    cout << "------用户B对数字签名解密------" << endl;
    readFile_int(C2);
    Decrypt_key(C2,e1,n1,digest);
   
    // 哈希运算
    digest1 = md5(mes);
    if(digest == digest1)
        cout << "文件安全传输成功！" << endl;
    else
        cout << "文件传输失败！" << endl;
    return true;
}


//建立公钥系统  
void init(){
    //公钥系统建立 AB产生自己的公私钥对
    cout << "------建立Alice公私钥对------" << endl;
    int p1,q1;
    Make_PublicKey_And_PrivateKey(p1,q1,n1,e1,d1);
    cout << "------建立Bob公私钥对------" << endl;
    int p2,q2;
    Make_PublicKey_And_PrivateKey(p2,q2,n2,e2,d2);
    cout << "------公钥系统已建立------" << endl;
}

int main(){
    //init();
    if(Alice_encrypt()){
        cout << "A已经完成加密!" << endl;
    }
    if(Bob_decrypt())
        cout << "B已经完成解密!" << endl;
        
    return 0;
}
