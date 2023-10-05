#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h> 
#define MaxSize 15
#define Inf 10000  //����� 
bool visited[MaxSize]; 
static int sn=-1;
typedef int ElemType;
//������ 
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
//˫���� 
typedef struct DNode{
	int data;
	struct DNode *prior,*next;
}DNode,*DLinklist;
//���������ӱ�ʾ��
typedef struct BiNode{
	char data;
	BiNode *lchild,*rchild;
}BiNode,*BiTree;
//���ĺ��ӱ�ʾ��
typedef struct CTreeNode{
	int vnum;//ͼ�н���� 
	struct CTreeNode *child[MaxSize];
	int cnum;//���Ӹ��� 
}*CTree,CTNode; 
//ͼ�ڽӾ����ʾ��
typedef struct {
	char Vex[MaxSize];//���㼯 
	int Edge[MaxSize][MaxSize];//�߼�  ��Ȩͼ�����ڱ���0��������1���Խ�����0����ȫͼ�����ڱ��ǡޣ����ڱ���Ȩֵ���Խ�����0 
	int vexnum,arcnum;//��ǰ��������ͱ߼� 
}MGraph;
//ͼ���ڽӱ��ʾ��
//�߽��
typedef struct ArcNode{
	int adjvex;//ָ�򶥵���
	struct ArcNode *next;//ָ����һ������ָ��
//	int weight;//Ȩֵ��Ϣ 
}ArcNode; 
//˳��洢������ 
typedef struct VNode{
	char data;
	ArcNode *first;//��һ���߽�� 
}VNode,AdjList[MaxSize]; 
//�洢ͼ���ڽӱ� 
typedef struct {
	AdjList adjlist;//����˳���
	int vexnum,arcnum;//����������߸����� 
}LGraph; 
//ջ
typedef struct{
	int top;//=-1;
	ElemType elem[MaxSize];
}Stack; 
//����
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
void Qsort(int a[],int m,int n);//��������  ��ã�nlogn,���n����ƽ����nlogn���ռ䣺nlogn������:���򣬲��ȶ� //ע����������������������¼����ȷ��������ѭ������ֹ������Ҫ�ڽ��뺯��֮ǰ����� 
void Bubble(int a[],int n);//ð������  ��ã�n ���n��  ƽ����n���� �ռ䣺1���ȶ������������������ڻ������� ע��flagʹ�ã���������û���������������˳��� 
void Insertsort(int a[],int n);//ֱ�Ӳ�������  ��ã�n  ���n��  ƽ����n��  �ռ䣺1���ȶ�  ���������������ڻ������� Ҫ�ƶ�Ԫ�� 
void ZBInsert(int a[],int n);//�۰��������  ��ã�n  ���n��  ƽ����n��  �ռ䣺1���ȶ�   ֻ������˳��� �Ƚϴ������ʼ״̬�޹� 
void Shellsort(int a[],int n);//ϣ������ ��ã�--  ���n��  ƽ����n  �ռ�1�����ȶ� ������ѡȡ�ķ��鳤�������й�һ��ѡd/2 
void Ssort(int a[],int n);//ֱ��ѡ������  ��ã� n��  ���n�� ƽ����n��  �ռ�  1�����ȶ�  ���ܣ��Ƚϴ�����ʱ�临�Ӷȣ����ʼ״̬�޹� 
void BuildMaxHeap(int a[],int len);//���� 
void AdjustDown(int a[],int k,int len);//������
void Heapsort(int a[],int len);//������   ��ã�nlogn ���nlogn ƽ����nlogn �ռ�:1;���ȶ�   ���ܣ��Ƚϴ�����ʱ�临�Ӷȣ����ʼ״̬�޹�
void Merge(int a[],int p,int q,int n,int b[]);//�������еĺϲ�  i��һ�����е���ʼ��ַ��j�ǵڶ������е���ʼ��ַ��n�Ǻϲ��õ����е���ʼ��ַ 
void Mpass(int a[],int n,int L,int b[]); //һ�˺ϲ��㷨   n�������ܳ��ȣ�L��ÿ�κϲ����������еĳ��� 
void Msort(int a[],int n,int b[]);//��·�鲢����   ��ã�nlogn  �: nlogn ƽ����nlogn �ռ䣺n��  �ȶ�  �������ʼ״̬�޹� 

void CreatLGraph(LGraph &G);//��ͼ���ڽӱ� 
void PrintLGraph(LGraph G);//���ͼ 
void BFS(LGraph G,int v);//������ȱ���
void BFSMinpath(LGraph G,int v);//������ȱ�������Ȩͼ���·���������ľ�������d��ÿ�α��������¾��룩 
bool BFSIstree(LGraph G,int v);//������ȱ����ж�ͼ�Ƿ�Ϊһ���� ���ж�visted���������ֳ�ͻ����ڻ��� 
void DFS(LGraph G,int v);//������ȱ������ݹ飩(Ҫ����ȫ�ֱ������visited)
void dfs(LGraph G,int v);//������ȱ������ǵݹ飩 
void ddfs(LGraph G,int i,int j,int d[],int n);
void FindPath(LGraph G,int u,int v,int k,int path[]);//������ȱ���������·��������ȫ�ֱ�����������visited,pathΪ·�����飬kΪ·���Ͻ��Ĵ��� 
void InDegree(LGraph G,int result[]);//�����ڽӱ����ͼ�и��������� 
void VList(LGraph G,LGraph VG);//����ͼ�����ڽӱ�
void BGraphTree(LGraph G,CTree &T,int v);//����ͼ�Ĳ������������ 
void Floyed(LGraph G,int dis[MaxSize][MaxSize]);//���������㷨��ͼ���������������·�� 

void CreatBiTree(BiTree &bt);//�������������ݹ�����
void PreOrder(BiTree bt);//����ݹ����
void InOrder(BiTree bt);//����ݹ����
void PostOrder(BiTree bt);//����ݹ���� 
void FPreOrder(BiTree bt);//����ǵݹ����
void FInOrder(BiTree bt);//����ǵݹ����
void FPostOrder(BiTree bt);//����ǵݹ���� 
void LevelOrder(BiTree bt);//�������
void BtHeight(BiTree bt,int &h);//�ݹ������� 
void Presum(BiTree bt,int &q);//�ݹ�������� 
void BtSwap(BiTree bt);//�ݹ齻���������� 
void BtDelete(BiTree bt);//�ݹ�ɾ�������ͷſռ� 
BiNode *CommonAncestor(BiTree bt,BiNode *p,BiNode *q);//�ݹ��ж�����Ĺ������� 
void Common(BiTree bt,BiNode *p,BiNode *q,BiNode **r);
BiNode* Ancestor(BiTree bt,BiNode *p);//�ݹ��ҵ���������
bool Isson(BiTree T,BiNode *u,BiNode *v);//�ݹ��ж�u�Ƿ�Ϊv������ 
BiTree piCreate(char pre[],char in[],int pl,int pr,int il,int ir);//������������򴴽������� 
int LHeight(BiTree bt);//�������������
int LWidth(BiTree bt);//������������� 
int LLnodecount(BiTree bt);//�����������Ҷ��or����֧or˫��֧�ڵ�or����Ҷ�ڵ����
void IsBalance(BiTree bt,int &b,int &h);//�ж϶������Ƿ�ƽ�⣬bΪ1ƽ�⣬hΪ�߶� 
void ReLevel(BiTree bt);//���ϵ��£����ҵ��������������� 
void BiString(BiTree &bt,char s[]);//����210���⣨��Ƥ��35�� ���� 
BiTree RBiString(char a[],int n); //����
BiTree DBiString(char a[]);//�ݹ� 
bool Push(Stack &S,ElemType e);//��ջ
ElemType Pop(Stack &S);//��ջ
bool EnQueue(Queue &Q,ElemType e);//���
ElemType DeQueue(Queue &Q);//����

bool InitList(LinkList &L);//��ͷ�ڵ�ĵ������ʼ�� 
bool InitDlist(DLinklist &L);//��ͷ���˫�����ʼ��
LinkList List_TailInsert(LinkList &L);//β�巨��������
LinkList List_HeadInsert(LinkList &L);//ͷ�巨��������
void creat(DLinklist &L);//��ͷ����˫������ 
bool ListInsert(LinkList &L,int n,ElemType e);//����ڵ�
bool InsertNextNode(LNode *p,ElemType e);//������
LNode *LocateElem(LinkList L,ElemType e);//��ֵ����
LNode *GetElem(LinkList L,int i);//��λ����
int Length(LinkList L);//���
void Del(LinkList &L,int x);//ɾ����� 
bool InsertNextDNode(DNode *p,DNode *s);//˫���������
void PrintList(LinkList L);//�������
bool ListDelete(LinkList &L,int i);//��λ��ɾ��
LinkList Reverse(LinkList &L);//�͵�����
int Search_k(LinkList &L,int k);//�ҵ�����k��Ԫ��
LNode *IsCommon(LinkList p,LinkList q);//�ж��Ƿ����������ཻ
bool Insert(LinkList &L,int n,int e);//�ڵ�n��λ�ò���ֵΪe�Ľ��
void LInsertSort(LinkList &L);//����ֱ�Ӳ������� 
void exchange(LinkList &L,LNode *p);// 2001��ѧ  1.����������
LinkList List_TailInsert_1(LinkList &L,LNode* &p,int a);

void Inverse(int a[],int m);//�������� 
int *Mul_Num(int a[],int b[],int m,int n);//������� 
void Matrix(int num[][MaxSize],int n);//�����������
void SubSet(char ch[],int n);//���Ӽ�����  ���ch�������Ӽ�
void Insert2(LinkList &L);// 2000��ѧ �����������
void dbubble(int a[],int n);// 2001��ѧ  3.˫��ð��
int *insert(int a[],int n,int e);//2002  1.�ݹ���� 
int maxlength(int a[],int n);//2002 2.��ݹ������� 
LNode *mergelist(LNode *p,LNode *q);//2002 3.��������ϲ� 
LNode *eightlist(LNode *p,LNode *q);//2002 4.8����������� 
void m90(int a[MaxSize][MaxSize],int n);//2003 ��ά����˳ʱ����ת90�� 
double funxy(double x,double y);//2003 5.�ǵݹ�ʵ�ֺ��� 
void deletex(BiTree &root,char x);//2013 ɾ��>=x�Ķ���������Ľ��
void Delallx(BiTree &bt,BiNode *p,char x,BiNode *&newhead);//ɾ�������������>=x �����н�� 
void Delx(BiTree &bt,char x);//ɾ��ֵΪx�Ķ����������Ľ�� 
bool IsPrime(int a);//�ж��Ƿ�Ϊ���� 
BiTree ret(BiTree root,char x);
void fun1(BiTree root,int sum[],int n);//2015 2 
void fun2(BiTree root); 
void DoubleSort(DLinklist &L);//2019  1
void prelevel(BiTree bt,int l);//��ѧ2018 1 
LinkList fun_2015_4_966(LinkList &L); 
bool duichen(BiNode *r,BiNode *l);//2020 ��ר �ݹ��ж����Ƿ�Գ�
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




//------------����----------
//2020 ��ר �ݹ��ж����Ƿ�Գ�
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
//��ѧ2018  1
void prelevel(BiTree bt,int l){
	if(bt==NULL) return;
	printf("%c  %d",bt->data,l);
	prelevel(bt->lchild,l+1);
	prelevel(bt->rchild,l+1); 
} 
//��ѧ2019  1
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
		r=p->next;//���������� 
		pre=L;//��ͷ��λ�� ע������preָ����÷�����pre->next�ȽϿ��Ա���ǰ��λ�� 
		while(pre->next!=NULL&&pre->next->data<=p->data) //�ҵ�λ��ʱpre����һ�����ֵ���ڴ������㣻δ�ҵ�λ��pre�¸����Ϊ�� 
			pre=pre->next;
		p->next=pre->next;//������������ҵ�λ�� 
		pre->next=p;
		p=r;//p����������	
		}
	return L; 
} 
//��ѧ2015 2�������Ҷ�ڵ� 
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
	for(int i=0;i<=4;i++) printf("��%d�㣺%d\n",i,sum[i]);
} 
//2013 ɾ��>=x�����Ľ��
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
//ɾ�������������>=x �����н��
void Delallx(BiTree &bt,BiNode *p,char x,BiNode *&newhead){
	if(bt==NULL)
		return;
	if(bt->data<x){
		Delallx(bt->rchild,bt,x,newhead);
		if(bt->data<x)
			newhead=bt;	//�����µ��������		 
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
		if(bt!=NULL&&bt->data>=x) //����������Ϊ�������п��ܴ��ڱ�xС�Ľ�㲢���ұ��ÿյĽ�� 
			free(bt);
	}
}
//ɾ��ֵΪx�Ķ����������Ľ�� 
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
//2003 5.�ǵݹ�ʵ�ֺ��� 
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
//2003 ��ά����˳ʱ����ת90�� 
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
//2002 4.8����������� 
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
//2002 3.��������ϲ� 
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
//2002 2.��ݹ������� 
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
//2002  1.�ݹ���� 
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
// 2001��ѧ  3.˫��ð��
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
// 2001��ѧ  1.����������
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
// 2000��ѧ �����������
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
	LNode *p=L->next,*pre;//preָ�����ڱ������򲿷֣��ҵ�����λ�� 
	LNode *r=p->next;//p ָ��Ϊ��ǰ�����㣬r���ڼ�¼�����㣬��Ϊ�ҵ�λ�ú�Ҫ�Ͽ����� 
	p->next=NULL;//���ｫ����ֳ������֣�ǰ�������� 
	p=r;//pָ��Ӻ󲿷����α��� 
	while(p!=NULL){
		r=p->next;//���������� 
		pre=L;//��ͷ��λ�� ע������preָ����÷�����pre->next�ȽϿ��Ա���ǰ��λ�� 
		while(pre->next!=NULL&&pre->next->data<=p->data) //�ҵ�λ��ʱpre����һ�����ֵ���ڴ������㣻δ�ҵ�λ��pre�¸����Ϊ�� 
			pre=pre->next;
		p->next=pre->next;//������������ҵ�λ�� 
		pre->next=p;
		p=r;//p����������	
		}
	}
//�ݹ��ж�����Ĺ�������
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
//�ݹ��ҵ���������
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
bool Isson(BiTree T,BiNode *u,BiNode *v){//�ݹ��ж�u�Ƿ�Ϊv������ 
//	printf("%c\n",u->data);
	if(u==NULL) return false;
	if(v==u) return true;
	bool flagr=false,flagl=false;
	flagl=Isson(T,u->lchild,v);
	flagr=Isson(T,u->rchild,v);
	return flagl||flagr;
} 
//������������򴴽������� 
BiTree piCreate(char pre[],char in[],int pl,int pr,int il,int ir){//pl���������������il������������� 
	if(pl>pr) return NULL;
//	printf("%s  %s",pre,in);
	BiNode *root=(BiNode *)malloc(sizeof(BiNode));
	root->data=pre[pl];
	int k=0;
	while(pre[pl]!=in[k]) k++;//�ҵ����ڵ��������е�λ�� 
	int leftnum=k-il;  //���������ڵ���� 
	root->lchild=piCreate(pre,in,pl+1,pl+leftnum,il,k-1);
	root->rchild=piCreate(pre,in,pl+leftnum+1,pr,k+1,ir);
	return root;
} 
//--------������ƻ���-------- 
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
//�������� 
void Inverse(int a[],int m){
	for(int i=0;i<m/2;i++){
		int temp=a[i];
		a[i]=a[m-i-1];
		a[m-i-1]=temp;
	}
}
//�������
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
//�����������
void Matrix(int num[][MaxSize],int n){
	int number=0;
	for(int i=0;i<=n/2;i++){    //n�׾����� n/2 ����ȡ���� //i��λ���Ʋ����ı��� 
		for(int j=i;j<n-i;j++)
			num[i][j]=number++;  //��i����ϱ�  �в��䣨�ϱ����±�i�� ��<n-i 
		for(int j=i+1;j<n-i;j++)
			num[j][n-i-1]=number++;// ��i����ұ�  �в��䣨�ұ����±�n-i-1�� ���±��i+1��ʼ��n-i-1 
		for(int j=n-i-2;j>=i;j--)
			num[n-i-1][j]=number++;// ��i����±�  �в��䣨���±�n-i-1�� ���±�n-i-2��i 
		for(int j=n-2-i;j>i;j--)
			num[j][i]=number++;   //��i������  �в��䣨���±� i�� ���±� n-i-2��i-1 
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%02d ",num[i][j]);
			printf("\n");
	}
} 
//���Ӽ�����  ���ch�������Ӽ�
//˼�룺����Ϊn��������2��n�η�-1�����򣬴�1��2��n�η�-1����2��n�η�-1���� ��ÿ����ת����Ϊ�����ƶ�Ӧ���Ӽ���0�����1��� 
void SubSet(char ch[],int n){
	int num=1;//����Ӽ����� 
	for(int i=0;i<n;i++)  //����Ϊn�ļ��Ϲ���2��n�η�-1���Ӽ� 
		num*=2;
	int sub[n];//��i��ʱ��Ӧ�Ķ��������� 
	for(int i=0;i<num;i++){  //��ÿ����ת����Ϊ�����ƣ������Ӧ���� 
		for(int j=0;j<n;j++)
			sub[j]=0;  //���һ����Ҫ���³�ʼ�� 
		int count=0;//������λ���±� 
		int subnum=i;
	while(subnum>0){ //ת��������  ��2ȡ�ֱ࣬��������Ϊ0����ʱ�õ��Ķ����������� 
		sub[count]=subnum%2;
		subnum/=2;
		count++;
	} 
	for(int j=0;j<n;j++){ //�����Ӧ���� 
		if(sub[j])
		printf("%c",ch[j]);
	}
		 printf("\n");	 
	} 
} 
//--------����--------- 
//	int a[MaxSize]={27,99,0,8,13,64,86,16,7,10,88,25,90}; 
// 	int a[6]={2,4,6,1,3,5};
// 	int b[6];
//int main(){
//	int a[MaxSize]={27,99,0,8,13,64,86,16,7,10,88,25,90}; 
// 	int a[6]={2,4,6,1,3,5};
// 	int b[6];
	//a[13]=Inf;//���������¼ȷ��ָ��i�����ұ��������п�����ֹ 
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
//��·�鲢����   ��ã�nlogn  �: nlogn ƽ����nlogn �ռ䣺n��  �ȶ�  �������ʼ״̬�޹�
void Msort(int a[],int n,int b[]){
	int l=1;
	while(l<n){
		Mpass(a,n,l,b);
		l*=2;
		Mpass(b,n,l,a);
		l*=2;
	} 
}
 //�������еĺϲ�  p��һ�����е���ʼ��ַ��q�ǵڶ������е���ʼ��ַ��n�Ǻϲ��õ����е���ʼ��ַ,b�Ǻϲ�֮������� 
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
//һ�˺ϲ��㷨   n�������ܳ��ȣ�L��ÿ�κϲ����������еĳ��� 
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
//������  ��ã�nlogn ���nlogn ƽ����nlogn �ռ�:1;���ȶ�   ���ܣ��Ƚϴ�����ʱ�临�Ӷȣ����ʼ״̬�޹�
void BuildMaxHeap(int a[],int len){//���� 
	for(int i=len/2;i>=0;i--)
		AdjustDown(a,i,len);
}
void AdjustDown(int a[],int k,int len){//������
	int temp=a[k];
	for(int i=2*k;i<len;i*=2){
		if(k==0) i=1;//ע��kΪ������������Ϊ1�������Ϲ�ʽ2*k�� 
		if(i<len-1&&a[i]<a[i+1])
			i++;              //������������ӽ�����Һ��ӱ����Ӵ� 
		if(a[k]>=a[i]) break;
		else{
			a[k]=a[i];
			k=i;     //��Ԫ���ϸ���СԪ�ؼ������±Ƚ��³� 
		}
		a[k]=temp;
	}
}
void Heapsort(int a[],int len){//������   
	BuildMaxHeap(a,len);
	for(int i=len-1;i>0;i--){
		int temp=a[0];
		a[0]=a[i];
		a[i]=temp;
		AdjustDown(a,0,i-1);//�����ѣ�ÿ�γ�ȥһ��Ԫ�س��ȼ�һ��
	}
}
//ֱ��ѡ������  ��ã� n��  ���n�� ƽ����n��  �ռ�  1�����ȶ�  �������ʼ״̬�޹� 
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
//ϣ������ ��ã�--  ���n��  ƽ����n  �ռ�1�����ȶ� ������ѡȡ�ķ��鳤�������й� һ��ѡȡd/2 
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
//�۰��������  ��ã�n  ���n��  ƽ����n��  �ռ䣺1���ȶ�   ֻ������˳���
//ע���۰���ҵ�����״̬��low=high+1��
//��ʱlow��ָ��λ��Ϊ����λ�ã�Ϊ�˱����ȶ��ԣ����ҵ����Ԫ����Ӧ�������ұ߲���λ�ã����Ե����������mid+1������� 
void ZBInsert(int a[],int n){
	int i,j,temp,mid,low,high;
	for(int i=1;i<n;i++)
		if(a[i]<a[i-1]){		//	��ߵ�Ԫ�رȴ���Ԫ�ش�����������ң���߱ȴ���Ԫ��С���򿼲���һ��Ԫ�� 
		temp=a[i];
		low=0;
		high=i-1;
		while(low<=high){
			mid=(low+high)/2;
			if(temp<a[mid])
				high=mid-1;
			else 
				low=mid+1;  //������Ϊ�˱����ȶ��ԣ���������Ԫ����ǰ���Ԫ�����ʱ��Ӧ�ü������Ұ벿����λ�� 
		}
		//�۰��������״̬��low=high+1��low��Ϊ����λ�� 
		printf("%d\n",mid);
		for(j=i-1;j>=low;j--) 
			a[j+1]=a[j];
		a[low]=temp;//�ҵ���һ���ȴ���Ԫ��С�ģ��ڸ�Ԫ�ص��ұ߲��� 
	}
	
} 
//ֱ�Ӳ�������  ��ã�n  ���n��  ƽ����n��  �ռ䣺1���ȶ�  ���������������ڻ�������  Ҫ�ƶ�Ԫ��  
//�ӵڶ���Ԫ�ؿ�ʼ �Ӻ���ǰ�Ƚϣ�ע����СԪ�ط�����ǰ������ ��
void Insertsort(int a[],int n){
	int i,j,temp;
	for(i=1;i<n;i++)
	if(a[i]<a[i-1]){		//��ߵ�Ԫ�رȴ���Ԫ�ش�����������ң���߱ȴ���Ԫ��С���򿼲���һ��Ԫ�� 
		temp=a[i];
		for(j=i-1;j>=0&&a[j]>temp;j--)  
			a[j+1]=a[j];
		a[j+1]=temp;//�ҵ���һ���ȴ���Ԫ��С�ģ��ڸ�Ԫ�ص��ұ߲��� 
	}
}
//ð������  ��ã�n ���n��  ƽ����n���� �ռ䣺1���ȶ�������������
//�����ڻ������� ע��flagʹ�ã���������û���������������˳���
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
			printf("\n��%d�ˣ�\n",n-i);
			for(int q=0;q<n;q++)
			printf("%d ",a[q]);
		 if(flag==false) return;	 
	 }
} 
//��������  ��ã�nlogn,���n����ƽ����nlogn���ռ䣺nlogn������:���򣬲��ȶ� 
//ע����������������������¼����ȷ��������ѭ������ֹ������Ҫ�ڽ��뺯��֮ǰ����� 
void Qsort(int a[],int m,int n){//�±��1��ʼ 
	if(m>=n) return;
	int i=m;
	int j=n+1;
	int k=m;
	int temp;
	while(i<j){
		i++;
		while(a[i]<=a[k]) i++;//�����ҵ���һ���Ȼ�׼��� 
		j--;
		while(a[j]>a[k]) j--;//�����ҵ���һ���Ȼ�׼С����ڵ� 
		if(i<j){//i��jû�ཻ 
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	
	}
	//��ʱi��j��
	temp=a[j];
	a[j]=a[k];
	a[k]=temp;
//		for(int q=0;q<13;q++)
//		printf("%d ",a[q]);	
//		printf("\n");
	//	return;
	//һ�λ������
	Qsort(a,m,j-1);
	Qsort(a,j+1,n);	
}















//---------ͼ------- 
//������ȱ������ǵݹ飩
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
//������ȱ������ݹ飩(Ҫ����ȫ�ֱ������visited)
void DFS(LGraph G,int v){
	printf("%c",G.adjlist[v].data);
	visited[v]=true;
	ArcNode *p=G.adjlist[v].first;
	for(p;p!=NULL;p=p->next){
		if(visited[p->adjvex]!=true)
			DFS(G,p->adjvex);
	}
} 
//������ȱ����Ҵ�u��v������·��������ȫ�ֱ�����������visited,pathΪ·�����飬kΪ·���Ͻ��Ĵ��򣩣��˻ʺ� 
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
//������ȱ���
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
//������ȱ����ж�ͼ�Ƿ�Ϊһ���� 
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
//������ȱ�������Ȩͼ���·��
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
		printf("��㣺%c  ��̾��룺 %d\n",G.adjlist[i].data,d[i]);	
} 
//�����ڽӱ����ͼ�и���������
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
		printf("��㣺%d   ���:%d\n",i,result[i]);	
}
//���������㷨��ͼ���������������·�� 
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
//		printf("���룺%d\n",k);
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
//����ͼ�Ĳ������������ 
//ע�⣺����������ʱ��bfs�Ķ���Ҫ������㣬����������򱣴�ͼ�ڵ����ţ�������Ϊ������������뺢�ӽڵ����� 
void BGraphTree(LGraph G,CTree &T,int v){
	CTree queue[G.vexnum];
	int front=-1,rear=-1;
	T=(CTNode *)malloc(sizeof(CTNode));
	bool visited[G.vexnum]={0};
		T->vnum=v;
		queue[++rear]=T;
		visited[v]=true;
	while(front!=rear){
		CTNode *t=queue[++front];//������ڵ� 
		ArcNode *p;
		for(p=G.adjlist[t->vnum].first;p!=NULL;p=p->next)
			if(visited[p->adjvex]!=true){
				visited[p->adjvex]=true;
				CTNode *q=(CTNode *)malloc(sizeof(CTNode));
				q->vnum=p->adjvex;  //��ʼ�����ӽ�� 
				t->child[t->cnum++]=q;
				queue[++rear]=q;
			}
	}
} 
//����ͼ�����ڽӱ� 
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
//����ͼ 
void CreatLGraph(LGraph &G){
	//int i,j,k;
	printf("������  ����:\n");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	printf("���붥������:\n") ;
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
	printf("����ߵ�������Ϣ��\n");
	for(int i=0;i<G.arcnum;i++){
		int x,y;//��ʾ��������
		scanf("%d %d",&x,&y);//x��ʾ��ͷ��y��ʾ��β��
		ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=y;
		p->next=G.adjlist[x].first;
		G.adjlist[x].first=p;//ͷ�巨 
	//	printf("����ߵ�Ȩֵ��"); 
	//	scanf("%d",&p->weight); 
		//��Ϊ����ͼ ��ͷ��βΪ˫��
//		ArcNode *q=(ArcNode *)malloc(sizeof(ArcNode));
//		q->adjvex=x;
//		q->next=G.adjlist[y].first;
//		G.adjlist[y].first=q; 
	} 
}
//���ͼ 
void PrintLGraph(LGraph G){
	ArcNode *p;
	for(int i=0;i<G.vexnum;i++){
		p=G.adjlist[i].first;
		printf("��㣺%c     ",G.adjlist[i].data);
		while(p!=NULL){
		//	printf("��㣺%c Ȩֵ��%d     ",G.adjlist[p->adjvex].data,p->weight);
			p=p->next;
		}
		printf("\n");
	} 
}

































//----------------��------------ 
//����
//����ABD*G***CEH**I**F**
//����DGBAHEICF
//����GDBHIEFCA  
//����: ABCDEFGHI 
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
	printf("ֵ��%c   ����%d��\n",bt->data,i);
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
//	//printf("��ȣ�%d",i);
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
//��-------- 
//�������������ݹ�����
//ABD*G***CEH**I**F**
//222*2***222**2**2** 
void CreatBiTree(BiTree &bt){
	char a;
	scanf("%c",&a);
	if(a=='*') {bt=NULL;}//����*����
	else{
		bt=(BiNode *)malloc(sizeof(BiNode));
		bt->data=a;
		CreatBiTree(bt->lchild);
		CreatBiTree(bt->rchild); 
	} 
} 
//����ݹ����
void PreOrder(BiTree bt){
	if(bt==NULL) return;
	printf("%c",bt->data);
	PreOrder(bt->lchild);
	PreOrder(bt->rchild); 
} 
//������� 
void Presum(BiTree bt,int &q){
	if(bt==NULL) return ;
	q+=(bt->data-'0');
	Presum(bt->lchild,q);
	Presum(bt->rchild,q); 
//	return bt->data+a+b-'0';
} 
//111*1***111**1**1**
//����ݹ����
void InOrder(BiTree bt){
	if(bt==NULL) return;
	InOrder(bt->lchild);
	printf("%c",bt->data);//
	InOrder(bt->rchild);
}
//����ݹ���� 
void PostOrder(BiTree bt){
	if(bt==NULL) return;
	PostOrder(bt->lchild);
	PostOrder(bt->rchild);
	printf("%c",bt->data);
}
//�ݹ������� 
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
//�ж϶������Ƿ�ƽ�⣬bƽ�����ӣ�0Ϊ��ƽ�⣬1Ϊƽ�⣬hΪ�߶�
/*˼�룺����ݹ��ж� ÿ����㣺 
	1.��������Ϊ�գ��߶�h=0,b=1;  
	//2.��������û�к��ӣ���h=1,b=1;
	3.����������������������������ôh=max{rh+1,lh+1}(�ϸߵ������߶�+1);
		������������ĸ߶Ȳ����1����ƽ�⣩��b=0;
		������������ĸ߶Ȳ�С�ڵ���1������ƽ�⣩����������Ҳ��ƽ��(rb==1&&lb==1)��b=1������b=0; 
*/
void IsBalance(BiTree bt,int &b,int &h){//b,h Ҫ������ 
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
		IsBalance(p->lchild,lb,lh);//������lb��lh�������εݹ��b��h��ʵ���ϵ�������lb��lh�����㣬��ʹ�������ô��� 
		IsBalance(p->rchild,rb,rh);//���ԣ�lb��lh��ֵ�ᱻ������ 
		h=(lh>rh?lh+1:rh+1);
		if(abs(lh-rh)>1) b=0;
		else{
			if(lb==1&&rb==1) b=1;
			else b=0;
		}
	}
} 
//�ݹ齻����������
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
//�ݹ�ɾ�������ͷſռ�
void BtDelete(BiTree bt){
	if(bt){
		BtDelete(bt->lchild);
		BtDelete(bt->rchild);
		free(bt);	
	}
	bt=NULL;
} 
//������� 
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
//�������������
int LHeight(BiTree bt){
	BiTree BQueue[MaxSize];
	BiNode *p=bt;
	int front=-1,rear=-1,level=0,last=0;//level������last��ʾ��ǰ���������һ������һ�����λ�� 
	BQueue[++rear]=p;
	while(front!=rear){
		p=BQueue[++front];
		if(p->lchild!=NULL)
			BQueue[++rear]=p->lchild;
		if(p->rchild!=NULL)
			BQueue[++rear]=p->rchild;
		if(front==last){//�� ͷ�����λ��ʱ����һ��������к��ӽ�㶼��ӣ�
			level++;	//����һ��Ľ�㶼��ӣ�������һ������λ�ã� ��ͷָ������� ��һ�㣬���� ��  ��
			last=rear;
		}
	}
	return level;
}
//�������������
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
			printf("��%d��Ŀ��Ϊ��%d\n",++level,width);
			width=0;
		}
	}
	return max;
} 
//�����������Ҷ��or����֧or˫��֧or����Ҷ�ڵ����
int LLnodecount(BiTree bt){
	BiTree BQueue[MaxSize];
	int front=-1,rear=-1,count=0;
	BiNode *p=bt;
	BQueue[++rear]=p;
	//Ҷ�ӽ�� 
//	while(front!=rear){
//		p=BQueue[++front];
//		if(p->lchild==NULL&&p->rchild==NULL) count++;
//		if(p->lchild) BQueue[++rear]=p->lchild;
//		if(p->rchild) BQueue[++rear]=p->rchild;
//	} 
	//����֧���
//	while(front!=rear){
//		p=BQueue[++front];
//		if((p->lchild==NULL&&p->rchild!=NULL)||(p->lchild!=NULL&&p->rchild==NULL)) count++;
//		if(p->lchild) BQueue[++rear]=p->lchild;
//		if(p->rchild) BQueue[++rear]=p->rchild;
//	}
	//˫��֧���
//	while(front!=rear){
//		p=BQueue[++front];
//		if(p->lchild!=NULL&&p->rchild!=NULL) count++;
//		if(p->lchild) BQueue[++rear]=p->lchild;
//		if(p->rchild) BQueue[++rear]=p->rchild;
//	}
	//����Ҷ�ڵ� 
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
//���ϵ��£����ҵ��������������� 
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
//����210����
//ע��������ռ��һ��Ҫ��ָ���򸳿�ֵ 
//���� 
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
//����
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
//�ݹ�
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
//����ǵݹ����
void FPreOrder(BiTree bt){
	//if(bt) return;
	BiTree TStack[MaxSize];
	int top=-1;
	BiNode *p=bt;
	//ע���ж������ǽ���ջ��Ϊ�գ���ֻ�ж�ջ��ʱ������ݹ�ص��������ջΪ�գ������������ڣ������ͷ��ʲ����������� 
	while(top!=-1||p){//p���գ����������գ�������������p�գ�ջ����Ԫ��ʱ����ջջ��Ԫ�أ�������������p��ջ�ս��� 
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
//�ǵݹ��������
void FInOrder(BiTree bt){
	BiTree TStack[MaxSize];
	int top=-1;
	BiNode *p=bt;
	//�ж�����������һ�� 
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
//����ǵݹ���� 
void FPostOrder(BiTree bt){
//	printf("%c",c);
	BiTree TStack[MaxSize];
	int top=-1;
	BiNode *p=bt,*r=NULL;//r������Ƿ��ʹ�����һ����� 
	while(top!=-1||p!=NULL){//ջ��ÿ��Ԫ�ض��ǵ�ǰ������������ 
		if(p!=NULL){//���������������·� 
	//	if(p->data=='I') break;
			TStack[++top]=p;
			p=p->lchild;
		}
		else{//��ߵ�ͷ��ص���һ�㵫�����ʣ����ŷ��������� 
			p=TStack[top];
			if(p->rchild!=NULL&&p->rchild!=r){//��������Ϊ����û�����ʹ�����Ϊ�ջ򱻷��ʹ��Ǵ������ϻ����Ĺ��� 
				p=p->rchild;
				TStack[++top]=p;//ÿ�α������½�㶼Ҫ��ջ 
				p=p->lchild;//�ڵݹ���������� 
			}
			else{//����������Ϊ�գ������������������ʹ��ص���һ�� 
				p=TStack[top--];
				printf("%c",p->data);
				r=p;//��Ǳ����ʹ� 
				p=NULL;//��ջ�ص���һ�㣬��p��Ϊ�ս��ظ����� 
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

//ջ�Ͷ���-------- 
//��ջ
bool Push(Stack &S,ElemType e){
	if(S.top==MaxSize-1){
		printf("ջ��!\n");
		return false;
	}
	else{
		S.elem[++S.top]=e;
		return true;
	}
} 
//��ջ
ElemType Pop(Stack &S){
	if(S.top==-1){
		printf("ջ�գ�\n");
		return 0;
	}
	else
		return S.elem[S.top--];
} 
//���
bool EnQueue(Queue &Q,ElemType e){
	if(Q.count==MaxSize){
		printf("����");
		return false; 
	}
	else {
		
		Q.elem[Q.rear]=e;
		Q.rear=(Q.rear+1)%MaxSize;
		Q.count++;
		
		return true;
	}
} 
//����
ElemType DeQueue(Queue &Q) {
	if(Q.count==0){
		printf("�ӿ�");
		return 0; 
	}
	else{
		int temp=Q.elem[Q.front];
		Q.front=(Q.front+1)%MaxSize;
		Q.count--;
		return temp;
	}
}



//����------------------ 
//��ͷ�ڵ�ĵ������ʼ�� 
bool InitList(LinkList &L){
	L=(LNode *)malloc(sizeof(LNode));
	if(L=NULL) return false;//�ڴ�����
	L->next=NULL;
	return true;
	}
/*����ͷ�ڵ�ĳ�ʼ����ͷָ�룩 
bool InitList(LinkList &L){
	L=null;
	return true;
	}
*/ 
//��ͷ���˫�����ʼ�� 
bool InitDlist(DLinklist &L){
	L=(DNode *)malloc(sizeof(DNode));
	if(L==NULL) return false;//�ڴ治��
	L->prior=NULL;
	L->next=NULL;
	return true; 
}
//�п�(��ͷ���)
bool Empty(LinkList L){
	return L->next==NULL;
}
bool DEmpty(DLinklist L){
	return L->next==NULL;
} 
//����ڵ�
bool ListInsert(LinkList &L,int n,ElemType e){
	if(n<1) return false;
	LNode *p;
	int j=0;//ͷ�ڵ㿴�������
	p=L; 
	while(p!=NULL&&j<n-1){//�ҵ���n-1��λ��
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
//ɾ����� 
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
//������
bool InsertNextNode(LNode *p,ElemType e){
	if(p==NULL) return false;
	LNode *s=(LNode *)malloc(sizeof(LNode));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return true; 
} 
//˫���������
bool InsertNextDNode(DNode *p,DNode *s){//��s�嵽p���� 
	if(p==NULL||s==NULL) return false;
	s->next=p->next;
	if(p->next!=NULL)//���p���к�̽ڵ�
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
//ǰ�����
bool InsertPriorNode(LNode *p,LNode *s){
	if(p==NULL||s==NULL) return false;
	s->next=p->next;
	p->next=s;
	ElemType temp=p->data;
	p->data=s->data;
	s->data=temp;
	return true;
} 
//��λ��ɾ��
bool ListDelete(LinkList &L,int i){
	if(i<1) return false;
	LNode *p;
	int j=0;//ͷ�ڵ㿴�������
	p=L; 
	while(p!=NULL&&j<i-1){//�ҵ���n-1��λ��
	p=p->next; 
	j++;	
	} 
	if(p==NULL||p->next==NULL) return false;
	LNode *q=p->next;
	printf("ɾ���ڵ�ֵΪ��%d\n",q->data);
	p->next=q->next;
	free(q);
	return true; 
}
//ɾ��ָ�����
bool DeleteNode(LNode *p){
	if(p==NULL) return false;
	LNode *q=p->next;
	p->data=q->data;
	p->next=q->next;
	free(q);
	return true;
} 
//��λ����
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
//��ֵ����
LNode *LocateElem(LinkList L,ElemType e){
	LNode *p=L->next;
	while(p!=NULL||p->data!=e)
	p=p->next;
	return p;
} 
//���
int Length(LinkList L){
	int len=0;
	LNode *p=L;
	while(p->next!=NULL){
		p=p->next;
		len++;
	}
	return len;
} 
//β�巨��������
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
//ͷ�巨��������
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
//����˫���� 
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
//������� 
void PrintList(LinkList L){
	while(L->next!=NULL){
		printf("%d ",L->next->data);
		L=L->next;
	}
	printf("\n");
}
//�͵����� 
//LinkList Reverse(LinkList &L){
//	if(L==NULL) return false;
//	LNode *p=L->next;
//	while(p->next!=NULL){
//		LNode *temp=p->next;//������ 
//		p->next=temp->next;//�Ͽ�Ҫ���ڵ㣬�����Ӻ���ڵ� 
//		temp->next=L->next;//���Ͽ��ڵ��ͷ���� 
//		L->next=temp;
//	}
//	return L;
//} 
//�ҵ�����k��Ԫ��
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
//�ж��Ƿ����������ཻ
LNode *IsCommon(LinkList p,LinkList q){
	//�ȱ�����������ĳ���
	int plen=0,qlen=0,alen=0,tag=0;//tag=1,p����tag=0,q��; 
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
	//�������߳���֮� 
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
//�ڵ�n��λ�ò���ֵΪe�Ľ��
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

//�������򴴽� 
//BTNode* CreateBTree(ElementType level[], ElementType in[], int l1, int r1, int l2, int r2){ 
//	if (l2 > r2){
//		return NULL;
//	}
//	else{
//		BTNode* bt = (BTNode*)malloc(sizeof(BTNode));
//		
//		int i, j;//�ֱ�ָ��level��in�������Ԫ��
//		int flag = 0;
// 
//		//Ѱ�Ҹ���㣬��level�е�һ����in��Ԫ��ƥ��ļ�Ϊ�����
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
//		bt->data = level[i];//����д�����д����level[j]��jָ�����in�е�Ԫ�أ�Ӧ��Ϊin[j]
//		bt->lchild = CreateBTree(level, in, l1 + 1, r1, l2, j - 1);
//		bt->rchild = CreateBTree(level, in, l1 + 1, r1, j + 1, r2);
// 	} 
//		return bt;
//	}










