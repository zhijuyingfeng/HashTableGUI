#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include "mainwindow.h"

using namespace std;

int HashTable::LastPrime(const int& x)//返回第一个小于等于x的素数
{
    bool *isPrime = new bool[x + 1];
    memset(isPrime, 0x11, sizeof(bool)*(x + 1));
    vector<int> prime;
    //线性筛素数
    for (int i = 2; i <= x; i++)
    {
        if (isPrime[i])
        {
            prime.push_back(i);
        }
        int size = prime.size();
        for(int j=0;j<size&&prime[j]*i<=x;j++)
        {
            isPrime[i*prime[j]] = 0;
            if (i%prime[j] == 0)
                break;
        }
    }
    delete[]isPrime;
    return prime.back();
}

HashTable::HashTable(const int&M)
{
    this->m = M;
    this->p = LastPrime(this->m);
    this->RandSeq = new int[this->m];
    this->Table = new string[this->m];
    this->placed = new bool[this->m];
    memset(placed, 0, sizeof(bool)*this->m);
    for (int i = 0; i < m; i++)
    {
        this->RandSeq[i] = i+1;
    }
    int a, b;
    for (int i = 0; i < m; i++)//使用交换来产生伪随机序列
    {
        a = rand() % this->m;
        b = rand() % this->m;
        swap(this->RandSeq[a], this->RandSeq[b]);
    }
}

HashTable::~HashTable()//析构函数
{
    delete[]Table;
    delete[]placed;
    delete[]RandSeq;
}

HashTable::HashTable()
{
    this->m = 30;
    this->p = LastPrime(this->m);
    this->Table = new string[this->m];
    this->RandSeq = new int[this->m];
    this->placed = new bool[this->m];
    memset(placed, 0, sizeof(bool)*this->m);
    for (int i = 0; i < m; i++)
    {
        this->RandSeq[i] = i+1;
    }
    int a, b;
    for (int i = 0; i < m; i++)
    {
        a = rand() % this->m;
        b = rand() % this->m;
        swap(this->RandSeq[a], this->RandSeq[b]);
    }
}

void HashTable::insert(const string& str)
{
    int sum = 0;
    int len = str.length();
    for (int i = 0; i < len; i++)//字符相加得到关键字
    {
        sum += str[i];
    }
    int hash = sum % p;//除留余数法
    if (placed[hash] == 0)
    {
        Table[hash] = str;
        placed[hash] = 1;
        return;
    }
    int i = 0;
    while(placed[hash] == 1 && str.compare(Table[hash]) )
    {
        hash = (hash + this->RandSeq[i++]) % p;//伪随机再散列处理冲突
        i = i % this->m;
    }
    Table[hash] = str;
    placed[hash] = 1;
}

int HashTable::find(const string& str, int& QueryTime)const
{
    int sum = 0;
    int len = str.length();
    for (int i = 0; i < len; i++)
    {
        sum += str[i];
    }
    int hash = sum % this->p;
    QueryTime = 1;
    if (placed[hash] == 0)//查找出错
    {
        cout << "No such record!!!" << endl;
        return -1;
    }
    else if (placed[hash] && str.compare(Table[hash]) == 0)//第一次查找成功
    {
        return hash;
    }
    else
    {
        int i = 0;
        while (placed[hash] && str.compare(Table[hash]))
        {
            hash = (hash + this->RandSeq[i++]) % p;//与插入时使用相同方法处理冲突
            QueryTime++;
            i = i % m;
        }
        if (!placed[hash])
        {
            return -1;
        }
        else
        {
            return hash;
        }
    }
}

void HashTable::Show()const//展示哈希表
{
    for (int i = 0; i < this->m; i++)
    {
        cout<<i<<"\t"<<Table[i] << endl;
    }
}


std::string HashTable::GetStr(const int &pos) const//返回表中指定下标处的字符串
{
    string str;
    if(pos<0||pos>=this->m)
        return str;
    else
    {
        return Table[pos];
    }
}

void HashTable::ShowSeq() const
{
    for(int i=0;i<m;i++)
    {
        cout<<this->RandSeq[i]<<endl;
    }
}
