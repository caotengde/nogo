#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
#include <vector>
#include <algorithm> 
using namespace std;
int board[9][9];
bool dfs_air_visit[9][9];
const int cx[] = { -1,0,1,0 };
const int cy[] = { 0,-1,0,1 };
int available_list[81];
int equal1 = 0;
int g = 0;
int n = 0;
bool inBorder(int x, int y) { return x >= 0 && y >= 0 && x<9 && y<9; }
typedef struct Node{
	int loc = 0;
	int value = 0;
}Node;
Node node[81];
//true: has air
bool dfs_air(int fx, int fy)
{
	dfs_air_visit[fx][fy] = true;
	bool flag = false;
	for (int dir = 0; dir < 4; dir++)
	{
		int dx = fx + cx[dir], dy = fy + cy[dir];
		if (inBorder(dx, dy))
		{
			if (board[dx][dy] == 0)
				flag = true;
			if (board[dx][dy] == board[fx][fy] && !dfs_air_visit[dx][dy])
				if (dfs_air(dx, dy))
					flag = true;
		}
	}
	return flag;
}

//true: available
bool judgeAvailable(int fx, int fy, int col)
{
	if (board[fx][fy]) return false;
	board[fx][fy] = col;
	memset(dfs_air_visit, 0, sizeof(dfs_air_visit));
	if (!dfs_air(fx, fy))
	{
		board[fx][fy] = 0;
		return false;
	}
	for (int dir = 0; dir < 4; dir++)
	{
		int dx = fx + cx[dir], dy = fy + cy[dir];
		if (inBorder(dx, dy))
		{
			if (board[dx][dy] && !dfs_air_visit[dx][dy])
				if (!dfs_air(dx, dy))
				{
					board[fx][fy] = 0;
					return false;
				}
		}
	}
	board[fx][fy] = 0;
	return true;
}
int staticValueOne(int loc, int times){
	board[loc/9][loc%9] = -1;
	int PowerN1 = -times;
	int Power1 = -times;
	for(int i = 0; i <= 8; i++)
		for(int j = 0; j <= 8; j++)
		{
			if(!judgeAvailable(i, j, 1)) Power1++;
		 } 
    board[loc/9][loc%9] = 1;
    for(int i = 0; i <= 8; i++)
		for(int j = 0; j <= 8; j++)
		{
			if(!judgeAvailable(i, j, -1)) PowerN1++;
		}
	board[loc/9][loc%9] = 0;
	return Power1 + PowerN1; 
}
bool cmp(Node a, Node b){
	return a.value > b.value;
}
void diguima(){
	if(equal1 == 1) return;
    g++;
    if(g == 5) return;
    int res;
    for(int j = 0; j < equal1; j++){
			res = node[j].loc;
			board[res/9][res%9] = (g%2 == 1 ? -1 : 1);
			for(int l = 0; l < equal1; l++){
				if(l != j) node[l].value = (node[l].value + staticValueOne(node[l].loc, n))/2;
			}
		}
		sort(node, node+equal1,cmp);
		    int e2 = equal1;
			equal1 = 0;
		    for(int i = 0; i < e2; i++)
			if(node[i].value == node[0].value) equal1++;
			diguima();
			board[res/9][res%9] = 0;
}
int main()
{
	srand((unsigned)time(0));

	int x, y, n;
	cin >> n;
	for (int i = 0; i < n - 1; i++)
	{
		cin >> x >> y; if (x != -1) board[x][y] = 1;	//对方
		cin >> x >> y; if (x != -1) board[x][y] = -1; //我方
	}
	cin >> x >> y;  if (x != -1) board[x][y] = 1;	//对方

	//此时board[][]里存储的就是当前棋盘的所有棋子信息,x和y存的是对方最近一步下的棋


	/************************************************************************************/
	/***********在下面填充你的代码，决策结果（本方将落子的位置）存入new_x和new_y中****************/

	//下面仅为随机策略的示例代码，可删除
 //合法位置表 
	int k = 0;
	for (int i = 0; i<9; i++)
		for (int j = 0; j<9; j++)
			if (judgeAvailable(i, j, x == -1 ? 1 : -1))
			{
				available_list[k] = i * 9 + j;
				k++;
			}
	for(int i = 0; i < k; i++){
		node[i].loc = available_list[i];
		node[i].value = staticValueOne(node[i].loc, n);
	}
	sort(node, node+k-1,cmp);
	
	for(int i = 0; i < k; i++)
		if(node[i].value == node[0].value) equal1++;//equal比下标多一个 
    diguima();
	int result = node[rand()%equal1].loc;
	int new_x = result / 9;
	int new_y = result % 9;

	/***********在上方填充你的代码，决策结果（本方将落子的位置）存入new_x和new_y中****************/
	/************************************************************************************/
	cout << new_x <<" "<< new_y << endl;
	return 0;
}