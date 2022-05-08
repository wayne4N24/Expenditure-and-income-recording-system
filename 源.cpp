#include <graphics.h>      // 引用图形库头文件
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <conio.h>
#include<tchar.h>
#include<time.h>
#include<wchar.h>


typedef struct record
{
	wchar_t flag[10];    //flag=1表示支出，flag=0表示收入
	wchar_t type[10];    //用于保存小种类，如“日用”、“交通”等
	wchar_t money[100];  //保存用户输入的数字
	wchar_t time[100];   //使用<time.h>无需用户输入日期，自动记录当天日期
	struct record* next;
}Node;



IMAGE welcome;
IMAGE welcome2;
IMAGE index_original;
IMAGE index_add;
IMAGE index_delete;
IMAGE index_change;
IMAGE index_exit;
IMAGE index_search;
IMAGE index_sort;
IMAGE end;
IMAGE add_exit;
IMAGE add_shouru;
IMAGE add_zhichu;
IMAGE add;
IMAGE delet;
IMAGE delet_zhichu;
IMAGE delet_shouru;
IMAGE delet_exit;
IMAGE search;
IMAGE search_zhichu;
IMAGE search_shouru;
IMAGE search_exit;
IMAGE sort;
IMAGE sort_zhichu;
IMAGE sort_shouru;
IMAGE sort_exit;
IMAGE change;
IMAGE change_zhichu;
IMAGE change_shouru;
IMAGE change_exit;

void Welcome(Node* &p, Node* &pre);
void Add(struct record* &p,Node*& pre);
void Change(struct record* p,Node* pre);
void Delete(struct record* &p,Node* &pre);
void Search(struct record* p,Node* pre);
void Select_MainMenu(struct record* &p,Node* &pre);
void Sort(struct record* p,Node* pre);
void Save(Node* p);
void output(Node* p);

//wchar_t转char函数
void WchartoChar(char* charStr, const wchar_t* wcharStr)  //wchar_t转char
{
	int len = WideCharToMultiByte(CP_ACP, 0, wcharStr, wcslen(wcharStr), NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, wcharStr, wcslen(wcharStr), charStr, len, NULL, NULL);
	charStr[len] = '\0';
}


//欢迎界面函数
void Welcome(Node* &p,Node* &pre)
{
	loadimage(&welcome, L"welcome.jpg");//导入欢迎界面（特别注意：双引号里面不能有空格，要跟图片命名完全一致）
	putimage(0, 0, &welcome);//显示欢迎界面
	/*下面进行鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 506 && msg.x < 752 && msg.y > 508 && msg.y < 598)//鼠标点击特定区域，即ENTER按钮所在区域
				{
					loadimage(&welcome2, L"welcome2.jpg");//导入橙色按钮图片
					putimage(0, 0, &welcome2);//显示橙色按钮图片
					Sleep(100);//延时，降低CPU占用率，并且做到点击效果
					Select_MainMenu(p,pre);//调用一级主菜单选项函数
				}
			}
		}
		
	}

}

//主菜单函数
void Select_MainMenu(Node* &p,Node* &pre)
{
	loadimage(&index_original, L"index_original.jpg");//导入初始界面
	putimage(0, 0, &index_original);//显示初始界面
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 147 && msg.x < 452 && msg.y > 183 && msg.y < 267)//鼠标点击特定区域，即“增加记录”按钮所在区域
					Add(p,pre);//调用增加函数
				if (msg.x > 145 && msg.x < 448 && msg.y > 335 && msg.y < 421)//鼠标点击特定区域，即“删除记录”按钮所在区域
					Delete(p,pre);//调用删除函数
				if (msg.x > 154 && msg.x < 447 && msg.y > 490 && msg.y < 577)//鼠标点击特定区域，即“支出排行榜”按钮所在区域
					Sort(p,pre);//调用排序函数
				if (msg.x > 734 && msg.x < 1028 && msg.y > 180 && msg.y < 264)//鼠标点击特定区域，即“更改记录”按钮所在区域
					Change(p,pre);//调用更改函数
				if (msg.x > 733 && msg.x < 1027 && msg.y > 332 && msg.y < 419)//鼠标点击特定区域，即“查询记录”按钮所在区域
					Search(p,pre);//调用查询函数
				if (msg.x > 734 && msg.x < 1027 && msg.y > 491 && msg.y < 580)
				{
					output(p);
					loadimage(&index_exit, L"index_exit.jpg");
					putimage(0, 0, &index_exit);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
				}
			}
		}
	}
}

//文件保存函数
void Save(Node* p)
{
	FILE* fp;
	fopen_s(&fp, "allinfo.dat", "wb");
	fclose(fp);
	fopen_s(&fp, "allinfo.dat", "ab+");
	Node* temp = p->next;
	//向文件输出全局变量
	while (temp)
	{
		fwrite(temp->flag, sizeof(wchar_t)*10, 1, fp);
		fwrite(temp->type, sizeof(wchar_t) * 10, 1, fp);
		fwrite(temp->money, sizeof(wchar_t) * 100, 1, fp);
		fwrite(temp->time, sizeof(wchar_t) * 100, 1, fp);
		temp = temp->next;
	}
	fclose(fp);
}

//添加记录函数
void Add(Node* &p,Node* &pre)
{
	time_t curr_time;    //系统时间 
	time(&curr_time);
	tm* curr_tm; 
	curr_tm = localtime(&curr_time);
	wchar_t flag_zhichu[10];
	wcscpy_s(flag_zhichu, L"1");
	wchar_t flag_shouru[10];
	wcscpy_s(flag_shouru, L"0");
	loadimage(&index_add, L"index_add.jpg");
	putimage(0, 0, &index_add);
	Sleep(100);
	loadimage(&add, L"add.jpg");//导入初始界面
	putimage(0, 0, &add);
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)//鼠标点击特定区域，即“支出”按钮所在区域
				{
					loadimage(&add_zhichu, L"add_zhichu.jpg");
					putimage(0, 0, &add_zhichu);
					Node* temp = (Node*)malloc(sizeof(Node));
					InputBox(temp->type, 2, _T("请选择支出类型：1.伙食；2.购物；3.日用；4.交通；5.礼金（输入数字即可）"));
					InputBox(temp->money, 100, _T("请输入支出金额（可包含小数）"));
					wcscpy(temp->flag, flag_zhichu);
					wcsftime(temp->time, 50, L"%B %d,%Y", curr_tm);
					temp->next =NULL;
					pre->next = temp;
					pre = temp;  //pre指针的改变需要使用&
					MessageBox(NULL, _T("添加成功！"), _T("添加记录"), MB_SETFOREGROUND);
					Save(p);
				}

				if (msg.x > 113 && msg.x <315 && msg.y > 369 && msg.y < 457)//鼠标点击特定区域，即“收入”按钮所在区域
				{
					loadimage(&add_shouru, L"add_shouru.jpg");
					putimage(0, 0, &add_shouru);
					Node* temp = (Node*)malloc(sizeof(Node));
					InputBox(temp->type, 2, _T("请选择收入类型：1.工资 2.其他（输入数字即可）"));
					
					InputBox(temp->money, 100, _T("请输入收入金额（可包含小数）"));
					wcscpy(temp->flag, flag_shouru);
					wcsftime(temp->time, 5000, L"%B %d,%Y", curr_tm);
					temp->next = NULL;
					pre->next = temp;
					pre = temp;
					MessageBox(NULL, _T("添加成功！"), _T("添加记录"), MB_SETFOREGROUND);
					Save(p);
				}
				
				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//鼠标点击返回按钮
				{
					loadimage(&add_exit, L"add_exit.jpg");
					putimage(0, 0, &add_exit);
					Sleep(100);
					Select_MainMenu(p,pre);
				}
			}
		}
	}
}

//查询记录函数
void Search(struct record* p, Node* pre)
{
	wchar_t flag_zhichu[10];
	wcscpy_s(flag_zhichu, L"1");
	wchar_t flag_shouru[10];
	wcscpy_s(flag_shouru, L"0");
	wchar_t type_1[10];
	wcscpy_s(type_1, L"1");
	wchar_t type_2[10];
	wcscpy_s(type_2, L"2");
	wchar_t type_3[10];
	wcscpy_s(type_3, L"3");
	wchar_t type_4[10];
	wcscpy_s(type_4, L"4");
	wchar_t type_5[10];
	wcscpy_s(type_5, L"5");
	loadimage(&index_search, L"index_search.jpg");//导入初始界面
	putimage(0, 0, &index_search);
	Sleep(100);
	loadimage(&search, L"search.jpg");//导入初始界面
	putimage(0, 0, &search);
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)//鼠标点击特定区域，即“支出”按钮所在区域
				{
					loadimage(&search_zhichu, L"search_zhichu.jpg");
					putimage(0, 0, &search_zhichu);
					int position_x = 409;//“序号”横坐标
					int position_y = 151;//“序号”纵坐标
					setbkmode(TRANSPARENT);//设置字体背景为透明
					settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
					settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
					outtextxy(position_x, position_y, _T("序号             时间               类型             金额"));//显示表格第一行表头
					wchar_t search_type[10];//临时保存查询方式的序号
					InputBox(search_type, 10, _T("请选择查询的方式：1.按种类查询；2.按金额区间查询；3.无条件全输出（输入数字即可）"));

					int j = -1;//j用于记录查询方式的序号
					if (wcscmp(search_type, L"1") == 0)
						j = 1;
					else if (wcscmp(search_type, L"2") == 0)
						j = 2;
					else if (wcscmp(search_type, L"3") == 0)
						j = 3;
					else //说明输入的数字没有在查询方式序号的范围内 
						MessageBox(NULL, _T("请重新输入"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);


					if (j == 1 || j == 2 || j == 3)
					{
						switch (j)
						{
						case 1:    //按种类查询
						{
							wchar_t type[10]; //临时保存按种类查询之种类的编号
							InputBox(type, 10, _T("请选择种类：1.伙食；2.购物；3.日用；4.交通；5.礼金（输入数字即可）"));
							int i = 1; //i为输出表格中的序号（int类型）
							wchar_t num[10];//临时保存输出序号（wchar_t类型）

							if (!wcscoll(type, type_1))  //类型为伙食
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_1))  //根据flag筛选“支出”节点且支出节点的种类为“伙食”
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											outtextxy(793, position_y, _T("伙食"));
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录1"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else if (!wcscoll(type, type_2))  //类型为购物
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_2))  //根据flag筛选“支出”节点,且支出节点为“购物”
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											outtextxy(793, position_y, _T("购物"));
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else if (!wcscoll(type, type_3))  //类型为日用
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //记录中是否有属于目标种类的节点的标记，0为没有，1为有
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_3))  //根据flag筛选“支出”节点,且节点种类为日用
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											outtextxy(793, position_y, _T("日用"));
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else if (!wcscoll(type, type_4))  //类型为交通
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_4))  //根据flag筛选“支出”节点且节点种类为“交通”
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											outtextxy(793, position_y, _T("交通"));
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else if (!wcscoll(type, type_5))  //类型为礼金
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_5))  //根据flag筛选“支出”节点，且种类为“礼金”
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											outtextxy(793, position_y, _T("礼金"));
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录5"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else  MessageBox(NULL, _T("输入数字错误，请重新输入"), _T("排序"), MB_ICONSTOP | MB_SETFOREGROUND);
						}

						case 2:  //按金额区间查询
						{
							wchar_t type[10]; //临时保存按金额区间查询之种类的序号
							InputBox(type, 10, _T("请选择金额区间：1.【0-100】；2.【101-200】；3.【200+】（输入区间前的数字代号即可）"));
							wchar_t num[10]; //临时保存输出序号（wchar_t类型）
							int i = 1;//i为输出表格中的编号（int 类型）
							if (!wcscoll(type, type_1))  //金额区间为【0-100】
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //记录中是否有处于目标金额区间的节点的标记，0为没有，1为有
									while (temp)
									{
										double money;  //money 为节点中金额的数字（int 类型）
										money = wcstod(temp->money, NULL);
										if (money > 0 && money <= 100)  //根据flag筛选“支出”节点
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											//显示种类
											{if (!wcscoll(temp->type, type_1))  //类型为伙食
												outtextxy(793, position_y, _T("伙食"));
											if (!wcscoll(temp->type, type_2))  //类型为购物
												outtextxy(793, position_y, _T("购物"));
											if (!wcscoll(temp->type, type_3))  //类型为日用
												outtextxy(793, position_y, _T("日用"));
											if (!wcscoll(temp->type, type_4))  //类型为交通
												outtextxy(793, position_y, _T("交通"));
											if (!wcscoll(temp->type, type_5))  //类型为礼金
												outtextxy(793, position_y, _T("礼金"));
											}
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有处于目标金额区间的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else if (!wcscoll(type, type_2)) //金额区间为【101-200】
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //记录中是否有处于目标金额区间的节点的标记，0为没有，1为有
									while (temp)
									{
										double money;  //money 为节点中金额的数字（int 类型）
										money = wcstod(temp->money, NULL);
										if (money >= 101 && money <= 200)  //节点的金额在目标区间里
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											//显示种类
											{if (!wcscoll(temp->type, type_1))  //类型为伙食
												outtextxy(793, position_y, _T("伙食"));
											if (!wcscoll(temp->type, type_2))  //类型为购物
												outtextxy(793, position_y, _T("购物"));
											if (!wcscoll(temp->type, type_3))  //类型为日用
												outtextxy(793, position_y, _T("日用"));
											if (!wcscoll(temp->type, type_4))  //类型为交通
												outtextxy(793, position_y, _T("交通"));
											if (!wcscoll(temp->type, type_5))  //类型为礼金
												outtextxy(793, position_y, _T("礼金"));
											}
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有处于目标金额区间的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else if (!wcscoll(type, type_3)) //金额区间为【200+】
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //记录中是否有处于目标金额区间的节点的标记，0为没有，1为有
									while (temp)
									{
										double money;  //money 为节点中金额的数字（int 类型）
										money = wcstod(temp->money, NULL);
										if (money > 200)  //节点的金额在目标区间里
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											//显示种类
											{if (!wcscoll(temp->type, type_1))  //类型为伙食
												outtextxy(793, position_y, _T("伙食"));
											if (!wcscoll(temp->type, type_2))  //类型为购物
												outtextxy(793, position_y, _T("购物"));
											if (!wcscoll(temp->type, type_3))  //类型为日用
												outtextxy(793, position_y, _T("日用"));
											if (!wcscoll(temp->type, type_4))  //类型为交通
												outtextxy(793, position_y, _T("交通"));
											if (!wcscoll(temp->type, type_5))  //类型为礼金
												outtextxy(793, position_y, _T("礼金"));
											}
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有处于目标金额区间的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else  MessageBox(NULL, _T("输入数字错误，请重新输入"), _T("排序"), MB_ICONSTOP | MB_SETFOREGROUND);
							break;
						}

						case 3:  //无条件全输出
						{
							Node* temp = p->next;
							int i = 1; //i为输出表格中的序号（int类型）
							wchar_t num[10];//临时保存输出序号（wchar_t类型）
							if (temp)
							{
								int flag = 0; //是否有“支出”记录的标记，0为没有，1为有
								while (temp)
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0)  //根据flag筛选“支出”节点
									{
										flag = 1;
										if (i == 1)
											wcscpy_s(num, L"1");
										if (i == 2)
											wcscpy_s(num, L"2");
										if (i == 3)
											wcscpy_s(num, L"3");
										if (i == 4)
											wcscpy_s(num, L"4");
										if (i == 5)
											wcscpy_s(num, L"5");
										if (i == 6)
											wcscpy_s(num, L"6");
										if (i == 7)
											wcscpy_s(num, L"7");
										if (i == 8)
											wcscpy_s(num, L"8");
										if (i == 9)
											wcscpy_s(num, L"9");
										if (i == 10)
											wcscpy_s(num, L"10");
										position_y += 20;//向下推一行
										outtextxy(424, position_y, num);//显示序号
										outtextxy(590, position_y, temp->time);//显示记录时间
										// 输出种类
										if (!wcscoll(temp->type, type_1))  //类型为伙食
											outtextxy(793, position_y, _T("伙食"));
										if (!wcscoll(temp->type, type_2))  //类型为购物
											outtextxy(793, position_y, _T("购物"));
										if (!wcscoll(temp->type, type_3))  //类型为日用
											outtextxy(793, position_y, _T("日用"));
										if (!wcscoll(temp->type, type_4))  //类型为交通
											outtextxy(793, position_y, _T("交通"));
										if (!wcscoll(temp->type, type_5))  //类型为礼金
											outtextxy(793, position_y, _T("礼金"));
										//输出种类结束
										outtextxy(988, position_y, temp->money);//显示金额
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
								if (flag == 0)  MessageBox(NULL, _T("没有“支出”记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							break;
						}
						}
					}
				}

				if (msg.x > 113 && msg.x < 315 && msg.y > 369 && msg.y < 457)//鼠标点击特定区域，即“收入”按钮所在区域
				{
					loadimage(&search_shouru, L"search_shouru.jpg");
					putimage(0, 0, &search_shouru);
					int position_x = 409;//“序号”横坐标
					int position_y = 151;//“序号”纵坐标
					setbkmode(TRANSPARENT);//设置字体背景为透明
					settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
					settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
					outtextxy(position_x, position_y, _T("序号             时间               类型             金额"));//显示表格第一行表头
					wchar_t search_type[10];//临时保存查询方式的序号
					InputBox(search_type, 10, _T("请选择查询的方式：1.按种类查询；2.按金额区间查询3.无条件全输出（输入数字即可）"));

					int j = -1;//j用于记录查询方式的序号
					if (wcscmp(search_type, L"1") == 0)
						j = 1;
					else if (wcscmp(search_type, L"2") == 0)
						j = 2;
					else if (wcscmp(search_type, L"3") == 0)
						j = 3;
					else //说明输入的数字没有在查询方式序号的范围内 
						MessageBox(NULL, _T("请重新输入"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);


					if (j == 1 || j == 2 || j == 3)
					{
						switch (j)
						{
						case 1:    //按种类查询
						{
							wchar_t type[10]; //临时保存按种类查询之种类的编号
							InputBox(type, 10, _T("请选择种类：1.工资；2.其他（输入数字即可）"));
							int i = 1; //i为输出表格中的序号（int类型）
							wchar_t num[10];//临时保存输出序号（wchar_t类型）

							if (!wcscoll(type, type_1))  //类型为工资
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_shouru) == 0 && !wcscoll(temp->type, type_1))  //根据flag筛选“收入”节点且支出节点的种类为“工资”
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											outtextxy(793, position_y, _T("工资"));
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录1"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							if (!wcscoll(type, type_2))  //类型为其他
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_shouru) == 0 && !wcscoll(temp->type, type_2))  //根据flag筛选“收入”节点,且收入节点为“其他”
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											outtextxy(793, position_y, _T("其他"));
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}
						}

						case 2:  //按金额区间查询
						{
							wchar_t type[10]; //临时保存按金额区间查询之种类的序号
							InputBox(type, 10, _T("请选择金额区间：1.【0-100】；2.【101-200】；3.【200+】（输入区间前的数字代号即可）"));
							wchar_t num[10]; //临时保存输出序号（wchar_t类型）
							int i = 1;//i为输出表格中的编号（int 类型）

							if (!wcscoll(type, type_1))  //金额区间为【0-100】
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //记录中是否有处于目标金额区间的节点的标记，0为没有，1为有
									while (temp)
									{
										double money;  //money 为节点中金额的数字（int 类型）
										money = wcstod(temp->money, NULL);
										if (money > 0 && money <= 100 && wcscoll(temp->flag, flag_shouru) == 0)  //根据flag筛选“收入”节点，且金额处在【0-100】
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											//显示种类
											{if (!wcscoll(temp->type, type_1))  //类型为工资
												outtextxy(793, position_y, _T("工资"));
											if (!wcscoll(temp->type, type_2))  //类型为其他
												outtextxy(793, position_y, _T("其他"));
											}
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有处于目标金额区间的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else if (!wcscoll(type, type_2)) //金额区间为【101-200】
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //记录中是否有处于目标金额区间的节点的标记，0为没有，1为有
									while (temp)
									{
										double money;  //money 为节点中金额的数字（int 类型）
										money = wcstod(temp->money, NULL);
										if (money >= 101 && money <= 200 && wcscoll(temp->flag, flag_shouru) == 0)  //筛选出“收入”节点，且节点的金额在目标区间里
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											//显示种类
											{if (!wcscoll(temp->type, type_1))  //类型为伙食
												outtextxy(793, position_y, _T("伙食"));
											if (!wcscoll(temp->type, type_2))  //类型为购物
												outtextxy(793, position_y, _T("购物"));
											if (!wcscoll(temp->type, type_3))  //类型为日用
												outtextxy(793, position_y, _T("日用"));
											if (!wcscoll(temp->type, type_4))  //类型为交通
												outtextxy(793, position_y, _T("交通"));
											if (!wcscoll(temp->type, type_5))  //类型为礼金
												outtextxy(793, position_y, _T("礼金"));
											}
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有处于目标金额区间的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else if (!wcscoll(type, type_3)) //金额区间为【200+】
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //记录中是否有处于目标金额区间的节点的标记，0为没有，1为有
									while (temp)
									{
										double money;  //money 为节点中金额的数字（int 类型）
										money = wcstod(temp->money, NULL);
										if (money > 200 && wcscoll(temp->flag, flag_shouru) == 0)  //筛选“收入”节点，节点的金额【200+】
										{
											flag = 1;
											if (i == 1)
												wcscpy_s(num, L"1");
											if (i == 2)
												wcscpy_s(num, L"2");
											if (i == 3)
												wcscpy_s(num, L"3");
											if (i == 4)
												wcscpy_s(num, L"4");
											if (i == 5)
												wcscpy_s(num, L"5");
											if (i == 6)
												wcscpy_s(num, L"6");
											if (i == 7)
												wcscpy_s(num, L"7");
											if (i == 8)
												wcscpy_s(num, L"8");
											if (i == 9)
												wcscpy_s(num, L"9");
											if (i == 10)
												wcscpy_s(num, L"10");
											position_y += 20;//向下推一行
											outtextxy(424, position_y, num);//显示序号
											outtextxy(590, position_y, temp->time);//显示记录时间
											//显示种类
											{if (!wcscoll(temp->type, type_1))  //类型为伙食
												outtextxy(793, position_y, _T("伙食"));
											if (!wcscoll(temp->type, type_2))  //类型为购物
												outtextxy(793, position_y, _T("购物"));
											if (!wcscoll(temp->type, type_3))  //类型为日用
												outtextxy(793, position_y, _T("日用"));
											if (!wcscoll(temp->type, type_4))  //类型为交通
												outtextxy(793, position_y, _T("交通"));
											if (!wcscoll(temp->type, type_5))  //类型为礼金
												outtextxy(793, position_y, _T("礼金"));
											}
											outtextxy(988, position_y, temp->money);//显示金额
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("没有处于目标金额区间的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							break;
						}

						case 3:  //无条件全输出
						{
							Node* temp = p->next;
							int i = 1; //i为输出表格中的序号（int类型）
							wchar_t num[10];//临时保存输出序号（wchar_t类型）
							if (temp)
							{
								int flag = 0; //是否有“收入”记录的标记，0为没有，1为有
								while (temp)
								{
									if (wcscoll(temp->flag, flag_shouru) == 0)  //根据flag筛选“收入”节点
									{
										flag = 1;
										if (i == 1)
											wcscpy_s(num, L"1");
										if (i == 2)
											wcscpy_s(num, L"2");
										if (i == 3)
											wcscpy_s(num, L"3");
										if (i == 4)
											wcscpy_s(num, L"4");
										if (i == 5)
											wcscpy_s(num, L"5");
										if (i == 6)
											wcscpy_s(num, L"6");
										if (i == 7)
											wcscpy_s(num, L"7");
										if (i == 8)
											wcscpy_s(num, L"8");
										if (i == 9)
											wcscpy_s(num, L"9");
										if (i == 10)
											wcscpy_s(num, L"10");
										position_y += 20;//向下推一行
										outtextxy(424, position_y, num);//显示序号
										outtextxy(590, position_y, temp->time);//显示记录时间
										// 输出种类
										if (!wcscoll(temp->type, type_1))  //类型为工资
											outtextxy(793, position_y, _T("工资"));
										if (!wcscoll(temp->type, type_2))  //类型为收入
											outtextxy(793, position_y, _T("收入"));
										//输出种类结束
										outtextxy(988, position_y, temp->money);//显示金额
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
								if (flag == 0)  MessageBox(NULL, _T("没有“支出”记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							else MessageBox(NULL, _T("记录为空"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							break;
						}
						}
					}
				}

				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//鼠标点击返回按钮
				{
					loadimage(&delet_exit, L"delet_exit.jpg");
					putimage(0, 0, &delet_exit);
					Sleep(100);
					Select_MainMenu(p, pre);
				}
			}
		}
	}
}

//排序函数
void Sort(struct record* p,Node* pre)
{
	wchar_t flag_zhichu[10];
	wcscpy_s(flag_zhichu, L"1");
	wchar_t flag_shouru[10];
	wcscpy_s(flag_shouru, L"0");
	wchar_t type_1[10];
	wcscpy_s(type_1, L"1");
	wchar_t type_2[10];
	wcscpy_s(type_2, L"2");
	wchar_t type_3[10];
	wcscpy_s(type_3, L"3");
	wchar_t type_4[10];
	wcscpy_s(type_4, L"4");
	wchar_t type_5[10];
	wcscpy_s(type_5, L"5");
	loadimage(&index_sort, L"index_sort.jpg");//导入初始界面
	putimage(0, 0, &index_sort);
	Sleep(100);
	loadimage(&sort, L"sort.jpg");//导入初始界面
	putimage(0, 0, &sort);
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)//鼠标点击特定区域，即“支出”按钮所在区域
				{
					loadimage(&sort_zhichu, L"sort_zhichu.jpg");
					putimage(0, 0, &sort_zhichu);
					int position_x = 409;//“序号”横坐标
					int position_y = 151;//“序号”纵坐标
					setbkmode(TRANSPARENT);//设置字体背景为透明
					settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
					settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
					outtextxy(position_x, position_y, _T("序号             时间               类型             金额"));//显示表格第一行表头
					wchar_t search_type[10];//临时保存查询方式的序号
					InputBox(search_type, 10, _T("请选择排序方式：1.某一种类单独排序；2.支出全种类总排序（输入数字即可）"));
					int j = -1;//j用于记录查询方式的序号
					if (wcscmp(search_type, L"1") == 0)
						j = 1;
					else if (wcscmp(search_type, L"2") == 0)
						j = 2;
					else //说明输入的数字没有在查询方式序号的范围内 
						MessageBox(NULL, _T("请重新输入"), _T("排序"), MB_ICONSTOP | MB_SETFOREGROUND);
					if (j == 1 || j == 2)
					{
						switch (j)
						{
						case 1:  //某一种类单独排序
						{
							wchar_t type[10]; //临时保存按种类排序之种类的编号
							InputBox(type, 10, _T("请选择种类：1.伙食；2.购物；3.日用；4.交通；5.礼金（输入数字即可）"));

							if (!wcscoll(type, type_1))  //类型为伙食
							{
								int i = 0; //i为temp1链表的元素个数
								wchar_t num[10];//临时保存输出序号（wchar_t类型）
								Node* temp = p->next;
								Node* temp1 = (Node*)malloc(sizeof(Node));  //使用temp1作为“伙食”类链表的头结点
								temp1->next = NULL;
								int flag = 0;
								if (temp)
								{
									while (temp)  //提取总链表中的“工资”记录
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_1))  //根据flag筛选“支出”节点且种类为“伙食”
										{
											flag = 1;
											//头插法建立“支出”链表
											Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11为temp1链表建立过程中的辅助节点
											wcscpy_s(temp11->flag, temp->flag);
											wcscpy_s(temp11->type, temp->type);
											wcscpy_s(temp11->money, temp->money);
											wcscpy_s(temp11->time, temp->time);
											temp11->next = temp1->next;
											temp1->next = temp11;
											//头插法结束
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
								}
								if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("排序"), MB_ICONSTOP | MB_SETFOREGROUND);
								else    //存在“伙食”种类的记录
								{
									for (int k = 1; k <= i; k++)  //冒泡从大到小排序
									{
										Node* t = temp1;
										while (t->next->next)
										{
											int  next_num = _wtoi(t->next->money);
											int next_next_num = _wtoi(t->next->next->money);
											if (next_num < next_next_num) // 小的往后放
											{
												Node* r1 = t->next;
												Node* r2 = t->next->next;
												r1->next = r2->next;
												r2->next = r1;
												t->next = r2;
											}

											t = t->next;
										}
									}
									int j = 1; //i为输出表格中的序号（int类型）
									wchar_t num[10];//临时保存输出序号（wchar_t类型）
									Node* temp2 = temp1->next;  //temp111为输出表格时的辅助指针
									//输出表格
									while (temp2)
									{
										if (j == 1)
											wcscpy_s(num, L"1");
										if (j == 2)
											wcscpy_s(num, L"2");
										if (j == 3)
											wcscpy_s(num, L"3");
										if (j == 4)
											wcscpy_s(num, L"4");
										if (j == 5)
											wcscpy_s(num, L"5");
										if (j == 6)
											wcscpy_s(num, L"6");
										if (j == 7)
											wcscpy_s(num, L"7");
										if (j == 8)
											wcscpy_s(num, L"8");
										if (j == 9)
											wcscpy_s(num, L"9");
										if (j == 10)
											wcscpy_s(num, L"10");
										position_y += 20;//向下推一行
										outtextxy(424, position_y, num);//显示序号
										outtextxy(590, position_y, temp2->time);//显示记录时间
										outtextxy(793, position_y, _T("伙食"));
										outtextxy(988, position_y, temp2->money);//显示金额
										temp2 = temp2->next;
										j++;
									}
									//输出表格结束
									MessageBox(NULL, _T("排序成功！"), _T("排序"), MB_SETFOREGROUND);
								}
							}

							else if (!wcscoll(type, type_2))  //类型为购物
							{
								int i = 0; //i为temp1链表的元素个数
								wchar_t num[10];//临时保存输出序号（wchar_t类型）
								Node* temp = p->next;
								Node* temp1 = (Node*)malloc(sizeof(Node));  //使用temp1作为“购物”类链表的头结点
								temp1->next = NULL;
								int flag = 0;
								if (temp)
								{
									while (temp)  //提取总链表中的“购物”记录
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_2))  //根据flag筛选“支出”节点且支出节点的种类为“伙食”
										{
											flag = 1;
											//头插法建立“购物”链表
											Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11为temp1链表建立过程中的辅助节点
											wcscpy_s(temp11->flag, temp->flag);
											wcscpy_s(temp11->type, temp->type);
											wcscpy_s(temp11->money, temp->money);
											wcscpy_s(temp11->time, temp->time);
											temp11->next = temp1->next;
											temp1->next = temp11;
											//头插法结束
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
								}
								if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								else    //存在“购物”种类的记录
								{
									for (int k = 1; k <= i; k++)  //冒泡从大到小排序
									{
										Node* t = temp1;
										while (t->next->next)
										{
											int  next_num = _wtoi(t->next->money);
											int next_next_num = _wtoi(t->next->next->money);
											if (next_num < next_next_num) // 小的往后放
											{
												Node* r1 = t->next;
												Node* r2 = t->next->next;
												r1->next = r2->next;
												r2->next = r1;
												t->next = r2;
											}

											t = t->next;
										}
									}
									int j = 1; //i为输出表格中的序号（int类型）
									wchar_t num[10];//临时保存输出序号（wchar_t类型）
									Node* temp2 = temp1->next;  //temp111为输出表格时的辅助指针
									//输出表格
									while (temp2)
									{
										if (j == 1)
											wcscpy_s(num, L"1");
										if (j == 2)
											wcscpy_s(num, L"2");
										if (j == 3)
											wcscpy_s(num, L"3");
										if (j == 4)
											wcscpy_s(num, L"4");
										if (j == 5)
											wcscpy_s(num, L"5");
										if (j == 6)
											wcscpy_s(num, L"6");
										if (j == 7)
											wcscpy_s(num, L"7");
										if (j == 8)
											wcscpy_s(num, L"8");
										if (j == 9)
											wcscpy_s(num, L"9");
										if (j == 10)
											wcscpy_s(num, L"10");
										position_y += 20;//向下推一行
										outtextxy(424, position_y, num);//显示序号
										outtextxy(590, position_y, temp2->time);//显示记录时间
										outtextxy(793, position_y, _T("购物"));
										outtextxy(988, position_y, temp2->money);//显示金额
										temp2 = temp2->next;
										j++;
									}
									//输出表格结束
									MessageBox(NULL, _T("排序成功！"), _T("排序"), MB_SETFOREGROUND);
								}
							}

							else if (!wcscoll(type, type_3))  //类型为日用
							{
							int i = 0; //i为temp1链表的元素个数
							wchar_t num[10];//临时保存输出序号（wchar_t类型）
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //使用temp1作为“日用”类链表的头结点
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //提取总链表中的“日用”记录
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_3))  //根据flag筛选“支出”节点且支出节点的种类为“日用”
									{
										flag = 1;
										//头插法建立“日用”链表
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11为temp1链表建立过程中的辅助节点
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//头插法结束
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //存在“日用”种类的记录
							{
								for (int k = 1; k <= i; k++)  //冒泡从大到小排序
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // 小的往后放
										{
											Node* r1 = t->next;
											Node* r2 = t->next->next;
											r1->next = r2->next;
											r2->next = r1;
											t->next = r2;
										}

										t = t->next;
									}
								}
								int j = 1; //i为输出表格中的序号（int类型）
								wchar_t num[10];//临时保存输出序号（wchar_t类型）
								Node* temp2 = temp1->next;  //temp111为输出表格时的辅助指针
								//输出表格
								while (temp2)
								{
									if (j == 1)
										wcscpy_s(num, L"1");
									if (j == 2)
										wcscpy_s(num, L"2");
									if (j == 3)
										wcscpy_s(num, L"3");
									if (j == 4)
										wcscpy_s(num, L"4");
									if (j == 5)
										wcscpy_s(num, L"5");
									if (j == 6)
										wcscpy_s(num, L"6");
									if (j == 7)
										wcscpy_s(num, L"7");
									if (j == 8)
										wcscpy_s(num, L"8");
									if (j == 9)
										wcscpy_s(num, L"9");
									if (j == 10)
										wcscpy_s(num, L"10");
									position_y += 20;//向下推一行
									outtextxy(424, position_y, num);//显示序号
									outtextxy(590, position_y, temp2->time);//显示记录时间
									outtextxy(793, position_y, _T("日用"));
									outtextxy(988, position_y, temp2->money);//显示金额
									temp2 = temp2->next;
									j++;
								}
								//输出表格结束
								MessageBox(NULL, _T("排序成功！"), _T("排序"), MB_SETFOREGROUND);
							}
							}

							else if (!wcscoll(type, type_4))  //类型为交通
							{
							int i = 0; //i为temp1链表的元素个数
							wchar_t num[10];//临时保存输出序号（wchar_t类型）
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //使用temp1作为“交通”类链表的头结点
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //提取总链表中的“日用”记录
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_4))  //根据flag筛选“支出”节点且支出节点的种类为“交通”
									{
										flag = 1;
										//头插法建立“交通”链表
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11为temp1链表建立过程中的辅助节点
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//头插法结束
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //存在“交通”种类的记录
							{
								for (int k = 1; k <= i; k++)  //冒泡从大到小排序
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // 小的往后放
										{
											Node* r1 = t->next;
											Node* r2 = t->next->next;
											r1->next = r2->next;
											r2->next = r1;
											t->next = r2;
										}

										t = t->next;
									}
								}
								int j = 1; //i为输出表格中的序号（int类型）
								wchar_t num[10];//临时保存输出序号（wchar_t类型）
								Node* temp2 = temp1->next;  //temp111为输出表格时的辅助指针
								//输出表格
								while (temp2)
								{
									if (j == 1)
										wcscpy_s(num, L"1");
									if (j == 2)
										wcscpy_s(num, L"2");
									if (j == 3)
										wcscpy_s(num, L"3");
									if (j == 4)
										wcscpy_s(num, L"4");
									if (j == 5)
										wcscpy_s(num, L"5");
									if (j == 6)
										wcscpy_s(num, L"6");
									if (j == 7)
										wcscpy_s(num, L"7");
									if (j == 8)
										wcscpy_s(num, L"8");
									if (j == 9)
										wcscpy_s(num, L"9");
									if (j == 10)
										wcscpy_s(num, L"10");
									position_y += 20;//向下推一行
									outtextxy(424, position_y, num);//显示序号
									outtextxy(590, position_y, temp2->time);//显示记录时间
									outtextxy(793, position_y, _T("交通"));
									outtextxy(988, position_y, temp2->money);//显示金额
									temp2 = temp2->next;
									j++;
								}
								//输出表格结束
								MessageBox(NULL, _T("排序成功！"), _T("排序"), MB_SETFOREGROUND);
							}
							}

							else if (!wcscoll(type, type_5))  //类型为礼金
							{
							int i = 0; //i为temp1链表的元素个数
							wchar_t num[10];//临时保存输出序号（wchar_t类型）
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //使用temp1作为“礼金”类链表的头结点
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //提取总链表中的“礼金”记录
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_5))  //根据flag筛选“支出”节点且支出节点的种类为“礼金”
									{
										flag = 1;
										//头插法建立“礼金”链表
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11为temp1链表建立过程中的辅助节点
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//头插法结束
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //存在“礼金”种类的记录
							{
								for (int k = 1; k <= i; k++)  //冒泡从大到小排序
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // 小的往后放
										{
											Node* r1 = t->next;
											Node* r2 = t->next->next;
											r1->next = r2->next;
											r2->next = r1;
											t->next = r2;
										}

										t = t->next;
									}
								}
								int j = 1; //i为输出表格中的序号（int类型）
								wchar_t num[10];//临时保存输出序号（wchar_t类型）
								Node* temp2 = temp1->next;  //temp111为输出表格时的辅助指针
								//输出表格
								while (temp2)
								{
									if (j == 1)
										wcscpy_s(num, L"1");
									if (j == 2)
										wcscpy_s(num, L"2");
									if (j == 3)
										wcscpy_s(num, L"3");
									if (j == 4)
										wcscpy_s(num, L"4");
									if (j == 5)
										wcscpy_s(num, L"5");
									if (j == 6)
										wcscpy_s(num, L"6");
									if (j == 7)
										wcscpy_s(num, L"7");
									if (j == 8)
										wcscpy_s(num, L"8");
									if (j == 9)
										wcscpy_s(num, L"9");
									if (j == 10)
										wcscpy_s(num, L"10");
									position_y += 20;//向下推一行
									outtextxy(424, position_y, num);//显示序号
									outtextxy(590, position_y, temp2->time);//显示记录时间
									outtextxy(793, position_y, _T("礼金"));
									outtextxy(988, position_y, temp2->money);//显示金额
									temp2 = temp2->next;
									j++;
								}
								//输出表格结束
								MessageBox(NULL, _T("排序成功！"), _T("排序"), MB_SETFOREGROUND);
							}
							}

							else  MessageBox(NULL, _T("输入数字错误，请重新输入"), _T("排序"), MB_ICONSTOP | MB_SETFOREGROUND);

							break;
						}

						case 2:  //支出全种类总排序
						{
							int i = 0; //i为temp1链表的元素个数
							wchar_t num[10];//临时保存输出序号（wchar_t类型）
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //使用temp1作为支出链表的头结点
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //提取总链表中的支出记录
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0 )  //根据flag筛选“支出”节点
									{
										flag = 1;
										//头插法建立支出链表
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11为temp1链表建立过程中的辅助节点
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//头插法结束
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("没有支出的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //存在支出的记录
							{
								for (int k = 1; k <= i; k++)  //冒泡从大到小排序
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // 小的往后放
										{
											Node* r1 = t->next;
											Node* r2 = t->next->next;
											r1->next = r2->next;
											r2->next = r1;
											t->next = r2;
										}

										t = t->next;
									}
								}
								int j = 1; //i为输出表格中的序号（int类型）
								wchar_t num[10];//临时保存输出序号（wchar_t类型）
								Node* temp2 = temp1->next;  //temp111为输出表格时的辅助指针
								//输出表格
								while (temp2)
								{
									if (j == 1)
										wcscpy_s(num, L"1");
									if (j == 2)
										wcscpy_s(num, L"2");
									if (j == 3)
										wcscpy_s(num, L"3");
									if (j == 4)
										wcscpy_s(num, L"4");
									if (j == 5)
										wcscpy_s(num, L"5");
									if (j == 6)
										wcscpy_s(num, L"6");
									if (j == 7)
										wcscpy_s(num, L"7");
									if (j == 8)
										wcscpy_s(num, L"8");
									if (j == 9)
										wcscpy_s(num, L"9");
									if (j == 10)
										wcscpy_s(num, L"10");
									position_y += 20;//向下推一行
									outtextxy(424, position_y, num);//显示序号
									outtextxy(590, position_y, temp2->time);//显示记录时间
									// 输出种类
									if (!wcscoll(temp2->type, type_1))  //类型为伙食
										outtextxy(793, position_y, _T("伙食"));
									if (!wcscoll(temp2->type, type_2))  //类型为购物
										outtextxy(793, position_y, _T("购物"));
									if (!wcscoll(temp2->type, type_3))  //类型为日用
										outtextxy(793, position_y, _T("日用"));
									if (!wcscoll(temp2->type, type_4))  //类型为交通
										outtextxy(793, position_y, _T("交通"));
									if (!wcscoll(temp2->type, type_5))  //类型为礼金
										outtextxy(793, position_y, _T("礼金"));
									//输出种类结束
									outtextxy(988, position_y, temp2->money);//显示金额
									temp2 = temp2->next;
									j++;
								}
								//输出表格结束
								MessageBox(NULL, _T("排序成功！"), _T("排序"), MB_SETFOREGROUND);
							}
							break;
						}

						}

					}
				}

				if (msg.x > 113 && msg.x < 315 && msg.y > 369 && msg.y < 457)  //鼠标点击特定区域，即“收入”按钮所在区域
				{
					loadimage(&sort_shouru, L"sort_shouru.jpg");
					putimage(0, 0, &sort_shouru);
					int position_x = 409;//“序号”横坐标
					int position_y = 151;//“序号”纵坐标
					setbkmode(TRANSPARENT);//设置字体背景为透明
					settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
					settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
					outtextxy(position_x, position_y, _T("序号             时间               类型             金额"));//显示表格第一行表头
					wchar_t search_type[10];//临时保存查询方式的序号
					InputBox(search_type, 10, _T("请选择排序方式：1.某一种类单独排序；2.收入全种类总排序（输入数字即可）"));
					int j = -1;//j用于记录查询方式的序号
					if (wcscmp(search_type, L"1") == 0)
						j = 1;
					else if (wcscmp(search_type, L"2") == 0)
						j = 2;
					else //说明输入的数字没有在查询方式序号的范围内 
						MessageBox(NULL, _T("请重新输入"), _T("排序"), MB_ICONSTOP | MB_SETFOREGROUND);

					if (j == 1 || j == 2)
					{
						switch (j)
						{
						case 1:  //某一种类单独排序
						{
							wchar_t type[10]; //临时保存按种类排序之种类的编号
							InputBox(type, 10, _T("请选择种类：1.工资；2.其他（输入数字即可）"));                   

							if (!wcscoll(type, type_1))  //类型为工资
							{
								int i = 0; //i为temp1链表的元素个数
								wchar_t num[10];//临时保存输出序号（wchar_t类型）
								Node* temp = p->next;
								Node* temp1 = (Node*)malloc(sizeof(Node));  //使用temp1作为“工资”类链表的头结点
								temp1->next = NULL;
								int flag = 0;
								if (temp)
								{
									while (temp)  //提取总链表中的“工资”记录
									{
										if (wcscoll(temp->flag, flag_shouru) == 0 && !wcscoll(temp->type, type_1))  //根据flag筛选“收入”节点且支出节点的种类为“工资”
										{
											flag = 1;
											//头插法建立“工资”链表
											Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11为temp1链表建立过程中的辅助节点
											wcscpy_s(temp11->flag, temp->flag);
											wcscpy_s(temp11->type, temp->type);
											wcscpy_s(temp11->money, temp->money);
											wcscpy_s(temp11->time, temp->time);
											temp11->next = temp1->next;
											temp1->next = temp11;
											//头插法结束
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
								}
								if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								else    //存在“工资”种类的记录
								{
									for (int k = 1; k <= i; k++)  //冒泡从大到小排序
									{
										Node* t = temp1;
										while (t->next->next)
										{
											int  next_num = _wtoi(t->next->money);
											int next_next_num = _wtoi(t->next->next->money);
											if (next_num < next_next_num) // 小的往后放
											{
												Node* r1 = t->next;
												Node* r2 = t->next->next;
												r1->next = r2->next;
												r2->next = r1;
												t->next = r2;
											}

											t = t->next;
										}
									}
									int j = 1; //i为输出表格中的序号（int类型）
									wchar_t num[10];//临时保存输出序号（wchar_t类型）
									Node* temp2 = temp1->next;  //temp111为输出表格时的辅助指针
									//输出表格
									while (temp2)
									{
										if (j == 1)
											wcscpy_s(num, L"1");
										if (j == 2)
											wcscpy_s(num, L"2");
										if (j == 3)
											wcscpy_s(num, L"3");
										if (j == 4)
											wcscpy_s(num, L"4");
										if (j == 5)
											wcscpy_s(num, L"5");
										if (j == 6)
											wcscpy_s(num, L"6");
										if (j == 7)
											wcscpy_s(num, L"7");
										if (j == 8)
											wcscpy_s(num, L"8");
										if (j == 9)
											wcscpy_s(num, L"9");
										if (j == 10)
											wcscpy_s(num, L"10");
										position_y += 20;//向下推一行
										outtextxy(424, position_y, num);//显示序号
										outtextxy(590, position_y, temp2->time);//显示记录时间
										outtextxy(793, position_y, _T("工资"));
										outtextxy(988, position_y, temp2->money);//显示金额
										temp2 = temp2->next;
										j++;
									}
									//输出表格结束
									MessageBox(NULL, _T("排序成功！"), _T("排序"), MB_SETFOREGROUND);
								}
							}

							if (!wcscoll(type, type_2))  //类型为其他
							{
								int i = 0; //i为temp1链表的元素个数
								wchar_t num[10];//临时保存输出序号（wchar_t类型）
								Node* temp = p->next;
								Node* temp1 = (Node*)malloc(sizeof(Node));  //使用temp1作为“其他”类链表的头结点
								temp1->next = NULL;
								int flag = 0;
								if (temp)
								{
									while (temp)  //提取总链表中的“其他”记录
									{
										if (wcscoll(temp->flag, flag_shouru) == 0 && !wcscoll(temp->type, type_2))  //根据flag筛选“收入”节点且收入节点的种类为“其他”
										{
											flag = 1;
											//头插法建立“其他”链表
											Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11为temp1链表建立过程中的辅助节点
											wcscpy_s(temp11->flag, temp->flag);
											wcscpy_s(temp11->type, temp->type);
											wcscpy_s(temp11->money, temp->money);
											wcscpy_s(temp11->time, temp->time);
											temp11->next = temp1->next;
											temp1->next = temp11;
											//头插法结束
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
								}
								if (flag == 0)  MessageBox(NULL, _T("没有属于目标种类的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
								else    //存在“其他”种类的记录
								{
									for (int k = 1; k <= i; k++)  //冒泡从大到小排序
									{
										Node* t = temp1;
										while (t->next->next)
										{
											int  next_num = _wtoi(t->next->money);
											int next_next_num = _wtoi(t->next->next->money);
											if (next_num < next_next_num) // 小的往后放
											{
												Node* r1 = t->next;
												Node* r2 = t->next->next;
												r1->next = r2->next;
												r2->next = r1;
												t->next = r2;
											}

											t = t->next;
										}
									}
									int j = 1; //i为输出表格中的序号（int类型）
									wchar_t num[10];//临时保存输出序号（wchar_t类型）
									Node* temp2 = temp1->next;  //temp111为输出表格时的辅助指针
									//输出表格
									while (temp2)
									{
										if (j == 1)
											wcscpy_s(num, L"1");
										if (j == 2)
											wcscpy_s(num, L"2");
										if (j == 3)
											wcscpy_s(num, L"3");
										if (j == 4)
											wcscpy_s(num, L"4");
										if (j == 5)
											wcscpy_s(num, L"5");
										if (j == 6)
											wcscpy_s(num, L"6");
										if (j == 7)
											wcscpy_s(num, L"7");
										if (j == 8)
											wcscpy_s(num, L"8");
										if (j == 9)
											wcscpy_s(num, L"9");
										if (j == 10)
											wcscpy_s(num, L"10");
										position_y += 20;//向下推一行
										outtextxy(424, position_y, num);//显示序号
										outtextxy(590, position_y, temp2->time);//显示记录时间
										outtextxy(793, position_y, _T("其他"));
										outtextxy(988, position_y, temp2->money);//显示金额
										temp2 = temp2->next;
										j++;
									}
									//输出表格结束
									MessageBox(NULL, _T("排序成功！"), _T("排序"), MB_SETFOREGROUND);
								}
							}
						}

						case 2:   //收入全种类总排序
						{
							int i = 0; //i为temp1链表的元素个数
							wchar_t num[10];//临时保存输出序号（wchar_t类型）
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //使用temp1作为支出链表的头结点
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //提取总链表中的支出记录
								{
									if (wcscoll(temp->flag, flag_shouru) == 0)  //根据flag筛选“收入”节点
									{
										flag = 1;
										//头插法建立收入链表
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11为temp1链表建立过程中的辅助节点
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//头插法结束
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("没有收入的记录"), _T("查询记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //存在收入的记录
							{
								for (int k = 1; k <= i; k++)  //冒泡从大到小排序
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // 小的往后放
										{
											Node* r1 = t->next;
											Node* r2 = t->next->next;
											r1->next = r2->next;
											r2->next = r1;
											t->next = r2;
										}

										t = t->next;
									}
								}
								int j = 1; //i为输出表格中的序号（int类型）
								wchar_t num[10];//临时保存输出序号（wchar_t类型）
								Node* temp2 = temp1->next;  //temp111为输出表格时的辅助指针
								//输出表格
								while (temp2)
								{
									if (j == 1)
										wcscpy_s(num, L"1");
									if (j == 2)
										wcscpy_s(num, L"2");
									if (j == 3)
										wcscpy_s(num, L"3");
									if (j == 4)
										wcscpy_s(num, L"4");
									if (j == 5)
										wcscpy_s(num, L"5");
									if (j == 6)
										wcscpy_s(num, L"6");
									if (j == 7)
										wcscpy_s(num, L"7");
									if (j == 8)
										wcscpy_s(num, L"8");
									if (j == 9)
										wcscpy_s(num, L"9");
									if (j == 10)
										wcscpy_s(num, L"10");
									position_y += 20;//向下推一行
									outtextxy(424, position_y, num);//显示序号
									outtextxy(590, position_y, temp2->time);//显示记录时间
									// 输出种类
									if (!wcscoll(temp2->type, type_1))  //类型为工资
										outtextxy(793, position_y, _T("工资"));
									if (!wcscoll(temp2->type, type_2))  //类型为其他
										outtextxy(793, position_y, _T("其他"));
									//输出种类结束
									outtextxy(988, position_y, temp2->money);//显示金额
									temp2 = temp2->next;
									j++;
								}
								//输出表格结束
								MessageBox(NULL, _T("排序成功！"), _T("排序"), MB_SETFOREGROUND);
							}
							break;
						}
						}
					}
				}

				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//鼠标点击返回按钮
				{
					loadimage(&delet_exit, L"delet_exit.jpg");
					putimage(0, 0, &delet_exit);
					Sleep(100);
					Select_MainMenu(p, pre);
				}
			}
		}
	}
}

//删除函数
void Delete(struct record*& p, Node*& pre)
{
	wchar_t flag_zhichu[10];
	wcscpy_s(flag_zhichu, L"1");
	wchar_t flag_shouru[10];
	wcscpy_s(flag_shouru, L"0");
	wchar_t type_1[10];
	wcscpy_s(type_1, L"1");
	wchar_t type_2[10];
	wcscpy_s(type_2, L"2");
	wchar_t type_3[10];
	wcscpy_s(type_3, L"3");
	wchar_t type_4[10];
	wcscpy_s(type_4, L"4");
	wchar_t type_5[10];
	wcscpy_s(type_5, L"5");
	loadimage(&index_delete, L"index_delete.jpg");//导入初始界面
	putimage(0, 0, &index_delete);
	Sleep(100);
	loadimage(&delet, L"delet.jpg");//导入初始界面
	putimage(0, 0, &delet);
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)//鼠标点击特定区域，即“支出”按钮所在区域
				{
					loadimage(&delet_zhichu, L"delet_zhichu.jpg");
					putimage(0, 0, &delet_zhichu);
					int position_x = 409;//“序号”横坐标
					int position_y = 151;//“序号”纵坐标
					setbkmode(TRANSPARENT);//设置字体背景为透明
					settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
					settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
					outtextxy(position_x, position_y, _T("序号             时间               类型             金额"));//显示表格第一行表头
					wchar_t num[100];//临时保存输出序号
					Node* temp = p->next;
					int i = 1, j = -1;
					if (temp == NULL) MessageBox(NULL, _T("记录为空，请返回菜单添加记录！1"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);//无任何内容，直接弹窗提醒输入数据
					else
					{
						while (temp)  //输出原有记录
						{
							if (wcscoll(temp->flag, flag_zhichu) == 0)  //根据flag筛选“支出”节点
							{
								//枚举得到序号
								{if (i == 1)
									wcscpy_s(num, L"1");
								if (i == 2)
									wcscpy_s(num, L"2");
								if (i == 3)
									wcscpy_s(num, L"3");
								if (i == 4)
									wcscpy_s(num, L"4");
								if (i == 5)
									wcscpy_s(num, L"5");
								if (i == 6)
									wcscpy_s(num, L"6");
								if (i == 7)
									wcscpy_s(num, L"7");
								if (i == 8)
									wcscpy_s(num, L"8");
								if (i == 9)
									wcscpy_s(num, L"9");
								if (i == 10)
									wcscpy_s(num, L"10");
								}
								position_y += 20;//向下推一行
								outtextxy(424, position_y, num);//显示序号
								outtextxy(590, position_y, temp->time);//显示记录时间
								//显示种类
								{if (!wcscoll(temp->type, type_1))  //类型为伙食
									outtextxy(793, position_y, _T("伙食"));
								if (!wcscoll(temp->type, type_2))  //类型为购物
									outtextxy(793, position_y, _T("购物"));
								if (!wcscoll(temp->type, type_3))  //类型为日用
									outtextxy(793, position_y, _T("日用"));
								if (!wcscoll(temp->type, type_4))  //类型为交通
									outtextxy(793, position_y, _T("交通"));
								if (!wcscoll(temp->type, type_5))  //类型为礼金
									outtextxy(793, position_y, _T("礼金"));
								}

								outtextxy(988, position_y, temp->money);//显示金额
								temp = temp->next;
								i++;
							}
							else { temp = temp->next; }
						}
						//while循环输出原有记录结束

						i--;       //此时i代表有i个记录
						if (i == 0)   MessageBox(NULL, _T("记录为空，请返回菜单添加记录！2"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);//无任何内容，直接弹窗提醒输入数据
						else
						{
							wchar_t temp_number[10];//临时保存输入的序号
							InputBox(temp_number, 10, _T("请选择需要删除的日程序号"));
							//将wchar_t序号转化为int
							{
								if (wcscmp(temp_number, L"1") == 0)
									j = 1;
								if (wcscmp(temp_number, L"2") == 0)
									j = 2;
								if (wcscmp(temp_number, L"3") == 0)
									j = 3;
								if (wcscmp(temp_number, L"4") == 0)
									j = 4;
								if (wcscmp(temp_number, L"5") == 0)
									j = 5;
								if (wcscmp(temp_number, L"6") == 0)
									j = 6;
								if (wcscmp(temp_number, L"7") == 0)
									j = 7;
								if (wcscmp(temp_number, L"81") == 0)
									j = 8;
								if (wcscmp(temp_number, L"9") == 0)
									j = 9;
								if (wcscmp(temp_number, L"10") == 0)
									j = 10;
								if (j > i || j < 0)//说明输入的数字没有在所有日程序号的范围内 
									MessageBox(NULL, _T("请重新输入"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							if (j > 0 && j <= i)
							{
								if (j == 1 && i == 1)  //仅有一个节点，特殊处理pre
								{
									if (p->next->next == NULL)//总链表只有一个节点
									{
										pre = p;
										Node* deletnode = p->next;
										p->next = NULL;
										free(deletnode);
									}
									else  //只是支出仅有一个节点，“收入”也存在节点
									{
										Node* t = p->next;

										while (wcscoll(t->next->flag, flag_zhichu) != 0 && wcscoll(t->flag, flag_zhichu) != 0)  //考虑支出、收入节点交替输入的情况
										{
											t = t->next;
										}
										if (t->next->next == NULL)  //“支出”节点恰为最后一个节点
										{
											pre = t;
											Node* deletnode = t->next;
											t->next = NULL;
											free(deletnode);
										}
										else                       //“支出”节点仅有一个，同时其并非属于最后一个节点，不影响pre
										{

											if (p->next == t)    //“支出”节点位于总链表的第一个特殊判断
											{
												Node* deletnode = p->next;
												p->next = p->next->next;
												free(deletnode);
											}
											else        //“支出”节点不位于总链表的第一个
											{
												Node* deletnode = t->next;
												t->next = t->next->next;
												free(deletnode);
											}
										}
									}
									MessageBox(NULL, _T("删除成功！"), _T("删除记录"), MB_SETFOREGROUND);
									Save(p);
								}
								else if (j == 1 && i > 1)
								{
									Node* t = p->next;

									while (wcscoll(t->next->flag, flag_zhichu) != 0 && wcscoll(t->flag, flag_zhichu) != 0)  //考虑支出、收入节点交替输入的情况
									{
										t = t->next;
									}
									if (t->next->next == NULL)  //“支出”节点恰为最后一个节点
									{
										pre = t;
										Node* deletnode = t->next;
										t->next = NULL;
										free(deletnode);
									}
									else                       //“支出”节点仅有一个，同时其并非属于最后一个节点，不影响pre
									{

										if (p->next == t)    //“支出”节点位于总链表的第一个特殊判断
										{
											Node* deletnode = p->next;
											p->next = p->next->next;
											free(deletnode);
										}
										else        //“支出”节点不位于总链表的第一个
										{
											Node* deletnode = t->next;
											t->next = t->next->next;
											free(deletnode);
										}
									}
									MessageBox(NULL, _T("删除成功！"), _T("删除记录"), MB_SETFOREGROUND);
									Save(p);
								}
								else if (j == i) //j为“支出”链最后一个节点
								{
									Node* t = p->next;
									int count = 1;
									while (t && count < j - 1)  //将t指向待删除结点的前一个结点
									{
										if (wcscoll(t->flag, flag_zhichu) == 0)
										{
											t = t->next;
											count++;
										}
										else
										{
											t = t->next;
										}
									}

									while (wcscoll(t->flag, flag_zhichu) != 0)  //考虑支出、收入节点交替输入的情况
									{
										t = t->next;
									}

									if (t->next->next == NULL)   //“支出”链最后一个恰为总链表最后一个
									{
										pre = t;
										Node* deletnode = t->next;
										t->next = NULL;
										free(deletnode);
									}
									else                       //“支出”链最后一个并非是总链表的最后一个，不影响pre
									{
										while (wcscoll(t->next->flag, flag_zhichu) != 0)  //考虑支出、收入节点交替输入的情况
										{
											t = t->next;
										}
										Node* deletnode = t->next;
										t->next = t->next->next;
										free(deletnode);
									}
									MessageBox(NULL, _T("删除成功！"), _T("删除记录"), MB_SETFOREGROUND);
									Save(p);
								}
								else   //j为一般情况，即j！=i
								{
									Node* t = p->next;
									int count = 1;
									while (t && count < j - 1)  //将temp指向待删除结点的前一个结点
									{
										if (wcscoll(t->flag, flag_zhichu) == 0) //筛选出“支出”节点
										{
											t = t->next;
											count++;
										}
										else
										{
											t = t->next;
										}
									}
									while (wcscoll(t->next->flag, flag_zhichu) != 0)  //考虑支出、收入节点交替输入的情况
									{
										t = t->next;
									}
									Node* deletnode = t->next;
									t->next = t->next->next;
									free(deletnode);
									MessageBox(NULL, _T("删除成功！"), _T("删除记录"), MB_SETFOREGROUND);
									Save(p);//调用文件保存函数
								}
							}
							else { MessageBox(NULL, _T("输入序号错误，请重新输入"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND); }
						}
					}

				}

				if (msg.x > 113 && msg.x < 315 && msg.y > 369 && msg.y < 457)//鼠标点击特定区域，即“收入”按钮所在区域
				{
					loadimage(&delet_shouru, L"delet_shouru.jpg");
					putimage(0, 0, &delet_shouru);
					int position_x = 409;//“序号”横坐标
					int position_y = 151;//“序号”纵坐标
					setbkmode(TRANSPARENT);//设置字体背景为透明
					settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
					settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
					outtextxy(position_x, position_y, _T("序号             时间               类型             金额"));//显示表格第一行表头
					wchar_t num[100];//临时保存输出序号
					Node* temp = p->next;
					int i = 1, j = -1;
					if (temp == NULL) MessageBox(NULL, _T("记录为空，请返回菜单添加记录！1"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);//无任何内容，直接弹窗提醒输入数据
					else
					{
						while (temp)  //输出原有记录
						{
							if (wcscoll(temp->flag, flag_shouru) == 0)  //根据flag筛选“收入”节点
							{
								//枚举得到序号
								{if (i == 1)
									wcscpy_s(num, L"1");
								if (i == 2)
									wcscpy_s(num, L"2");
								if (i == 3)
									wcscpy_s(num, L"3");
								if (i == 4)
									wcscpy_s(num, L"4");
								if (i == 5)
									wcscpy_s(num, L"5");
								if (i == 6)
									wcscpy_s(num, L"6");
								if (i == 7)
									wcscpy_s(num, L"7");
								if (i == 8)
									wcscpy_s(num, L"8");
								if (i == 9)
									wcscpy_s(num, L"9");
								if (i == 10)
									wcscpy_s(num, L"10");
								}
								position_y += 20;//向下推一行
								outtextxy(424, position_y, num);//显示序号
								outtextxy(590, position_y, temp->time);//显示记录时间
								//输出种类
								if (!wcscoll(temp->type, type_1))  //类型为工资
									outtextxy(793, position_y, _T("工资"));
								if (!wcscoll(temp->type, type_2))  //类型为其他
									outtextxy(793, position_y, _T("其他"));
								//输出种类结束
								outtextxy(988, position_y, temp->money);//显示金额
								temp = temp->next;
								i++;
							}
							else { temp = temp->next; }
						}//while循环输出原有记录结束

						i--;//此时i代表有i个结果

						if (i == 0)  MessageBox(NULL, _T("记录为空，请返回菜单添加记录！2"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);//无任何内容，直接弹窗提醒输入数据
						else
						{
							wchar_t temp_number[10];//临时保存输入的序号
							InputBox(temp_number, 10, _T("请选择需要删除的序号"));
							//将wchar_t序号转化为int
							{if (wcscmp(temp_number, L"1") == 0)
								j = 1;
							if (wcscmp(temp_number, L"2") == 0)
								j = 2;
							if (wcscmp(temp_number, L"3") == 0)
								j = 3;
							if (wcscmp(temp_number, L"4") == 0)
								j = 4;
							if (wcscmp(temp_number, L"5") == 0)
								j = 5;
							if (wcscmp(temp_number, L"6") == 0)
								j = 6;
							if (wcscmp(temp_number, L"7") == 0)
								j = 7;
							if (wcscmp(temp_number, L"81") == 0)
								j = 8;
							if (wcscmp(temp_number, L"9") == 0)
								j = 9;
							if (wcscmp(temp_number, L"10") == 0)
								j = 10;
							if (j > i || j < 0)//说明输入的数字没有在所有序号的范围内 
								MessageBox(NULL, _T("请重新输入"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							if (j > 0 && j <= i)
							{
								if (j == 1 && i == 1)  //仅有一个节点，特殊处理pre
								{
									if (p->next->next == NULL)//总链表只有一个节点
									{
										pre = p;
										Node* deletnode = p->next;
										p->next = NULL;
										free(deletnode);
									}
									else  //只是收入仅有一个节点，“支出”也存在节点
									{
										Node* t = p->next;
										while (wcscoll(t->next->flag, flag_shouru) != 0 && wcscoll(t->flag, flag_shouru) != 0)  //考虑支出、收入节点交替输入的情况
										{
											t = t->next;
										}
										if (t->next->next == NULL)  //“收入”节点恰为最后一个节点
										{
											pre = t;
											Node* deletnode = t->next;
											t->next = NULL;
											free(deletnode);
										}
										else                       //“收入”节点仅有一个，同时其并非属于最后一个节点，不影响pre
										{
											if (p->next == t)    //“收入”节点位于总链表的第一个特殊判断
											{
												Node* deletnode = p->next;
												p->next = p->next->next;
												free(deletnode);
											}
											else   //“收入”节点不位于总链表的第一个
											{
												Node* deletnode = t->next;
												t->next = t->next->next;
												free(deletnode);
											}
										}
									}
									MessageBox(NULL, _T("删除成功！"), _T("删除记录"), MB_SETFOREGROUND);
									Save(p);
								}
								else if (j == 1 && i > 1)
								{
									Node* t = p->next;

									while (wcscoll(t->next->flag, flag_shouru) != 0 && wcscoll(t->flag, flag_shouru) != 0)  //考虑支出、收入节点交替输入的情况
									{
										t = t->next;
									}
									if (t->next->next == NULL)  //“收入”节点恰为最后一个节点
									{
										pre = t;
										Node* deletnode = t->next;
										t->next = NULL;
										free(deletnode);
									}
									else                       //“收入”节点仅有一个，同时其并非属于最后一个节点，不影响pre
									{

										if (p->next == t)    //“收入”节点位于总链表的第一个特殊判断
										{
											Node* deletnode = p->next;
											p->next = p->next->next;
											free(deletnode);
										}
										else        //“收入”节点不位于总链表的第一个
										{
											Node* deletnode = t->next;
											t->next = t->next->next;
											free(deletnode);
										}
									}
									MessageBox(NULL, _T("删除成功！"), _T("删除记录"), MB_SETFOREGROUND);
									Save(p);
								}
								else if (j == i) //j为“收入”链最后一个节点
								{
									Node* t = p->next;
									int count = 1;
									while (t && count < j - 1)  //将t指向待删除结点的前一个结点
									{
										if (wcscoll(t->flag, flag_shouru) == 0)
										{
											t = t->next;
											count++;
										}
										else
										{
											t = t->next;
										}

										while (wcscoll(t->flag, flag_shouru) != 0)  //考虑支出、收入节点交替输入的情况
										{
											t = t->next;
										}
										if (t->next->next == NULL)   //“收入”链最后一个恰为总链表最后一个
										{
											pre = t;
											Node* deletnode = t->next;
											t->next = NULL;
											free(deletnode);
										}
										else                       //“收入”链最后一个并非是总链表的最后一个，不影响pre
										{
											while (wcscoll(t->next->flag, flag_shouru) != 0)  //考虑支出、收入节点交替输入的情况
											{
												t = t->next;
											}
											Node* deletnode = t->next;
											t->next = t->next->next;
											free(deletnode);
										}
										MessageBox(NULL, _T("删除成功！"), _T("删除记录"), MB_SETFOREGROUND);
										Save(p);
									}
								}
								else   //j为一般情况，即j！=i
								{
									Node* t = p->next;
									int count = 1;
									while (t && count < j - 1)  //将temp指向待删除结点的前一个结点
									{
										if (wcscoll(t->flag, flag_shouru) == 0) //筛选出“支出”节点
										{
											t = t->next;
											count++;
										}
										else
										{
											t = t->next;
										}
									}
									while (wcscoll(t->next->flag, flag_shouru) != 0)  //考虑支出、收入节点交替输入的情况
									{
										t = t->next;
									}
									Node* deletnode = t->next;
									t->next = t->next->next;
									free(deletnode);
									MessageBox(NULL, _T("删除成功！"), _T("删除记录"), MB_SETFOREGROUND);
									Save(p);//调用文件保存函数
								}
							}
							else { MessageBox(NULL, _T("输入序号错误，请重新输入"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND); }
						}
					}
				}

				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//鼠标点击返回按钮
				{
					loadimage(&delet_exit, L"delet_exit.jpg");
					putimage(0, 0, &delet_exit);
					Sleep(100);
					Select_MainMenu(p, pre);
				}
			}
		}
	}
}

//更改函数
void Change(struct record* p,Node* pre)
{
	wchar_t flag_zhichu[10];
	wcscpy_s(flag_zhichu, L"1");
	wchar_t flag_shouru[10];
	wcscpy_s(flag_shouru, L"0");
	wchar_t type_1[10];
	wcscpy_s(type_1, L"1");
	wchar_t type_2[10];
	wcscpy_s(type_2, L"2");
	wchar_t type_3[10];
	wcscpy_s(type_3, L"3");
	wchar_t type_4[10];
	wcscpy_s(type_4, L"4");
	wchar_t type_5[10];
	wcscpy_s(type_5, L"5");
	loadimage(&index_change, L"index_change.jpg");//导入初始界面
	putimage(0, 0, &index_change);
	Sleep(100);
	loadimage(&change, L"change.jpg");//导入初始界面
	putimage(0, 0, &change);
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)  //鼠标点击特定区域，即“支出”按钮所在区域
				{
					loadimage(&change_zhichu, L"change_zhichu.jpg");
					putimage(0, 0, &change_zhichu);
					int position_x = 409;//“序号”横坐标
					int position_y = 151;//“序号”纵坐标
					setbkmode(TRANSPARENT);//设置字体背景为透明
					settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
					settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
					outtextxy(position_x, position_y, _T("序号             时间               类型             金额"));//显示表格第一行表头
					wchar_t num[100];//临时保存输出序号
					Node* temp = p->next;
					int i = 1, j = -1;
					if (temp == NULL) MessageBox(NULL, _T("记录为空，请返回菜单添加记录！1"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);//无任何内容，直接弹窗提醒输入数据
					else
					{
						while (temp)  //输出原有记录
						{
							if (wcscoll(temp->flag, flag_zhichu) == 0)  //根据temp->flag筛选出“支出”节点
							{
								//枚举得到序号
								{if (i == 1)
									wcscpy_s(num, L"1");
								if (i == 2)
									wcscpy_s(num, L"2");
								if (i == 3)
									wcscpy_s(num, L"3");
								if (i == 4)
									wcscpy_s(num, L"4");
								if (i == 5)
									wcscpy_s(num, L"5");
								if (i == 6)
									wcscpy_s(num, L"6");
								if (i == 7)
									wcscpy_s(num, L"7");
								if (i == 8)
									wcscpy_s(num, L"8");
								if (i == 9)
									wcscpy_s(num, L"9");
								if (i == 10)
									wcscpy_s(num, L"10");
								}
								position_y += 20;//向下推一行
								outtextxy(424, position_y, num);//显示序号
								outtextxy(590, position_y, temp->time);//显示记录时间
								//显示种类
								{if (!wcscoll(temp->type, type_1))  //类型为伙食
									outtextxy(793, position_y, _T("伙食"));
								if (!wcscoll(temp->type, type_2))  //类型为购物
									outtextxy(793, position_y, _T("购物"));
								if (!wcscoll(temp->type, type_3))  //类型为日用
									outtextxy(793, position_y, _T("日用"));
								if (!wcscoll(temp->type, type_4))  //类型为交通
									outtextxy(793, position_y, _T("交通"));
								if (!wcscoll(temp->type, type_5))  //类型为礼金
									outtextxy(793, position_y, _T("礼金"));
								}

								outtextxy(988, position_y, temp->money);//显示金额
								temp = temp->next;
								i++;
							}
							else { temp = temp->next; }
						}
						//while循环输出原有记录结束
						i--;//此时i表示共有i条记录
						if (i == 0)   MessageBox(NULL, _T("记录为空，请返回菜单添加记录！2"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);//无任何内容，直接弹窗提醒输入数据
						else
						{
							wchar_t temp_number[10];//临时保存输入的序号
							InputBox(temp_number, 10, _T("请选择需要修改的日程序号"));
							//将wchar_t序号转化为int
							{
								if (wcscmp(temp_number, L"1") == 0)
									j = 1;
								if (wcscmp(temp_number, L"2") == 0)
									j = 2;
								if (wcscmp(temp_number, L"3") == 0)
									j = 3;
								if (wcscmp(temp_number, L"4") == 0)
									j = 4;
								if (wcscmp(temp_number, L"5") == 0)
									j = 5;
								if (wcscmp(temp_number, L"6") == 0)
									j = 6;
								if (wcscmp(temp_number, L"7") == 0)
									j = 7;
								if (wcscmp(temp_number, L"81") == 0)
									j = 8;
								if (wcscmp(temp_number, L"9") == 0)
									j = 9;
								if (wcscmp(temp_number, L"10") == 0)
									j = 10;
								if (j > i || j < 0)//说明输入的数字没有在所有日程序号的范围内 
									MessageBox(NULL, _T("请重新输入"), _T("修改记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							if (j > 0 && j <= i)
							{
								Node* t = p->next;
								Node* pret = p;
								int count = 0;
								while (t && count < j)  //将temp指向待删除结点的前一个结点
								{
									if (wcscoll(t->flag, flag_zhichu) == 0) //筛选出“支出”节点
									{
										t = t->next;
										pret = pret->next;
										count++;
									}
									else
									{
										t = t->next;
										pret = pret->next;
									}
								}
								 t = pret;  //考虑收入、支出交叉存入的情况
								wchar_t temp_number[100];//保存修改的金额
								InputBox(temp_number, 100, _T("请输入修改的金额"));
								wcscpy_s(t->money, temp_number);
								MessageBox(NULL, _T("修改成功！"), _T("修改记录"), MB_SETFOREGROUND);
								Save(p);

							}

						}
					}

				}

				if (msg.x > 113 && msg.x < 315 && msg.y > 369 && msg.y < 457)  //鼠标点击特定区域，即“支出”按钮所在区域
				{
					loadimage(&change_shouru, L"change_shouru.jpg");
					putimage(0, 0, &change_shouru);
					int position_x = 409;//“序号”横坐标
					int position_y = 151;//“序号”纵坐标
					setbkmode(TRANSPARENT);//设置字体背景为透明
					settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
					settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
					outtextxy(position_x, position_y, _T("序号             时间               类型             金额"));//显示表格第一行表头
					wchar_t num[100];//临时保存输出序号
					Node* temp = p->next;
					int i = 1, j = -1;
					if (temp == NULL) MessageBox(NULL, _T("记录为空，请返回菜单添加记录！1"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);//无任何内容，直接弹窗提醒输入数据
					else
					{
						while (temp)  //输出原有记录
						{
							if (wcscoll(temp->flag, flag_shouru) == 0)  //根据temp->flag筛选出“收入”节点
							{
								//枚举得到序号
								{if (i == 1)
									wcscpy_s(num, L"1");
								if (i == 2)
									wcscpy_s(num, L"2");
								if (i == 3)
									wcscpy_s(num, L"3");
								if (i == 4)
									wcscpy_s(num, L"4");
								if (i == 5)
									wcscpy_s(num, L"5");
								if (i == 6)
									wcscpy_s(num, L"6");
								if (i == 7)
									wcscpy_s(num, L"7");
								if (i == 8)
									wcscpy_s(num, L"8");
								if (i == 9)
									wcscpy_s(num, L"9");
								if (i == 10)
									wcscpy_s(num, L"10");
								}
								position_y += 20;//向下推一行
								outtextxy(424, position_y, num);//显示序号
								outtextxy(590, position_y, temp->time);//显示记录时间
								//显示种类
								{if (!wcscoll(temp->type, type_1))  //类型为工资
									outtextxy(793, position_y, _T("工资"));
								if (!wcscoll(temp->type, type_2))  //类型为其他
									outtextxy(793, position_y, _T("其他"));
								}

								outtextxy(988, position_y, temp->money);//显示金额
								temp = temp->next;
								i++;
							}
							else { temp = temp->next; }
						}
						//while循环输出原有记录结束
						i--;//此时i表示共有i条记录
						if (i == 0)   MessageBox(NULL, _T("记录为空，请返回菜单添加记录！2"), _T("删除记录"), MB_ICONSTOP | MB_SETFOREGROUND);//无任何内容，直接弹窗提醒输入数据
						else
						{
							wchar_t temp_number[10];//临时保存输入的序号
							InputBox(temp_number, 10, _T("请选择需要修改的日程序号"));
							//将wchar_t序号转化为int
							{
								if (wcscmp(temp_number, L"1") == 0)
									j = 1;
								if (wcscmp(temp_number, L"2") == 0)
									j = 2;
								if (wcscmp(temp_number, L"3") == 0)
									j = 3;
								if (wcscmp(temp_number, L"4") == 0)
									j = 4;
								if (wcscmp(temp_number, L"5") == 0)
									j = 5;
								if (wcscmp(temp_number, L"6") == 0)
									j = 6;
								if (wcscmp(temp_number, L"7") == 0)
									j = 7;
								if (wcscmp(temp_number, L"81") == 0)
									j = 8;
								if (wcscmp(temp_number, L"9") == 0)
									j = 9;
								if (wcscmp(temp_number, L"10") == 0)
									j = 10;
								if (j > i || j < 0)//说明输入的数字没有在所有日程序号的范围内 
									MessageBox(NULL, _T("请重新输入"), _T("修改记录"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							if (j > 0 && j <= i)
							{
								Node* t = p->next;
								Node* pret = p;
								int count = 0;
								while (t && count < j)  
								{
									if (wcscoll(t->flag, flag_shouru) == 0) //筛选出“收入”节点
									{
										t = t->next;
										pret = pret->next;
										count++;
									}
									else
									{
										t = t->next;
										pret = pret->next;
									}
								}
								t = pret; //此时t指向待修改节点
								wchar_t temp_number[100];//保存修改的金额
								InputBox(temp_number, 100, _T("请输入修改的金额"));
								wcscpy_s(t->money, temp_number);
								MessageBox(NULL, _T("修改成功！"), _T("修改记录"), MB_SETFOREGROUND);
								Save(p);
							}

						}
					}
				}

				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//鼠标点击返回按钮
				{
					loadimage(&change_exit, L"change_exit.jpg");
					putimage(0, 0, &change_exit);
					Sleep(100);
					Select_MainMenu(p, pre);
				}
			}
		}
	}
}

//输出十进制可读文件函数
void output(Node* p) // 输出链表到本地文件并实现推出功能
{
	wchar_t flag_zhichu[10];
	wcscpy_s(flag_zhichu, L"1");
	wchar_t flag_shouru[10];
	wcscpy_s(flag_shouru, L"0");
	wchar_t type_1[10];
	wcscpy_s(type_1, L"1");
	wchar_t type_2[10];
	wcscpy_s(type_2, L"2");
	wchar_t type_3[10];
	wcscpy_s(type_3, L"3");
	wchar_t type_4[10];
	wcscpy_s(type_4, L"4");
	wchar_t type_5[10];
	wcscpy_s(type_5, L"5");
	FILE* fp = NULL;
	Node* t = p->next; // 辅助指针指向开头
	fp = fopen("十进制可读文件.txt", "w");
	fprintf(fp, "支出/收入\t种类\t时间\t\t金额\t\n");
	while (t)
	{
		wchar_t type1[100];//type1临时储存支出/收入  wchar_t
		if (!wcscoll(t->flag, flag_zhichu))  
			wcscpy_s(type1, L"支出");
		if (!wcscoll(t->flag, flag_shouru))  
			wcscpy_s(type1, L"收入");
		wchar_t type2[100];//type2临时存储种类  wchar_t
		if (!wcscoll(t->flag, flag_zhichu))
		{
			if (!wcscoll(t->type, type_1))
				wcscpy_s(type2, L"伙食");
			if (!wcscoll(t->type, type_2))
				wcscpy_s(type2, L"购物");
			if (!wcscoll(t->type, type_3))
				wcscpy_s(type2, L"日用");
			if (!wcscoll(t->type, type_4))
				wcscpy_s(type2, L"交通");
			if (!wcscoll(t->type, type_5))
				wcscpy_s(type2, L"礼金");
		}
		else
		{
			if (!wcscoll(t->type, type_1))
				wcscpy_s(type2, L"工资");
			if (!wcscoll(t->type, type_2))
				wcscpy_s(type2, L"其他");
		}

		// 使用WchartoChar函数转换
		char type11[1024];//  支出/收入 int
		char type22[1024];//  类型 int
		char time[1024];
		char money[1024];
		WchartoChar(type11, type1);
		WchartoChar(type22, type2);
		WchartoChar(time, t->time);
		WchartoChar(money, t->money);

		fprintf(fp, "%s\t%s\t%s\t%s\n",type11,type22,time,money);
		t = t->next;
	}
	fclose(fp);
}

int main()
{
	Node* p, * pre;
	p = (Node*)malloc(sizeof(Node));
	wchar_t pflag[10];
	wcscpy_s(pflag, L"-1");
	wcscpy(p->flag, pflag);
	p->next = NULL;
	pre = p;
	FILE* fp;
	fopen_s(&fp, "allinfo.dat", "rb");
	/*从文件中读入全局变量*/
	if (fp!=NULL)
	{
		char ch;
		fread(&ch, sizeof(char), 1, fp);
		if (!feof(fp)) rewind(fp);
		while (!feof(fp))
		{
			fread(&ch, sizeof(char), 1, fp);
			if (!feof(fp))  //和while循环前的作用一样，判断文件是否为空
			{
				fseek(fp, -sizeof(char), 1);// 将文件指针向左移动一个字节，返回测试的ch处的内容
				Node* temp = (Node*)malloc(sizeof(Node));
				fread(temp->flag, sizeof(wchar_t) * 10, 1, fp);
				fread(temp->type, sizeof(wchar_t) * 10, 1, fp);
				fread(temp->money, sizeof(wchar_t) * 100, 1, fp);
				fread(temp->time, sizeof(wchar_t) * 100, 1, fp);
				temp->next = NULL;
				pre->next = temp;
				pre = temp;
			}
			else break;
		}
		fclose(fp);
		/*读入结束*/
	}
	
	initgraph(1292, 678);
	
	Welcome(p,pre);

	return 0;
}