#pragma once
#ifndef HASH_TABLE
#include <iostream>
class HashTable
{
private:
    int m;//表的长度
    int p;//小于m的最大素数
    std::string* Table;//存储字符串
    bool *placed;//标志是否有记录
    int* RandSeq;//伪随机序列
public:
    void insert(const std::string& str);//向哈希表中插入元素
    int find(const std::string &str, int& QueryTime)const;//在哈希表中查找
    void Show()const;
    std::string GetStr(const int& pos)const;
    static int LastPrime(const int& x);//找到小于等于x的最大素数
    HashTable(const int &M);
    HashTable();//默认构造函数
    ~HashTable();//析构函数
    void ShowSeq()const;
};

#endif // !HASH_TABLE

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <QTableWidgetItem>
#include <QAbstractItemView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ShowHashTable();

private slots:
    void on_query_clicked();

    void on_LookupAll_clicked();

private:
    Ui::MainWindow *ui;
    int Cap;
    HashTable *HT;
    QTableWidget *tableWidget;
};

#endif // MAINWINDOW_H
