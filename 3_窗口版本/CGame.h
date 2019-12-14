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
	int **map;   //num个数 -1雷
	char **show;  //#未打开的 $打开的 @插旗 
	int wide;
	int mine_num;  //个数
	int mine_get;  //标记到的雷个数
	float percent; //比例
	bool game_over;  //踩到雷
	int level; //难度
public:
	CGame();  //默认难度初始化
	bool IfFlaged(int x,int y);  //是否插旗
	bool GetAllMine();  // 获取雷的个数
	int GetMapWide();  //得到地图宽度
	void LevelUp();  //难度切换
	int GetLevel();   //得到当前难度
	void SetLevel(int level);   //设置难度
	void StartGame();  //开始游戏/重新开始游戏
	virtual ~CGame();
	bool GameEnd();   //游戏是否结束
	void Print(HDC hdc);  //绘制
	void FlgMine(int x, int y);  //插旗
	void RemoveFlgMine(int x, int y);  //取消插旗
	void Open(int x, int y);  //打开
	bool Judge();  //判断游戏是否结束
	void LROpen(int x,int y);  //左右键一起点快速打开
};