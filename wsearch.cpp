#include<iostream>
using namespace std;
#define R 1
#define L 4
#define D 2
#define U 3
int crt = 0;
template<class T>
class Qnode {
public:
	T data;
	Qnode* up;
	Qnode* down;
	Qnode* right;
	Qnode* left;
public:
	Qnode(T a):data(a),up(NULL),down(NULL),right(NULL),left(NULL){}
};
template <class T>
class QList {
private:	
	Qnode<T>* header;
	Qnode<T>* traverse;
	int rows;
	int cols;
	int occ=0;
public:
	QList(int x,int y):rows(x),cols(y),header(NULL){}
	void insert(T a) {
		Qnode<T>* temp=new Qnode<T>(a);
		traverse = header;
		if (header == NULL) {
			header = temp;
			occ++;
			return;
		}
		Qnode<T>* tu=NULL;
		Qnode<T>* tl=NULL;
		for (int i = 0; i < occ / cols; i++) {
			//if (traverse->down != NULL) {
			tu = traverse;
			traverse = traverse->down;
			//}
		}
		for (int i = 0; i < occ%cols; i++) {
			tl = traverse;
			if(tu)
			tu = tu->right;
			traverse = traverse->right;
		}
		traverse = temp;
		if(tl)
		tl->right = temp;
		temp->left = tl;
		if(tu)
		tu->down = temp;
		temp->up = tu;
		occ++;
	}
	void print() {
		for (int i = 0; i < occ; i++) {
			if (i % cols == 0) {
				traverse = header;
				cout << endl;
				for (int j = 0; j < i / rows; j++)
					traverse = traverse->down;
			}
			else {
				traverse = traverse->right;
			}
			cout << traverse->data<<" ";
		}
	}
	string str_re(int x, int y,int d) {
		traverse = header;
		string str;
		for (int i = 0; i <x; i++) {
			traverse = traverse->down;
		}
		for (int i = 0; i <y; i++)
			traverse = traverse->right;
			
		switch (d)
		{
		case 1:
			while (traverse != NULL) {
				str += traverse->data;
				traverse = traverse->right;
			}
		case 2:
			while (traverse != NULL) {
				str += traverse->data;
				traverse = traverse->down;
			}
			break;
		case 3:
			while (traverse != NULL) {
				str += traverse->data;
				traverse = traverse->up;
			}
			break;
		case 4:
			while (traverse != NULL) {
				str += traverse->data;
				traverse = traverse->left;
			}
		}
		return str;
			
	}
	bool stcp(string &a,string &b){
		a.shrink_to_fit();
		b.shrink_to_fit();
		bool p = false;
		if (a[0] != b[0]&& a[0]!='*'&&a[0]!='+'&&a[0]!='?')
			return 0;
		int k = 0;
		for (int i = 0; i < b.size(); i++) {
			if (i >= a.size())
				return 0;
			if (a[i] != b[i] && a[i] != '*' && a[i] != '+' && a[i] != '?')
				return 0;
			if (a[i] == '*') {
				int o = i + 1;
				if (i + 1 != a.size())
				for (int j = i; j < b.size(); j++) 
						if (a[o] == b[j]) {
							p = true;
							i = j;
							break;
						}
				if (!p)
					return 0;
			}
			k++;
		}

		if (k < 3)
			return 0;
		return 1;
	}
	bool find(string* p, int w) {
		string temp;
		for(int a=0;a<rows;a++)
			for(int b=0;b<cols;b++)
				for (int j = 0; j < w; j++) {
					if (a == 1)
						a = 2;
					else if (a == 2)
						a = 1;
					for (int i = 1; i < 5; i++) {
						temp = str_re(a, b, i);
						//cout << temp << endl;
						if (stcp(temp, p[j])) {
							crt++;
							//cout << p[j] << " ";
							cout << a << " " << b << " ";
							switch (i)
							{
							case 1:
								cout << "R" << endl; break;
							case 2:
								cout << "D" << endl; break;
							case 3:
								cout << "U" << endl; break;
							case 4:
								cout << "L" << endl; break;
							}
						}
					}
					if (a == 1)
						a = 2;
					else if (a == 2)
						a = 1;
				}
		return 1;
	}
};

int main() {
	int x, y;
	cin >> x >> y;
	char temp;
	QList<char> list(x, y);
	for (int i = 0; i < x; i++) {
		int j = 0;
		cin >> temp;
		while (temp != 10) {
			if (temp != 32) {
				list.insert(temp);
				j++;
			}
			temp = getchar();
			
		}
		//if(j-1!=y)
		for (; j < y; j++) {
			temp = '0';
			list.insert(temp);
		}
	}
	int w;
	cin >> w;
	string* p = new string[w];
	for (int i = 0; i < w; i++) {
		cin >> temp;
		while (temp != 10) {
			if(temp!=32)
			p[i] += temp;
			temp = getchar();
		}
	}
	//for (int i = 0; i < x; i++)
		//for (int j = 0; j < y; j++)
		//	for (int k = 1; k < 5; k++)
			//	cout << list.str_re(i, j, k) << endl;
	list.find(p, w);
	if (crt == 0)
		cout << "N";
	return 0;
	//list.print();
}