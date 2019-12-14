#pragma once
#include <iostream>
#include <time.h>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
#include "define.h"


using namespace std;

class CGame
{
private:
	int **map;   //num���� -1��
	char **show;  //#δ�򿪵� $�򿪵� @���� 
	int wide;
	int mine_num;  //����
	int mine_get;  //��ǵ����׸���
	float percent; //����
	bool game_over;  //�ȵ���
	int level; //�Ѷ�
public:
	CGame();  //Ĭ���Ѷȳ�ʼ��
	bool IfFlaged(int x,int y);  //�Ƿ����
	bool GetAllMine();  // ��ȡ�׵ĸ���
	int GetMapWide();  //�õ���ͼ���
	void LevelUp();  //�Ѷ��л�
	int GetLevel();   //�õ���ǰ�Ѷ�
	void SetLevel(int level);   //�����Ѷ�
	void StartGame();  //��ʼ��Ϸ/���¿�ʼ��Ϸ
	virtual ~CGame();
	bool GameEnd();   //��Ϸ�Ƿ����
	void Print(HDC hdc);  //����
	void FlgMine(int x, int y);  //����
	void RemoveFlgMine(int x, int y);  //ȡ������
	void Open(int x, int y);  //��
	bool Judge();  //�ж���Ϸ�Ƿ����
	void LROpen(int x,int y);  //���Ҽ�һ�����ٴ�
};