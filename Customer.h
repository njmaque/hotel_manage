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
	void set_name(char *n){strcpy(name,n);}
	void set_ID(char *p){strcpy(ID,p);}
	void set_room_number(int n){room_number=n;}
	void set_day(int d){ day=d;}
	void set_prepaid(int p){prepaid=p;}
	char *get_name(){return name; }
	char *get_ID(){ return ID;}
	int get_room_number(){return room_number;}
	int get_day(){return day;}
	int get_prepaid(){return prepaid;}
	virtual ~Customer();

private:
	char name[10],ID[19];
	int room_number;
	int prepaid;
	int change;
	int day;
};


#endif /* CUSTOMER_H_ */
