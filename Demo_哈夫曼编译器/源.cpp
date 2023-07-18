#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <fstream>
#include <cstring>
#include<graphics.h> //EasyXͼ�ο�ͷ�ļ�
#include <conio.h>

using namespace std;

typedef struct //��������
{
	double x;
	double y;
}Point;

typedef struct node //�����Ϣ
{
	int weight;//���Ȩֵ
	char data;//�������
	int parent, lch, rch;//˫�ס����ӡ�����
	double idx, idy;//���궨λ
	Point p;
}HT_Node, * HuffmanTree;

typedef char** HuffmanCode;//������Ϣ

class Huffman_compiler  //��������������
{
public:
	void select(HuffmanTree& HT, int n, int& s1, int& s2);//Ѱ����������㶼��0����СԪ�������СԪ��
	void Initialization(HuffmanTree& HT, int n,char s);//��ʼ����������������
	void Encoding(HuffmanTree HT, HuffmanCode& HC, int n);//�Թ�����������
	void TextCode(HuffmanTree HT, HuffmanCode& HC, int n);//���ļ����б���
	void Decoding(HuffmanTree HT, int n);//���ļ��������� 
	void Print(HuffmanTree HT);//��ӡ�����ļ�	 
	void TreePrint(HuffmanTree HT, int n);//��ӡ��������
};

void menu()//���ܲ˵�
{
	cout << "------������������------" << endl;
	cout << "I:��ʼ��(Initialization)" << endl;
	cout << "E:����(Encoding)" << endl;
	cout << "D:����(Decoding)" << endl;
	cout << "P:ӡ�����ļ�(Print)" << endl;
	cout << "T:ӡ��������(Treeprinting)" << endl;
	cout << "Q:�˳�(Quit)" << endl;
}

int main()//������
{
	HuffmanTree Tree=NULL;
	HuffmanCode HC;
	Huffman_compiler T;
	int n=0;
	char c,s=0;
	int flag = 1;
	menu();
	cout << endl << "��������ȡ���ܴ��룺" << endl;
	while (1)
	{
		cin >> c;
		switch (c)
		{
		case 'I':
			cout << "��ѡ��Ԫ���ַ��Լ�Ȩֵ���뷽ʽ��" << endl;
			cout << "0���ն����룬�ʺϲ��԰���1���ַ���ĿС���ֶ����뷽�㡣��" << endl;
			cout << "1���ļ����룬�ʺϲ��԰���2���ַ���Ŀ���ֶ����벻�㡣��" << endl;
			
			while (flag==1)
			{
				cin >> s;
				if (s == '0')
				{
					cout << "�ն����룺" << endl;
					cout << "������Ԫ����Ŀ��" << endl;
					cin >> n;
					T.Initialization(Tree, n, s);
					flag = 0;
				}
				else if (s == '1')
				{
					cout << "�ļ����룺" << endl;
					ifstream file;
					file.open("���԰���2.txt");
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
					cout << "�ļ������Ԫ����ĿΪ��" << n << endl;
					T.Initialization(Tree, n, s);
					flag = 0;
				}
				else
				{
					cout << "�����������������..." << endl;
					flag = 1;
				}
			}
			cout << endl << "�ù�������ɣ��������������蹦�ܴ��룺" << endl;
			break;
		case'E':
			if (Tree != NULL)
			{
				T.Encoding(Tree, HC, n);
				T.TextCode(Tree, HC, n);
				cout << endl << "�ù�������ɣ��������������蹦�ܴ��룺" << endl;
			}
			else
				cout << "δ��������������" << endl;
			break;
		case'D':
			if (Tree != NULL)
			{
				T.Decoding(Tree, n);
				cout << endl << "�ù�������ɣ��������������蹦�ܴ��룺" << endl;
			}
			else
				cout << "δ��������������" << endl;
			break;
		case'P':
			if (Tree != NULL)
			{
				T.Print(Tree);
				cout << endl << "�ù�������ɣ��������������蹦�ܴ��룺" << endl;
			}
			else
				cout << "δ��������������" << endl;
			break;
		case'T':
			if (Tree != NULL)
			{
				T.TreePrint(Tree, n);
				cout << endl<< "�ù��������ѻ�ͼ��ɣ�������鿴�������Ӧ���ܴ��롣" << endl;
				cout << "�ù�������ɣ��������������蹦�ܴ��룺" ;
			}
			else
				cout << "δ��������������" << endl;
			break;
		case'Q':
			exit(0);
		default:
			cout << "�����������������...";
			cin >> c;
		}
	}
	return 0;
}
//������������
void Huffman_compiler::select(HuffmanTree& HT, int n, int& s1, int& s2)//Ѱ����������㶼��0����СԪ��
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
	int temp = HT[s1].weight;//����ȡ��ֵ�ݴ��������ٸ���ֵ��ֹ���ظ�ѡ��
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

void Huffman_compiler::Initialization(HuffmanTree& HT, int n,char s)//��ʼ����������������
{
	//����������ʼ��
	int m = 0;
	if (n <= 1)
	{
		cout << "�ַ���������" << endl;
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
			//�ֶ������ַ��Լ���ӦȨֵ
			for (int i = 1; i <= n; i++)
			{
				cout << "�������" << i << "���ַ���" << endl;
				char ch, c;
				c = getchar();//ȷ����������cin.get()����
				ch = cin.get();
				if (ch == '\n') continue;//ȷ��������ܻس���һ�ַ�����֤��ȡ���ַ�����������ַ�
				HT[i].data = ch;
				cout << "�������" << i << "���ַ��Ķ�ӦȨֵ��" << endl;
				cin >> HT[i].weight;
			}
			flag = 0;
		}
		else if (s == '1')
		{
			//�ļ������ַ��Լ���ӦȨֵ
			ifstream file;
			file.open("���԰���2.txt");
			string s1,s2;

			cout << "Ԫ���ַ����ӦȨֵ��" << endl;
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
	//������������
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
	//���������Ĺ�������д���ļ���
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

void Huffman_compiler::Encoding(HuffmanTree HT, HuffmanCode& HC, int n)//����
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
		HC[i] = new char[n - start];//Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &CN[start]);//�����븴�Ƶ�HC��
	}
	delete[]CN;
	cout << "��Ӧ�ַ�����Ϊ��" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << HT[i].data << ":" << HC[i] << endl;
	}
	//���ַ�����д���ļ�
	ofstream fout("Code.txt");
	for (int i = 1; i <= n; i++)
	{
		fout << HT[i].data << ":" << HC[i];
		fout << endl;
	}
	fout.close();
}

void Huffman_compiler::TextCode(HuffmanTree HT, HuffmanCode& HC, int n)//���ļ����б���
{
	ifstream file;
	file.open("ToBeTran.txt");
	if (!file)
	{
		cout << "ToBeTran�ļ���ʧ�ܣ�" << endl;
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
	cout << "������ɣ�" << endl;
}

void Huffman_compiler::Decoding(HuffmanTree HT, int n)//���ļ��������� 
{
	ifstream file;
	file.open("CodeFile.txt");
	if (!file)
	{
		cout << "�ļ�CodeFile.txt��ʧ��!" << endl;
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
	cout << "������ɣ�" << endl;
}

void Huffman_compiler::Print(HuffmanTree HT)//��ӡ�����ļ�	 
{
	char ch;
	ifstream fileCode;
	ofstream fout("CodePrint.txt");
	int i = 1;

	fileCode.open("CodeFile.txt");
	if (!fileCode)
	{
		cout << "��CodeFile.txtʧ��!" << endl;
		exit(0);
	}
	cout << "���ı�������" << endl;
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

void Huffman_compiler::TreePrint(HuffmanTree HT, int n)//��ӡ��������(��EasyXͼ�ο�ʵ��)
{
	//��ʼ��
	HT[2 * n - 1].idx = 1;
	HT[2 * n - 1].idy = 1;
	for (int i = 2 * n - 1; i >= n+1; i--)//��λ�ڵ�����
	{
		HT[HT[i].lch].idx = 2 * HT[i].idx;
		HT[HT[i].rch].idx = 2 * HT[i].idx + 1;
		HT[HT[i].lch].idy = 2 * HT[i].idy;
		HT[HT[i].rch].idy = 2 * HT[i].idy + 1;
	}
	for (int i = 2 * n - 1; i >= 1; i--)//��idx��ֵ
	{
		HT[i].idx = HT[i].idx /
			pow(2, (int)(log10(HT[i].idx) / log10(2)));
	}
	for (int i = 1; i <= n ; i++)//���ÿ��iҶ�ӽڵ��idx����
	{
		for (int j = 0, k = 1; j < n; j++)
		{
			if (HT[j].idx < HT[i].idx)
				k++;
			HT[i].p.x = 100 + (double)k * 30;//����Ҷ�ӽڵ��idx�������Ҷ�ӽڵ��x����
		}
	}
	for (int i = n+1; i < 2 * n ; i++)//����Ҷ�ӽڵ����˫�׵�x����
	{
		HT[i].p.x = (HT[HT[i].lch].p.x +
			HT[HT[i].rch].p.x) / 2;
	}
	for (int i = 1; i < 2 * n ; i++)
	{
		HT[i].p.y = (double)40 * int(log10(HT[i].idy) / log10(2));//���ݽڵ�Ĳ�������ڵ��y����
	}
	//��ӡ��״��������
	initgraph(1000, 600);
	setcolor(WHITE);
	setbkcolor(WHITE);
	setfillstyle(WHITE);
	cleardevice();
	setcolor(BLACK);

	for (int i = 1; i < 2 * n ; i++)//���ƽڵ㣬��СԲ����
	{
		circle((int)HT[i].p.x - 100, 100 + (int)HT[i].p.y, 2);
		if (HT[i].lch == 0)
			outtextxy((int)HT[i].p.x - 100, 105 + (int)HT[i].p.y, HT[i].data);
		if (HT[i].lch != 0)//���ƽڵ����������
		{
			outtextxy((int)(HT[i].p.x + HT[HT[i].lch].p.x) / 2 - 100,//��0
				(int)(HT[i].p.y + HT[HT[i].lch].p.y) / 2 + 100, '0');
			outtextxy((int)(HT[i].p.x + HT[HT[i].rch].p.x) / 2 - 100,//��1
				(int)(HT[i].p.y + HT[HT[i].rch].p.y) / 2 + 100, '1');
			line((int)HT[i].p.x - 100, (int)HT[i].p.y + 100,//���ƽڵ���������������
				(int)HT[HT[i].lch].p.x - 100,
				(int)HT[HT[i].lch].p.y + 100);
			line((int)HT[i].p.x - 100, (int)HT[i].p.y + 100,//���ƽڵ���������������
				(int)HT[HT[i].rch].p.x - 100,
				(int)HT[HT[i].rch].p.y + 100);
		}
	}
	TCHAR s[] = _T("���س�����");
	outtextxy(10, 10, s);
	ExMessage m;
	m = getmessage(EX_CHAR);
	closegraph(); 
}