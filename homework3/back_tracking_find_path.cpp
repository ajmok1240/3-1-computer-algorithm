#include <iostream>
#include <time.h>

using namespace std;


int cnt, index; //���� ������ ���� cnt
				//�Էµ� ���ڿ��� ��ġ�� ��Ÿ���� index
				
char arr[49] = {0}; //�Է� ���ڿ� ������ ���� arr

//�Է��� '?'�� ��쿡 ���������� Ž���ϱ� ���� U,R,D,L �迭 
char dir[4] = {'U','R','D','L'};  

//���� ��ǥ x,y���� �Է� ���� ch�������� �̵��� �������� �˻� 
bool promise(int x, int y, char ch, int (*matrix)[7])
{
	if(ch == 'U') { //���� �̵��� �������� �˻� 
		if(matrix[x-1][y] || x-1<0) { return false; }
		else { return true; }
	}else if(ch == 'R') { //���������� �̵��� �������� �˻� 
		if(matrix[x][y+1] || y+1>6) { return false; }
		else { return true; }
	}else if(ch == 'D') { //�Ʒ��� �̵��� �������� �˻� 
		if(matrix[x+1][y] || x+1>6) { return false; }
		else { return true; }
	}else if(ch == 'L') { //�������� �̵��� �������� �˻� 
		if(matrix[x][y-1] || y-1<0) { return false; }
		else { return true; }
	}
}

void back_tracking(int x, int y, char ch, int (*matrix)[7])
{
	matrix[x][y] = 1; //���� ��ǥ�� �湮�ߴٴ� ǥ�� (1) 

	//pruning
	
	//inner fragment(0) �˻�
	
	//2-1�� 1�� ��� 
	if((matrix[x-1][y] || x-1<0) && (matrix[x+1][y] || x+1>6)) {
		//2-3�� ���ܰ� �ƴϸ� ���� ����
		if(!(matrix[x][y-1]) && !(matrix[x][y+1])){ 
			//�׷����� ���� �ܰ�� back tracking
			index--; matrix[x][y]=0; return;
			}
		}
	//2-1�� 2�� ��� 
	if((matrix[x][y-1] || y-1<0) && (matrix[x][y+1] || y+1>6)) {
		//2-3�� ���ܰ� �ƴϸ� ���� ����
		if(!(matrix[x-1][y]) && !(matrix[x+1][y])){
			//�׷����� ���� �ܰ�� back tracking
			index--; matrix[x][y]=0; return;
			}
		}

	//2-2�� ��� 
	if(!(matrix[x-1][y+1]) && (x-1>=0 && y+1<=6)) { //���밢 0 �˻� 
		if((matrix[x-2][y+1] || (x-2<0)) && (matrix[x][y+1]) && (matrix[x-1][y]) && (matrix[x-1][y+2] || (y+2>6))) {
			//�ش�Ǹ� ���� ����
			//�׷����� ���� �ܰ�� back tracking
			index--; matrix[x][y]=0; return;
		}
	}
	if(!(matrix[x+1][y+1]) && (x-1>=0 && y+1<=6)) { //���ϴ밢 0 �˻� 
		if((matrix[x][y+1]) && (matrix[x+2][y+1] || (x+2>6)) && (matrix[x+1][y]) && (matrix[x+1][y+2] || (y+2>6))) {
			//�ش�Ǹ� ���� ����
			//�׷����� ���� �ܰ�� back tracking
			index--; matrix[x][y]=0; return;
		}
	}
	if(!(matrix[x+1][y-1]) && (x-1>=0 && y+1<=6)) { //���ϴ밢 0 �˻� 
		if((matrix[x][y-1]) && (matrix[x+2][y-1] || (x+2>6)) && (matrix[x+1][y-2] || (y-2<0)) && (matrix[x+1][y])) {
			//�ش�Ǹ� ���� ����
			//�׷����� ���� �ܰ�� back tracking
			index--; matrix[x][y]=0; return;
		}
	}
	if(!(matrix[x-1][y-1]) && (x-1>=0 && y+1<=6)) { //�»�밢 0 �˻� 
		if((matrix[x-2][y-1] || (x-2<0)) && (matrix[x][y-1]) && (matrix[x-1][y-2] || (y-2<0)) && (matrix[x-1][y])) {
			//�ش�Ǹ� ���� ����
			//�׷����� ���� �ܰ�� back tracking
			index--; matrix[x][y]=0; return;
		}
	}
	
	//��� ĭ�� �湮�ϰ� ������ ����(���� �Է� ���ڰ� '#')
	//cnt�� 1 ������Ű�� �׷����� ���� �ܰ�� back tracking
	if(ch=='#' && x==6 && y==0) { cnt++; index--; matrix[x][y]=0; }
	
	//��� ĭ�� �湮���� �ʰ� ������ ����(���� �Է� ���ڰ� '#'�� �ƴ�)
	//�׷����� ���� �ܰ�� back tracking
	else if(ch!='#' && x==6 && y==0) { index--; matrix[x][y]=0; }
	
	
	else if(ch == '?') { //�Է� ���ڰ� ? �� ��� 
	
		//��,��,��,�� ������ ������ �˻� �Ŀ� �̵� 
		for(int i=0; i<4; i++)
		{
			if(promise(x,y,dir[i], matrix)) {
				index++;
				switch(dir[i]) {
					case 'U':
						back_tracking(x-1,y,arr[index],matrix); break;
					case 'R':
						back_tracking(x,y+1,arr[index],matrix); break;
					case 'D':
						back_tracking(x+1,y,arr[index],matrix); break;
					case 'L':
						back_tracking(x,y-1,arr[index],matrix); break;
				}
			}
		}
		//�׷����� ���� �ܰ�� back tracking 
		index--; matrix[x][y]=0;
	}else { //�Է� ���ڰ� ?�� �ƴ� U,D,R,L �߿� �ϳ��� ��� 
		if(promise(x,y,ch, matrix)) {
			index++;
			switch(ch) {
				case 'U':
					back_tracking(x-1,y,arr[index],matrix); break;
				case 'R':
					back_tracking(x,y+1,arr[index],matrix); break;
				case 'D':
					back_tracking(x+1,y,arr[index],matrix); break;
				case 'L':
					back_tracking(x,y-1,arr[index],matrix); break;
			}
		}
		//�׷����� ���� �ܰ�� back tracking
		index--; matrix[x][y]=0;
	}
	return ;
}

void clear_matrix(int (*matrix)[7])
{
	for(int i=0; i<7; i++)
	{
		for(int j=0; j<7; j++)
		{
			matrix[i][j]=0;
		}
	}
}

int main(void)
{
	cnt=0; index=0;
	
	//���ڿ� �Է¹ޱ�
	for(int i=0; i<48; i++)
	{
		cin >> arr[i];
	}
	arr[48]='#'; //���ڿ��� �������� ǥ���ϴ� ���� '#' 
	
	int matrix[7][7] = {0}; // 7 X 7 ��� ���� 
	
	//0,0���� �Է� ���ڿ��� ���� back tracking
	back_tracking(0,0,arr[index], matrix);
		
	cout << cnt;
	
	return 0;
}
