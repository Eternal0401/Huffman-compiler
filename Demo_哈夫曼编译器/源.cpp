#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <fstream>
#include <cstring>
#include<graphics.h> //EasyX图形库头文件
#include <conio.h>

using namespace std;

typedef struct //坐标数据
{
	double x;
	double y;
}Point;

typedef struct node //结点信息
{
	int weight;//结点权值
	char data;//结点数据
	int parent, lch, rch;//双亲、左子、右子
	double idx, idy;//坐标定位
	Point p;
}HT_Node, * HuffmanTree;

typedef char** HuffmanCode;//编码信息

class Huffman_compiler  //哈夫曼编译器类
{
public:
	void select(HuffmanTree& HT, int n, int& s1, int& s2);//寻找两个根结点都是0的最小元素与次最小元素
	void Initialization(HuffmanTree& HT, int n,char s);//初始化，创建哈夫曼树
	void Encoding(HuffmanTree HT, HuffmanCode& HC, int n);//对哈夫曼树编码
	void TextCode(HuffmanTree HT, HuffmanCode& HC, int n);//对文件进行编码
	void Decoding(HuffmanTree HT, int n);//对文件进行译码 
	void Print(HuffmanTree HT);//打印代码文件	 
	void TreePrint(HuffmanTree HT, int n);//打印哈夫曼树
};

void menu()//功能菜单
{
	cout << "------哈夫曼编译器------" << endl;
	cout << "I:初始化(Initialization)" << endl;
	cout << "E:编码(Encoding)" << endl;
	cout << "D:译码(Decoding)" << endl;
	cout << "P:印代码文件(Print)" << endl;
	cout << "T:印哈夫曼树(Treeprinting)" << endl;
	cout << "Q:退出(Quit)" << endl;
}

int main()//主程序
{
	HuffmanTree Tree=NULL;
	HuffmanCode HC;
	Huffman_compiler T;
	int n=0;
	char c,s=0;
	int flag = 1;
	menu();
	cout << endl << "请输入所取功能代码：" << endl;
	while (1)
	{
		cin >> c;
		switch (c)
		{
		case 'I':
			cout << "请选择元素字符以及权值输入方式：" << endl;
			cout << "0：终端输入，适合测试案例1（字符数目小，手动输入方便。）" << endl;
			cout << "1：文件输入，适合测试案例2（字符数目大，手动输入不便。）" << endl;
			
			while (flag==1)
			{
				cin >> s;
				if (s == '0')
				{
					cout << "终端输入：" << endl;
					cout << "请输入元素数目：" << endl;
					cin >> n;
					T.Initialization(Tree, n, s);
					flag = 0;
				}
				else if (s == '1')
				{
					cout << "文件输入：" << endl;
					ifstream file;
					file.open("测试案例2.txt");
					string s1, s2;
					int num = 0;
					while (!file.eof())
					{
						getline(file, s1);
						getline(file, s2);
						num++;
					}
					file.close();
					n = num;
					cout << "文件输入的元素数目为：" << n << endl;
					T.Initialization(Tree, n, s);
					flag = 0;
				}
				else
				{
					cout << "输入错误，请重新输入..." << endl;
					flag = 1;
				}
			}
			cout << endl << "该功能已完成，请输入其他所需功能代码：" << endl;
			break;
		case'E':
			if (Tree != NULL)
			{
				T.Encoding(Tree, HC, n);
				T.TextCode(Tree, HC, n);
				cout << endl << "该功能已完成，请输入其他所需功能代码：" << endl;
			}
			else
				cout << "未创建哈夫曼树！" << endl;
			break;
		case'D':
			if (Tree != NULL)
			{
				T.Decoding(Tree, n);
				cout << endl << "该功能已完成，请输入其他所需功能代码：" << endl;
			}
			else
				cout << "未创建哈夫曼树！" << endl;
			break;
		case'P':
			if (Tree != NULL)
			{
				T.Print(Tree);
				cout << endl << "该功能已完成，请输入其他所需功能代码：" << endl;
			}
			else
				cout << "未创建哈夫曼树！" << endl;
			break;
		case'T':
			if (Tree != NULL)
			{
				T.TreePrint(Tree, n);
				cout << endl<< "该哈夫曼树已绘图完成，如再需查看请输入对应功能代码。" << endl;
				cout << "该功能已完成，请输入其他所需功能代码：" ;
			}
			else
				cout << "未创建哈夫曼树！" << endl;
			break;
		case'Q':
			exit(0);
		default:
			cout << "输入错误！请重新输入...";
			cin >> c;
		}
	}
	return 0;
}
//各方法函数：
void Huffman_compiler::select(HuffmanTree& HT, int n, int& s1, int& s2)//寻找两个根结点都是0的最小元素
{
	int Min, S_Min;
	Min = S_Min = 999;
	for (int i = 1; i <= n; i++)
	{
		if ((HT[i].parent == 0) && HT[i].weight < Min)
		{
			Min = HT[i].weight;
			s1 = i;
		}
	}
	int temp = HT[s1].weight;//将获取的值暂存起来，再赋回值防止被重复选择
	HT[s1].weight = 999;
	for (int i = 1; i <= n; i++)
	{
		if ((HT[i].parent == 0) && HT[i].weight < S_Min)
		{
			S_Min = HT[i].weight;
			s2 = i;
		}
	}
	HT[s1].weight = temp;
}

void Huffman_compiler::Initialization(HuffmanTree& HT, int n,char s)//初始化，创建哈夫曼树
{
	//哈夫曼树初始化
	int m = 0;
	if (n <= 1)
	{
		cout << "字符个数不足" << endl;
		return;
	}
	m = 2 * n - 1;
	HT = new HT_Node[m + 1];
	for (int i = 1; i <= m; i++)
	{
		HT[i].parent = 0;
		HT[i].lch = 0;
		HT[i].rch = 0;
	}
	int flag = 1;
	while (flag == 1)
	{
		if (s == '0')
		{
			//手动输入字符以及对应权值
			for (int i = 1; i <= n; i++)
			{
				cout << "请输入第" << i << "个字符：" << endl;
				char ch, c;
				c = getchar();//确保不会跳过cin.get()操作
				ch = cin.get();
				if (ch == '\n') continue;//确保不会接受回车这一字符，保证获取的字符是所输入的字符
				HT[i].data = ch;
				cout << "请输入第" << i << "个字符的对应权值：" << endl;
				cin >> HT[i].weight;
			}
			flag = 0;
		}
		else if (s == '1')
		{
			//文件输入字符以及对应权值
			ifstream file;
			file.open("测试案例2.txt");
			string s1,s2;

			cout << "元素字符与对应权值：" << endl;
			while (!file.eof())
			{
				for (int i = 1; i <= n; i++)
				{
					getline(file, s1);
					for (int j = 0; j < s1.length(); j++)
						HT[i].data = s1[j];
					getline(file, s2);
						HT[i].weight = stoi(s2);
					cout << s1 << " " << s2 << endl;
				}
			}
			file.close();
			flag = 0;
		}
	}
	//创建哈夫曼树
	int s1, s2;
	for (int i = n + 1; i <= m; i++)
	{
		select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;

		HT[i].lch = s1;
		HT[i].rch = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//将所创建的哈夫曼树写入文件中
	ofstream out;
	out.open("HuffmanTree.txt", ios::out);
	int i = 1;
	for (i = 1; i <= n; i++)
	{
		out << i << " " << HT[i].data << " " << HT[i].weight << " " << HT[i].parent << " " << HT[i].lch << " " << HT[i].rch << endl;
	}
	for (; i <= m; i++)
	{
		out << i << " " << " " << " " << HT[i].weight << " " << HT[i].parent << " " << HT[i].lch << " " << HT[i].rch << endl;
	}
	out.close();
}

void Huffman_compiler::Encoding(HuffmanTree HT, HuffmanCode& HC, int n)//编码
{
	int start, parent, child;
	HC = new char* [n + 1];
	char* CN = new char[n];
	CN[n - 1] = '\0';
	for (int i = 1; i <= n; i++)
	{
		start = n - 1;
		child = i;
		parent = HT[i].parent;
		while (parent != 0)
		{
			--start;
			if (HT[parent].lch == child)
				CN[start] = '0';
			else
				CN[start] = '1';
			child = parent;
			parent = HT[parent].parent;
		}
		HC[i] = new char[n - start];//为第i个字符编码分配空间
		strcpy(HC[i], &CN[start]);//将编码复制到HC中
	}
	delete[]CN;
	cout << "对应字符编码为：" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << HT[i].data << ":" << HC[i] << endl;
	}
	//将字符编码写入文件
	ofstream fout("Code.txt");
	for (int i = 1; i <= n; i++)
	{
		fout << HT[i].data << ":" << HC[i];
		fout << endl;
	}
	fout.close();
}

void Huffman_compiler::TextCode(HuffmanTree HT, HuffmanCode& HC, int n)//对文件进行编码
{
	ifstream file;
	file.open("ToBeTran.txt");
	if (!file)
	{
		cout << "ToBeTran文件打开失败！" << endl;
		exit(0);
	}
	ofstream fout("CodeFile.txt");
	int flag = 0;
	char ch;
	while (file.get(ch))
	{
		for (int i = 1; i <= n; i++)
		{
			if (ch == HT[i].data)
			{
				fout << HC[i];
				flag = 1;
				break;
			}
			else
				flag = 0;
		}
		if (!flag)
			fout << ch;
	}
	file.close();
	cout << "编码完成！" << endl;
}

void Huffman_compiler::Decoding(HuffmanTree HT, int n)//对文件进行译码 
{
	ifstream file;
	file.open("CodeFile.txt");
	if (!file)
	{
		cout << "文件CodeFile.txt打开失败!" << endl;
		exit(0);
	}
	ofstream fout("TextFile.txt");
	int m = 2 * n - 1;;
	char ch;
	while (file.get(ch))
	{
		if (ch == '1')
			m = HT[m].rch;
		else if (ch == '0')
			m = HT[m].lch;
		if (HT[m].lch == 0 && HT[m].rch == 0)
		{
			fout << HT[m].data;
			m = 2 * n - 1;
		}
	}
	file.close();
	cout << "译码完成！" << endl;
}

void Huffman_compiler::Print(HuffmanTree HT)//打印代码文件	 
{
	char ch;
	ifstream fileCode;
	ofstream fout("CodePrint.txt");
	int i = 1;

	fileCode.open("CodeFile.txt");
	if (!fileCode)
	{
		cout << "打开CodeFile.txt失败!" << endl;
		exit(0);
	}
	cout << "正文编码结果：" << endl;
	while (fileCode.get(ch))
	{
		cout << ch;
		fout << ch;
		if (i == 50)
		{
			cout << endl;
			fout << endl;
			i = 0;
		}
		i++;
	}
	fileCode.close();
	cout << endl;
}

void Huffman_compiler::TreePrint(HuffmanTree HT, int n)//打印哈夫曼树(用EasyX图形库实现)
{
	//初始化
	HT[2 * n - 1].idx = 1;
	HT[2 * n - 1].idy = 1;
	for (int i = 2 * n - 1; i >= n+1; i--)//定位节点坐标
	{
		HT[HT[i].lch].idx = 2 * HT[i].idx;
		HT[HT[i].rch].idx = 2 * HT[i].idx + 1;
		HT[HT[i].lch].idy = 2 * HT[i].idy;
		HT[HT[i].rch].idy = 2 * HT[i].idy + 1;
	}
	for (int i = 2 * n - 1; i >= 1; i--)//给idx域赋值
	{
		HT[i].idx = HT[i].idx /
			pow(2, (int)(log10(HT[i].idx) / log10(2)));
	}
	for (int i = 1; i <= n ; i++)//求出每个i叶子节点的idx排序
	{
		for (int j = 0, k = 1; j < n; j++)
		{
			if (HT[j].idx < HT[i].idx)
				k++;
			HT[i].p.x = 100 + (double)k * 30;//根据叶子节点的idx排序求出叶子节点的x坐标
		}
	}
	for (int i = n+1; i < 2 * n ; i++)//根据叶子节点求出双亲的x坐标
	{
		HT[i].p.x = (HT[HT[i].lch].p.x +
			HT[HT[i].rch].p.x) / 2;
	}
	for (int i = 1; i < 2 * n ; i++)
	{
		HT[i].p.y = (double)40 * int(log10(HT[i].idy) / log10(2));//根据节点的层数求出节点的y坐标
	}
	//打印树状哈夫曼树
	initgraph(1000, 600);
	setcolor(WHITE);
	setbkcolor(WHITE);
	setfillstyle(WHITE);
	cleardevice();
	setcolor(BLACK);

	for (int i = 1; i < 2 * n ; i++)//绘制节点，以小圆代替
	{
		circle((int)HT[i].p.x - 100, 100 + (int)HT[i].p.y, 2);
		if (HT[i].lch == 0)
			outtextxy((int)HT[i].p.x - 100, 105 + (int)HT[i].p.y, HT[i].data);
		if (HT[i].lch != 0)//绘制节点的左右子树
		{
			outtextxy((int)(HT[i].p.x + HT[HT[i].lch].p.x) / 2 - 100,//左0
				(int)(HT[i].p.y + HT[HT[i].lch].p.y) / 2 + 100, '0');
			outtextxy((int)(HT[i].p.x + HT[HT[i].rch].p.x) / 2 - 100,//右1
				(int)(HT[i].p.y + HT[HT[i].rch].p.y) / 2 + 100, '1');
			line((int)HT[i].p.x - 100, (int)HT[i].p.y + 100,//绘制节点与左子树的连线
				(int)HT[HT[i].lch].p.x - 100,
				(int)HT[HT[i].lch].p.y + 100);
			line((int)HT[i].p.x - 100, (int)HT[i].p.y + 100,//绘制节点与右子树的连线
				(int)HT[HT[i].rch].p.x - 100,
				(int)HT[HT[i].rch].p.y + 100);
		}
	}
	TCHAR s[] = _T("按回车返回");
	outtextxy(10, 10, s);
	ExMessage m;
	m = getmessage(EX_CHAR);
	closegraph(); 
}