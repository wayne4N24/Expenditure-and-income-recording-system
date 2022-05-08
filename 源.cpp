#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
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
	wchar_t flag[10];    //flag=1��ʾ֧����flag=0��ʾ����
	wchar_t type[10];    //���ڱ���С���࣬�硰���á�������ͨ����
	wchar_t money[100];  //�����û����������
	wchar_t time[100];   //ʹ��<time.h>�����û��������ڣ��Զ���¼��������
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

//wchar_tתchar����
void WchartoChar(char* charStr, const wchar_t* wcharStr)  //wchar_tתchar
{
	int len = WideCharToMultiByte(CP_ACP, 0, wcharStr, wcslen(wcharStr), NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, wcharStr, wcslen(wcharStr), charStr, len, NULL, NULL);
	charStr[len] = '\0';
}


//��ӭ���溯��
void Welcome(Node* &p,Node* &pre)
{
	loadimage(&welcome, L"welcome.jpg");//���뻶ӭ���棨�ر�ע�⣺˫�������治���пո�Ҫ��ͼƬ������ȫһ�£�
	putimage(0, 0, &welcome);//��ʾ��ӭ����
	/*���������꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 506 && msg.x < 752 && msg.y > 508 && msg.y < 598)//������ض����򣬼�ENTER��ť��������
				{
					loadimage(&welcome2, L"welcome2.jpg");//�����ɫ��ťͼƬ
					putimage(0, 0, &welcome2);//��ʾ��ɫ��ťͼƬ
					Sleep(100);//��ʱ������CPUռ���ʣ������������Ч��
					Select_MainMenu(p,pre);//����һ�����˵�ѡ���
				}
			}
		}
		
	}

}

//���˵�����
void Select_MainMenu(Node* &p,Node* &pre)
{
	loadimage(&index_original, L"index_original.jpg");//�����ʼ����
	putimage(0, 0, &index_original);//��ʾ��ʼ����
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 147 && msg.x < 452 && msg.y > 183 && msg.y < 267)//������ض����򣬼������Ӽ�¼����ť��������
					Add(p,pre);//�������Ӻ���
				if (msg.x > 145 && msg.x < 448 && msg.y > 335 && msg.y < 421)//������ض����򣬼���ɾ����¼����ť��������
					Delete(p,pre);//����ɾ������
				if (msg.x > 154 && msg.x < 447 && msg.y > 490 && msg.y < 577)//������ض����򣬼���֧�����а񡱰�ť��������
					Sort(p,pre);//����������
				if (msg.x > 734 && msg.x < 1028 && msg.y > 180 && msg.y < 264)//������ض����򣬼������ļ�¼����ť��������
					Change(p,pre);//���ø��ĺ���
				if (msg.x > 733 && msg.x < 1027 && msg.y > 332 && msg.y < 419)//������ض����򣬼�����ѯ��¼����ť��������
					Search(p,pre);//���ò�ѯ����
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

//�ļ����溯��
void Save(Node* p)
{
	FILE* fp;
	fopen_s(&fp, "allinfo.dat", "wb");
	fclose(fp);
	fopen_s(&fp, "allinfo.dat", "ab+");
	Node* temp = p->next;
	//���ļ����ȫ�ֱ���
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

//��Ӽ�¼����
void Add(Node* &p,Node* &pre)
{
	time_t curr_time;    //ϵͳʱ�� 
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
	loadimage(&add, L"add.jpg");//�����ʼ����
	putimage(0, 0, &add);
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)//������ض����򣬼���֧������ť��������
				{
					loadimage(&add_zhichu, L"add_zhichu.jpg");
					putimage(0, 0, &add_zhichu);
					Node* temp = (Node*)malloc(sizeof(Node));
					InputBox(temp->type, 2, _T("��ѡ��֧�����ͣ�1.��ʳ��2.���3.���ã�4.��ͨ��5.����������ּ��ɣ�"));
					InputBox(temp->money, 100, _T("������֧�����ɰ���С����"));
					wcscpy(temp->flag, flag_zhichu);
					wcsftime(temp->time, 50, L"%B %d,%Y", curr_tm);
					temp->next =NULL;
					pre->next = temp;
					pre = temp;  //preָ��ĸı���Ҫʹ��&
					MessageBox(NULL, _T("��ӳɹ���"), _T("��Ӽ�¼"), MB_SETFOREGROUND);
					Save(p);
				}

				if (msg.x > 113 && msg.x <315 && msg.y > 369 && msg.y < 457)//������ض����򣬼������롱��ť��������
				{
					loadimage(&add_shouru, L"add_shouru.jpg");
					putimage(0, 0, &add_shouru);
					Node* temp = (Node*)malloc(sizeof(Node));
					InputBox(temp->type, 2, _T("��ѡ���������ͣ�1.���� 2.�������������ּ��ɣ�"));
					
					InputBox(temp->money, 100, _T("������������ɰ���С����"));
					wcscpy(temp->flag, flag_shouru);
					wcsftime(temp->time, 5000, L"%B %d,%Y", curr_tm);
					temp->next = NULL;
					pre->next = temp;
					pre = temp;
					MessageBox(NULL, _T("��ӳɹ���"), _T("��Ӽ�¼"), MB_SETFOREGROUND);
					Save(p);
				}
				
				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//��������ذ�ť
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

//��ѯ��¼����
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
	loadimage(&index_search, L"index_search.jpg");//�����ʼ����
	putimage(0, 0, &index_search);
	Sleep(100);
	loadimage(&search, L"search.jpg");//�����ʼ����
	putimage(0, 0, &search);
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)//������ض����򣬼���֧������ť��������
				{
					loadimage(&search_zhichu, L"search_zhichu.jpg");
					putimage(0, 0, &search_zhichu);
					int position_x = 409;//����š�������
					int position_y = 151;//����š�������
					setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
					settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������С20����ʽ����
					outtextxy(position_x, position_y, _T("���             ʱ��               ����             ���"));//��ʾ����һ�б�ͷ
					wchar_t search_type[10];//��ʱ�����ѯ��ʽ�����
					InputBox(search_type, 10, _T("��ѡ���ѯ�ķ�ʽ��1.�������ѯ��2.����������ѯ��3.������ȫ������������ּ��ɣ�"));

					int j = -1;//j���ڼ�¼��ѯ��ʽ�����
					if (wcscmp(search_type, L"1") == 0)
						j = 1;
					else if (wcscmp(search_type, L"2") == 0)
						j = 2;
					else if (wcscmp(search_type, L"3") == 0)
						j = 3;
					else //˵�����������û���ڲ�ѯ��ʽ��ŵķ�Χ�� 
						MessageBox(NULL, _T("����������"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);


					if (j == 1 || j == 2 || j == 3)
					{
						switch (j)
						{
						case 1:    //�������ѯ
						{
							wchar_t type[10]; //��ʱ���水�����ѯ֮����ı��
							InputBox(type, 10, _T("��ѡ�����ࣺ1.��ʳ��2.���3.���ã�4.��ͨ��5.����������ּ��ɣ�"));
							int i = 1; //iΪ�������е���ţ�int���ͣ�
							wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�

							if (!wcscoll(type, type_1))  //����Ϊ��ʳ
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_1))  //����flagɸѡ��֧�����ڵ���֧���ڵ������Ϊ����ʳ��
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											outtextxy(793, position_y, _T("��ʳ"));
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼1"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else if (!wcscoll(type, type_2))  //����Ϊ����
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_2))  //����flagɸѡ��֧�����ڵ�,��֧���ڵ�Ϊ�����
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											outtextxy(793, position_y, _T("����"));
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else if (!wcscoll(type, type_3))  //����Ϊ����
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //��¼���Ƿ�������Ŀ������Ľڵ�ı�ǣ�0Ϊû�У�1Ϊ��
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_3))  //����flagɸѡ��֧�����ڵ�,�ҽڵ�����Ϊ����
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											outtextxy(793, position_y, _T("����"));
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else if (!wcscoll(type, type_4))  //����Ϊ��ͨ
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_4))  //����flagɸѡ��֧�����ڵ��ҽڵ�����Ϊ����ͨ��
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											outtextxy(793, position_y, _T("��ͨ"));
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else if (!wcscoll(type, type_5))  //����Ϊ���
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_5))  //����flagɸѡ��֧�����ڵ㣬������Ϊ�����
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											outtextxy(793, position_y, _T("���"));
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼5"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							else  MessageBox(NULL, _T("�������ִ�������������"), _T("����"), MB_ICONSTOP | MB_SETFOREGROUND);
						}

						case 2:  //����������ѯ
						{
							wchar_t type[10]; //��ʱ���水��������ѯ֮��������
							InputBox(type, 10, _T("��ѡ�������䣺1.��0-100����2.��101-200����3.��200+������������ǰ�����ִ��ż��ɣ�"));
							wchar_t num[10]; //��ʱ���������ţ�wchar_t���ͣ�
							int i = 1;//iΪ�������еı�ţ�int ���ͣ�
							if (!wcscoll(type, type_1))  //�������Ϊ��0-100��
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //��¼���Ƿ��д���Ŀ��������Ľڵ�ı�ǣ�0Ϊû�У�1Ϊ��
									while (temp)
									{
										double money;  //money Ϊ�ڵ��н������֣�int ���ͣ�
										money = wcstod(temp->money, NULL);
										if (money > 0 && money <= 100)  //����flagɸѡ��֧�����ڵ�
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											//��ʾ����
											{if (!wcscoll(temp->type, type_1))  //����Ϊ��ʳ
												outtextxy(793, position_y, _T("��ʳ"));
											if (!wcscoll(temp->type, type_2))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_3))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_4))  //����Ϊ��ͨ
												outtextxy(793, position_y, _T("��ͨ"));
											if (!wcscoll(temp->type, type_5))  //����Ϊ���
												outtextxy(793, position_y, _T("���"));
											}
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û�д���Ŀ��������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else if (!wcscoll(type, type_2)) //�������Ϊ��101-200��
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //��¼���Ƿ��д���Ŀ��������Ľڵ�ı�ǣ�0Ϊû�У�1Ϊ��
									while (temp)
									{
										double money;  //money Ϊ�ڵ��н������֣�int ���ͣ�
										money = wcstod(temp->money, NULL);
										if (money >= 101 && money <= 200)  //�ڵ�Ľ����Ŀ��������
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											//��ʾ����
											{if (!wcscoll(temp->type, type_1))  //����Ϊ��ʳ
												outtextxy(793, position_y, _T("��ʳ"));
											if (!wcscoll(temp->type, type_2))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_3))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_4))  //����Ϊ��ͨ
												outtextxy(793, position_y, _T("��ͨ"));
											if (!wcscoll(temp->type, type_5))  //����Ϊ���
												outtextxy(793, position_y, _T("���"));
											}
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û�д���Ŀ��������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else if (!wcscoll(type, type_3)) //�������Ϊ��200+��
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //��¼���Ƿ��д���Ŀ��������Ľڵ�ı�ǣ�0Ϊû�У�1Ϊ��
									while (temp)
									{
										double money;  //money Ϊ�ڵ��н������֣�int ���ͣ�
										money = wcstod(temp->money, NULL);
										if (money > 200)  //�ڵ�Ľ����Ŀ��������
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											//��ʾ����
											{if (!wcscoll(temp->type, type_1))  //����Ϊ��ʳ
												outtextxy(793, position_y, _T("��ʳ"));
											if (!wcscoll(temp->type, type_2))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_3))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_4))  //����Ϊ��ͨ
												outtextxy(793, position_y, _T("��ͨ"));
											if (!wcscoll(temp->type, type_5))  //����Ϊ���
												outtextxy(793, position_y, _T("���"));
											}
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û�д���Ŀ��������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else  MessageBox(NULL, _T("�������ִ�������������"), _T("����"), MB_ICONSTOP | MB_SETFOREGROUND);
							break;
						}

						case 3:  //������ȫ���
						{
							Node* temp = p->next;
							int i = 1; //iΪ�������е���ţ�int���ͣ�
							wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
							if (temp)
							{
								int flag = 0; //�Ƿ��С�֧������¼�ı�ǣ�0Ϊû�У�1Ϊ��
								while (temp)
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0)  //����flagɸѡ��֧�����ڵ�
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
										position_y += 20;//������һ��
										outtextxy(424, position_y, num);//��ʾ���
										outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
										// �������
										if (!wcscoll(temp->type, type_1))  //����Ϊ��ʳ
											outtextxy(793, position_y, _T("��ʳ"));
										if (!wcscoll(temp->type, type_2))  //����Ϊ����
											outtextxy(793, position_y, _T("����"));
										if (!wcscoll(temp->type, type_3))  //����Ϊ����
											outtextxy(793, position_y, _T("����"));
										if (!wcscoll(temp->type, type_4))  //����Ϊ��ͨ
											outtextxy(793, position_y, _T("��ͨ"));
										if (!wcscoll(temp->type, type_5))  //����Ϊ���
											outtextxy(793, position_y, _T("���"));
										//����������
										outtextxy(988, position_y, temp->money);//��ʾ���
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
								if (flag == 0)  MessageBox(NULL, _T("û�С�֧������¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							break;
						}
						}
					}
				}

				if (msg.x > 113 && msg.x < 315 && msg.y > 369 && msg.y < 457)//������ض����򣬼������롱��ť��������
				{
					loadimage(&search_shouru, L"search_shouru.jpg");
					putimage(0, 0, &search_shouru);
					int position_x = 409;//����š�������
					int position_y = 151;//����š�������
					setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
					settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������С20����ʽ����
					outtextxy(position_x, position_y, _T("���             ʱ��               ����             ���"));//��ʾ����һ�б�ͷ
					wchar_t search_type[10];//��ʱ�����ѯ��ʽ�����
					InputBox(search_type, 10, _T("��ѡ���ѯ�ķ�ʽ��1.�������ѯ��2.����������ѯ3.������ȫ������������ּ��ɣ�"));

					int j = -1;//j���ڼ�¼��ѯ��ʽ�����
					if (wcscmp(search_type, L"1") == 0)
						j = 1;
					else if (wcscmp(search_type, L"2") == 0)
						j = 2;
					else if (wcscmp(search_type, L"3") == 0)
						j = 3;
					else //˵�����������û���ڲ�ѯ��ʽ��ŵķ�Χ�� 
						MessageBox(NULL, _T("����������"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);


					if (j == 1 || j == 2 || j == 3)
					{
						switch (j)
						{
						case 1:    //�������ѯ
						{
							wchar_t type[10]; //��ʱ���水�����ѯ֮����ı��
							InputBox(type, 10, _T("��ѡ�����ࣺ1.���ʣ�2.�������������ּ��ɣ�"));
							int i = 1; //iΪ�������е���ţ�int���ͣ�
							wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�

							if (!wcscoll(type, type_1))  //����Ϊ����
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_shouru) == 0 && !wcscoll(temp->type, type_1))  //����flagɸѡ�����롱�ڵ���֧���ڵ������Ϊ�����ʡ�
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											outtextxy(793, position_y, _T("����"));
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼1"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}

							if (!wcscoll(type, type_2))  //����Ϊ����
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0;
									while (temp)
									{
										if (wcscoll(temp->flag, flag_shouru) == 0 && !wcscoll(temp->type, type_2))  //����flagɸѡ�����롱�ڵ�,������ڵ�Ϊ��������
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											outtextxy(793, position_y, _T("����"));
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								break;
							}
						}

						case 2:  //����������ѯ
						{
							wchar_t type[10]; //��ʱ���水��������ѯ֮��������
							InputBox(type, 10, _T("��ѡ�������䣺1.��0-100����2.��101-200����3.��200+������������ǰ�����ִ��ż��ɣ�"));
							wchar_t num[10]; //��ʱ���������ţ�wchar_t���ͣ�
							int i = 1;//iΪ�������еı�ţ�int ���ͣ�

							if (!wcscoll(type, type_1))  //�������Ϊ��0-100��
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //��¼���Ƿ��д���Ŀ��������Ľڵ�ı�ǣ�0Ϊû�У�1Ϊ��
									while (temp)
									{
										double money;  //money Ϊ�ڵ��н������֣�int ���ͣ�
										money = wcstod(temp->money, NULL);
										if (money > 0 && money <= 100 && wcscoll(temp->flag, flag_shouru) == 0)  //����flagɸѡ�����롱�ڵ㣬�ҽ��ڡ�0-100��
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											//��ʾ����
											{if (!wcscoll(temp->type, type_1))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_2))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											}
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û�д���Ŀ��������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else if (!wcscoll(type, type_2)) //�������Ϊ��101-200��
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //��¼���Ƿ��д���Ŀ��������Ľڵ�ı�ǣ�0Ϊû�У�1Ϊ��
									while (temp)
									{
										double money;  //money Ϊ�ڵ��н������֣�int ���ͣ�
										money = wcstod(temp->money, NULL);
										if (money >= 101 && money <= 200 && wcscoll(temp->flag, flag_shouru) == 0)  //ɸѡ�������롱�ڵ㣬�ҽڵ�Ľ����Ŀ��������
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											//��ʾ����
											{if (!wcscoll(temp->type, type_1))  //����Ϊ��ʳ
												outtextxy(793, position_y, _T("��ʳ"));
											if (!wcscoll(temp->type, type_2))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_3))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_4))  //����Ϊ��ͨ
												outtextxy(793, position_y, _T("��ͨ"));
											if (!wcscoll(temp->type, type_5))  //����Ϊ���
												outtextxy(793, position_y, _T("���"));
											}
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û�д���Ŀ��������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							else if (!wcscoll(type, type_3)) //�������Ϊ��200+��
							{
								Node* temp = p->next;
								if (temp)
								{
									int flag = 0; //��¼���Ƿ��д���Ŀ��������Ľڵ�ı�ǣ�0Ϊû�У�1Ϊ��
									while (temp)
									{
										double money;  //money Ϊ�ڵ��н������֣�int ���ͣ�
										money = wcstod(temp->money, NULL);
										if (money > 200 && wcscoll(temp->flag, flag_shouru) == 0)  //ɸѡ�����롱�ڵ㣬�ڵ�Ľ�200+��
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
											position_y += 20;//������һ��
											outtextxy(424, position_y, num);//��ʾ���
											outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
											//��ʾ����
											{if (!wcscoll(temp->type, type_1))  //����Ϊ��ʳ
												outtextxy(793, position_y, _T("��ʳ"));
											if (!wcscoll(temp->type, type_2))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_3))  //����Ϊ����
												outtextxy(793, position_y, _T("����"));
											if (!wcscoll(temp->type, type_4))  //����Ϊ��ͨ
												outtextxy(793, position_y, _T("��ͨ"));
											if (!wcscoll(temp->type, type_5))  //����Ϊ���
												outtextxy(793, position_y, _T("���"));
											}
											outtextxy(988, position_y, temp->money);//��ʾ���
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
									if (flag == 0)  MessageBox(NULL, _T("û�д���Ŀ��������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								}
								else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							break;
						}

						case 3:  //������ȫ���
						{
							Node* temp = p->next;
							int i = 1; //iΪ�������е���ţ�int���ͣ�
							wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
							if (temp)
							{
								int flag = 0; //�Ƿ��С����롱��¼�ı�ǣ�0Ϊû�У�1Ϊ��
								while (temp)
								{
									if (wcscoll(temp->flag, flag_shouru) == 0)  //����flagɸѡ�����롱�ڵ�
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
										position_y += 20;//������һ��
										outtextxy(424, position_y, num);//��ʾ���
										outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
										// �������
										if (!wcscoll(temp->type, type_1))  //����Ϊ����
											outtextxy(793, position_y, _T("����"));
										if (!wcscoll(temp->type, type_2))  //����Ϊ����
											outtextxy(793, position_y, _T("����"));
										//����������
										outtextxy(988, position_y, temp->money);//��ʾ���
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
								if (flag == 0)  MessageBox(NULL, _T("û�С�֧������¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							else MessageBox(NULL, _T("��¼Ϊ��"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							break;
						}
						}
					}
				}

				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//��������ذ�ť
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

//������
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
	loadimage(&index_sort, L"index_sort.jpg");//�����ʼ����
	putimage(0, 0, &index_sort);
	Sleep(100);
	loadimage(&sort, L"sort.jpg");//�����ʼ����
	putimage(0, 0, &sort);
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)//������ض����򣬼���֧������ť��������
				{
					loadimage(&sort_zhichu, L"sort_zhichu.jpg");
					putimage(0, 0, &sort_zhichu);
					int position_x = 409;//����š�������
					int position_y = 151;//����š�������
					setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
					settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������С20����ʽ����
					outtextxy(position_x, position_y, _T("���             ʱ��               ����             ���"));//��ʾ����һ�б�ͷ
					wchar_t search_type[10];//��ʱ�����ѯ��ʽ�����
					InputBox(search_type, 10, _T("��ѡ������ʽ��1.ĳһ���൥������2.֧��ȫ�����������������ּ��ɣ�"));
					int j = -1;//j���ڼ�¼��ѯ��ʽ�����
					if (wcscmp(search_type, L"1") == 0)
						j = 1;
					else if (wcscmp(search_type, L"2") == 0)
						j = 2;
					else //˵�����������û���ڲ�ѯ��ʽ��ŵķ�Χ�� 
						MessageBox(NULL, _T("����������"), _T("����"), MB_ICONSTOP | MB_SETFOREGROUND);
					if (j == 1 || j == 2)
					{
						switch (j)
						{
						case 1:  //ĳһ���൥������
						{
							wchar_t type[10]; //��ʱ���水��������֮����ı��
							InputBox(type, 10, _T("��ѡ�����ࣺ1.��ʳ��2.���3.���ã�4.��ͨ��5.����������ּ��ɣ�"));

							if (!wcscoll(type, type_1))  //����Ϊ��ʳ
							{
								int i = 0; //iΪtemp1�����Ԫ�ظ���
								wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
								Node* temp = p->next;
								Node* temp1 = (Node*)malloc(sizeof(Node));  //ʹ��temp1��Ϊ����ʳ���������ͷ���
								temp1->next = NULL;
								int flag = 0;
								if (temp)
								{
									while (temp)  //��ȡ�������еġ����ʡ���¼
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_1))  //����flagɸѡ��֧�����ڵ�������Ϊ����ʳ��
										{
											flag = 1;
											//ͷ�巨������֧��������
											Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11Ϊtemp1�����������еĸ����ڵ�
											wcscpy_s(temp11->flag, temp->flag);
											wcscpy_s(temp11->type, temp->type);
											wcscpy_s(temp11->money, temp->money);
											wcscpy_s(temp11->time, temp->time);
											temp11->next = temp1->next;
											temp1->next = temp11;
											//ͷ�巨����
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
								}
								if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("����"), MB_ICONSTOP | MB_SETFOREGROUND);
								else    //���ڡ���ʳ������ļ�¼
								{
									for (int k = 1; k <= i; k++)  //ð�ݴӴ�С����
									{
										Node* t = temp1;
										while (t->next->next)
										{
											int  next_num = _wtoi(t->next->money);
											int next_next_num = _wtoi(t->next->next->money);
											if (next_num < next_next_num) // С�������
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
									int j = 1; //iΪ�������е���ţ�int���ͣ�
									wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
									Node* temp2 = temp1->next;  //temp111Ϊ������ʱ�ĸ���ָ��
									//������
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
										position_y += 20;//������һ��
										outtextxy(424, position_y, num);//��ʾ���
										outtextxy(590, position_y, temp2->time);//��ʾ��¼ʱ��
										outtextxy(793, position_y, _T("��ʳ"));
										outtextxy(988, position_y, temp2->money);//��ʾ���
										temp2 = temp2->next;
										j++;
									}
									//���������
									MessageBox(NULL, _T("����ɹ���"), _T("����"), MB_SETFOREGROUND);
								}
							}

							else if (!wcscoll(type, type_2))  //����Ϊ����
							{
								int i = 0; //iΪtemp1�����Ԫ�ظ���
								wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
								Node* temp = p->next;
								Node* temp1 = (Node*)malloc(sizeof(Node));  //ʹ��temp1��Ϊ������������ͷ���
								temp1->next = NULL;
								int flag = 0;
								if (temp)
								{
									while (temp)  //��ȡ�������еġ������¼
									{
										if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_2))  //����flagɸѡ��֧�����ڵ���֧���ڵ������Ϊ����ʳ��
										{
											flag = 1;
											//ͷ�巨�������������
											Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11Ϊtemp1�����������еĸ����ڵ�
											wcscpy_s(temp11->flag, temp->flag);
											wcscpy_s(temp11->type, temp->type);
											wcscpy_s(temp11->money, temp->money);
											wcscpy_s(temp11->time, temp->time);
											temp11->next = temp1->next;
											temp1->next = temp11;
											//ͷ�巨����
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
								}
								if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								else    //���ڡ��������ļ�¼
								{
									for (int k = 1; k <= i; k++)  //ð�ݴӴ�С����
									{
										Node* t = temp1;
										while (t->next->next)
										{
											int  next_num = _wtoi(t->next->money);
											int next_next_num = _wtoi(t->next->next->money);
											if (next_num < next_next_num) // С�������
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
									int j = 1; //iΪ�������е���ţ�int���ͣ�
									wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
									Node* temp2 = temp1->next;  //temp111Ϊ������ʱ�ĸ���ָ��
									//������
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
										position_y += 20;//������һ��
										outtextxy(424, position_y, num);//��ʾ���
										outtextxy(590, position_y, temp2->time);//��ʾ��¼ʱ��
										outtextxy(793, position_y, _T("����"));
										outtextxy(988, position_y, temp2->money);//��ʾ���
										temp2 = temp2->next;
										j++;
									}
									//���������
									MessageBox(NULL, _T("����ɹ���"), _T("����"), MB_SETFOREGROUND);
								}
							}

							else if (!wcscoll(type, type_3))  //����Ϊ����
							{
							int i = 0; //iΪtemp1�����Ԫ�ظ���
							wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //ʹ��temp1��Ϊ�����á��������ͷ���
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //��ȡ�������еġ����á���¼
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_3))  //����flagɸѡ��֧�����ڵ���֧���ڵ������Ϊ�����á�
									{
										flag = 1;
										//ͷ�巨���������á�����
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11Ϊtemp1�����������еĸ����ڵ�
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//ͷ�巨����
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //���ڡ����á�����ļ�¼
							{
								for (int k = 1; k <= i; k++)  //ð�ݴӴ�С����
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // С�������
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
								int j = 1; //iΪ�������е���ţ�int���ͣ�
								wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
								Node* temp2 = temp1->next;  //temp111Ϊ������ʱ�ĸ���ָ��
								//������
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
									position_y += 20;//������һ��
									outtextxy(424, position_y, num);//��ʾ���
									outtextxy(590, position_y, temp2->time);//��ʾ��¼ʱ��
									outtextxy(793, position_y, _T("����"));
									outtextxy(988, position_y, temp2->money);//��ʾ���
									temp2 = temp2->next;
									j++;
								}
								//���������
								MessageBox(NULL, _T("����ɹ���"), _T("����"), MB_SETFOREGROUND);
							}
							}

							else if (!wcscoll(type, type_4))  //����Ϊ��ͨ
							{
							int i = 0; //iΪtemp1�����Ԫ�ظ���
							wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //ʹ��temp1��Ϊ����ͨ���������ͷ���
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //��ȡ�������еġ����á���¼
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_4))  //����flagɸѡ��֧�����ڵ���֧���ڵ������Ϊ����ͨ��
									{
										flag = 1;
										//ͷ�巨��������ͨ������
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11Ϊtemp1�����������еĸ����ڵ�
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//ͷ�巨����
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //���ڡ���ͨ������ļ�¼
							{
								for (int k = 1; k <= i; k++)  //ð�ݴӴ�С����
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // С�������
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
								int j = 1; //iΪ�������е���ţ�int���ͣ�
								wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
								Node* temp2 = temp1->next;  //temp111Ϊ������ʱ�ĸ���ָ��
								//������
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
									position_y += 20;//������һ��
									outtextxy(424, position_y, num);//��ʾ���
									outtextxy(590, position_y, temp2->time);//��ʾ��¼ʱ��
									outtextxy(793, position_y, _T("��ͨ"));
									outtextxy(988, position_y, temp2->money);//��ʾ���
									temp2 = temp2->next;
									j++;
								}
								//���������
								MessageBox(NULL, _T("����ɹ���"), _T("����"), MB_SETFOREGROUND);
							}
							}

							else if (!wcscoll(type, type_5))  //����Ϊ���
							{
							int i = 0; //iΪtemp1�����Ԫ�ظ���
							wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //ʹ��temp1��Ϊ������������ͷ���
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //��ȡ�������еġ���𡱼�¼
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0 && !wcscoll(temp->type, type_5))  //����flagɸѡ��֧�����ڵ���֧���ڵ������Ϊ�����
									{
										flag = 1;
										//ͷ�巨�������������
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11Ϊtemp1�����������еĸ����ڵ�
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//ͷ�巨����
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //���ڡ��������ļ�¼
							{
								for (int k = 1; k <= i; k++)  //ð�ݴӴ�С����
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // С�������
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
								int j = 1; //iΪ�������е���ţ�int���ͣ�
								wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
								Node* temp2 = temp1->next;  //temp111Ϊ������ʱ�ĸ���ָ��
								//������
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
									position_y += 20;//������һ��
									outtextxy(424, position_y, num);//��ʾ���
									outtextxy(590, position_y, temp2->time);//��ʾ��¼ʱ��
									outtextxy(793, position_y, _T("���"));
									outtextxy(988, position_y, temp2->money);//��ʾ���
									temp2 = temp2->next;
									j++;
								}
								//���������
								MessageBox(NULL, _T("����ɹ���"), _T("����"), MB_SETFOREGROUND);
							}
							}

							else  MessageBox(NULL, _T("�������ִ�������������"), _T("����"), MB_ICONSTOP | MB_SETFOREGROUND);

							break;
						}

						case 2:  //֧��ȫ����������
						{
							int i = 0; //iΪtemp1�����Ԫ�ظ���
							wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //ʹ��temp1��Ϊ֧�������ͷ���
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //��ȡ�������е�֧����¼
								{
									if (wcscoll(temp->flag, flag_zhichu) == 0 )  //����flagɸѡ��֧�����ڵ�
									{
										flag = 1;
										//ͷ�巨����֧������
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11Ϊtemp1�����������еĸ����ڵ�
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//ͷ�巨����
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("û��֧���ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //����֧���ļ�¼
							{
								for (int k = 1; k <= i; k++)  //ð�ݴӴ�С����
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // С�������
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
								int j = 1; //iΪ�������е���ţ�int���ͣ�
								wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
								Node* temp2 = temp1->next;  //temp111Ϊ������ʱ�ĸ���ָ��
								//������
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
									position_y += 20;//������һ��
									outtextxy(424, position_y, num);//��ʾ���
									outtextxy(590, position_y, temp2->time);//��ʾ��¼ʱ��
									// �������
									if (!wcscoll(temp2->type, type_1))  //����Ϊ��ʳ
										outtextxy(793, position_y, _T("��ʳ"));
									if (!wcscoll(temp2->type, type_2))  //����Ϊ����
										outtextxy(793, position_y, _T("����"));
									if (!wcscoll(temp2->type, type_3))  //����Ϊ����
										outtextxy(793, position_y, _T("����"));
									if (!wcscoll(temp2->type, type_4))  //����Ϊ��ͨ
										outtextxy(793, position_y, _T("��ͨ"));
									if (!wcscoll(temp2->type, type_5))  //����Ϊ���
										outtextxy(793, position_y, _T("���"));
									//����������
									outtextxy(988, position_y, temp2->money);//��ʾ���
									temp2 = temp2->next;
									j++;
								}
								//���������
								MessageBox(NULL, _T("����ɹ���"), _T("����"), MB_SETFOREGROUND);
							}
							break;
						}

						}

					}
				}

				if (msg.x > 113 && msg.x < 315 && msg.y > 369 && msg.y < 457)  //������ض����򣬼������롱��ť��������
				{
					loadimage(&sort_shouru, L"sort_shouru.jpg");
					putimage(0, 0, &sort_shouru);
					int position_x = 409;//����š�������
					int position_y = 151;//����š�������
					setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
					settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������С20����ʽ����
					outtextxy(position_x, position_y, _T("���             ʱ��               ����             ���"));//��ʾ����һ�б�ͷ
					wchar_t search_type[10];//��ʱ�����ѯ��ʽ�����
					InputBox(search_type, 10, _T("��ѡ������ʽ��1.ĳһ���൥������2.����ȫ�����������������ּ��ɣ�"));
					int j = -1;//j���ڼ�¼��ѯ��ʽ�����
					if (wcscmp(search_type, L"1") == 0)
						j = 1;
					else if (wcscmp(search_type, L"2") == 0)
						j = 2;
					else //˵�����������û���ڲ�ѯ��ʽ��ŵķ�Χ�� 
						MessageBox(NULL, _T("����������"), _T("����"), MB_ICONSTOP | MB_SETFOREGROUND);

					if (j == 1 || j == 2)
					{
						switch (j)
						{
						case 1:  //ĳһ���൥������
						{
							wchar_t type[10]; //��ʱ���水��������֮����ı��
							InputBox(type, 10, _T("��ѡ�����ࣺ1.���ʣ�2.�������������ּ��ɣ�"));                   

							if (!wcscoll(type, type_1))  //����Ϊ����
							{
								int i = 0; //iΪtemp1�����Ԫ�ظ���
								wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
								Node* temp = p->next;
								Node* temp1 = (Node*)malloc(sizeof(Node));  //ʹ��temp1��Ϊ�����ʡ��������ͷ���
								temp1->next = NULL;
								int flag = 0;
								if (temp)
								{
									while (temp)  //��ȡ�������еġ����ʡ���¼
									{
										if (wcscoll(temp->flag, flag_shouru) == 0 && !wcscoll(temp->type, type_1))  //����flagɸѡ�����롱�ڵ���֧���ڵ������Ϊ�����ʡ�
										{
											flag = 1;
											//ͷ�巨���������ʡ�����
											Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11Ϊtemp1�����������еĸ����ڵ�
											wcscpy_s(temp11->flag, temp->flag);
											wcscpy_s(temp11->type, temp->type);
											wcscpy_s(temp11->money, temp->money);
											wcscpy_s(temp11->time, temp->time);
											temp11->next = temp1->next;
											temp1->next = temp11;
											//ͷ�巨����
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
								}
								if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								else    //���ڡ����ʡ�����ļ�¼
								{
									for (int k = 1; k <= i; k++)  //ð�ݴӴ�С����
									{
										Node* t = temp1;
										while (t->next->next)
										{
											int  next_num = _wtoi(t->next->money);
											int next_next_num = _wtoi(t->next->next->money);
											if (next_num < next_next_num) // С�������
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
									int j = 1; //iΪ�������е���ţ�int���ͣ�
									wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
									Node* temp2 = temp1->next;  //temp111Ϊ������ʱ�ĸ���ָ��
									//������
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
										position_y += 20;//������һ��
										outtextxy(424, position_y, num);//��ʾ���
										outtextxy(590, position_y, temp2->time);//��ʾ��¼ʱ��
										outtextxy(793, position_y, _T("����"));
										outtextxy(988, position_y, temp2->money);//��ʾ���
										temp2 = temp2->next;
										j++;
									}
									//���������
									MessageBox(NULL, _T("����ɹ���"), _T("����"), MB_SETFOREGROUND);
								}
							}

							if (!wcscoll(type, type_2))  //����Ϊ����
							{
								int i = 0; //iΪtemp1�����Ԫ�ظ���
								wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
								Node* temp = p->next;
								Node* temp1 = (Node*)malloc(sizeof(Node));  //ʹ��temp1��Ϊ���������������ͷ���
								temp1->next = NULL;
								int flag = 0;
								if (temp)
								{
									while (temp)  //��ȡ�������еġ���������¼
									{
										if (wcscoll(temp->flag, flag_shouru) == 0 && !wcscoll(temp->type, type_2))  //����flagɸѡ�����롱�ڵ�������ڵ������Ϊ��������
										{
											flag = 1;
											//ͷ�巨����������������
											Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11Ϊtemp1�����������еĸ����ڵ�
											wcscpy_s(temp11->flag, temp->flag);
											wcscpy_s(temp11->type, temp->type);
											wcscpy_s(temp11->money, temp->money);
											wcscpy_s(temp11->time, temp->time);
											temp11->next = temp1->next;
											temp1->next = temp11;
											//ͷ�巨����
											temp = temp->next;
											i++;
										}
										else { temp = temp->next; }
									}
								}
								if (flag == 0)  MessageBox(NULL, _T("û������Ŀ������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
								else    //���ڡ�����������ļ�¼
								{
									for (int k = 1; k <= i; k++)  //ð�ݴӴ�С����
									{
										Node* t = temp1;
										while (t->next->next)
										{
											int  next_num = _wtoi(t->next->money);
											int next_next_num = _wtoi(t->next->next->money);
											if (next_num < next_next_num) // С�������
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
									int j = 1; //iΪ�������е���ţ�int���ͣ�
									wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
									Node* temp2 = temp1->next;  //temp111Ϊ������ʱ�ĸ���ָ��
									//������
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
										position_y += 20;//������һ��
										outtextxy(424, position_y, num);//��ʾ���
										outtextxy(590, position_y, temp2->time);//��ʾ��¼ʱ��
										outtextxy(793, position_y, _T("����"));
										outtextxy(988, position_y, temp2->money);//��ʾ���
										temp2 = temp2->next;
										j++;
									}
									//���������
									MessageBox(NULL, _T("����ɹ���"), _T("����"), MB_SETFOREGROUND);
								}
							}
						}

						case 2:   //����ȫ����������
						{
							int i = 0; //iΪtemp1�����Ԫ�ظ���
							wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
							Node* temp = p->next;
							Node* temp1 = (Node*)malloc(sizeof(Node));  //ʹ��temp1��Ϊ֧�������ͷ���
							temp1->next = NULL;
							int flag = 0;
							if (temp)
							{
								while (temp)  //��ȡ�������е�֧����¼
								{
									if (wcscoll(temp->flag, flag_shouru) == 0)  //����flagɸѡ�����롱�ڵ�
									{
										flag = 1;
										//ͷ�巨������������
										Node* temp11 = (Node*)malloc(sizeof(Node));  //temp11Ϊtemp1�����������еĸ����ڵ�
										wcscpy_s(temp11->flag, temp->flag);
										wcscpy_s(temp11->type, temp->type);
										wcscpy_s(temp11->money, temp->money);
										wcscpy_s(temp11->time, temp->time);
										temp11->next = temp1->next;
										temp1->next = temp11;
										//ͷ�巨����
										temp = temp->next;
										i++;
									}
									else { temp = temp->next; }
								}
							}
							if (flag == 0)  MessageBox(NULL, _T("û������ļ�¼"), _T("��ѯ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							else    //��������ļ�¼
							{
								for (int k = 1; k <= i; k++)  //ð�ݴӴ�С����
								{
									Node* t = temp1;
									while (t->next->next)
									{
										int  next_num = _wtoi(t->next->money);
										int next_next_num = _wtoi(t->next->next->money);
										if (next_num < next_next_num) // С�������
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
								int j = 1; //iΪ�������е���ţ�int���ͣ�
								wchar_t num[10];//��ʱ���������ţ�wchar_t���ͣ�
								Node* temp2 = temp1->next;  //temp111Ϊ������ʱ�ĸ���ָ��
								//������
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
									position_y += 20;//������һ��
									outtextxy(424, position_y, num);//��ʾ���
									outtextxy(590, position_y, temp2->time);//��ʾ��¼ʱ��
									// �������
									if (!wcscoll(temp2->type, type_1))  //����Ϊ����
										outtextxy(793, position_y, _T("����"));
									if (!wcscoll(temp2->type, type_2))  //����Ϊ����
										outtextxy(793, position_y, _T("����"));
									//����������
									outtextxy(988, position_y, temp2->money);//��ʾ���
									temp2 = temp2->next;
									j++;
								}
								//���������
								MessageBox(NULL, _T("����ɹ���"), _T("����"), MB_SETFOREGROUND);
							}
							break;
						}
						}
					}
				}

				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//��������ذ�ť
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

//ɾ������
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
	loadimage(&index_delete, L"index_delete.jpg");//�����ʼ����
	putimage(0, 0, &index_delete);
	Sleep(100);
	loadimage(&delet, L"delet.jpg");//�����ʼ����
	putimage(0, 0, &delet);
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)//������ض����򣬼���֧������ť��������
				{
					loadimage(&delet_zhichu, L"delet_zhichu.jpg");
					putimage(0, 0, &delet_zhichu);
					int position_x = 409;//����š�������
					int position_y = 151;//����š�������
					setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
					settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������С20����ʽ����
					outtextxy(position_x, position_y, _T("���             ʱ��               ����             ���"));//��ʾ����һ�б�ͷ
					wchar_t num[100];//��ʱ����������
					Node* temp = p->next;
					int i = 1, j = -1;
					if (temp == NULL) MessageBox(NULL, _T("��¼Ϊ�գ��뷵�ز˵���Ӽ�¼��1"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);//���κ����ݣ�ֱ�ӵ���������������
					else
					{
						while (temp)  //���ԭ�м�¼
						{
							if (wcscoll(temp->flag, flag_zhichu) == 0)  //����flagɸѡ��֧�����ڵ�
							{
								//ö�ٵõ����
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
								position_y += 20;//������һ��
								outtextxy(424, position_y, num);//��ʾ���
								outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
								//��ʾ����
								{if (!wcscoll(temp->type, type_1))  //����Ϊ��ʳ
									outtextxy(793, position_y, _T("��ʳ"));
								if (!wcscoll(temp->type, type_2))  //����Ϊ����
									outtextxy(793, position_y, _T("����"));
								if (!wcscoll(temp->type, type_3))  //����Ϊ����
									outtextxy(793, position_y, _T("����"));
								if (!wcscoll(temp->type, type_4))  //����Ϊ��ͨ
									outtextxy(793, position_y, _T("��ͨ"));
								if (!wcscoll(temp->type, type_5))  //����Ϊ���
									outtextxy(793, position_y, _T("���"));
								}

								outtextxy(988, position_y, temp->money);//��ʾ���
								temp = temp->next;
								i++;
							}
							else { temp = temp->next; }
						}
						//whileѭ�����ԭ�м�¼����

						i--;       //��ʱi������i����¼
						if (i == 0)   MessageBox(NULL, _T("��¼Ϊ�գ��뷵�ز˵���Ӽ�¼��2"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);//���κ����ݣ�ֱ�ӵ���������������
						else
						{
							wchar_t temp_number[10];//��ʱ������������
							InputBox(temp_number, 10, _T("��ѡ����Ҫɾ�����ճ����"));
							//��wchar_t���ת��Ϊint
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
								if (j > i || j < 0)//˵�����������û���������ճ���ŵķ�Χ�� 
									MessageBox(NULL, _T("����������"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							if (j > 0 && j <= i)
							{
								if (j == 1 && i == 1)  //����һ���ڵ㣬���⴦��pre
								{
									if (p->next->next == NULL)//������ֻ��һ���ڵ�
									{
										pre = p;
										Node* deletnode = p->next;
										p->next = NULL;
										free(deletnode);
									}
									else  //ֻ��֧������һ���ڵ㣬�����롱Ҳ���ڽڵ�
									{
										Node* t = p->next;

										while (wcscoll(t->next->flag, flag_zhichu) != 0 && wcscoll(t->flag, flag_zhichu) != 0)  //����֧��������ڵ㽻����������
										{
											t = t->next;
										}
										if (t->next->next == NULL)  //��֧�����ڵ�ǡΪ���һ���ڵ�
										{
											pre = t;
											Node* deletnode = t->next;
											t->next = NULL;
											free(deletnode);
										}
										else                       //��֧�����ڵ����һ����ͬʱ�䲢���������һ���ڵ㣬��Ӱ��pre
										{

											if (p->next == t)    //��֧�����ڵ�λ��������ĵ�һ�������ж�
											{
												Node* deletnode = p->next;
												p->next = p->next->next;
												free(deletnode);
											}
											else        //��֧�����ڵ㲻λ��������ĵ�һ��
											{
												Node* deletnode = t->next;
												t->next = t->next->next;
												free(deletnode);
											}
										}
									}
									MessageBox(NULL, _T("ɾ���ɹ���"), _T("ɾ����¼"), MB_SETFOREGROUND);
									Save(p);
								}
								else if (j == 1 && i > 1)
								{
									Node* t = p->next;

									while (wcscoll(t->next->flag, flag_zhichu) != 0 && wcscoll(t->flag, flag_zhichu) != 0)  //����֧��������ڵ㽻����������
									{
										t = t->next;
									}
									if (t->next->next == NULL)  //��֧�����ڵ�ǡΪ���һ���ڵ�
									{
										pre = t;
										Node* deletnode = t->next;
										t->next = NULL;
										free(deletnode);
									}
									else                       //��֧�����ڵ����һ����ͬʱ�䲢���������һ���ڵ㣬��Ӱ��pre
									{

										if (p->next == t)    //��֧�����ڵ�λ��������ĵ�һ�������ж�
										{
											Node* deletnode = p->next;
											p->next = p->next->next;
											free(deletnode);
										}
										else        //��֧�����ڵ㲻λ��������ĵ�һ��
										{
											Node* deletnode = t->next;
											t->next = t->next->next;
											free(deletnode);
										}
									}
									MessageBox(NULL, _T("ɾ���ɹ���"), _T("ɾ����¼"), MB_SETFOREGROUND);
									Save(p);
								}
								else if (j == i) //jΪ��֧���������һ���ڵ�
								{
									Node* t = p->next;
									int count = 1;
									while (t && count < j - 1)  //��tָ���ɾ������ǰһ�����
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

									while (wcscoll(t->flag, flag_zhichu) != 0)  //����֧��������ڵ㽻����������
									{
										t = t->next;
									}

									if (t->next->next == NULL)   //��֧���������һ��ǡΪ���������һ��
									{
										pre = t;
										Node* deletnode = t->next;
										t->next = NULL;
										free(deletnode);
									}
									else                       //��֧���������һ������������������һ������Ӱ��pre
									{
										while (wcscoll(t->next->flag, flag_zhichu) != 0)  //����֧��������ڵ㽻����������
										{
											t = t->next;
										}
										Node* deletnode = t->next;
										t->next = t->next->next;
										free(deletnode);
									}
									MessageBox(NULL, _T("ɾ���ɹ���"), _T("ɾ����¼"), MB_SETFOREGROUND);
									Save(p);
								}
								else   //jΪһ���������j��=i
								{
									Node* t = p->next;
									int count = 1;
									while (t && count < j - 1)  //��tempָ���ɾ������ǰһ�����
									{
										if (wcscoll(t->flag, flag_zhichu) == 0) //ɸѡ����֧�����ڵ�
										{
											t = t->next;
											count++;
										}
										else
										{
											t = t->next;
										}
									}
									while (wcscoll(t->next->flag, flag_zhichu) != 0)  //����֧��������ڵ㽻����������
									{
										t = t->next;
									}
									Node* deletnode = t->next;
									t->next = t->next->next;
									free(deletnode);
									MessageBox(NULL, _T("ɾ���ɹ���"), _T("ɾ����¼"), MB_SETFOREGROUND);
									Save(p);//�����ļ����溯��
								}
							}
							else { MessageBox(NULL, _T("������Ŵ�������������"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND); }
						}
					}

				}

				if (msg.x > 113 && msg.x < 315 && msg.y > 369 && msg.y < 457)//������ض����򣬼������롱��ť��������
				{
					loadimage(&delet_shouru, L"delet_shouru.jpg");
					putimage(0, 0, &delet_shouru);
					int position_x = 409;//����š�������
					int position_y = 151;//����š�������
					setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
					settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������С20����ʽ����
					outtextxy(position_x, position_y, _T("���             ʱ��               ����             ���"));//��ʾ����һ�б�ͷ
					wchar_t num[100];//��ʱ����������
					Node* temp = p->next;
					int i = 1, j = -1;
					if (temp == NULL) MessageBox(NULL, _T("��¼Ϊ�գ��뷵�ز˵���Ӽ�¼��1"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);//���κ����ݣ�ֱ�ӵ���������������
					else
					{
						while (temp)  //���ԭ�м�¼
						{
							if (wcscoll(temp->flag, flag_shouru) == 0)  //����flagɸѡ�����롱�ڵ�
							{
								//ö�ٵõ����
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
								position_y += 20;//������һ��
								outtextxy(424, position_y, num);//��ʾ���
								outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
								//�������
								if (!wcscoll(temp->type, type_1))  //����Ϊ����
									outtextxy(793, position_y, _T("����"));
								if (!wcscoll(temp->type, type_2))  //����Ϊ����
									outtextxy(793, position_y, _T("����"));
								//����������
								outtextxy(988, position_y, temp->money);//��ʾ���
								temp = temp->next;
								i++;
							}
							else { temp = temp->next; }
						}//whileѭ�����ԭ�м�¼����

						i--;//��ʱi������i�����

						if (i == 0)  MessageBox(NULL, _T("��¼Ϊ�գ��뷵�ز˵���Ӽ�¼��2"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);//���κ����ݣ�ֱ�ӵ���������������
						else
						{
							wchar_t temp_number[10];//��ʱ������������
							InputBox(temp_number, 10, _T("��ѡ����Ҫɾ�������"));
							//��wchar_t���ת��Ϊint
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
							if (j > i || j < 0)//˵�����������û����������ŵķ�Χ�� 
								MessageBox(NULL, _T("����������"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}

							if (j > 0 && j <= i)
							{
								if (j == 1 && i == 1)  //����һ���ڵ㣬���⴦��pre
								{
									if (p->next->next == NULL)//������ֻ��һ���ڵ�
									{
										pre = p;
										Node* deletnode = p->next;
										p->next = NULL;
										free(deletnode);
									}
									else  //ֻ���������һ���ڵ㣬��֧����Ҳ���ڽڵ�
									{
										Node* t = p->next;
										while (wcscoll(t->next->flag, flag_shouru) != 0 && wcscoll(t->flag, flag_shouru) != 0)  //����֧��������ڵ㽻����������
										{
											t = t->next;
										}
										if (t->next->next == NULL)  //�����롱�ڵ�ǡΪ���һ���ڵ�
										{
											pre = t;
											Node* deletnode = t->next;
											t->next = NULL;
											free(deletnode);
										}
										else                       //�����롱�ڵ����һ����ͬʱ�䲢���������һ���ڵ㣬��Ӱ��pre
										{
											if (p->next == t)    //�����롱�ڵ�λ��������ĵ�һ�������ж�
											{
												Node* deletnode = p->next;
												p->next = p->next->next;
												free(deletnode);
											}
											else   //�����롱�ڵ㲻λ��������ĵ�һ��
											{
												Node* deletnode = t->next;
												t->next = t->next->next;
												free(deletnode);
											}
										}
									}
									MessageBox(NULL, _T("ɾ���ɹ���"), _T("ɾ����¼"), MB_SETFOREGROUND);
									Save(p);
								}
								else if (j == 1 && i > 1)
								{
									Node* t = p->next;

									while (wcscoll(t->next->flag, flag_shouru) != 0 && wcscoll(t->flag, flag_shouru) != 0)  //����֧��������ڵ㽻����������
									{
										t = t->next;
									}
									if (t->next->next == NULL)  //�����롱�ڵ�ǡΪ���һ���ڵ�
									{
										pre = t;
										Node* deletnode = t->next;
										t->next = NULL;
										free(deletnode);
									}
									else                       //�����롱�ڵ����һ����ͬʱ�䲢���������һ���ڵ㣬��Ӱ��pre
									{

										if (p->next == t)    //�����롱�ڵ�λ��������ĵ�һ�������ж�
										{
											Node* deletnode = p->next;
											p->next = p->next->next;
											free(deletnode);
										}
										else        //�����롱�ڵ㲻λ��������ĵ�һ��
										{
											Node* deletnode = t->next;
											t->next = t->next->next;
											free(deletnode);
										}
									}
									MessageBox(NULL, _T("ɾ���ɹ���"), _T("ɾ����¼"), MB_SETFOREGROUND);
									Save(p);
								}
								else if (j == i) //jΪ�����롱�����һ���ڵ�
								{
									Node* t = p->next;
									int count = 1;
									while (t && count < j - 1)  //��tָ���ɾ������ǰһ�����
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

										while (wcscoll(t->flag, flag_shouru) != 0)  //����֧��������ڵ㽻����������
										{
											t = t->next;
										}
										if (t->next->next == NULL)   //�����롱�����һ��ǡΪ���������һ��
										{
											pre = t;
											Node* deletnode = t->next;
											t->next = NULL;
											free(deletnode);
										}
										else                       //�����롱�����һ������������������һ������Ӱ��pre
										{
											while (wcscoll(t->next->flag, flag_shouru) != 0)  //����֧��������ڵ㽻����������
											{
												t = t->next;
											}
											Node* deletnode = t->next;
											t->next = t->next->next;
											free(deletnode);
										}
										MessageBox(NULL, _T("ɾ���ɹ���"), _T("ɾ����¼"), MB_SETFOREGROUND);
										Save(p);
									}
								}
								else   //jΪһ���������j��=i
								{
									Node* t = p->next;
									int count = 1;
									while (t && count < j - 1)  //��tempָ���ɾ������ǰһ�����
									{
										if (wcscoll(t->flag, flag_shouru) == 0) //ɸѡ����֧�����ڵ�
										{
											t = t->next;
											count++;
										}
										else
										{
											t = t->next;
										}
									}
									while (wcscoll(t->next->flag, flag_shouru) != 0)  //����֧��������ڵ㽻����������
									{
										t = t->next;
									}
									Node* deletnode = t->next;
									t->next = t->next->next;
									free(deletnode);
									MessageBox(NULL, _T("ɾ���ɹ���"), _T("ɾ����¼"), MB_SETFOREGROUND);
									Save(p);//�����ļ����溯��
								}
							}
							else { MessageBox(NULL, _T("������Ŵ�������������"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND); }
						}
					}
				}

				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//��������ذ�ť
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

//���ĺ���
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
	loadimage(&index_change, L"index_change.jpg");//�����ʼ����
	putimage(0, 0, &index_change);
	Sleep(100);
	loadimage(&change, L"change.jpg");//�����ʼ����
	putimage(0, 0, &change);
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 104 && msg.x < 320 && msg.y >183 && msg.y < 279)  //������ض����򣬼���֧������ť��������
				{
					loadimage(&change_zhichu, L"change_zhichu.jpg");
					putimage(0, 0, &change_zhichu);
					int position_x = 409;//����š�������
					int position_y = 151;//����š�������
					setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
					settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������С20����ʽ����
					outtextxy(position_x, position_y, _T("���             ʱ��               ����             ���"));//��ʾ����һ�б�ͷ
					wchar_t num[100];//��ʱ����������
					Node* temp = p->next;
					int i = 1, j = -1;
					if (temp == NULL) MessageBox(NULL, _T("��¼Ϊ�գ��뷵�ز˵���Ӽ�¼��1"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);//���κ����ݣ�ֱ�ӵ���������������
					else
					{
						while (temp)  //���ԭ�м�¼
						{
							if (wcscoll(temp->flag, flag_zhichu) == 0)  //����temp->flagɸѡ����֧�����ڵ�
							{
								//ö�ٵõ����
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
								position_y += 20;//������һ��
								outtextxy(424, position_y, num);//��ʾ���
								outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
								//��ʾ����
								{if (!wcscoll(temp->type, type_1))  //����Ϊ��ʳ
									outtextxy(793, position_y, _T("��ʳ"));
								if (!wcscoll(temp->type, type_2))  //����Ϊ����
									outtextxy(793, position_y, _T("����"));
								if (!wcscoll(temp->type, type_3))  //����Ϊ����
									outtextxy(793, position_y, _T("����"));
								if (!wcscoll(temp->type, type_4))  //����Ϊ��ͨ
									outtextxy(793, position_y, _T("��ͨ"));
								if (!wcscoll(temp->type, type_5))  //����Ϊ���
									outtextxy(793, position_y, _T("���"));
								}

								outtextxy(988, position_y, temp->money);//��ʾ���
								temp = temp->next;
								i++;
							}
							else { temp = temp->next; }
						}
						//whileѭ�����ԭ�м�¼����
						i--;//��ʱi��ʾ����i����¼
						if (i == 0)   MessageBox(NULL, _T("��¼Ϊ�գ��뷵�ز˵���Ӽ�¼��2"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);//���κ����ݣ�ֱ�ӵ���������������
						else
						{
							wchar_t temp_number[10];//��ʱ������������
							InputBox(temp_number, 10, _T("��ѡ����Ҫ�޸ĵ��ճ����"));
							//��wchar_t���ת��Ϊint
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
								if (j > i || j < 0)//˵�����������û���������ճ���ŵķ�Χ�� 
									MessageBox(NULL, _T("����������"), _T("�޸ļ�¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							if (j > 0 && j <= i)
							{
								Node* t = p->next;
								Node* pret = p;
								int count = 0;
								while (t && count < j)  //��tempָ���ɾ������ǰһ�����
								{
									if (wcscoll(t->flag, flag_zhichu) == 0) //ɸѡ����֧�����ڵ�
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
								 t = pret;  //�������롢֧�������������
								wchar_t temp_number[100];//�����޸ĵĽ��
								InputBox(temp_number, 100, _T("�������޸ĵĽ��"));
								wcscpy_s(t->money, temp_number);
								MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸ļ�¼"), MB_SETFOREGROUND);
								Save(p);

							}

						}
					}

				}

				if (msg.x > 113 && msg.x < 315 && msg.y > 369 && msg.y < 457)  //������ض����򣬼���֧������ť��������
				{
					loadimage(&change_shouru, L"change_shouru.jpg");
					putimage(0, 0, &change_shouru);
					int position_x = 409;//����š�������
					int position_y = 151;//����š�������
					setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
					settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������С20����ʽ����
					outtextxy(position_x, position_y, _T("���             ʱ��               ����             ���"));//��ʾ����һ�б�ͷ
					wchar_t num[100];//��ʱ����������
					Node* temp = p->next;
					int i = 1, j = -1;
					if (temp == NULL) MessageBox(NULL, _T("��¼Ϊ�գ��뷵�ز˵���Ӽ�¼��1"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);//���κ����ݣ�ֱ�ӵ���������������
					else
					{
						while (temp)  //���ԭ�м�¼
						{
							if (wcscoll(temp->flag, flag_shouru) == 0)  //����temp->flagɸѡ�������롱�ڵ�
							{
								//ö�ٵõ����
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
								position_y += 20;//������һ��
								outtextxy(424, position_y, num);//��ʾ���
								outtextxy(590, position_y, temp->time);//��ʾ��¼ʱ��
								//��ʾ����
								{if (!wcscoll(temp->type, type_1))  //����Ϊ����
									outtextxy(793, position_y, _T("����"));
								if (!wcscoll(temp->type, type_2))  //����Ϊ����
									outtextxy(793, position_y, _T("����"));
								}

								outtextxy(988, position_y, temp->money);//��ʾ���
								temp = temp->next;
								i++;
							}
							else { temp = temp->next; }
						}
						//whileѭ�����ԭ�м�¼����
						i--;//��ʱi��ʾ����i����¼
						if (i == 0)   MessageBox(NULL, _T("��¼Ϊ�գ��뷵�ز˵���Ӽ�¼��2"), _T("ɾ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);//���κ����ݣ�ֱ�ӵ���������������
						else
						{
							wchar_t temp_number[10];//��ʱ������������
							InputBox(temp_number, 10, _T("��ѡ����Ҫ�޸ĵ��ճ����"));
							//��wchar_t���ת��Ϊint
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
								if (j > i || j < 0)//˵�����������û���������ճ���ŵķ�Χ�� 
									MessageBox(NULL, _T("����������"), _T("�޸ļ�¼"), MB_ICONSTOP | MB_SETFOREGROUND);
							}
							if (j > 0 && j <= i)
							{
								Node* t = p->next;
								Node* pret = p;
								int count = 0;
								while (t && count < j)  
								{
									if (wcscoll(t->flag, flag_shouru) == 0) //ɸѡ�������롱�ڵ�
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
								t = pret; //��ʱtָ����޸Ľڵ�
								wchar_t temp_number[100];//�����޸ĵĽ��
								InputBox(temp_number, 100, _T("�������޸ĵĽ��"));
								wcscpy_s(t->money, temp_number);
								MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸ļ�¼"), MB_SETFOREGROUND);
								Save(p);
							}

						}
					}
				}

				if (msg.x > 1146 && msg.x < 1269 && msg.y > 571 && msg.y < 657)//��������ذ�ť
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

//���ʮ���ƿɶ��ļ�����
void output(Node* p) // ������������ļ���ʵ���Ƴ�����
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
	Node* t = p->next; // ����ָ��ָ��ͷ
	fp = fopen("ʮ���ƿɶ��ļ�.txt", "w");
	fprintf(fp, "֧��/����\t����\tʱ��\t\t���\t\n");
	while (t)
	{
		wchar_t type1[100];//type1��ʱ����֧��/����  wchar_t
		if (!wcscoll(t->flag, flag_zhichu))  
			wcscpy_s(type1, L"֧��");
		if (!wcscoll(t->flag, flag_shouru))  
			wcscpy_s(type1, L"����");
		wchar_t type2[100];//type2��ʱ�洢����  wchar_t
		if (!wcscoll(t->flag, flag_zhichu))
		{
			if (!wcscoll(t->type, type_1))
				wcscpy_s(type2, L"��ʳ");
			if (!wcscoll(t->type, type_2))
				wcscpy_s(type2, L"����");
			if (!wcscoll(t->type, type_3))
				wcscpy_s(type2, L"����");
			if (!wcscoll(t->type, type_4))
				wcscpy_s(type2, L"��ͨ");
			if (!wcscoll(t->type, type_5))
				wcscpy_s(type2, L"���");
		}
		else
		{
			if (!wcscoll(t->type, type_1))
				wcscpy_s(type2, L"����");
			if (!wcscoll(t->type, type_2))
				wcscpy_s(type2, L"����");
		}

		// ʹ��WchartoChar����ת��
		char type11[1024];//  ֧��/���� int
		char type22[1024];//  ���� int
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
	/*���ļ��ж���ȫ�ֱ���*/
	if (fp!=NULL)
	{
		char ch;
		fread(&ch, sizeof(char), 1, fp);
		if (!feof(fp)) rewind(fp);
		while (!feof(fp))
		{
			fread(&ch, sizeof(char), 1, fp);
			if (!feof(fp))  //��whileѭ��ǰ������һ�����ж��ļ��Ƿ�Ϊ��
			{
				fseek(fp, -sizeof(char), 1);// ���ļ�ָ�������ƶ�һ���ֽڣ����ز��Ե�ch��������
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
		/*�������*/
	}
	
	initgraph(1292, 678);
	
	Welcome(p,pre);

	return 0;
}