/*
 * Customer.cpp
 *
 *  Created on: 2017年10月25日
 *      Author: 18962
 */

#include "Customer.h"
#include <iostream>
using namespace std;

//定义构造函数
Customer::Customer() {
	cout<<"请您输入顾客的姓名\n";
	cin>>name;
	cout<<"请您输入顾客的身份证号码\n";
	cin>>ID;
	prepaid=change=day=0;

}

//定义析构函数
Customer::~Customer() {
	cout<<"该顾客退房成功!"<<endl;
}
