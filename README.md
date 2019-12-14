# Mines-sweeper #
## 【需求规格说明】 ##
- （1）题号：3 

- （2）题目：

	完成一个控制台扫雷游戏。每个网格相邻区域只包含同一行和同一列紧邻的 4 个网格。


![](https://github.com/Coder-0x7fffffff/Mines-sweeper/blob/master/img/1.png)

	
• 规则：

（1）随机产生 8*8 的雷分布图；

（2）用户“y”表示游戏，“q”退出游戏；

（3）让用户输入行列号，用键盘“m”标雷，“k”打开； 

（4）打开区域为雷或者全部区域被翻开，则 game over。 

• 参考：

（1）P62 例 4.3 输出雷分布图, P74 例 4.5 打开无雷连通区域； 

（2） 按如下 CGame 类的定义完成代码。 

	class CGame
	{
		public:
		CGame();              //初始化
		virtual ~CGame();
		void Print();           //打印当前图 
		bool DoStep();
		void FlgMine(int x,int y);      //标记雷 
		void Open(int x,int y);        //打开该结点
		bool Judge();            //判断是否结束 
		void Run();             //游戏运行 
	} 


• 进阶加分：    

（1）设置不同难度，变换网格数和地雷比例；

（2）每个网格相邻区域设定为 8 个（既加入对角线方块）。 

（3）自阐述创新点。

（3）问题分析：问题分为四部分，第一是棋盘的存储与显示内容存储的问题，第二是扩展连通0区域，第三是程序界面交互问题，第四是左右键一起点击时快速打开。

## 【算法设计】 ##

- （1）设计思想：

首先，棋盘存储与显示内容存储采用两个动态二维数组分别表示，第一个二维数组存储雷的位置以及周围八格雷的个数，第二个二维数组表示用户是否打开或标记该方块。然后，打开无雷连通区域采用光度搜索（BFS）并改进采用双队列（queue容器），第一个队列用于原始BFS搜索使用，第二个队列用于存储搜索到的元素，最后集中扩展边界即展开到最外圈数字。其次，是界面交互问题，采用Windows32API纯API编程写的可点击交互界面。最后，左右键一起点击时如果插旗不足则不会展开，如果插旗错误则游戏结束，首先可以判断插错旗直接游戏结束，然后判断有雷的地方未插旗则不展开，最后直接对周围八格掉用打开函数即可。

- （2）设计表示：

![](https://github.com/Coder-0x7fffffff/Mines-sweeper/blob/master/img/2.png)

## 【调试报告】 ##

- （1）问题：

	1.描述问题：时间长了之后游戏会刷新异常
	
	解决方案：由于GDI对象泄露，所以每次设置画笔使用之后删除画笔
	
	2.描述问题：展开时标记错误的旗子会被删除
	
	解决方案：展开时判断是否插了旗子

- （2）创新：

	1.Win32API+GDI 使界面人性化，操作简单化
	
	2.BFS搜索，扩展连续相通的0到数字为止


## 【附录】 ##

- （1）源程序清单：

	3_窗口版本.cpp     //windows消息循环
	
	CGame.cpp         //游戏类实现
	
	CGame.h           //游戏类声明
	
	define.h            //常量定义（便于修改界面）

- （2）测试数据及运行结果：


![](https://github.com/Coder-0x7fffffff/Mines-sweeper/blob/master/img/3.png)
![](https://github.com/Coder-0x7fffffff/Mines-sweeper/blob/master/img/4.png)
![](https://github.com/Coder-0x7fffffff/Mines-sweeper/blob/master/img/5.png)
![](https://github.com/Coder-0x7fffffff/Mines-sweeper/blob/master/img/6.png)