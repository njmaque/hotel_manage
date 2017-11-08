/*
 * Manager.cpp
 *
 *  Created on: 2017年10月25日
 *      Author: 18962
 */

#include "Manager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

const int R_SIZE=80;//房间和客户数
const int S_SIZE=20;//输入字符串长度
const char* FILE_LOC="record.txt";  //写文件

Manager::Manager()
{
	//申请数组指针
	room = new Room* [R_SIZE];
	cust = new Customer* [R_SIZE];
	// 初始化房间信息
	int j,k=601;
	for(j=0;j<20;j++)
	{
		room[j] = new Room(k++,1,150,0);
	}
	k=701;
	for(j=20;j<40;j++)
	{
		room[j] = new Room(k++,2,200,0);
	}
	k=801;
	for(j=40;j<60;j++)
	{
		room[j] = new Room(k++,3,300,0);
	}
	k=901;
	for(j=60;j<80;j++)
	{
		room[j] = new Room(k++,4,600,0);
	}

	//初始化二维cust指针

	for(int i=0;i<R_SIZE;i++)
	{
		cust[i]=NULL;
	}
	//初始化客户数cust_num
	cust_num = 0;
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
	for(int i=0;i<R_SIZE;i++)
	{
		delete room[i];
	}
	delete []room;   //析构room
	cout<<"room Destructor!"<<endl;

	for(int i=0;i<R_SIZE;i++)
	{
		delete cust[i];
	}
	delete []cust;   //析构cust
	cout<<"cust Destructor!"<<endl;
}


//系统登陆界面
void Manager::login()
{
	char name[S_SIZE],code[S_SIZE];
	cout<<"请输入用户名和密码(以空格隔开):\n";
	cin>>name>>code;
	while((strcmp(name,"root")!=0)||(strcmp(code,"666666")!=0))
	{
		cout<<"用户名或密码输入有误,请重新输入!\n";
		cin>>name>>code;
	}
	cout<<endl;
	cout<<endl;
	cout<<" ▲***************************▲\n";
	cout<<" △  欢迎使用酒店客房管理系统 △\n";
	cout<<" ▲***************************▲\n";
	cout<<endl;
}

void Manager::enter()
{
	int kind_of_service;
	cout<<"请选择服务类别:订房、入住、退房还是查询? \n";
	cout<<" 1->订房 2->入住 3->退房 4->查询: ";
	cin>>kind_of_service;
	if((kind_of_service>4) || (kind_of_service<1))
	{
		cout<<"您的输入有误，请重试!\n";
		cin>>kind_of_service;
	}
	else
		switch(kind_of_service)
		{
			case 1: book_room(); //订房
			break;
			case 2: check_in(); //入住
			break;
			case 3: check_out(); //退房
			break;
			case 4: inquire(); //查询
			break;
		}
}

void Manager::start()
{
	char choice='1';
	login(); //验证用户登陆,登陆成功显示欢迎信息

	while(choice=='1')
	{
		enter(); //根据用户的选择执行不同的功能
		cout<<endl;
		cout<<"继续使用本系统请按\"1\",退出请按\"2\"! ";
		cin>>choice;
		cout<<endl;
	}
}

//本次程序运行接收后房间与客户情况输出到文件
void Manager::output()
{
	time_t rawtime;
	time(&rawtime);
	ofstream fout(FILE_LOC,ios::out | ios::app);
	if (!fout.is_open())
	{
		cerr<<"Can't open "<<FILE_LOC<<"file for output."<<endl;
		exit(EXIT_FAILURE);
	}
	fout<<"-----------------------"<<ctime(&rawtime)<<"--------------------------"<<endl;
	fout<<"---------RommInfo------"<<endl;
	for(int i=0;i<R_SIZE;i++)
	{
		fout<<"RommNo="<<room[i]->get_number()<<" dank="<<room[i]->get_dank()
		<<" price="<<room[i]->get_price()<<" state="<<room[i]->get_state()<<endl;
	}
	fout<<"--------CustomerInof------"<<endl;
	for(int i=0;i<cust_num;i++)
	{
		fout<<"cust_name= "<<cust[i]->get_name()<<" cust_id= "<<cust[i]->get_ID()
		<<" days= "<<cust[i]->get_day()<<" room_number= "<<cust[i]->get_room_number()
		<<" pre_paid= "<<cust[i]->get_prepaid()<<endl;
	}
	fout.close();
}



//订房实现***************************************************************************
void Manager::book_room()
{
	cust[cust_num]=new Customer;
	int room_standard,day;
	cout<<"请您选择预定房间的标准:\n";
	cout<<"1.单人间/天150元\n 2.双人间/天200元\n 3.标准间/天300元\n 4.总统套房/天600元\n";
	cin>>room_standard;
	cout<<"请输入预定天数\n";
	cin>>day;
	cust[cust_num]->set_day(day); //设定住宿的天数
	switch(room_standard)
	{
		int n;
		case 1:
			cout<<"住房费用总共为: "<<day*150<<"元\n"; //计算单人间住房费用
			for(n=0;n<20;n++) //从第一个级别的房间中查找一个空闲的房间
			{
				if(room[n]->get_state()==0) //state=0表示该住房没有被预定的
				{
					cout<<"预定成功★房间号码为: "<<room[n]->get_number()<<endl;
					room[n]->set_state(1);
					cust[cust_num]->set_room_number(room[n]->get_number());
					break;
				}
			}
			break;

		case 2: //标准2的房间预订
			cout<<"住房费用总共为: "<<day*200<<" 元\n";
			for(n=20;n<40;n++)
			{
				if(room[n]->get_state()==0)
				{
					cout<<"预定成功★房间号码为: "<<room[n]->get_number()<<endl;
					room[n]->set_state(1);
					cust[cust_num]->set_room_number(room[n]->get_number()); //？？
					break;
				}
			}
			break;

		case 3:
			cout<<"住房费用总共为: "<<day*300<<" 元\n";
			for(n=40;n<60;n++)
			{
				if(room[n]->get_state()==0)
				{
					cout<<"预定成功★房间号码为: "<<room[n]->get_number()<<endl;
					room[n]->set_state(1);
					cust[cust_num]->set_room_number(room[n]->get_number());
					break;
				}
			}
			break;
		case 4:
			cout<<"住房费用总共为: "<<day*600<<"元\n";
			for(n=60;n<80;n++)
			{
				if(room[n]->get_state()==0)
				{
					cout<<"预定成功★房间号码为: "<<room[n]->get_number()<<endl;
					room[n]->set_state(1);
					cust[cust_num]->set_room_number(room[n]->get_number());
					break;
				}
			}
			break;
	}
	cust_num++; //住房的顾客数加1
}


void Manager::check_in() //入住查询
{
	char name1[S_SIZE],id1[S_SIZE];
	int ding_or_no,prepaid;
	cout<<"该顾客订房了吗? (1->订了 2->没订) ";
	cin>>ding_or_no;
	if(ding_or_no==1)
	{
		cout<<"请输入顾客的姓名:"<<endl;
		cin>>name1;
		cout<<"请输入顾客的身份证号码:"<<endl;
		cin>>id1;
		for(int j=0;j<=cust_num;j++)
		{
			if((strcmp(cust[j]->get_name(),name1)==0)&&(strcmp(cust[j]->get_ID(),id1)==0)) //查找该顾客的定房信息
			{
				int num=cust[j]->get_room_number(); //取得定房的房间号
				cout<<"顾客"<<name1<<"今天入住本宾馆! 房间号码为: "<<num<<endl;
				switch(num/100)
				{
					case 6:
						prepaid=cust[j]->get_day()*150;
						cust[j]->set_prepaid(prepaid);
						cout<<"请收房费 "<<prepaid<<"元整!"<<endl; //开始收费
						room[num%100-1]->set_state(2); //修改房间状态为入住状态
						break;
					case 7:
						prepaid=cust[j]->get_day()*200;
						cust[j]->set_prepaid(prepaid);
						cout<<"请收房费 "<<prepaid<<"元整!"<<endl;
						room[19+num%100]->set_state(2);
						break;
					case 8:
						prepaid=cust[j]->get_day()*300;
						cust[j]->set_prepaid(prepaid);
						cout<<"请收房费 "<<prepaid<<"元整!"<<endl;
						room[39+num%100]->set_state(2);
						break;
					case 9:
						prepaid=cust[j]->get_day()*600;
						cust[j]->set_prepaid(prepaid);
						cout<<"请收房费 "<<prepaid<<"元整!"<<endl;
						room[59+num%100]->set_state(2);
						break;
				}
				break;
			}
		}
	}
	else
	{
		cust[cust_num]=new Customer;
		int room_standard,day;
		cout<<"请您选择预定房间的标准:\n";
		cout<<"1.单人间/天150元\n2.双人间/天200元\n3.标准间/天300元\n4.总统套房/天600元\n";
		cin>>room_standard;
		cout<<"请输入住宿天数\n";
		cin>>day;
		cust[cust_num]->set_day(day);
		switch(room_standard)
		{
			int n;
			case 1:
				prepaid=day*150;
				cust[cust_num]->set_prepaid(prepaid);
				cout<<"请收房费 "<<prepaid<<"元整!\n";
				for(n=0;n<20;n++)
				{
					if(room[n]->get_state()==0)
					{
						cout<<"入住房间号码为: "<<room[n]->get_number()<<endl;
						room[n]->set_state(2);
						cust[cust_num]->set_room_number(room[n]->get_number());
						break;
					}
				}
				break;
			case 2:
				prepaid=day*200;
				cust[cust_num]->set_prepaid(prepaid);
				cout<<"请收房费 "<<prepaid<<"元整!\n";
				for(n=20;n<40;n++)
				{
					if(room[n]->get_state()==0)
					{
						cout<<"入住房间号码为: "<<room[n]->get_number()<<endl;
						room[n]->set_state(2);
						cust[cust_num]->set_room_number(room[n]->get_number());
						break;
					}
				}
				break;
			case 3:
				prepaid=day*300;
				cust[cust_num]->set_prepaid(prepaid);
				cout<<"请收房费 "<<prepaid<<"元整!\n";
				for(n=40;n<60;n++)
				{
					if(room[n]->get_state()==0)
					{
						cout<<"入住房间号码为: "<<room[n]->get_number()<<endl;
						room[n]->set_state(2);
						cust[cust_num]->set_room_number(room[n]->get_number());
						break;
					}
				}
				break;
			case 4:
				prepaid=day*600;
				cust[cust_num]->set_prepaid(prepaid);
				cout<<"请收房费 "<<prepaid<<"元整!\n";
				for(n=60;n<80;n++)
				{
					if(room[n]->get_state()==0)
					{
						cout<<"入住房间号码为: "<<room[n]->get_number()<<endl;
						room[n]->set_state(2);
						cust[cust_num]->set_room_number(room[n]->get_number());
						break;
					}
				}
				break;
		}
		cust_num++;
	}
}


//退房结算***************************************************************************
void Manager::check_out()
{
	char name2[S_SIZE],id2[S_SIZE];
	int standard,j,room_number,day1,day2,day;
	cout<<"请输入要退房的顾客姓名:\n"<<endl;
	cin>>name2;
	cout<<"请输入要退房的顾客身份证:\n"<<endl;
	cin>>id2;
	cout<<"请输入该顾客实住天数:\n";
	cin>>day2;
	for(j=0;j<cust_num;j++)
	{
		if((strcmp(cust[j]->get_name(),name2)==0)&&(strcmp(cust[j]->get_ID(),id2)==0))
		{
			room_number=cust[j]->get_room_number();
			standard=room_number/100;
			day1=cust[j]->get_day();
			day=day1-day2;
			switch(standard)
			{
			case 6:
				cout<<"顾客的房间号是"<<room_number<<" :为单人间,每天150元\n";
				cout<<"该顾客预付了房费 "<<cust[j]->get_prepaid()<<"元, 实际消费 "<<day2*150<<"元整!\n";
				cout<<endl;
				if(day>0)
					cout<<"请退给该顾客 "<<day*150<<" 元整!\n";
				if(day<0)
					cout<<"请补收该顾客住房费 "<<-day*150<<" 元整!\n";
				break;
			case 7:
				cout<<"顾客的房间号是"<<room_number<<" :为双人间,每天200元\n";
				cout<<"该顾客预付了房费 "<<cust[j]->get_prepaid()<<"元, 实际消费 "<<day2*200<<"元整!\n";
				cout<<endl;
				if(day>0)
					cout<<"请退给该顾客 "<<day*200<<" 元整!\n";
				if(day<0)
					cout<<"请补收该顾客住房费 "<<-day*200<<" 元整!\n";
				break;
			case 8:
				cout<<"顾客的房间号是"<<room_number<<" :为标准间,每天300元\n";
				cout<<"该顾客预付了房费 "<<cust[j]->get_prepaid()<<"元, 实际消费 "<<day2*300<<"元整!\n";
				cout<<endl;
				if(day>0)
					cout<<"请退给该顾客 "<<day*300<<" 元整!\n";
				if(day<0)
					cout<<"请补收该顾客住房费 "<<-day*300<<" 元整!\n";
				break;
			case 9:
				cout<<"顾客的房间号是"<<room_number<<" :为总统套房,每天600元\n";
				cout<<"该顾客预付了房费 "<<cust[j]->get_prepaid()<<"元, 实际消费 "<<day2*600<<"元整!\n";
				cout<<endl;
				if(day>0)
					cout<<"请退给该顾客 "<<day*600<<" 元整!\n";
				if(day<0)
					cout<<"请补收该顾客住房费 "<<-day*600<<" 元整!\n";
				break;
			}
			cout<<endl;
			cout<<"退房核算清楚,请按1: ";
			char account;
			cin>>account;
			if(account=='1')
			{
				for(int k=0;k<R_SIZE;k++)
				{
					if(room[k]->get_number()==cust[j]->get_room_number())
						room[k]->set_state(0);
				}
				delete cust[j];
				cust[j]=NULL;   //回收资料
				cust_num--;
				for(;j<cust_num;j++)
				{
					cust[j]=cust[j+1];   //数组移动
				}
				cust[cust_num]=NULL; //最后一个元素置空值

			}
		}
	}
}

//信息查询***************************************************************************
void Manager::inquire()
{
	char inquire_choice;
	cout<<"房间信息查询请按1, 顾客信息查询请按2: "<<endl;
	cin>>inquire_choice;
	if(inquire_choice=='1')
	{
		int j,k=0;
		cout<<endl;
		cout<<"下列房间还没人预订，也没人入住："<<endl;
		for(j=0;j<R_SIZE;j++)
		{
			if(room[j]->get_state()==0)
			{
				if(k%10==0) cout<<endl;
				cout<<room[j]->get_number()<<'\t';
				k++;
			}
		}
		cout<<endl;
		cout<<endl;
		k=0;
		cout<<"下列房间已预订："<<endl;
		for(j=0;j<R_SIZE;j++)
		{
			if(room[j]->get_state()==1)
			{
				if(k%10==0) cout<<endl;
				cout<<room[j]->get_number()<<'\t';
				k++;
			}
		}
		k=0;
		cout<<endl;
		cout<<endl;
		cout<<"下列房间有人入住："<<endl;
		for(j=0;j<R_SIZE;j++)
		{
			if(room[j]->get_state()==2)
			{
				if(k%10==0) cout<<endl;
				cout<<room[j]->get_number()<<'\t';
				k++;
			}
		}
		cout<<endl;
		cout<<endl;
	}
	else if(inquire_choice=='2')
	{
		cout<<"按姓名查询请按1, 按身份证查询请按2: "<<endl;
		char inquire_choice2;
		cin>>inquire_choice2;
		if(inquire_choice2=='1')
		{
			char name3[S_SIZE];
			cout<<"请输入顾客的姓名: "<<endl;
			cin>>name3;
			for(int j=0;j<cust_num;j++)
			{
				if(strcmp(cust[j]->get_name(),name3)==0)
				{
					cout<<name3<<"的住房信息如下:\n";
					cout<<'\t'<<"房间号为: "<<cust[j]->get_room_number()<<endl;
					cout<<"\t"<<"预付房费为: "<<cust[j]->get_prepaid()<<endl;
				}
			}
		}
		if(inquire_choice2=='2')
		{
			char id3[S_SIZE];
			cout<<"请输入顾客的身份证号: "<<endl;
			cin>>id3;
			for(int j=0;j<cust_num;j++)
			{
				if(strcmp(cust[j]->get_ID(),id3)==0)
				{
					cout<<cust[j]->get_name()<<"的住房信息如下:\n";
					cout<<'\t'<<"房间号为: "<<cust[j]->get_room_number()<<endl;
					cout<<"\t"<<"预付房费为: "<<cust[j]->get_prepaid()<<endl;
				}
			}
		}
	}
}
