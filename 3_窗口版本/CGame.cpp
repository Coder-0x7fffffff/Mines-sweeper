#include "stdafx.h"
#include "CGame.h"

bool CGame::GameEnd()
{
	return game_over;
}

CGame::CGame()  //默认难度初始化
{
	SetLevel(0);
	StartGame();
}

bool CGame::IfFlaged(int x, int y)
{
	return show[x][y] == '@' ? true : false;
}

bool CGame::GetAllMine()
{
	return mine_get == mine_num;
}

int CGame::GetMapWide()
{
	return wide;
}

void CGame::LevelUp()
{
	level++;
	level = level % 3;
}

int CGame::GetLevel()
{
	return level;
}

void CGame::SetLevel(int lev)
{
	this->level = lev;
}

void CGame::StartGame()
{
	game_over = false;
	mine_get = 0;
	switch (level)   //选择游戏难度
	{
	case 0:
		wide = 8;
		percent = 0.15;
		break;
	case 1:
		wide = 9;
		percent = 0.15;
		break;
	case 2:
		wide = 10;
		percent = 0.2;
		break;
	default:
		wide = 8;
		percent = 0.15;
	}
	mine_num = wide * wide*percent;
	map = new int*[wide + 2];   //初始化数组
	show = new char*[wide + 2];
	for (int i = 0; i < wide + 2; i++)
	{
		map[i] = new int[wide + 2];
		memset(map[i], 0, sizeof(int)*(wide + 2));
		show[i] = new char[wide + 2];
		memset(show[i], '#', sizeof(char)*(wide + 2));
	}
	srand((unsigned int)time(NULL));  //随机雷
	for (int i = 1; i <= mine_num; i++)
	{
		int tp = rand() % (wide*wide);
		while (1)
		{
			if (map[tp / wide + 1][tp%wide + 1] != -1)
			{
				map[tp / wide + 1][tp%wide + 1] = -1;
				break;
			}
			tp = rand() % (wide*wide);
		}
	}
	for (int i = 0; i <= wide + 1; i++)  //记录雷个数
	{
		for (int j = 0; j <= wide + 1; j++)
			if (map[i][j] != -1)
			{
				if (i - 1 >= 0 && j - 1 >= 0 && map[i - 1][j - 1] == -1)   //左上
					map[i][j]++;
				if (i - 1 >= 0 && j + 1 <= wide + 1 && map[i - 1][j + 1] == -1)   //左下
					map[i][j]++;
				if (i + 1 <= wide + 1 && j - 1 >= 0 && map[i + 1][j - 1] == -1)   //右上
					map[i][j]++;
				if (i + 1 <= wide + 1 && j + 1 <= wide + 1 && map[i + 1][j + 1] == -1)   //右下
					map[i][j]++;
				if (j - 1 >= 0 && map[i][j - 1] == -1)   //上
					map[i][j]++;
				if (j + 1 <= wide + 1 && map[i][j + 1] == -1)   //下
					map[i][j]++;
				if (i - 1 >= 0 && map[i - 1][j] == -1)   //左
					map[i][j]++;
				if (i + 1 <= wide + 1 && map[i + 1][j] == -1)   //右
					map[i][j]++;
			}
	}
}

CGame::~CGame()
{
	for (int i = 0; i < wide + 1; i++)
	{
		delete[](map[i]);
		delete[]show[i];
	}
	delete[]map;
	delete[]show;
}

void CGame::Print(HDC hdc)
{
	RECT rec;
	HBRUSH brush;
	int block_wide = (WND_WIDE - WND_FRAME_GAP * 2) / wide;
	for (int j = 1; j <= wide; j++)
	{
		for (int i = 1; i <= wide; i++)
		{
			brush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, brush);
			Rectangle(hdc, WND_FRAME_GAP + block_wide * (i - 1), WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE) + block_wide * (j - 1), WND_FRAME_GAP + block_wide * i, WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE) + block_wide * j);
			DeleteObject(brush);
		}
	}
	wchar_t str[10];
	if (!GameEnd())
	{
		for (int i = 1; i <= wide; i++)
		{
			for (int j = 1; j <= wide; j++)
			{
				if (show[i][j] == '$')
				{
					if (map[i][j])
					{
						wsprintf(str, TEXT("%d"), map[i][j]);
						rec.left = WND_FRAME_GAP + block_wide * (i - 1);
						rec.top = WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE) + block_wide * (j - 1);
						rec.right = WND_FRAME_GAP + block_wide * i;
						rec.bottom = WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE) + block_wide * j;
						DrawText(hdc, str, wcslen(str), &rec, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

					}
				}
				else if (show[i][j] == '#'|| show[i][j] == '@')
				{
					brush = CreateSolidBrush(RGB(128, 128, 128));
					SelectObject(hdc, brush);
					Rectangle(hdc,
						WND_FRAME_GAP + block_wide * (i - 1),
						WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE) + block_wide * (j - 1),
						WND_FRAME_GAP + block_wide * i,
						WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE) + block_wide * j
					);
					DeleteObject(brush);
					if (show[i][j] == '@')
					{
						Ellipse(hdc,
							WND_FRAME_GAP + block_wide * (i - 1),
							WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE) + block_wide * (j - 1),
							WND_FRAME_GAP + block_wide * i,
							WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE) + block_wide * j
						);
					}
				}
			}
		}
	}
}

void CGame::FlgMine(int x, int y)
{
	if (show[x][y] == '#')
	{
		show[x][y] = '@';
		if (map[x][y] == -1)
			mine_get++;
	}
	if (mine_get == mine_num)
		game_over = true;
}

void CGame::RemoveFlgMine(int x, int y)
{
	if (show[x][y] == '@')
	{
		show[x][y] = '#';
		if (map[x][y] == -1)
			mine_get--;
	}
}

void CGame::Open(int x, int y)
{
	if (show[x][y] == '@')return;
	if (show[x][y] == '#')
	{
		if (map[x][y] == -1)
		{
			game_over = true;
			return;
		}
		show[x][y] = '$';
		//-----bfs-------
		queue<POINT> que, que2;
		POINT now, temp, num_block;
		now.x = x;
		now.y = y;
		que.push(now);
		while (!que.empty())
		{
			now = que.front();
			que.pop();
			if (now.y - 1 >= 0 && map[now.x][now.y - 1] == 0 && show[now.x][now.y - 1] != '@')   //上
			{
				if (show[now.x][now.y - 1] != '$')
				{
					temp.x = now.x;
					temp.y = now.y - 1;
					que.push(temp);
				}
				show[now.x][now.y - 1] = '$';
				que2.push(temp);
			}
			if (now.y + 1 <= wide + 1 && map[now.x][now.y + 1] == 0 && show[now.x][now.y + 1] != '@')   //下
			{
				if (show[now.x][now.y + 1] != '$')
				{
					temp.x = now.x;
					temp.y = now.y + 1;
					que.push(temp);
				}
				show[now.x][now.y + 1] = '$';
				que2.push(temp);
			}
			if (now.x - 1 >= 0 && map[now.x - 1][now.y] == 0 && show[now.x - 1][now.y] != '@')   //左
			{
				if (show[now.x - 1][now.y] != '$')
				{
					temp.x = now.x - 1;
					temp.y = now.y;
					que.push(temp);
				}
				show[now.x - 1][now.y] = '$';
				que2.push(temp);
			}
			if (now.x + 1 <= wide + 1 && map[now.x + 1][now.y] == 0 && show[now.x + 1][now.y] != '@')   //右
			{
				if (show[now.x + 1][now.y] != '$')
				{
					temp.x = now.x + 1;
					temp.y = now.y;
					que.push(temp);
				}
				show[now.x + 1][now.y] = '$';
				que2.push(temp);
			}
		}
		while (!que2.empty())  //扩展边界
		{
			now = que2.front();
			que2.pop();
			int x = now.x;
			int y = now.y;
			if (x - 1 >= 0 && y - 1 >= 0)   //左上
			{
				if (show[x - 1][y - 1] != '@')
					show[x - 1][y - 1] = '$';
			}
			if (x - 1 >= 0 && y + 1 < wide)  //左下
			{
				if (show[x - 1][y + 1] != '@')
					show[x - 1][y + 1] = '$';
			}
			if (x + 1 < wide && y - 1 >= 0)  //右上
			{
				if(show[x + 1][y - 1] != '@')
					show[x + 1][y - 1] = '$';
			}
			if (x + 1 < wide && y + 1 < wide)   //右下
			{
				if(show[x + 1][y + 1] != '@')
					show[x + 1][y + 1] = '$';
			}
			if (y - 1 >= 0)   //上
			{
				if(show[x][y - 1] != '@')
				show[x][y - 1] = '$';
			}
			if (y + 1 < wide)   //下
			{
				if(show[x][y + 1] != '@')
					show[x][y + 1] = '$';
			}
			if (x - 1 >= 0)   //左
			{
				if(show[x - 1][y] != '@')
					show[x - 1][y] = '$';
			}
			if (x + 1 < wide)   //右
			{
				if(show[x + 1][y] != '@')
					show[x + 1][y] = '$';
			}
		}
	}
}

bool CGame::Judge()
{
	if (game_over)
		return 0;
	else return 1;
}

void CGame::LROpen(int x, int y)
{
	if (show[x][y] == '#' && show[x][y] == '@')return;
	if (
		(show[x - 1][y - 1] == '@' && map[x - 1][y - 1] != -1) ||
		(show[x][y - 1] == '@' && map[x][y - 1] != -1) ||
		(show[x + 1][y - 1] == '@' && map[x + 1][y - 1] != -1) ||
		(show[x - 1][y] == '@' && map[x - 1][y] != -1) ||
		(show[x + 1][y] == '@' && map[x + 1][y] != -1) ||
		(show[x - 1][y + 1] == '@' && map[x - 1][y + 1] != -1) ||
		(show[x][y + 1] == '@' && map[x][y + 1] != -1) ||
		(show[x + 1][y + 1] == '@' && map[x + 1][y + 1] != -1)
		)  //乱插
	{
		game_over = true;
		return;
	}
	if (
		(show[x - 1][y - 1] != '@' && map[x - 1][y - 1] == -1) ||
		(show[x][y - 1] != '@' && map[x][y - 1] == -1) ||
		(show[x + 1][y - 1] != '@' && map[x + 1][y - 1] == -1) ||
		(show[x - 1][y] != '@' && map[x - 1][y] == -1) ||
		(show[x + 1][y] != '@' && map[x + 1][y] == -1) ||
		(show[x - 1][y + 1] != '@' && map[x - 1][y + 1] == -1) ||
		(show[x][y + 1] != '@' && map[x][y + 1] == -1) ||
		(show[x + 1][y + 1] != '@' && map[x + 1][y + 1] == -1)
		)  //棋不够
	{
		return;
	}
	if (map[x - 1][y - 1] != -1)  //打开
		Open(x - 1,y - 1);
	if (map[x][y - 1] != -1)
		Open(x,y - 1);
	if (map[x + 1][y - 1] != -1)
		Open(x + 1,y - 1);
	if (map[x - 1][y] != -1)
		Open(x - 1,y);
	if (map[x + 1][y] != -1)
		Open(x + 1,y);
	if (map[x - 1][y + 1] != -1)
		Open(x - 1,y + 1);
	if (map[x][y + 1] != -1)
		Open(x,y + 1);
	if (map[x + 1][y + 1] != -1)
		Open(x + 1,y + 1);
}