/*
 * Manager.cpp
 *
 *  Created on: 2017��10��25��
 *      Author: 18962
 */

#include "Manager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

const int R_SIZE=80;//����Ϳͻ���
const int S_SIZE=20;//�����ַ�������
const char* FILE_LOC="record.txt";  //д�ļ�

Manager::Manager()
{
	//��������ָ��
	room = new Room* [R_SIZE];
	cust = new Customer* [R_SIZE];
	// ��ʼ��������Ϣ
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

	//��ʼ����άcustָ��

	for(int i=0;i<R_SIZE;i++)
	{
		cust[i]=NULL;
	}
	//��ʼ���ͻ���cust_num
	cust_num = 0;
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
	for(int i=0;i<R_SIZE;i++)
	{
		delete room[i];
	}
	delete []room;   //����room
	cout<<"room Destructor!"<<endl;

	for(int i=0;i<R_SIZE;i++)
	{
		delete cust[i];
	}
	delete []cust;   //����cust
	cout<<"cust Destructor!"<<endl;
}


//ϵͳ��½����
void Manager::login()
{
	char name[S_SIZE],code[S_SIZE];
	cout<<"�������û���������(�Կո����):\n";
	cin>>name>>code;
	while((strcmp(name,"root")!=0)||(strcmp(code,"666666")!=0))
	{
		cout<<"�û�����������������,����������!\n";
		cin>>name>>code;
	}
	cout<<endl;
	cout<<endl;
	cout<<" ��***************************��\n";
	cout<<" ��  ��ӭʹ�þƵ�ͷ�����ϵͳ ��\n";
	cout<<" ��***************************��\n";
	cout<<endl;
}

void Manager::enter()
{
	int kind_of_service;
	cout<<"��ѡ��������:��������ס���˷����ǲ�ѯ? \n";
	cout<<" 1->���� 2->��ס 3->�˷� 4->��ѯ: ";
	cin>>kind_of_service;
	if((kind_of_service>4) || (kind_of_service<1))
	{
		cout<<"������������������!\n";
		cin>>kind_of_service;
	}
	else
		switch(kind_of_service)
		{
			case 1: book_room(); //����
			break;
			case 2: check_in(); //��ס
			break;
			case 3: check_out(); //�˷�
			break;
			case 4: inquire(); //��ѯ
			break;
		}
}

void Manager::start()
{
	char choice='1';
	login(); //��֤�û���½,��½�ɹ���ʾ��ӭ��Ϣ

	while(choice=='1')
	{
		enter(); //�����û���ѡ��ִ�в�ͬ�Ĺ���
		cout<<endl;
		cout<<"����ʹ�ñ�ϵͳ�밴\"1\",�˳��밴\"2\"! ";
		cin>>choice;
		cout<<endl;
	}
}

//���γ������н��պ󷿼���ͻ����������ļ�
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



//����ʵ��***************************************************************************
void Manager::book_room()
{
	cust[cust_num]=new Customer;
	int room_standard,day;
	cout<<"����ѡ��Ԥ������ı�׼:\n";
	cout<<"1.���˼�/��150Ԫ\n 2.˫�˼�/��200Ԫ\n 3.��׼��/��300Ԫ\n 4.��ͳ�׷�/��600Ԫ\n";
	cin>>room_standard;
	cout<<"������Ԥ������\n";
	cin>>day;
	cust[cust_num]->set_day(day); //�趨ס�޵�����
	switch(room_standard)
	{
		int n;
		case 1:
			cout<<"ס�������ܹ�Ϊ: "<<day*150<<"Ԫ\n"; //���㵥�˼�ס������
			for(n=0;n<20;n++) //�ӵ�һ������ķ����в���һ�����еķ���
			{
				if(room[n]->get_state()==0) //state=0��ʾ��ס��û�б�Ԥ����
				{
					cout<<"Ԥ���ɹ��﷿�����Ϊ: "<<room[n]->get_number()<<endl;
					room[n]->set_state(1);
					cust[cust_num]->set_room_number(room[n]->get_number());
					break;
				}
			}
			break;

		case 2: //��׼2�ķ���Ԥ��
			cout<<"ס�������ܹ�Ϊ: "<<day*200<<" Ԫ\n";
			for(n=20;n<40;n++)
			{
				if(room[n]->get_state()==0)
				{
					cout<<"Ԥ���ɹ��﷿�����Ϊ: "<<room[n]->get_number()<<endl;
					room[n]->set_state(1);
					cust[cust_num]->set_room_number(room[n]->get_number()); //����
					break;
				}
			}
			break;

		case 3:
			cout<<"ס�������ܹ�Ϊ: "<<day*300<<" Ԫ\n";
			for(n=40;n<60;n++)
			{
				if(room[n]->get_state()==0)
				{
					cout<<"Ԥ���ɹ��﷿�����Ϊ: "<<room[n]->get_number()<<endl;
					room[n]->set_state(1);
					cust[cust_num]->set_room_number(room[n]->get_number());
					break;
				}
			}
			break;
		case 4:
			cout<<"ס�������ܹ�Ϊ: "<<day*600<<"Ԫ\n";
			for(n=60;n<80;n++)
			{
				if(room[n]->get_state()==0)
				{
					cout<<"Ԥ���ɹ��﷿�����Ϊ: "<<room[n]->get_number()<<endl;
					room[n]->set_state(1);
					cust[cust_num]->set_room_number(room[n]->get_number());
					break;
				}
			}
			break;
	}
	cust_num++; //ס���Ĺ˿�����1
}


void Manager::check_in() //��ס��ѯ
{
	char name1[S_SIZE],id1[S_SIZE];
	int ding_or_no,prepaid;
	cout<<"�ù˿Ͷ�������? (1->���� 2->û��) ";
	cin>>ding_or_no;
	if(ding_or_no==1)
	{
		cout<<"������˿͵�����:"<<endl;
		cin>>name1;
		cout<<"������˿͵����֤����:"<<endl;
		cin>>id1;
		for(int j=0;j<=cust_num;j++)
		{
			if((strcmp(cust[j]->get_name(),name1)==0)&&(strcmp(cust[j]->get_ID(),id1)==0)) //���Ҹù˿͵Ķ�����Ϣ
			{
				int num=cust[j]->get_room_number(); //ȡ�ö����ķ����
				cout<<"�˿�"<<name1<<"������ס������! �������Ϊ: "<<num<<endl;
				switch(num/100)
				{
					case 6:
						prepaid=cust[j]->get_day()*150;
						cust[j]->set_prepaid(prepaid);
						cout<<"���շ��� "<<prepaid<<"Ԫ��!"<<endl; //��ʼ�շ�
						room[num%100-1]->set_state(2); //�޸ķ���״̬Ϊ��ס״̬
						break;
					case 7:
						prepaid=cust[j]->get_day()*200;
						cust[j]->set_prepaid(prepaid);
						cout<<"���շ��� "<<prepaid<<"Ԫ��!"<<endl;
						room[19+num%100]->set_state(2);
						break;
					case 8:
						prepaid=cust[j]->get_day()*300;
						cust[j]->set_prepaid(prepaid);
						cout<<"���շ��� "<<prepaid<<"Ԫ��!"<<endl;
						room[39+num%100]->set_state(2);
						break;
					case 9:
						prepaid=cust[j]->get_day()*600;
						cust[j]->set_prepaid(prepaid);
						cout<<"���շ��� "<<prepaid<<"Ԫ��!"<<endl;
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
		cout<<"����ѡ��Ԥ������ı�׼:\n";
		cout<<"1.���˼�/��150Ԫ\n2.˫�˼�/��200Ԫ\n3.��׼��/��300Ԫ\n4.��ͳ�׷�/��600Ԫ\n";
		cin>>room_standard;
		cout<<"������ס������\n";
		cin>>day;
		cust[cust_num]->set_day(day);
		switch(room_standard)
		{
			int n;
			case 1:
				prepaid=day*150;
				cust[cust_num]->set_prepaid(prepaid);
				cout<<"���շ��� "<<prepaid<<"Ԫ��!\n";
				for(n=0;n<20;n++)
				{
					if(room[n]->get_state()==0)
					{
						cout<<"��ס�������Ϊ: "<<room[n]->get_number()<<endl;
						room[n]->set_state(2);
						cust[cust_num]->set_room_number(room[n]->get_number());
						break;
					}
				}
				break;
			case 2:
				prepaid=day*200;
				cust[cust_num]->set_prepaid(prepaid);
				cout<<"���շ��� "<<prepaid<<"Ԫ��!\n";
				for(n=20;n<40;n++)
				{
					if(room[n]->get_state()==0)
					{
						cout<<"��ס�������Ϊ: "<<room[n]->get_number()<<endl;
						room[n]->set_state(2);
						cust[cust_num]->set_room_number(room[n]->get_number());
						break;
					}
				}
				break;
			case 3:
				prepaid=day*300;
				cust[cust_num]->set_prepaid(prepaid);
				cout<<"���շ��� "<<prepaid<<"Ԫ��!\n";
				for(n=40;n<60;n++)
				{
					if(room[n]->get_state()==0)
					{
						cout<<"��ס�������Ϊ: "<<room[n]->get_number()<<endl;
						room[n]->set_state(2);
						cust[cust_num]->set_room_number(room[n]->get_number());
						break;
					}
				}
				break;
			case 4:
				prepaid=day*600;
				cust[cust_num]->set_prepaid(prepaid);
				cout<<"���շ��� "<<prepaid<<"Ԫ��!\n";
				for(n=60;n<80;n++)
				{
					if(room[n]->get_state()==0)
					{
						cout<<"��ס�������Ϊ: "<<room[n]->get_number()<<endl;
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


//�˷�����***************************************************************************
void Manager::check_out()
{
	char name2[S_SIZE],id2[S_SIZE];
	int standard,j,room_number,day1,day2,day;
	cout<<"������Ҫ�˷��Ĺ˿�����:\n"<<endl;
	cin>>name2;
	cout<<"������Ҫ�˷��Ĺ˿����֤:\n"<<endl;
	cin>>id2;
	cout<<"������ù˿�ʵס����:\n";
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
				cout<<"�˿͵ķ������"<<room_number<<" :Ϊ���˼�,ÿ��150Ԫ\n";
				cout<<"�ù˿�Ԥ���˷��� "<<cust[j]->get_prepaid()<<"Ԫ, ʵ������ "<<day2*150<<"Ԫ��!\n";
				cout<<endl;
				if(day>0)
					cout<<"���˸��ù˿� "<<day*150<<" Ԫ��!\n";
				if(day<0)
					cout<<"�벹�ոù˿�ס���� "<<-day*150<<" Ԫ��!\n";
				break;
			case 7:
				cout<<"�˿͵ķ������"<<room_number<<" :Ϊ˫�˼�,ÿ��200Ԫ\n";
				cout<<"�ù˿�Ԥ���˷��� "<<cust[j]->get_prepaid()<<"Ԫ, ʵ������ "<<day2*200<<"Ԫ��!\n";
				cout<<endl;
				if(day>0)
					cout<<"���˸��ù˿� "<<day*200<<" Ԫ��!\n";
				if(day<0)
					cout<<"�벹�ոù˿�ס���� "<<-day*200<<" Ԫ��!\n";
				break;
			case 8:
				cout<<"�˿͵ķ������"<<room_number<<" :Ϊ��׼��,ÿ��300Ԫ\n";
				cout<<"�ù˿�Ԥ���˷��� "<<cust[j]->get_prepaid()<<"Ԫ, ʵ������ "<<day2*300<<"Ԫ��!\n";
				cout<<endl;
				if(day>0)
					cout<<"���˸��ù˿� "<<day*300<<" Ԫ��!\n";
				if(day<0)
					cout<<"�벹�ոù˿�ס���� "<<-day*300<<" Ԫ��!\n";
				break;
			case 9:
				cout<<"�˿͵ķ������"<<room_number<<" :Ϊ��ͳ�׷�,ÿ��600Ԫ\n";
				cout<<"�ù˿�Ԥ���˷��� "<<cust[j]->get_prepaid()<<"Ԫ, ʵ������ "<<day2*600<<"Ԫ��!\n";
				cout<<endl;
				if(day>0)
					cout<<"���˸��ù˿� "<<day*600<<" Ԫ��!\n";
				if(day<0)
					cout<<"�벹�ոù˿�ס���� "<<-day*600<<" Ԫ��!\n";
				break;
			}
			cout<<endl;
			cout<<"�˷��������,�밴1: ";
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
				cust[j]=NULL;   //��������
				cust_num--;
				for(;j<cust_num;j++)
				{
					cust[j]=cust[j+1];   //�����ƶ�
				}
				cust[cust_num]=NULL; //���һ��Ԫ���ÿ�ֵ

			}
		}
	}
}

//��Ϣ��ѯ***************************************************************************
void Manager::inquire()
{
	char inquire_choice;
	cout<<"������Ϣ��ѯ�밴1, �˿���Ϣ��ѯ�밴2: "<<endl;
	cin>>inquire_choice;
	if(inquire_choice=='1')
	{
		int j,k=0;
		cout<<endl;
		cout<<"���з��仹û��Ԥ����Ҳû����ס��"<<endl;
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
		cout<<"���з�����Ԥ����"<<endl;
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
		cout<<"���з���������ס��"<<endl;
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
		cout<<"��������ѯ�밴1, �����֤��ѯ�밴2: "<<endl;
		char inquire_choice2;
		cin>>inquire_choice2;
		if(inquire_choice2=='1')
		{
			char name3[S_SIZE];
			cout<<"������˿͵�����: "<<endl;
			cin>>name3;
			for(int j=0;j<cust_num;j++)
			{
				if(strcmp(cust[j]->get_name(),name3)==0)
				{
					cout<<name3<<"��ס����Ϣ����:\n";
					cout<<'\t'<<"�����Ϊ: "<<cust[j]->get_room_number()<<endl;
					cout<<"\t"<<"Ԥ������Ϊ: "<<cust[j]->get_prepaid()<<endl;
				}
			}
		}
		if(inquire_choice2=='2')
		{
			char id3[S_SIZE];
			cout<<"������˿͵����֤��: "<<endl;
			cin>>id3;
			for(int j=0;j<cust_num;j++)
			{
				if(strcmp(cust[j]->get_ID(),id3)==0)
				{
					cout<<cust[j]->get_name()<<"��ס����Ϣ����:\n";
					cout<<'\t'<<"�����Ϊ: "<<cust[j]->get_room_number()<<endl;
					cout<<"\t"<<"Ԥ������Ϊ: "<<cust[j]->get_prepaid()<<endl;
				}
			}
		}
	}
}
