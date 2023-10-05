#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h> 
#define MaxSize 15
#define Inf 10000  //无穷大 
bool visited[MaxSize]; 
static int sn=-1;
typedef int ElemType;
//单链表 
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
//双链表 
typedef struct DNode{
	int data;
	struct DNode *prior,*next;
}DNode,*DLinklist;
//二叉树孩子表示法
typedef struct BiNode{
	char data;
	BiNode *lchild,*rchild;
}BiNode,*BiTree;
//树的孩子表示法
typedef struct CTreeNode{
	int vnum;//图中结点编号 
	struct CTreeNode *child[MaxSize];
	int cnum;//孩子个数 
}*CTree,CTNode; 
//图邻接矩阵表示法
typedef struct {
	char Vex[MaxSize];//顶点集 
	int Edge[MaxSize][MaxSize];//边级  无权图不存在边是0，存在是1，对角线是0；有全图不存在边是∞，存在边是权值，对角线是0 
	int vexnum,arcnum;//当前顶点个数和边集 
}MGraph;
//图的邻接表表示法
//边结点
typedef struct ArcNode{
	int adjvex;//指向顶点编号
	struct ArcNode *next;//指向下一条弧的指针
//	int weight;//权值信息 
}ArcNode; 
//顺序存储顶点结点 
typedef struct VNode{
	char data;
	ArcNode *first;//第一条边结点 
}VNode,AdjList[MaxSize]; 
//存储图的邻接表 
typedef struct {
	AdjList adjlist;//顶点顺序表；
	int vexnum,arcnum;//顶点个数，边个数； 
}LGraph; 
//栈
typedef struct{
	int top;//=-1;
	ElemType elem[MaxSize];
}Stack; 
//队列
typedef struct Queue{
	int count;//=0;
	ElemType elem[MaxSize];
	//int front=0,rear=0;
	int front,rear;
}Queue;
typedef struct Flink{
	char num[10];
	char name[10];
	int score;
	Flink *next;
}*FLink,Flnode;
void Qsort(int a[],int m,int n);//快速排序  最好：nlogn,最坏：n方，平均：nlogn；空间：nlogn；最坏情况:有序，不稳定 //注意在素组最后的无穷大虚拟记录，来确保从左到右循环的终止，而且要在进入函数之前定义好 
void Bubble(int a[],int n);//冒泡排序  最好：n 最坏：n方  平均：n方； 空间：1；稳定；最坏情况：逆序，适用于基本有序 注意flag使用（在排序是没发生交换则有序退出） 
void Insertsort(int a[],int n);//直接插入排序  最好：n  最坏：n方  平均：n方  空间：1；稳定  最坏情况：逆序，适用于基本有序 要移动元素 
void ZBInsert(int a[],int n);//折半插入排序  最好：n  最坏：n方  平均：n方  空间：1；稳定   只能用于顺序表 比较次数与初始状态无关 
void Shellsort(int a[],int n);//希尔排序 最好：--  最坏：n方  平均：n  空间1；不稳定 性能与选取的分组长度序列有关一般选d/2 
void Ssort(int a[],int n);//直接选择排序  最好： n方  最坏：n方 平均：n方  空间  1；不稳定  性能（比较次数和时间复杂度）与初始状态无关 
void BuildMaxHeap(int a[],int len);//建堆 
void AdjustDown(int a[],int k,int len);//调整堆
void Heapsort(int a[],int len);//堆排序   最好：nlogn 最坏：nlogn 平均：nlogn 空间:1;不稳定   性能（比较次数和时间复杂度）与初始状态无关
void Merge(int a[],int p,int q,int n,int b[]);//两个序列的合并  i第一个序列的起始地址，j是第二个序列的起始地址，n是合并好的序列的起始地址 
void Mpass(int a[],int n,int L,int b[]); //一趟合并算法   n是序列总长度，L是每次合并相邻子序列的长度 
void Msort(int a[],int n,int b[]);//二路归并排序   最好：nlogn  最坏: nlogn 平均：nlogn 空间：n；  稳定  性能与初始状态无关 

void CreatLGraph(LGraph &G);//建图（邻接表） 
void PrintLGraph(LGraph G);//输出图 
void BFS(LGraph G,int v);//广度优先遍历
void BFSMinpath(LGraph G,int v);//广度优先遍历求无权图最短路径（建立的距离数组d，每次遍历到更新距离） 
bool BFSIstree(LGraph G,int v);//广度优先遍历判断图是否为一棵树 （判断visted数组若出现冲突则存在环） 
void DFS(LGraph G,int v);//深度优先遍历（递归）(要定义全局标记数组visited)
void dfs(LGraph G,int v);//深度优先遍历（非递归） 
void ddfs(LGraph G,int i,int j,int d[],int n);
void FindPath(LGraph G,int u,int v,int k,int path[]);//深度优先遍历找所有路径（定义全局变量访问数组visited,path为路径数组，k为路径上结点的次序） 
void InDegree(LGraph G,int result[]);//遍历邻接表计算图中各顶点的入度 
void VList(LGraph G,LGraph VG);//创建图的逆邻接表
void BGraphTree(LGraph G,CTree &T,int v);//创建图的层序遍历生成树 
void Floyed(LGraph G,int dis[MaxSize][MaxSize]);//弗洛伊德算法求图中任意两点间的最短路径 

void CreatBiTree(BiTree &bt);//二叉树创建（递归先序）
void PreOrder(BiTree bt);//先序递归遍历
void InOrder(BiTree bt);//中序递归遍历
void PostOrder(BiTree bt);//后序递归遍历 
void FPreOrder(BiTree bt);//先序非递归遍历
void FInOrder(BiTree bt);//中序非递归遍历
void FPostOrder(BiTree bt);//后序非递归遍历 
void LevelOrder(BiTree bt);//层序遍历
void BtHeight(BiTree bt,int &h);//递归求树高 
void Presum(BiTree bt,int &q);//递归先序求和 
void BtSwap(BiTree bt);//递归交换左右子树 
void BtDelete(BiTree bt);//递归删除树，释放空间 
BiNode *CommonAncestor(BiTree bt,BiNode *p,BiNode *q);//递归判断最近的公共祖先 
void Common(BiTree bt,BiNode *p,BiNode *q,BiNode **r);
BiNode* Ancestor(BiTree bt,BiNode *p);//递归找到所有祖先
bool Isson(BiTree T,BiNode *u,BiNode *v);//递归判断u是否为v的祖先 
BiTree piCreate(char pre[],char in[],int pl,int pr,int il,int ir);//根据先序和中序创建二叉树 
int LHeight(BiTree bt);//层序遍历求树高
int LWidth(BiTree bt);//层序遍历求树宽 
int LLnodecount(BiTree bt);//层序求二叉树叶子or单分支or双分支节点or独生叶节点个数
void IsBalance(BiTree bt,int &b,int &h);//判断二叉树是否平衡，b为1平衡，h为高度 
void ReLevel(BiTree bt);//从上到下，从右到左层序遍历二叉树 
void BiString(BiTree &bt,char s[]);//真题210问题（红皮书35） 正向 
BiTree RBiString(char a[],int n); //逆向
BiTree DBiString(char a[]);//递归 
bool Push(Stack &S,ElemType e);//入栈
ElemType Pop(Stack &S);//出栈
bool EnQueue(Queue &Q,ElemType e);//入队
ElemType DeQueue(Queue &Q);//出队

bool InitList(LinkList &L);//带头节点的单链表初始化 
bool InitDlist(DLinklist &L);//带头结点双链表初始化
LinkList List_TailInsert(LinkList &L);//尾插法建立链表
LinkList List_HeadInsert(LinkList &L);//头插法建立链表
void creat(DLinklist &L);//带头结点的双链表创建 
bool ListInsert(LinkList &L,int n,ElemType e);//插入节点
bool InsertNextNode(LNode *p,ElemType e);//后插操作
LNode *LocateElem(LinkList L,ElemType e);//按值查找
LNode *GetElem(LinkList L,int i);//按位查找
int Length(LinkList L);//求表长
void Del(LinkList &L,int x);//删除结点 
bool InsertNextDNode(DNode *p,DNode *s);//双链表后插操作
void PrintList(LinkList L);//输出链表
bool ListDelete(LinkList &L,int i);//按位序删除
LinkList Reverse(LinkList &L);//就地逆置
int Search_k(LinkList &L,int k);//找到倒数k个元素
LNode *IsCommon(LinkList p,LinkList q);//判断是否两个链表相交
bool Insert(LinkList &L,int n,int e);//在第n个位置插入值为e的结点
void LInsertSort(LinkList &L);//链表直接插入排序 
void exchange(LinkList &L,LNode *p);// 2001计学  1.交换链表结点
LinkList List_TailInsert_1(LinkList &L,LNode* &p,int a);

void Inverse(int a[],int m);//数组逆置 
int *Mul_Num(int a[],int b[],int m,int n);//大数相乘 
void Matrix(int num[][MaxSize],int n);//螺旋矩阵输出
void SubSet(char ch[],int n);//求子集问题  输出ch的所有子集
void Insert2(LinkList &L);// 2000计学 链表插入排序
void dbubble(int a[],int n);// 2001计学  3.双端冒泡
int *insert(int a[],int n,int e);//2002  1.递归插入 
int maxlength(int a[],int n);//2002 2.最长递归子序列 
LNode *mergelist(LNode *p,LNode *q);//2002 3.无序链表合并 
LNode *eightlist(LNode *p,LNode *q);//2002 4.8进制链表相加 
void m90(int a[MaxSize][MaxSize],int n);//2003 二维矩阵顺时针旋转90度 
double funxy(double x,double y);//2003 5.非递归实现函数 
void deletex(BiTree &root,char x);//2013 删除>=x的二叉查找树的结点
void Delallx(BiTree &bt,BiNode *p,char x,BiNode *&newhead);//删除二叉查找树中>=x 的所有结点 
void Delx(BiTree &bt,char x);//删除值为x的二叉排序树的结点 
bool IsPrime(int a);//判断是否为质数 
BiTree ret(BiTree root,char x);
void fun1(BiTree root,int sum[],int n);//2015 2 
void fun2(BiTree root); 
void DoubleSort(DLinklist &L);//2019  1
void prelevel(BiTree bt,int l);//软学2018 1 
LinkList fun_2015_4_966(LinkList &L); 
bool duichen(BiNode *r,BiNode *l);//2020 计专 递归判断树是否对称
//int main(){
//	FLink fl;
//	FLink p,h;
//	int a;
//	char a1[10],a2[10];
//	FILE *f;
//		fl=NULL;
//		f=fopen("D:\\Code\\test\\tt.txt","r");
//		while(!feof(f)){
//			p=(Flnode *)malloc(sizeof(Flnode));
//			fscanf(f,"%s",p->name);
//			fscanf(f,"%s",p->num);
//			fscanf(f,"%d",&p->score);
//			if(fl==NULL){
//				fl=p;
//				h=fl;
//			}
//			else{
//				fl->next=p;
//				p->next=NULL;
//				fl=p;
//			}
//		}
//	while(h!=NULL){
//		printf("%s %s %d\n",h->name,h->num,h->score);
//		h=h->next;
//	}
//	fclose(f);
//	return 0;
//}

//5 6 4 8 3 9 2 9999
//542*3***986**7**1**
//431*2***875**6**9**
//111*1***111**1**1**
//ABD*G***CEH**I**F**
//int main(){
//	//6321***4*5**87**9**
//	//1234***5**67**8*9**
//	BiTree L;
////	BiNode *u,*v;
//	CreatBiTree(L);
//	InOrder(L);
//	printf("\n%d",duichen(L->rchild,L->lchild));
	//printf("\n");
//	Delallx(L,L,'4',u);
	//InOrder(u);
//prelevel(L,1);
	//PreOrder1(L,u,v);
//	printf("%c   ",L->data);
//	printf("%d",Isson(L,u,v));
//	BiNode *temp;
//	printf("\n%d",LWidth(L));
//	fun2(L);
///	char pre[8]="ABDECFG";
//	char in[8]="DBEACGF"; 
//	L=piCreate(pre,in,0,6,0,6);
//	int q=0;
//	Presum(L,q);
//	printf("%d",q);
	//PreOrder(L);
//	deletex(L,'3',temp);
//	temp=ret(L,'8');
	//printf("%c",temp->data);
	//printf("%c",L->data);
//	LNode *p=NULL,*q=NULL,*r=NULL;
//	p=List_TailInsert(p);
//	q=List_TailInsert(L);
//	int a[MaxSize][MaxSize]={0};
//	m90(a,4);
//	PrintList(p);
//	p=fun_2015_4_966(p);
//	PrintList(p);
//	exchange(L,p);
//	PrintList(q);
//	r=eightlist(p,q);
//	PrintList(r);
 //	int a[7]={5,6,3,8,9,12,10};
 //	int b=maxlength(a,7);
 	//	for(int i=0;i<7;i++)
 	//	printf("%lf ",funxy(1.0,3.0));
 	
// 	
//return 0;
//}




//------------真题----------
//2020 计专 递归判断树是否对称
bool duichen(BiNode *r,BiNode *l){
	bool ll,rr;
	if((l==NULL&&r!=NULL)||(l!=NULL&&r==NULL))
		return false;
	if(l==NULL&&r==NULL)
		return true;
	if(l!=NULL&&r!=NULL){
		ll=duichen(r->rchild,l->lchild);
		rr=duichen(r->lchild,l->rchild);
	}
//	printf("%d %d\n",ll,rr);
	if(ll&&rr) return true;
	else return false;
} 
//软学2018  1
void prelevel(BiTree bt,int l){
	if(bt==NULL) return;
	printf("%c  %d",bt->data,l);
	prelevel(bt->lchild,l+1);
	prelevel(bt->rchild,l+1); 
} 
//计学2019  1
void DoubleSort(DLinklist &L){
	 DNode *t=L,*pre,*r;
	 while(t->next!=NULL) {
	 t=t->next;	
//	 printf("\n%d ",t->data);
	 }
	 t->next=L;
	 L->prior=t;
	 L->next->prior=NULL;
	 DNode *p=t;
	 r=p->prior;
	 p->prior=NULL;
	 p=r;
	 //L=L->next;
	//printf("\n%d ",L->data);
	while(p){
		r=p->prior;
		pre=L;
		while(pre->prior!=NULL&&pre->prior->data<p->data)
			pre=pre->prior;
			p->prior=pre->prior;
			pre->prior=p; 
			p=r;
	//	printf("\n%d ",p->data);	
	}
} 
LinkList fun_2015_4_966(LinkList &L){
	LNode *p=L->next,*r,*pre=L;
	while(p!=NULL){
		if(IsPrime(abs(p->data))){
			pre->next=p->next;
			free(p);
			p=pre->next; 
		}else{	
			pre=p;
			p=p->next;
			}
	}
	p=L->next;
	r=p->next;
	p->next=NULL;
	p=r;
	while(p!=NULL){
		r=p->next;//保存后续结点 
		pre=L;//从头找位置 注意这里pre指针的用法，用pre->next比较可以保留前驱位置 
		while(pre->next!=NULL&&pre->next->data<=p->data) //找到位置时pre的下一个结点值大于待考察结点；未找到位置pre下个结点为空 
			pre=pre->next;
		p->next=pre->next;//将考察结点插入找到位置 
		pre->next=p;
		p=r;//p继续向后遍历	
		}
	return L; 
} 
//计学2015 2输出独生叶节点 
void fun1(BiTree root,int sum[],int n){
	if(root==NULL) return;
	if(root->lchild!=NULL&&root->rchild==NULL&&root->lchild->lchild==NULL&&root->lchild->rchild==NULL) {
		sum[n+1]++;printf("%d %d %c",n+1,sum[n+1],root->data); 
	}
	if(root->rchild!=NULL&&root->lchild==NULL&&root->rchild->lchild==NULL&&root->rchild->rchild==NULL) {
		sum[n+1]++;printf("%d %d %c",n+1,sum[n+1],root->data); 
	}
	fun1(root->lchild,sum,n+1);
	fun1(root->rchild,sum,n+1);
}
void fun2(BiTree root){
	int sum[5]={0};
	fun1(root,sum,0);
	for(int i=0;i<=4;i++) printf("第%d层：%d\n",i,sum[i]);
} 
//2013 删除>=x的树的结点
void deletex(BiTree &root,char x){
	BiNode *p,*q;
	BiNode *t=root;
//	printf("%c\n",root->data);
	if(t->data>=x){
		p=t->lchild;
		q=t->rchild;
		t->data=p->data;
		t->lchild=p->lchild;
		t->rchild=p->rchild;
		free(p);
		BtDelete(q);
		deletex(t,x);
	}
	else{
		if(t->rchild==NULL) {	//printf("%c\n",root->data);
		//	temp=t;
			return;
		}
		else 
			deletex(t->rchild,x); 
	}
} 
BiTree ret(BiTree root,char x){
	BiNode *temp=root;
		while(x<=temp->data) temp=temp->lchild;
	deletex(root,x);
	return temp;
}
//删除二叉查找树中>=x 的所有结点
void Delallx(BiTree &bt,BiNode *p,char x,BiNode *&newhead){
	if(bt==NULL)
		return;
	if(bt->data<x){
		Delallx(bt->rchild,bt,x,newhead);
		if(bt->data<x)
			newhead=bt;	//创造新的树根结点		 
	}	
	else{
		Delallx(bt->lchild,bt,x,newhead);
		Delallx(bt->rchild,bt,x,newhead);
		if(bt->lchild!=NULL){
			if(p->lchild==bt) p->lchild=bt->lchild;
			else p->rchild=bt->lchild;
		}
		else{
			if(p->lchild==bt) p->lchild=NULL;
			else p->rchild=NULL;
		}
		if(bt!=NULL&&bt->data>=x) //加条件是因为右子树中可能存在比x小的结点并且右被置空的结点 
			free(bt);
	}
}
//删除值为x的二叉排序树的结点 
void Delx(BiTree &bt,char x){
	BiNode *p=bt,*pre=p;
	BiTree stack[MaxSize];
	int top=-1;
	while(p->data!=x){
	if(p->data>x){
		pre=p;
		p=p->lchild;
	}
	if(p->data<x) {
		pre=p;
		p=p->rchild; 
	}
	} 
	if(p->lchild==NULL&&p->rchild==NULL){
		free(p);
		p=pre->lchild=NULL;
		p=pre->rchild=NULL;
		return ;
						}
	else{
		if(p->lchild==NULL&&p->rchild!=NULL){
			if(pre->lchild==p)
				pre->lchild=p->rchild;	
			else{
				//printf("%c  ",stack[top]->data);
				pre->rchild=p->rchild;
				}	
				free(p);
				return ;
				}
			if(p->lchild!=NULL&&p->rchild==NULL){
				if((pre->lchild==p))
					pre->lchild=p->lchild;
				else 
					pre->rchild=p->lchild;
					free(p);
					return ;
					}
			if(p->lchild!=NULL&&p->rchild!=NULL){
				BiNode *r=p->rchild;
						pre=p;
				while(r->lchild){
					pre=r;
					r=r->lchild;
					}
					p->data=r->data;
				if(r->rchild!=NULL){
					if(pre->lchild==r) pre->lchild=r->rchild;
					else pre->rchild=r->rchild;
					}
				else{
					if(pre->lchild==r) pre->lchild=NULL;
					else pre->rchild=NULL;
				}
						free(r);		
						return ;
				}
			}
} 
//2003 5.非递归实现函数 
double funxy(double x,double y){
	double stack1[MaxSize];
	double stack2[MaxSize];
	double stack3[MaxSize];
	stack1[0]=x;
	stack2[0]=y;
	stack3[0]=x/y;
	int top=0;
	while(1)
	if(x<0){
		double temp=stack1[top]+stack2[top];
		top--;
		while(top>=0){
				temp=temp+stack3[top--];
		}

		return temp;	
	}
	else{
		stack1[++top]=x-1;
		stack2[top]=stack1[top-1]+stack2[top-1];
		stack3[top]=stack1[top]/stack2[top];
		x-=1;
	}
} 
//2003 二维矩阵顺时针旋转90度 
void m90(int a[MaxSize][MaxSize],int n){
	int k=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		a[i][j]=k++;
	for(int i=0;i<n;i++)
		for(int j=i;j<n;j++){
			int temp=0;
			temp=a[i][j];
			a[i][j]=a[j][i];
			a[j][i]=temp;
		}
	for(int i=0;i<n/2;i++)
		for(int j=0;j<n;j++){
			int temp=a[j][i];
			a[j][i]=a[j][n-i-1];
			a[j][n-i-1]=temp;
		}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
		printf("%2d ",a[i][j]);
		printf("\n");
	}
}
//2002 4.8进制链表相加 
/*
5 3 6 9999
7 2 4 3 9999
*/
LNode *eightlist(LNode *p,LNode *q){
	int a[100]={0};
	int b[100]={0};
	int c[100]={0};
	int i=0,j=0,jin=0,k=0;
	LNode *L=(LNode *)malloc(sizeof(LNode));
	LNode *l;
	l=L;
	while((p=p->next)!=NULL){
		a[i++]=p->data;
	}	
	while((q=q->next)!=NULL){
		b[j++]=q->data;
	}
		
	int min=i<j?i:j;
	j--;
	for(int i=min-1;i>=0;i--){
		c[k++]=(b[j]+a[i]+jin)%8;
		jin=(b[j]+a[i]+jin)/8;
		j--;
	}
//	printf("j=%d  jin=%d b[j]=%d\n",j,jin,b[j]);
	while(j>=0){
		c[k++]=(b[j]+jin)%8;
		jin=(b[j]+jin)/8;
		j--;
	}
	if(jin!=0) c[k++]=jin;
//	for(int o=0;o<k;o++) //printf("%d",c[o]);
//	printf("%d",k);
	for(int qq=k-1;qq>=0;qq--){
	LNode *ll=(LNode *)malloc(sizeof(LNode));
	ll->data=c[qq];	//printf("%d",qq,c[qq]);
	l->next=ll;
	l=l->next;	
	}
	l->next=NULL; 
//	printf("%d\n",L->next->data);
	return L;
} 
//2002 3.无序链表合并 
LNode *mergelist(LNode *p,LNode *q){
	LNode *r=NULL,*qq=NULL,*rr=NULL;
	r=(LNode *)malloc(sizeof(LNode));
	rr=r;
	qq=q;
	bool flag;
	while(p=p->next){
		flag=false;
		q=qq;
		while(q=q->next)
			if(p->data==q->data){
				flag=true;
				break;
			}
		if(flag==false){
			LNode *m=(LNode *)malloc(sizeof(LNode));
			m->data=p->data;
			m->next=NULL;
			r->next=m;
			r=r->next;	
		}	
	}
	r->next=qq->next;
	return rr;
} 
//2002 2.最长递归子序列 
int maxlength(int a[],int n){
	int i=1,count=1,max=1; 
	for(i;i<n;i++){
		if(a[i]>=a[i-1])
			count++;
		else	count=1;
		if(max<count) {
		max=count;	
		}
	}
	return max;
} 
//2002  1.递归插入 
int *insert(int a[],int n,int e){
	if(e<a[n-1]) {
		a[n]=a[n-1];
		int *b=insert(a,n-1,e);
	}
	else{
		a[n]=e;
		return a;
	}
} 
// 2001计学  3.双端冒泡
void dbubble(int a[],int n){
	int r=n-1,l=0;
	int temp;
	while(l<r){
		for(int i=l;i<r;i++)
		if(a[i]>a[i+1]){
				temp=a[i];
				a[i]=a[i+1];
				a[i+1]=temp;
		}
		r--;
		for(int i=r;i>0;i--)
		if(a[i]<a[i-1]){
				temp=a[i];
				a[i]=a[i-1];
				a[i-1]=temp;
		}
		l++;
	} 
} 
// 2001计学  1.交换链表结点
void exchange(LinkList &L,LNode *p){
	LNode *t=L,*pre;
	while(t!=p){
		pre=t;
		t=t->next;
	}
	pre->next=p->next;
	p->next=p->next->next;
	pre->next->next=p;
}
LinkList List_TailInsert_1(LinkList &L,LNode* &p,int a){
	int i;
	L=(LNode *)malloc(sizeof(LNode));
	LNode *s,*r=L;
	scanf("%d",&i);
	while(i!=9999){
		s=(LNode *)malloc(sizeof(LNode));
		s->data=i;
		if(i==a) p=s;
		r->next=s;
		r=s;
		scanf("%d",&i);
	}
	r->next=NULL;
	return L;
}  
// 2000计学 链表插入排序
void Insert2(LinkList &L){
	LNode *p=L->next;
	LNode *t=p->next;
	while(t){
		LNode *temp=t->next;
		if(t->data<p->data){
			LNode *q=L->next,*pre=L;
			while(t->data>=q->data){printf("q=%d\n",q->data);
				pre=q;
				q=q->next;
			}
			t->next=q;
			pre->next=t;
			p->next=temp;
			t=temp;
		}
		else{
			p=t;
			t=temp;	
		}
		
	}
} 
void LInsertSort(LinkList &L){
	LNode *p=L->next,*pre;//pre指针终于遍历有序部分，找到插入位置 
	LNode *r=p->next;//p 指针为当前考察结点，r用于记录后面结点，因为找到位置后要断开连接 
	p->next=NULL;//这里将链表分成两部分，前部分有序 
	p=r;//p指针从后部分依次遍历 
	while(p!=NULL){
		r=p->next;//保存后续结点 
		pre=L;//从头找位置 注意这里pre指针的用法，用pre->next比较可以保留前驱位置 
		while(pre->next!=NULL&&pre->next->data<=p->data) //找到位置时pre的下一个结点值大于待考察结点；未找到位置pre下个结点为空 
			pre=pre->next;
		p->next=pre->next;//将考察结点插入找到位置 
		pre->next=p;
		p=r;//p继续向后遍历	
		}
	}
//递归判断最近的公共祖先
BiNode *CommonAncestor(BiTree bt,BiNode *p,BiNode *q){
	if(bt==NULL||bt==p||bt==q)
		return bt;
	BiNode *left=CommonAncestor(bt->lchild,p,q);
	BiNode *right=CommonAncestor(bt->rchild,p,q);
	if(left==NULL) return right;
	else if(right==NULL) return left;
	else return bt; 
} 
void Common(BiTree bt,BiNode *p,BiNode *q,BiNode* &r){
	r=CommonAncestor(bt,p,q);
}
//递归找到所有祖先
BiNode* Ancestor(BiTree bt,BiNode *p){
	if(bt==NULL||bt==p)
		return bt;
	BiNode *q=Ancestor(bt->lchild,p);
	BiNode *t=Ancestor(bt->rchild,p);
	if(q==p||t==p) {
		printf("%c  ",bt->data);
		return q;
	}
} 
bool Isson(BiTree T,BiNode *u,BiNode *v){//递归判断u是否为v的祖先 
//	printf("%c\n",u->data);
	if(u==NULL) return false;
	if(v==u) return true;
	bool flagr=false,flagl=false;
	flagl=Isson(T,u->lchild,v);
	flagr=Isson(T,u->rchild,v);
	return flagl||flagr;
} 
//根据先序和中序创建二叉树 
BiTree piCreate(char pre[],char in[],int pl,int pr,int il,int ir){//pl是先序左子树左端il中序左子树左端 
	if(pl>pr) return NULL;
//	printf("%s  %s",pre,in);
	BiNode *root=(BiNode *)malloc(sizeof(BiNode));
	root->data=pre[pl];
	int k=0;
	while(pre[pl]!=in[k]) k++;//找到根节点在中序中的位置 
	int leftnum=k-il;  //求左子树节点个数 
	root->lchild=piCreate(pre,in,pl+1,pl+leftnum,il,k-1);
	root->rchild=piCreate(pre,in,pl+leftnum+1,pr,k+1,ir);
	return root;
} 
//--------程序设计基础-------- 
/*
1 2 3 4 5 6
1 2 3 4 5 6
*/
//int main(){
//	int a[6],b[6];
//	int num[15][15];
//	char c[5]="abcd";
//	SubSet(c,4);
//	Matrix(num,7);
//	for(int i=0;i<6;i++){
//		scanf("%d",&a[i]);
//	}
//	for(int i=0;i<6;i++){
//		scanf("%d",&b[i]);
//	}
//	int *c=(int *)malloc(sizeof(int )*12);
//	c=Mul_Num(a,b,6,6);
//	for(int i=0;i<11;i++){
//		printf("%d",c[i]);
//	}
//} 
bool IsPrime(int a){
	bool flag=true;
	for(int i=2;i<=sqrt(a);i++)
		if(a%i==0){
			flag=false;
			break;
		}
	 return flag;
}
//数组逆置 
void Inverse(int a[],int m){
	for(int i=0;i<m/2;i++){
		int temp=a[i];
		a[i]=a[m-i-1];
		a[m-i-1]=temp;
	}
}
//大数相乘
int *Mul_Num(int a[],int b[],int m,int n){
	int *c=(int *)malloc(sizeof(int )*(m+n));
	for(int k=0;k<m+n;k++)
		c[k]=0;
	Inverse(a,m);
	Inverse(b,n);
	for(int i=0;i<m;i++)
	for(int j=0;j<n;j++)
		c[i+j]=a[i]*b[j]+c[i+j];
	for(int p=0;p<m+n-1;p++){
		int num=c[p];
		c[p]=num%10;
		c[p+1]=num/10+c[p+1];
	}
	Inverse(c,m+n);
	int p=0;
	while(c[p]==0) p++;
	int j=0;
	for(int i=p;i<m+n;i++){
		c[j++]=c[i];
	}
	for(int k=0;k<j;k++)
	printf("%d",c[k]);
	printf("\n");
	return c;
}
//螺旋矩阵输出
void Matrix(int num[][MaxSize],int n){
	int number=0;
	for(int i=0;i<=n/2;i++){    //n阶矩阵共有 n/2 向上取整层 //i座位控制层数的变量 
		for(int j=i;j<n-i;j++)
			num[i][j]=number++;  //第i层的上边  行不变（上边行下标i） 列<n-i 
		for(int j=i+1;j<n-i;j++)
			num[j][n-i-1]=number++;// 第i层的右边  列不变（右边列下标n-i-1） 行下标从i+1开始到n-i-1 
		for(int j=n-i-2;j>=i;j--)
			num[n-i-1][j]=number++;// 第i层的下边  行不变（行下标n-i-1） 列下标n-i-2到i 
		for(int j=n-2-i;j>i;j--)
			num[j][i]=number++;   //第i层的左边  列不变（列下标 i） 行下标 n-i-2到i-1 
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%02d ",num[i][j]);
			printf("\n");
	}
} 
//求子集问题  输出ch的所有子集
//思想：长度为n的序列有2的n次方-1种排序，从1到2的n次方-1共有2的n次方-1个数 ，每个数转换成为二进制对应的子集，0输出，1输出 
void SubSet(char ch[],int n){
	int num=1;//算出子集个数 
	for(int i=0;i<n;i++)  //长度为n的集合共有2的n次方-1个子集 
		num*=2;
	int sub[n];//第i种时对应的二进制序列 
	for(int i=0;i<num;i++){  //把每个数转化成为二进制，输出对应序列 
		for(int j=0;j<n;j++)
			sub[j]=0;  //输出一个号要重新初始化 
		int count=0;//二进制位数下标 
		int subnum=i;
	while(subnum>0){ //转化二进制  除2取余，直到被除数为0，这时得到的二进制是逆序 
		sub[count]=subnum%2;
		subnum/=2;
		count++;
	} 
	for(int j=0;j<n;j++){ //输出对应序列 
		if(sub[j])
		printf("%c",ch[j]);
	}
		 printf("\n");	 
	} 
} 
//--------排序--------- 
//	int a[MaxSize]={27,99,0,8,13,64,86,16,7,10,88,25,90}; 
// 	int a[6]={2,4,6,1,3,5};
// 	int b[6];
//int main(){
//	int a[MaxSize]={27,99,0,8,13,64,86,16,7,10,88,25,90}; 
// 	int a[6]={2,4,6,1,3,5};
// 	int b[6];
	//a[13]=Inf;//快排虚拟记录确保指针i在向右遍历过程中可以终止 
	//Qsort(a,0,13);
	//Bubble(a,13);
	//Insertsort(a,13); 
	//ZBInsert(a,13);
	//Shellsort(a,13);
	//Ssort(a,13);
	//BuildMaxHeap(a,13);
	//Heapsort(a,13); 
	//Merge(a,0,3,6,b);
	//Mpass(a,6,1,b);
//	Msort(a,6,b);
//	for(int i=0;i<6;i++)
//		printf("%d ",b[i]);	
//	printf("\n");
			
//}
//二路归并排序   最好：nlogn  最坏: nlogn 平均：nlogn 空间：n；  稳定  性能与初始状态无关
void Msort(int a[],int n,int b[]){
	int l=1;
	while(l<n){
		Mpass(a,n,l,b);
		l*=2;
		Mpass(b,n,l,a);
		l*=2;
	} 
}
 //两个序列的合并  p第一个序列的起始地址，q是第二个序列的起始地址，n是合并好的序列的起始地址,b是合并之后的数组 
void Merge(int a[],int p,int q,int n,int b[]){
	int i=p,j=q,k=i;
	while(i<q&&j<n){
			if(a[i]<=a[j]){
			b[k]=a[i];
			i++;
		}
		else {
			b[k]=a[j];
			j++;
		}
		k++;
	}
	while(i<q) b[k++]=a[i++];
	while(j<n) b[k++]=a[j++];
} 
//一趟合并算法   n是序列总长度，L是每次合并相邻子序列的长度 
void Mpass(int a[],int n,int L,int b[]){
	int i=0;
	while(i+2*L<n){
		Merge(a,i,i+L,i+2*L,b);
		i=i+2*L;
	}
	if(i+L<n) Merge(a,i,i+L,n,b);
	else 
		for(int j=i;j<n;j++)
			b[j]=a[j];
} 
//堆排序  最好：nlogn 最坏：nlogn 平均：nlogn 空间:1;不稳定   性能（比较次数和时间复杂度）与初始状态无关
void BuildMaxHeap(int a[],int len){//建堆 
	for(int i=len/2;i>=0;i--)
		AdjustDown(a,i,len);
}
void AdjustDown(int a[],int k,int len){//调整堆
	int temp=a[k];
	for(int i=2*k;i<len;i*=2){
		if(k==0) i=1;//注意k为零是他的左孩子为1，不符合公式2*k； 
		if(i<len-1&&a[i]<a[i+1])
			i++;              //如果有两个孩子结点且右孩子比左孩子大 
		if(a[k]>=a[i]) break;
		else{
			a[k]=a[i];
			k=i;     //大元素上浮，小元素继续向下比较下沉 
		}
		a[k]=temp;
	}
}
void Heapsort(int a[],int len){//堆排序   
	BuildMaxHeap(a,len);
	for(int i=len-1;i>0;i--){
		int temp=a[0];
		a[0]=a[i];
		a[i]=temp;
		AdjustDown(a,0,i-1);//调整堆，每次出去一个元素长度减一；
	}
}
//直接选择排序  最好： n方  最坏：n方 平均：n方  空间  1；不稳定  性能与初始状态无关 
void Ssort(int a[],int n){ 
	int i,j,temp,k;
	int max=a[0];
	for(i=n-1;i>0;i--){
		k=0;
		for(j=1;j<=i;j++)
			if(a[j]>a[k])
				k=j;
		temp=a[i];
		a[i]=a[k];
		a[k]=temp;
	}
} 
//希尔排序 最好：--  最坏：n方  平均：n  空间1；不稳定 性能与选取的分组长度序列有关 一般选取d/2 
void Shellsort(int a[],int n){
	int i,j,k,dk,temp;
	for(dk=n/2;dk>=1;dk=dk/2){
		j=0;
		while(j<dk){
		for(i=dk+j;i<n;i+=dk)
			if(a[i]<a[i-dk]){
				temp=a[i];
				for(k=i-dk;a[k]>temp&&k>=0;k-=(dk))
					a[k+dk]=a[k];
				a[k+dk]=temp;
			}
		j++;
		}
	} 
} 
//折半插入排序  最好：n  最坏：n方  平均：n方  空间：1；稳定   只能用于顺序表
//注意折半查找的最终状态是low=high+1；
//此时low所指的位置为插入位置，为了保持稳定性，当找到相等元素是应继续在右边查找位置，所以等于情况放在mid+1的情况里 
void ZBInsert(int a[],int n){
	int i,j,temp,mid,low,high;
	for(int i=1;i<n;i++)
		if(a[i]<a[i-1]){		//	左边的元素比待插元素大，则继续向左找，左边比待插元素小，则考察下一个元素 
		temp=a[i];
		low=0;
		high=i-1;
		while(low<=high){
			mid=(low+high)/2;
			if(temp<a[mid])
				high=mid-1;
			else 
				low=mid+1;  //这里是为了保持稳定性，后来待插元素与前面的元素相等时，应该继续在右半部分找位置 
		}
		//折半查找最终状态是low=high+1；low即为插入位置 
		printf("%d\n",mid);
		for(j=i-1;j>=low;j--) 
			a[j+1]=a[j];
		a[low]=temp;//找到第一个比待插元素小的，在该元素的右边插入 
	}
	
} 
//直接插入排序  最好：n  最坏：n方  平均：n方  空间：1；稳定  最坏情况：逆序，适用于基本有序  要移动元素  
//从第二个元素开始 从后向前比较，注意最小元素放在最前面的情况 。
void Insertsort(int a[],int n){
	int i,j,temp;
	for(i=1;i<n;i++)
	if(a[i]<a[i-1]){		//左边的元素比待插元素大，则继续向左找，左边比待插元素小，则考察下一个元素 
		temp=a[i];
		for(j=i-1;j>=0&&a[j]>temp;j--)  
			a[j+1]=a[j];
		a[j+1]=temp;//找到第一个比待插元素小的，在该元素的右边插入 
	}
}
//冒泡排序  最好：n 最坏：n方  平均：n方； 空间：1；稳定；最坏情况：逆序
//适用于基本有序 注意flag使用（在排序是没发生交换则有序退出）
void Bubble(int a[],int n){
	int temp;
 	bool flag;
 	for(int i=n-1;i>0;i--){
 		flag=false;
 		for(int j=0;j<i;j++)
 			if(a[j]>a[j+1]){
 				temp=a[j];
 				a[j]=a[j+1];
 				a[j+1]=temp;
 				flag=true;
			 }
			printf("\n第%d趟：\n",n-i);
			for(int q=0;q<n;q++)
			printf("%d ",a[q]);
		 if(flag==false) return;	 
	 }
} 
//快速排序  最好：nlogn,最坏：n方，平均：nlogn；空间：nlogn；最坏情况:有序，不稳定 
//注意在素组最后的无穷大虚拟记录，来确保从左到右循环的终止，而且要在进入函数之前定义好 
void Qsort(int a[],int m,int n){//下标从1开始 
	if(m>=n) return;
	int i=m;
	int j=n+1;
	int k=m;
	int temp;
	while(i<j){
		i++;
		while(a[i]<=a[k]) i++;//从左找到第一个比基准大的 
		j--;
		while(a[j]>a[k]) j--;//从右找到第一个比基准小或等于的 
		if(i<j){//i和j没相交 
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	
	}
	//此时i比j大
	temp=a[j];
	a[j]=a[k];
	a[k]=temp;
//		for(int q=0;q<13;q++)
//		printf("%d ",a[q]);	
//		printf("\n");
	//	return;
	//一次划分完成
	Qsort(a,m,j-1);
	Qsort(a,j+1,n);	
}















//---------图------- 
//深度优先遍历（非递归）
/*
4 5
0123
0 1
0 2
0 3
1 3
2 3 
*/ 
/*
6 6
012345
0 1
0 2
1 3
2 4
4 5
5 3
*/
/*
4 8
0123
0 1
1
0 3
4
1 2
9
1 3
2
2 0
3
2 1
5
2 3
8
3 2
6*/
void ddfs(LGraph G,int i,int j,int d[],int n){
	if(i==j){
		for(int i=0;i<=n;i++){	
			printf("%c ",G.adjlist[d[i]].data);
		}
		printf("\n");
	}
	ArcNode *p;
	for(p=G.adjlist[i].first;p!=NULL;p=p->next)
		if(visited[p->adjvex]==false){
			visited[p->adjvex]==true;
			d[n+1]=p->adjvex;
			ddfs(G,p->adjvex,j,d,n+1);
			visited[p->adjvex]=false;
		}
}
void dfs(LGraph G,int v){
 	int stack[G.vexnum];
	int top=-1;
	bool vis[G.vexnum];
//	printf("%c",G.adjlist[v].data);
	vis[v]=true;
	stack[++top]=v;
	while(top!=-1){
	ArcNode *p;
	int i=stack[top--];
	printf("%c",G.adjlist[i].data);
	for(p=G.adjlist[i].first;p!=NULL;p=p->next){
		if(vis[p->adjvex]!=true){
			stack[++top]=p->adjvex;
			vis[p->adjvex]=true;
			}
		} 		
	}
} 
//深度优先遍历（递归）(要定义全局标记数组visited)
void DFS(LGraph G,int v){
	printf("%c",G.adjlist[v].data);
	visited[v]=true;
	ArcNode *p=G.adjlist[v].first;
	for(p;p!=NULL;p=p->next){
		if(visited[p->adjvex]!=true)
			DFS(G,p->adjvex);
	}
} 
//深度优先遍历找从u到v的所有路径（定义全局变量访问数组visited,path为路径数组，k为路径上结点的次序）（八皇后） 
void FindPath(LGraph G,int u,int v,int k,int path[]){
	path[k]=u;
	visited[u]=true;//printf("u==%d ,v==%d\n",u,v);
	if(u==v){
		for(int i=0;i<=k;i++){	
			printf("%c",G.adjlist[path[i]].data);
		}
		printf("\n");
	}else{
		 
		ArcNode *p=G.adjlist[u].first;
		for(p;p!=NULL;p=p->next){
			if(visited[p->adjvex]!=true){
				FindPath(G,p->adjvex,v,k+1,path);
			}
		}
	}
	visited[u]=false; 
} 
//广度优先遍历
void BFS(LGraph G,int v){
	bool vis[MaxSize];
	int queue[G.vexnum];
	int front=-1,rear=-1;
	printf("%c",G.adjlist[v].data);
	vis[v]=true;
	queue[++rear]=v;
	while(front!=rear){
		int p=queue[++front];
		ArcNode *q=G.adjlist[p].first;
		for(q;q!=NULL;q=q->next){
			if(vis[q->adjvex]!=true){
				printf("%c",G.adjlist[q->adjvex].data);
				vis[q->adjvex]=true;
				queue[++rear]=q->adjvex;
			}
		}
	}	
} 
//广度优先遍历判断图是否为一棵树 
bool BFSIstree(LGraph G,int v){
	bool vis[MaxSize];
	int queue[G.vexnum];
	int front=-1,rear=-1;
	//printf("%c",G.adjlist[v].data);
	vis[v]=true;
	queue[++rear]=v;
	while(front!=rear){
		int p=queue[++front];
		ArcNode *q=G.adjlist[p].first;
		for(q;q!=NULL;q=q->next){
			if(vis[q->adjvex]!=true){
			//	printf("%c",G.adjlist[q->adjvex].data);
				vis[q->adjvex]=true;
				queue[++rear]=q->adjvex;
			}
			else return false;
		}
	}	
	return true;
} 
//广度优先遍历求无权图最短路径
void BFSMinpath(LGraph G,int v){
	bool vis[MaxSize];
	int d[G.vexnum]={0};
	d[v]=0;
	int queue[G.vexnum];
	int front=-1,rear=-1;
	//printf("%c",G.adjlist[v].data);
	vis[v]=true;
	queue[++rear]=v;
	while(front!=rear){
		int p=queue[++front];
		ArcNode *q=G.adjlist[p].first;
		for(q;q!=NULL;q=q->next){
			if(vis[q->adjvex]!=true){
			//	printf("%c",G.adjlist[q->adjvex].data);
				vis[q->adjvex]=true;
				queue[++rear]=q->adjvex;
				d[q->adjvex]=d[p]+1;
			}
		}
	}
	for(int i=0;i<G.vexnum;i++)
		printf("结点：%c  最短距离： %d\n",G.adjlist[i].data,d[i]);	
} 
//遍历邻接表计算图中各顶点的入度
void InDegree(LGraph G,int result[]){
	for(int i=0;i<MaxSize;i++) result[i]=0;
	for(int i=0;i<G.vexnum;i++){
		ArcNode *p=G.adjlist[i].first;
		while(p!=NULL){
			result[p->adjvex]++;
			p=p->next;
		}
	}
	for(int i=0;i<G.vexnum;i++)
		printf("结点：%d   入度:%d\n",i,result[i]);	
}
//弗洛伊德算法求图中任意两点间的最短路径 
void Floyed(LGraph G,int dis[MaxSize][MaxSize]){
	for(int i=0;i<G.vexnum;i++){
		for(int j=0;j<G.vexnum;j++)
			dis[i][j]=0;
		}
	for(int i=0;i<G.vexnum;i++){
		ArcNode *p=G.adjlist[i].first;
		for(p;p!=NULL;p=p->next)
			dis[i][p->adjvex]=p->weight;
		for(int j=0;j<G.vexnum;j++){
			if(i!=j&&dis[i][j]==0)
				dis[i][j]=Inf;
		}		
	}	
	for(int k=0;k<G.vexnum;k++){
		for(int i=0;i<G.vexnum;i++){
			for(int j=0;j<G.vexnum;j++){
				if(dis[i][k]!=Inf&&dis[k][j]!=Inf&&dis[i][k]+dis[k][j]<dis[i][j])
					dis[i][j]=dis[i][k]+dis[k][j];
			} 
		}
//		printf("加入：%d\n",k);
//		for(int i=0;i<G.vexnum;i++){
//		for(int j=0;j<G.vexnum;j++)
//			printf("%10d",dis[i][j]);
//			printf("\n");
//		} 
	}
	for(int i=0;i<G.vexnum;i++){
		for(int j=0;j<G.vexnum;j++)
			printf("%10d",dis[i][j]);
			printf("\n");
		} 	
} 
//创建图的层序遍历生成树 
//注意：创建生成树时，bfs的队列要是树结点，树结点数据域保存图节点的序号，这样是为了让数根结点与孩子节点链接 
void BGraphTree(LGraph G,CTree &T,int v){
	CTree queue[G.vexnum];
	int front=-1,rear=-1;
	T=(CTNode *)malloc(sizeof(CTNode));
	bool visited[G.vexnum]={0};
		T->vnum=v;
		queue[++rear]=T;
		visited[v]=true;
	while(front!=rear){
		CTNode *t=queue[++front];//保存根节点 
		ArcNode *p;
		for(p=G.adjlist[t->vnum].first;p!=NULL;p=p->next)
			if(visited[p->adjvex]!=true){
				visited[p->adjvex]=true;
				CTNode *q=(CTNode *)malloc(sizeof(CTNode));
				q->vnum=p->adjvex;  //初始化孩子结点 
				t->child[t->cnum++]=q;
				queue[++rear]=q;
			}
	}
} 
//创建图的逆邻接表 
//void VList(LGraph,VNode verlist[]);
void VList(LGraph G,LGraph &VG){
	VG.arcnum=G.arcnum;
	VG.vexnum=G.vexnum;
	for(int i=0;i<VG.vexnum;i++){
		VG.adjlist[i].first=NULL;
		VG.adjlist[i].data=G.adjlist[i].data;
	}
	for(int i=0;i<G.vexnum;i++){
		ArcNode *p=G.adjlist[i].first;
		for(p;p!=NULL;p=p->next){
			ArcNode *t=(ArcNode *)malloc(sizeof(ArcNode));
			t->adjvex=i;
			t->next=VG.adjlist[p->adjvex].first;
			VG.adjlist[p->adjvex].first=t;	
		}	
	}
} 
//创建图 
void CreatLGraph(LGraph &G){
	//int i,j,k;
	printf("顶点数  边数:\n");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	printf("输入顶点名称:\n") ;
	getchar();
	for(int i=0;i<G.vexnum;i++){
		scanf("%c",&G.adjlist[i].data);
		G.adjlist[i].first=NULL;
	}
//	G.adjlist[0].data='1';
//	printf("%d",G.vexnum);
//	for(int i=0;i<G.vexnum;i++){
//		printf("%d  %c\n",i,G.adjlist[i].data);
//		//G.adjlist[i].first=NULL;
//	}
	printf("输入边的坐标信息：\n");
	for(int i=0;i<G.arcnum;i++){
		int x,y;//表示他的坐标
		scanf("%d %d",&x,&y);//x表示弧头，y表示弧尾；
		ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=y;
		p->next=G.adjlist[x].first;
		G.adjlist[x].first=p;//头插法 
	//	printf("输入边的权值："); 
	//	scanf("%d",&p->weight); 
		//若为无向图 则弧头弧尾为双向
//		ArcNode *q=(ArcNode *)malloc(sizeof(ArcNode));
//		q->adjvex=x;
//		q->next=G.adjlist[y].first;
//		G.adjlist[y].first=q; 
	} 
}
//输出图 
void PrintLGraph(LGraph G){
	ArcNode *p;
	for(int i=0;i<G.vexnum;i++){
		p=G.adjlist[i].first;
		printf("结点：%c     ",G.adjlist[i].data);
		while(p!=NULL){
		//	printf("结点：%c 权值：%d     ",G.adjlist[p->adjvex].data,p->weight);
			p=p->next;
		}
		printf("\n");
	} 
}

































//----------------树------------ 
//样例
//先序：ABD*G***CEH**I**F**
//中序：DGBAHEICF
//后序：GDBHIEFCA  
//层序: ABCDEFGHI 
void postpath(BiTree bt,char c){
	BiTree stack[10];
	int top=-1;
	BiNode *p=bt,*r;
	while(top!=-1||p!=NULL){
		if(p!=NULL){
			stack[++top]=p;
			r=p;
			p=p->lchild;if(r->data=='I') break;
		}
		
		else{
			p=stack[top];
			if(p->rchild!=NULL&&p->rchild!=r){
				p=p->rchild;
			}
			else{
				r=p;
				top--;
			//	printf("%c",p->data);
				p=NULL;
			}
		}
	}
	for(int i=0;stack[i]!=NULL;i++){
		printf("%c",stack[i]->data);
	}
}
void Pre(BiTree bt,int i){
	BiNode *p=bt;
	if(p==NULL) return;
	printf("值：%c   层数%d：\n",bt->data,i);
	Pre(p->lchild,i+1);
	Pre(p->rchild,i+1);
}
int wid(BiTree bt){
	BiTree Queue[10];
	int front=-1,rear=-1,last=0,wide=0,max=1;
	BiNode *p=bt;
	Queue[++rear]=p;
	while(front!=rear){
		p=Queue[++front];
		if(p->lchild!=NULL) {
			Queue[++rear]=p->lchild;
			wide++;
		}
		if(p->rchild!=NULL) {
			Queue[++rear]=p->rchild;
			wide++;
		}
		if(front==last){
			last=rear;
			if(max<wide) max=wide;
			wide=0;
		}
	}
	return max;
}

//int main(){
//	BiTree bt;
//	BiNode *q,*p,*r;
//	char c='H';
//	//bt=(BiNode *)malloc(sizeof(BiNode));
////	bt->data='A';
//	CreatBiTree(bt);
////	char c='I';
////	postpath(bt,c);
//	//int h,b;
//	//BtSwap(bt);
//	//BtDelete(bt);
//	//bt=NULL; 
//	//printf("%c",bt->data);
//	//char s[99];
//	//scanf("%s",s);
//	//int i=wid(bt);
//	//printf("%c",bt->data);
//	//bt=DBiString(s);
//	//printf("%c",bt->data);
//	//LevelOrder(bt);
//	//printf("宽度：%d",i);
//	//ReLevel(bt);
//	//IsBalance(bt,h,b);
//	PreOrder(bt,q,'H');
////	PreOrder(bt,p,'F');
// 	p=Ancestor(bt,q);
////	Common(bt,p,q,r);	printf("\n%c  %c   %c",q->data,p->data,r->data);
//	//printf("\n");
//	//FInOrder(bt);
//	//printf("\n");
////	FPostOrder(bt,c);
//	//printf("\n");
//	//printf("%d %d",h,b);
//	//L=List_TailInsert(L);
//	//ListDelete(L,2);
//	//Reverse(L);
////	PrintList(bt);
//	return 0;
//}
//树-------- 
//二叉树创建（递归先序）
//ABD*G***CEH**I**F**
//222*2***222**2**2** 
void CreatBiTree(BiTree &bt){
	char a;
	scanf("%c",&a);
	if(a=='*') {bt=NULL;}//输入*结束
	else{
		bt=(BiNode *)malloc(sizeof(BiNode));
		bt->data=a;
		CreatBiTree(bt->lchild);
		CreatBiTree(bt->rchild); 
	} 
} 
//先序递归遍历
void PreOrder(BiTree bt){
	if(bt==NULL) return;
	printf("%c",bt->data);
	PreOrder(bt->lchild);
	PreOrder(bt->rchild); 
} 
//先序求和 
void Presum(BiTree bt,int &q){
	if(bt==NULL) return ;
	q+=(bt->data-'0');
	Presum(bt->lchild,q);
	Presum(bt->rchild,q); 
//	return bt->data+a+b-'0';
} 
//111*1***111**1**1**
//中序递归遍历
void InOrder(BiTree bt){
	if(bt==NULL) return;
	InOrder(bt->lchild);
	printf("%c",bt->data);//
	InOrder(bt->rchild);
}
//后序递归遍历 
void PostOrder(BiTree bt){
	if(bt==NULL) return;
	PostOrder(bt->lchild);
	PostOrder(bt->rchild);
	printf("%c",bt->data);
}
//递归求树高 
void BtHeight(BiTree bt,int &h){
	BiNode *p=bt;
	int lh=0,rh=0;
	if(p==NULL) h=0;
	else{
		BtHeight(p->lchild,lh);
		BtHeight(p->rchild,rh);	
		h=lh>rh?lh+1:rh+1;	
	}
	
//	int lh=BtHeight(p->lchild);
//	int rh=BtHeight(p->rchild);
//	if(lh>rh) return lh+1;
//	else return rh+1;
} 
//判断二叉树是否平衡，b平衡因子，0为不平衡，1为平衡，h为高度
/*思想：后序递归判断 每个结点： 
	1.若这个结点为空，高度h=0,b=1;  
	//2.若这个结点没有孩子，则h=1,b=1;
	3.若这个结点有左子树或右子树，那么h=max{rh+1,lh+1}(较高的子树高度+1);
		如果左右子树的高度差大于1（不平衡）：b=0;
		如果左右子树的高度差小于等于1（大树平衡）且左右子树也都平衡(rb==1&&lb==1)：b=1；否则b=0; 
*/
void IsBalance(BiTree bt,int &b,int &h){//b,h 要带出来 
	BiNode *p=bt;
	int rh=0,lh=0,rb=0,lb=0;
	if(p==NULL){
		h=0;
		b=1;
	}
//	else if(p->lchild==NULL&&p->rchild==NULL){
//		h=1;
//		b=1;
//	}
	else{
		IsBalance(p->lchild,lb,lh);//传参是lb，lh，即本次递归的b和h；实际上的运算是lb和lh在运算，有使用了引用传参 
		IsBalance(p->rchild,rb,rh);//所以，lb和lh的值会被带出来 
		h=(lh>rh?lh+1:rh+1);
		if(abs(lh-rh)>1) b=0;
		else{
			if(lb==1&&rb==1) b=1;
			else b=0;
		}
	}
} 
//递归交换左右子树
void BtSwap(BiTree bt){
	BiNode *p=bt,*temp;
	if(p){
		BtSwap(p->lchild);
		BtSwap(p->rchild);
		temp=p->lchild;
		p->lchild=p->rchild;
		p->rchild=temp;
	} 
	else return;
} 
//递归删除树，释放空间
void BtDelete(BiTree bt){
	if(bt){
		BtDelete(bt->lchild);
		BtDelete(bt->rchild);
		free(bt);	
	}
	bt=NULL;
} 
//层序遍历 
void LevelOrder(BiTree bt){
	BiTree BQueue[MaxSize];
	if(bt==NULL) return;
	int front=-1;
	int rear=-1; 
	BQueue[++rear]=bt;
	while(front!=rear){
		printf("%c",BQueue[++front]->data);
		if(BQueue[front]->lchild!=NULL)
			BQueue[++rear]=BQueue[front]->lchild;
		if(BQueue[front]->rchild!=NULL)
			BQueue[++rear]=BQueue[front]->rchild;
	}
}
//层序遍历求树高
int LHeight(BiTree bt){
	BiTree BQueue[MaxSize];
	BiNode *p=bt;
	int front=-1,rear=-1,level=0,last=0;//level层数，last表示当前队列中最后一层的最后一个结点位置 
	BQueue[++rear]=p;
	while(front!=rear){
		p=BQueue[++front];
		if(p->lchild!=NULL)
			BQueue[++rear]=p->lchild;
		if(p->rchild!=NULL)
			BQueue[++rear]=p->rchild;
		if(front==last){//对 头到最后位置时，这一层结点的所有孩子结点都入队，
			level++;	//即下一层的结点都入队，更新下一层的最后位置， 对头指针遍历到 下一层，更新 层  数
			last=rear;
		}
	}
	return level;
}
//层序遍历求树宽
int LWidth(BiTree bt){
	BiTree BQueue[MaxSize];
	int front=-1,rear=-1,level=1,width=0,last=0,max=1;
	BiNode *p=bt;
	BQueue[++rear]=p;
	while(front!=rear){
		p=BQueue[++front];
	
		if(p->lchild!=NULL){
		BQueue[++rear]=p->lchild;	width++;
		} 
			
		if(p->rchild!=NULL){
		BQueue[++rear]=p->rchild;  width++;
		} 
			
		if(front==last){
			last=rear;
			if(max<width) max=width;
			printf("第%d层的宽度为：%d\n",++level,width);
			width=0;
		}
	}
	return max;
} 
//层序求二叉树叶子or单分支or双分支or独生叶节点个数
int LLnodecount(BiTree bt){
	BiTree BQueue[MaxSize];
	int front=-1,rear=-1,count=0;
	BiNode *p=bt;
	BQueue[++rear]=p;
	//叶子结点 
//	while(front!=rear){
//		p=BQueue[++front];
//		if(p->lchild==NULL&&p->rchild==NULL) count++;
//		if(p->lchild) BQueue[++rear]=p->lchild;
//		if(p->rchild) BQueue[++rear]=p->rchild;
//	} 
	//单分支结点
//	while(front!=rear){
//		p=BQueue[++front];
//		if((p->lchild==NULL&&p->rchild!=NULL)||(p->lchild!=NULL&&p->rchild==NULL)) count++;
//		if(p->lchild) BQueue[++rear]=p->lchild;
//		if(p->rchild) BQueue[++rear]=p->rchild;
//	}
	//双分支结点
//	while(front!=rear){
//		p=BQueue[++front];
//		if(p->lchild!=NULL&&p->rchild!=NULL) count++;
//		if(p->lchild) BQueue[++rear]=p->lchild;
//		if(p->rchild) BQueue[++rear]=p->rchild;
//	}
	//独生叶节点 
	while(front!=rear){
		p=BQueue[++front];
		if(p->lchild==NULL&&p->rchild!=NULL)
			if(p->rchild->lchild==NULL&&p->rchild->rchild==NULL) count++;
		if(p->lchild!=NULL&&p->rchild==NULL)
			if(p->lchild->lchild==NULL&&p->lchild->rchild==NULL) count++;
		if(p->lchild) BQueue[++rear]=p->lchild;
		if(p->rchild) BQueue[++rear]=p->rchild;
	}
	return count;
} 
//从上到下，从右到左层序遍历二叉树 
void ReLevel(BiTree bt){
	BiTree BQueue[MaxSize];
	int front=-1,rear=-1,last=0;
	BiTree BStack[MaxSize];
	int top=-1;
	BiNode *p=bt;
	BQueue[++rear]=p;
	while(rear!=front){
		p=BQueue[++front];
		BStack[++top]=p;
		if(p->lchild!=NULL)
			BQueue[++rear]=p->lchild;
		if(p->rchild!=NULL)
			BQueue[++rear]=p->rchild;
		if(last==front){
			last=rear;
			while(top>-1)
				printf("%c",BStack[top--]->data);
		}
	}
} 
//真题210问题
//注意在申请空间后一定要把指针域赋空值 
//正向 
void BiString(BiTree &bt,char s[]){
	BiNode *p=bt,*t;
	BiTree BStack[MaxSize];
	int top=-1;
	int j=65;
	char c;
	for(int i=0;s[i]!='\0';i++){
	//	printf("\n%d: %c ",i,s[i]);//21200110
		if(s[i]=='0'){
			p=BStack[top--];
			if(p->rchild!=NULL&&t!=p->rchild){
				t=p;
				BStack[++top]=p;
				p=p->rchild;
			}
			while(p->rchild==NULL&&t==p->rchild)
					p=BStack[top--];
		}
		if(s[i]=='1'){
			BStack[++top]=p;
			BiNode *q=(BiNode *)malloc(sizeof(BiNode));
			q->lchild=NULL;
			q->rchild=NULL;
			j++;
			q->data=j;
			p->lchild=q;
			t=p;
			p=p->lchild;
		}
		if(s[i]=='2'){
			BStack[++top]=p;
			BiNode *l=(BiNode *)malloc(sizeof(BiNode));
			BiNode *r=(BiNode *)malloc(sizeof(BiNode));
			r->lchild=NULL;
			l->rchild=NULL;
			r->rchild=NULL;
			l->lchild=NULL;
			j++;
			l->data=j;
			j++;
			r->data=j;
			p->lchild=l;
			p->rchild=r;
			t=p;
			p=p->lchild;
		}
	}
} 
//逆向
BiTree RBiString(int a[],int n) {
	BiTree BStack[n];
	int top=-1;
	for(int i=n-1;i>=0;i--){
		if(a[i]=='0'){
			BiNode *p=(BiNode *)malloc(sizeof(BiNode));
			p->lchild=NULL;
			p->rchild=NULL;
			BStack[++top]=p;
		}
		if(a[i]=='1'){
			BiNode *p=(BiNode *)malloc(sizeof(BiNode));
			p->lchild=BStack[top--];
			p->rchild=NULL;
			BStack[++top]=p;
		}
		if(a[i]=='2'){
			BiNode *p=(BiNode *)malloc(sizeof(BiNode));
			p->lchild=BStack[top--];
			p->rchild=BStack[top--];
			BStack[++top]=p;
		}
	}
	return BStack[0];
} 
//递归
BiTree DBiString(char a[]){ 
	sn++;
	BiNode *p=(BiNode *)malloc(sizeof(BiNode));
	printf("%d\n",sn);
	if(sn>strlen(a)-1) return NULL;
	if(a[sn]=='0'){
		p->lchild=NULL;
		p->rchild==NULL;
		return p;
	}
	else{
		if(a[sn]=='1'){
		p->lchild=DBiString(a);
		p->rchild=NULL;
	}
		else{
		p->lchild=DBiString(a);
		p->rchild=DBiString(a);
	}
		return p;
	}
} 
//先序非递归遍历
void FPreOrder(BiTree bt){
	//if(bt) return;
	BiTree TStack[MaxSize];
	int top=-1;
	BiNode *p=bt;
	//注意判断条件是结点或栈不为空，若只判断栈空时，先序递归回到根结点是栈为空，且右子树存在，这样就访问不了右子树。 
	while(top!=-1||p){//p不空，左子树不空，访问左子树，p空，栈里有元素时，出栈栈顶元素，访问右子树，p空栈空结束 
		if(p){
			printf("%c",p->data);
			TStack[++top]=p;
			p=p->lchild;
		}
		else{
			p=TStack[top--];
			p=p->rchild;
		}		
	}	
}
//非递归中序遍历
void FInOrder(BiTree bt){
	BiTree TStack[MaxSize];
	int top=-1;
	BiNode *p=bt;
	//判断条件与先序一样 
	while(top!=-1||p){
		if(p){
			TStack[++top]=p;
			p=p->lchild;
		}
		else{
			p=TStack[top--];
			printf("%c",p->data);
			p=p->rchild;
		}
	}	
}
//后序非递归遍历 
void FPostOrder(BiTree bt){
//	printf("%c",c);
	BiTree TStack[MaxSize];
	int top=-1;
	BiNode *p=bt,*r=NULL;//r用来标记访问过的上一个结点 
	while(top!=-1||p!=NULL){//栈里每个元素都是当前遍历结点的祖先 
		if(p!=NULL){//遍历到树的最左下方 
	//	if(p->data=='I') break;
			TStack[++top]=p;
			p=p->lchild;
		}
		else{//左边到头后回到上一层但不访问，接着访问右子树 
			p=TStack[top];
			if(p->rchild!=NULL&&p->rchild!=r){//右子树不为空且没被访问过，若为空或被访问过是从下往上回来的过程 
				p=p->rchild;
				TStack[++top]=p;//每次遍历到新结点都要入栈 
				p=p->lchild;//在递归遍历左子树 
			}
			else{//左右子树都为空，或左右子树都被访问过回到上一层 
				p=TStack[top--];
				printf("%c",p->data);
				r=p;//标记被访问过 
				p=NULL;//出栈回到上一层，若p不为空讲重复访问 
			}
		}
//			for(int i=0;i<1;i++)
//				printf("%c",TStack[0]->data);
//				printf("\n");
	}
	for(int i=0;TStack[i]!=NULL;i++)
		printf("%c",TStack[i]->data);
//printf("1");
}

//栈和队列-------- 
//入栈
bool Push(Stack &S,ElemType e){
	if(S.top==MaxSize-1){
		printf("栈满!\n");
		return false;
	}
	else{
		S.elem[++S.top]=e;
		return true;
	}
} 
//出栈
ElemType Pop(Stack &S){
	if(S.top==-1){
		printf("栈空！\n");
		return 0;
	}
	else
		return S.elem[S.top--];
} 
//入队
bool EnQueue(Queue &Q,ElemType e){
	if(Q.count==MaxSize){
		printf("队满");
		return false; 
	}
	else {
		
		Q.elem[Q.rear]=e;
		Q.rear=(Q.rear+1)%MaxSize;
		Q.count++;
		
		return true;
	}
} 
//出队
ElemType DeQueue(Queue &Q) {
	if(Q.count==0){
		printf("队空");
		return 0; 
	}
	else{
		int temp=Q.elem[Q.front];
		Q.front=(Q.front+1)%MaxSize;
		Q.count--;
		return temp;
	}
}



//链表------------------ 
//带头节点的单链表初始化 
bool InitList(LinkList &L){
	L=(LNode *)malloc(sizeof(LNode));
	if(L=NULL) return false;//内存已满
	L->next=NULL;
	return true;
	}
/*不带头节点的初始化（头指针） 
bool InitList(LinkList &L){
	L=null;
	return true;
	}
*/ 
//带头结点双链表初始化 
bool InitDlist(DLinklist &L){
	L=(DNode *)malloc(sizeof(DNode));
	if(L==NULL) return false;//内存不足
	L->prior=NULL;
	L->next=NULL;
	return true; 
}
//判空(带头结点)
bool Empty(LinkList L){
	return L->next==NULL;
}
bool DEmpty(DLinklist L){
	return L->next==NULL;
} 
//插入节点
bool ListInsert(LinkList &L,int n,ElemType e){
	if(n<1) return false;
	LNode *p;
	int j=0;//头节点看作第零个
	p=L; 
	while(p!=NULL&&j<n-1){//找到第n-1个位置
	p=p->next; 
	j++;	
	} 
	if(p==NULL) return false;
	LNode *s=(LNode *)malloc(sizeof(LNode));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return true;
}
//删除结点 
void Del(LinkList &L,int x){
	LNode* p=L->next,*pre=L;
	while(p){
		if(p->data!=x){
			pre=p;
			p=p->next;
		}
		else{
		pre->next=p->next;
		free(p);
		p=pre->next;
		}	
	}
} 
//后插操作
bool InsertNextNode(LNode *p,ElemType e){
	if(p==NULL) return false;
	LNode *s=(LNode *)malloc(sizeof(LNode));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return true; 
} 
//双链表后插操作
bool InsertNextDNode(DNode *p,DNode *s){//把s插到p后面 
	if(p==NULL||s==NULL) return false;
	s->next=p->next;
	if(p->next!=NULL)//如果p后有后继节点
		p->next->prior=s;
	s->prior=p;
	p->next=s;
	return true; 
} 
bool DeleteDNode(DNode *p,DNode *s){
	if(p==NULL||s==NULL) return false;
	DNode *q=p->next;
	p->next=q->next;
	if(q==NULL) return false;
	if(q->next!=NULL)
		q->next->prior=p;
	free(q);
}
//前插操作
bool InsertPriorNode(LNode *p,LNode *s){
	if(p==NULL||s==NULL) return false;
	s->next=p->next;
	p->next=s;
	ElemType temp=p->data;
	p->data=s->data;
	s->data=temp;
	return true;
} 
//按位序删除
bool ListDelete(LinkList &L,int i){
	if(i<1) return false;
	LNode *p;
	int j=0;//头节点看作第零个
	p=L; 
	while(p!=NULL&&j<i-1){//找到第n-1个位置
	p=p->next; 
	j++;	
	} 
	if(p==NULL||p->next==NULL) return false;
	LNode *q=p->next;
	printf("删除节点值为：%d\n",q->data);
	p->next=q->next;
	free(q);
	return true; 
}
//删除指定结点
bool DeleteNode(LNode *p){
	if(p==NULL) return false;
	LNode *q=p->next;
	p->data=q->data;
	p->next=q->next;
	free(q);
	return true;
} 
//按位查找
//LNode *GetElem(LinkList L,int i){
//	if(i<0) return false;
//	LNode *p;
//	int j=0;
//	p=L;
//	while(p!=NULL&&j<i){
//		p=p->next;
//		j++;
//	}
//	return p;
//} 
//按值查找
LNode *LocateElem(LinkList L,ElemType e){
	LNode *p=L->next;
	while(p!=NULL||p->data!=e)
	p=p->next;
	return p;
} 
//求表长
int Length(LinkList L){
	int len=0;
	LNode *p=L;
	while(p->next!=NULL){
		p=p->next;
		len++;
	}
	return len;
} 
//尾插法建立链表
LinkList List_TailInsert(LinkList &L){
	int i;
	L=(LNode *)malloc(sizeof(LNode));
	LNode *s,*r=L;
	scanf("%d",&i);
	while(i!=9999){
		s=(LNode *)malloc(sizeof(LNode));
		s->data=i;
		r->next=s;
		r=s;
		scanf("%d",&i);
	}
	r->next=NULL;
	return L;
} 
//头插法建立链表
LinkList List_HeadInsert(LinkList &L){
	int i;
	L=(LNode *)malloc(sizeof(LNode));
	LNode *s;
	L->next=NULL;
	scanf("%d",&i);
	while(i!=9999){
		s=(LNode *)malloc(sizeof(LNode));
		s->data=i;
		s->next=L->next;
		L->next=s;
		scanf("%d",&i);
	}
	return L;
}
//创建双链表 
void creat(DLinklist &L){
	InitDlist(L);
	for(int i=0;i<6;i++){
		DNode *p=(DNode *)malloc(sizeof(DNode));
		int a;
		scanf("%d",&a);
		p->data=a;
		InsertNextDNode(L,p);
	}	
}
//输出链表 
void PrintList(LinkList L){
	while(L->next!=NULL){
		printf("%d ",L->next->data);
		L=L->next;
	}
	printf("\n");
}
//就地逆置 
//LinkList Reverse(LinkList &L){
//	if(L==NULL) return false;
//	LNode *p=L->next;
//	while(p->next!=NULL){
//		LNode *temp=p->next;//保存结点 
//		p->next=temp->next;//断开要动节点，并连接后面节点 
//		temp->next=L->next;//将断开节点从头插入 
//		L->next=temp;
//	}
//	return L;
//} 
//找到倒数k个元素
int Search_k(LinkList L,int k){
	LNode *p=L,*q=L;
	if(q==NULL||p==NULL) return 0;
	while(k--)
		q=q->next;
	while(q!=NULL){
		q=q->next;
		p=p->next;
	}
	if(p==L) return 0;
	printf("%d\n",p->data);
	return 1;
} 
//判断是否两个链表相交
LNode *IsCommon(LinkList p,LinkList q){
	//先遍历两个链表的长度
	int plen=0,qlen=0,alen=0,tag=0;//tag=1,p长，tag=0,q长; 
	LNode *tp=p;
	LNode *tq=q;
	while(tp!=NULL||tq!=NULL){
		if(tp!=NULL) {
		plen++;
		tp=tp->next;
		}
		if(tq!=NULL) {
		qlen++;
		tq=tq->next;
		}
	}

	if(plen>=qlen){
		alen=plen-qlen;
		tag=1;
	}
	else{
		alen=qlen-plen;
		tag=0;
	}
	//长的先走长度之差步 
	if(tag==1){
		while(alen--)
			p=p->next;
		while(qlen--){
			p=p->next;
			q=q->next;
			if(p->data==q->data) return p;
		}
	}
		
	else{
		while(alen--)
			q=q->next; 
		while(plen--){
			p=p->next;
			q=q->next;
			if(p->data==q->data) return p;
		}
	}
	return NULL;
} 
//在第n个位置插入值为e的结点
bool Insert(LinkList &L,int n,int e){
	LNode *pre=L,*p=L->next;
	int i=1;
	while(i<n&&p){
		pre=p;
		p=p->next;
		i++; 
	}
	if(i==n){
		LNode *s=(LNode*)malloc(sizeof(LNode));
		s->data=e;
		s->next=pre->next;
		pre->next=s;
		return true;
	}
	else return false;
} 
/*1 2 3 4 5 9999
9 8 7 3 4 5 9999*/

//层序中序创建 
//BTNode* CreateBTree(ElementType level[], ElementType in[], int l1, int r1, int l2, int r2){ 
//	if (l2 > r2){
//		return NULL;
//	}
//	else{
//		BTNode* bt = (BTNode*)malloc(sizeof(BTNode));
//		
//		int i, j;//分别指向level和in中数组的元素
//		int flag = 0;
// 
//		//寻找根结点，若level中第一个与in中元素匹配的即为根结点
//		for (i = l1; i <= r1; ++i)
//		{
//			for (j = l2; j <= r2; ++j)
//			{
//				if (level[i] == in[j])
//				{
//					flag = 1;
//					break;
//				}
//			}
//			if (flag == 1)
//				break;
//		}
// 
//		bt->data = level[i];//曾经写错过，写成了level[j]，j指向的是in中的元素，应改为in[j]
//		bt->lchild = CreateBTree(level, in, l1 + 1, r1, l2, j - 1);
//		bt->rchild = CreateBTree(level, in, l1 + 1, r1, j + 1, r2);
// 	} 
//		return bt;
//	}










