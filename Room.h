/*
 * Room.h
 *
 *  Created on: 2017年10月25日
 *      Author: 18962
 */

#ifndef ROOM_H_
#define ROOM_H_

class Room
{
public:
	Room(int n,int d,int p,int s);  //带参构造函数
	void set_state(int n){state=n;} //设置房间状态 0：空置  1：预定 2：入住
	int get_number(){return number;} //取得房间号
	int get_state(){return state;} //获取房间状态
	int get_dank(){return dank;} //获取房间等级
	int get_price(){return price;} //获取房间单价
	 ~Room();
private:
	int number; //房间号
	int dank;//住房等级
	int price; //价格
	int state; //状态
};

#endif /* ROOM_H_ */
