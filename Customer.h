/*
 * Customer.h
 *
 *  Created on: 2017年10月24日
 *      Author: 18962
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <cstring>

class Customer {
public:
	Customer();
	void set_name(char *n){strcpy(name,n);} //设置客户姓名
	void set_ID(char *p){strcpy(ID,p);} //设置客户ID
	void set_room_number(int n){room_number=n;} //设置房号
	void set_day(int d){ day=d;} //设置入住天数
	void set_prepaid(int p){prepaid=p;} //设置找零
	char *get_name(){return name; } //获取客户姓名
	char *get_ID(){ return ID;} //获取客户ID
	int get_room_number(){return room_number;} //获取房间号
	int get_day(){return day;} //获取入住天数
	int get_prepaid(){return prepaid;} //获取找零信息
	virtual ~Customer();

private:
	char name[10],ID[19]; //客户姓名，客户ID
	int room_number; //房间号
	int prepaid; //预付款
	int change; //找零
	int day; //入住天数
};


#endif /* CUSTOMER_H_ */
