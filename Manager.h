/*
 * Manager.h
 *
 *  Created on: 2017年10月25日
 *      Author: 18962
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "Room.h"
#include "Customer.h"

class Manager
{
public:
	Manager();    //构造函数：初始化房间信息和cust二级指针
	void output(); //本次运行结束房间使用情况和客户入住情况输出到文件
	void login();   //系统登陆界面：模拟用户名密码
	void start();//系统启动函数：循环体内执行命令项
	void enter();	//系统入口函数，按照输入选择具体操作：预定，入住，退房，查询
	void book_room(); //预定，填写客户信息，匹配空房间，房间状态设置为已预定
	void check_in(); //入住，如果已预定，则校验客户身份，设置预付款，如果没预定则新增客户信息，办理入住
	void check_out(); //退房结算，验证客户信息，通过实际住房天数计算实收（应付-预付），置该房间为可用状态，删除该客户信息
	void inquire();   //查询：房间信息插叙，客户信息查询
	 ~Manager(); //析构所有内存空间
private:
	Room** room;  //二维指针，room指向一个Room类型的指针数组
	Customer** cust; //二维指针，cust指向一个Customer类型的指针数组，
	int cust_num; //记录目前的客户数
};

#endif /* MANAGER_H_ */
