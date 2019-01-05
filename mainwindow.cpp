#include "mainwindow.h"
#include "ui_mainwindow.h"

const int n = 30;
static int ClickLookupAllTimes=0;
//const std::string name[n] =
//{
//"TangBingXin","RuanLisha","HanJing","XiaoHuaiYu","SiTuYuanHao","YangXin","HuangRuoTong","LinZeBang",
//"XuMinRui","GuoMingHao","ZhangYue","TangLuYao","FengYiKai","LiuLiHong","DengZiRu","LiJiaDai",
//"WangShiYou","XiongShuYang","WeiJunQuan","HuangKangRui","WangYaJun","YaoJieQian","YanJingYa",
//"MaiTianWei","HuZiRui","RenShuangYin","WangJunDa","WangLiang","Nigao","WangXinYu"
//};
const std::string name[n]=
{
    "DengZiRu","FengYiKai","GuoMingHao","HanJing","HuZiRui","HuangKangRui","HuangRuoTong","LiJiaDai",
    "LinZeBang","LiuLiHong","MaiTianWei","Nigao","RenShuangYin","RuanLisha","SiTuYuanHao","TangBingXin",
    "TangLuYao","WangJunDa","WangLiang","WangShiYou","WangXinYu","WangYaJun","WeiJunQuan","XiaoHuaiYu",
    "XiongShuYang","XuMinRui","YanJingYa","YangXin","YaoJieQian","ZhangYue"
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Cap=HashTable::LastPrime(n<<1);
    tableWidget=new QTableWidget(this);
    tableWidget->setColumnCount(1);
    tableWidget->setRowCount(Cap);
    tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Name"));
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setGeometry(10,10,201,421);

    HT=new HashTable(Cap);
    for(int i=0;i<n;i++)
    {
        HT->insert(name[i]);
    }
    ShowHashTable();
    tableWidget->show();
}

MainWindow::~MainWindow()
{
    delete tableWidget;
    delete HT;
    delete ui;
}

void MainWindow::on_query_clicked()//查找某个姓名
{
 int time,pos;
 QString str=this->ui->Selector->currentText();
 pos=HT->find(str.toStdString(),time);
 if(pos>=0)
 {
     char Pos[10]={0};
     char Time[10]={0};
     sprintf(Pos,"%d",pos);
     sprintf(Time,"%d",time);
     this->ui->pos->setText(QString(Pos));
     this->ui->QueryTime->setText(QString(Time));
 }
 else
 {
     this->ui->pos->setText("No such record");
     this->ui->QueryTime->setText("No such record");
 }
}

void MainWindow::on_LookupAll_clicked()//对所有姓名进行一次查找，并统计和输出信息
{
    if(ClickLookupAllTimes>0)
        return;
    ClickLookupAllTimes++;
    int total=0,time,pos,cnt=0;
    std::vector<std::string> vec;
    for(int i=0;i<n;i++)
    {
        pos=HT->find(name[i],time);
        if(pos>=0)
        {
            total+=time;
            cnt++;
        }
        else
        {
            vec.push_back(name[i]);
        }
    }
    char Total[11]={0};
    sprintf(Total,"%d",total);
    this->ui->TotalLookupTimes->setText(QString(Total));
    double ALT=1.0*total/cnt;
    char Alt[11]={0};
    sprintf(Alt,"%.2lf",ALT);
    this->ui->ALT->setText(QString(Alt));
    int size=vec.size();
    QString str;
    if(size>1)
    {
        str=str+"It failed when look up these names:\n";
        for(int i=0;i<size;i++)
        {
            str=str+QString(vec[i].c_str());
            str=str+"\n";
        }
    }
    else if(size==1)
    {
        str=str+"It failed when look up this name:\n";
        str=str+QString(vec[0].c_str());
        str=str+"\n";
    }
    else
    {
        str=str+"No wrong info\n";
    }
    this->ui->WrongInfo->setText(str);
}

void MainWindow::ShowHashTable()
{
    char str[10]={0};
    for(int i=0;i<Cap;i++)
    {
        memset(str,0,sizeof(str));
        sprintf(str,"%d",i);
        tableWidget->setVerticalHeaderItem(i,new QTableWidgetItem(str));
    }
    for(int i=0;i<Cap;i++)
    {
        std::string str=HT->GetStr(i);
        tableWidget->setColumnWidth(i,180);
        tableWidget->setItem(i,0,new QTableWidgetItem(str.c_str()));
    }
}
