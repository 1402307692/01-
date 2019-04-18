#include<iostream>
using namespace std;
 int main()
{
	int v[100], w[100], c, n, m[100][10],x[100];
	cout << "请输入物品数目"<<endl;
	cin >> n;
	cout << "请输入背包容量" << endl;
	cin >> c;
	cout << "请输入各物品的重量" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> w[i];
	}
	cout << "请输入各物品的价值" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	Knapsack( v, w, c, n, m);
	Traceback(m,w,c,n,x);
}
int min(int x, int y)
{
	if (x >= y)
		return y;
}
int max(int x, int y)
{
	if (x <= y)
		return x;
}
void Knapsack(int v[],int w[], int c, int n, int m[][10])
{
	int jMax = min(w[n] - 1, c);//背包剩余容量上限 范围[0~W[n-1]]
	for (int j = 0; j <= jMax; j++)
	{
		m[n][j] = 0;
	}
	for (int j = w[n]; j <= c; j++)//限制范围【W[n]-c】
	{
		m[n][j] = v[n];
	}
	for (int i = n - 1; i > 1; i--)
	{
		jMax = min(w[i] - 1, c);
		for (int j = 0; j <= jMax; j++)//背包不同剩余容量j<=jMax<c
		{
			m[i][j] = m[i + 1][j];//没产生任何效益
		}
		for (int j = w[i]; j <= c; j++)//剩余容量从第i个的到c遍历，如果
		{
			m[i][j] = max(m[i + 1][j], m[i + 1][j - w[i]] + v[i]);//效益值增长vi
		}
	}
	m[1][c] = m[2][c];
	if (c > -w[1])
	{
		m[1][c] = max(m[1][c], m[2][c - w[1]] + v[1]);
	}
}
void Traceback(int m[][10], int w[], int c, int n, int x[])
{
	//构造数组x【n】，将添加的物品放入数组x【n】为一 中
	for (int i = 1; i < n; i++)
	{
		if (m[i][c] == m[i + 1][c])
		{
			x[i] = 0;//未加入物品i+1
		}
		else
		{
			x[i] = 1;
			c -= w[i];
		}
	}
	x[n] = (m[n][c]) ? 1 : 0;//如果m[n][c]的值不为0则把1赋值给x[n],否则把0赋值给x[n].
}