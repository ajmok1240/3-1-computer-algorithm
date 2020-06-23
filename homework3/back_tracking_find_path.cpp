#include <iostream>
#include <time.h>

using namespace std;


int cnt, index; //정답 갯수를 세는 cnt
				//입력된 문자열의 위치를 나타내는 index
				
char arr[49] = {0}; //입력 문자열 저장을 위한 arr

//입력이 '?'인 경우에 순차적으로 탐색하기 위한 U,R,D,L 배열 
char dir[4] = {'U','R','D','L'};  

//현재 좌표 x,y에서 입력 문자 ch방향으로 이동이 유망한지 검사 
bool promise(int x, int y, char ch, int (*matrix)[7])
{
	if(ch == 'U') { //위로 이동이 가능한지 검사 
		if(matrix[x-1][y] || x-1<0) { return false; }
		else { return true; }
	}else if(ch == 'R') { //오른쪽으로 이동이 가능한지 검사 
		if(matrix[x][y+1] || y+1>6) { return false; }
		else { return true; }
	}else if(ch == 'D') { //아래로 이동이 가능한지 검사 
		if(matrix[x+1][y] || x+1>6) { return false; }
		else { return true; }
	}else if(ch == 'L') { //왼쪽으로 이동이 가능한지 검사 
		if(matrix[x][y-1] || y-1<0) { return false; }
		else { return true; }
	}
}

void back_tracking(int x, int y, char ch, int (*matrix)[7])
{
	matrix[x][y] = 1; //현재 좌표에 방문했다는 표시 (1) 

	//pruning
	
	//inner fragment(0) 검사
	
	//2-1의 1번 경우 
	if((matrix[x-1][y] || x-1<0) && (matrix[x+1][y] || x+1>6)) {
		//2-3의 예외가 아니면 진행 멈춤
		if(!(matrix[x][y-1]) && !(matrix[x][y+1])){ 
			//그래프의 이전 단계로 back tracking
			index--; matrix[x][y]=0; return;
			}
		}
	//2-1의 2번 경우 
	if((matrix[x][y-1] || y-1<0) && (matrix[x][y+1] || y+1>6)) {
		//2-3의 예외가 아니면 진행 멈춤
		if(!(matrix[x-1][y]) && !(matrix[x+1][y])){
			//그래프의 이전 단계로 back tracking
			index--; matrix[x][y]=0; return;
			}
		}

	//2-2의 방법 
	if(!(matrix[x-1][y+1]) && (x-1>=0 && y+1<=6)) { //우상대각 0 검사 
		if((matrix[x-2][y+1] || (x-2<0)) && (matrix[x][y+1]) && (matrix[x-1][y]) && (matrix[x-1][y+2] || (y+2>6))) {
			//해당되면 진행 멈춤
			//그래프의 이전 단계로 back tracking
			index--; matrix[x][y]=0; return;
		}
	}
	if(!(matrix[x+1][y+1]) && (x-1>=0 && y+1<=6)) { //우하대각 0 검사 
		if((matrix[x][y+1]) && (matrix[x+2][y+1] || (x+2>6)) && (matrix[x+1][y]) && (matrix[x+1][y+2] || (y+2>6))) {
			//해당되면 진행 멈춤
			//그래프의 이전 단계로 back tracking
			index--; matrix[x][y]=0; return;
		}
	}
	if(!(matrix[x+1][y-1]) && (x-1>=0 && y+1<=6)) { //좌하대각 0 검사 
		if((matrix[x][y-1]) && (matrix[x+2][y-1] || (x+2>6)) && (matrix[x+1][y-2] || (y-2<0)) && (matrix[x+1][y])) {
			//해당되면 진행 멈춤
			//그래프의 이전 단계로 back tracking
			index--; matrix[x][y]=0; return;
		}
	}
	if(!(matrix[x-1][y-1]) && (x-1>=0 && y+1<=6)) { //좌상대각 0 검사 
		if((matrix[x-2][y-1] || (x-2<0)) && (matrix[x][y-1]) && (matrix[x-1][y-2] || (y-2<0)) && (matrix[x-1][y])) {
			//해당되면 진행 멈춤
			//그래프의 이전 단계로 back tracking
			index--; matrix[x][y]=0; return;
		}
	}
	
	//모든 칸을 방문하고 목적지 도착(다음 입력 문자가 '#')
	//cnt를 1 증가시키고 그래프의 이전 단계로 back tracking
	if(ch=='#' && x==6 && y==0) { cnt++; index--; matrix[x][y]=0; }
	
	//모든 칸을 방문하지 않고 목적지 도착(다음 입력 문자가 '#'이 아님)
	//그래프의 이전 단계로 back tracking
	else if(ch!='#' && x==6 && y==0) { index--; matrix[x][y]=0; }
	
	
	else if(ch == '?') { //입력 문자가 ? 인 경우 
	
		//상,우,하,좌 순으로 유망성 검사 후에 이동 
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
		//그래프의 이전 단계로 back tracking 
		index--; matrix[x][y]=0;
	}else { //입력 문자가 ?가 아닌 U,D,R,L 중에 하나인 경우 
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
		//그래프의 이전 단계로 back tracking
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
	
	//문자열 입력받기
	for(int i=0; i<48; i++)
	{
		cin >> arr[i];
	}
	arr[48]='#'; //문자열이 끝났음을 표시하는 문자 '#' 
	
	int matrix[7][7] = {0}; // 7 X 7 행렬 선언 
	
	//0,0부터 입력 문자열에 따라 back tracking
	back_tracking(0,0,arr[index], matrix);
		
	cout << cnt;
	
	return 0;
}
