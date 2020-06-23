//201824520_안주현
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

class info  //class for information about input(대회 정보 저장을 위한 class)
{
public:
	int starting_day;
	int ending_day;
	int reward;
	long long int max_to_ending; //optimal reward to ending_day(끝나는 날까지의 최대 reward)
  
	info()
	{
		starting_day = 0;
		ending_day = 0;
		reward = 0;
		max_to_ending = 0; 
	}
	bool operator <(info &info)
	{
		return this->ending_day < info.ending_day;
	}
};
int main(void)
{
	int line=0;
	info *inf = new info[200000];
	
	cin >> line;
	
	for(int i=0; i<line; i++) {
		cin >> inf[i].starting_day
			>> inf[i].ending_day
			>> inf[i].reward;
	}
	
	clock_t start = clock(); //start clock(실행 시간 측정 시작)
	
	sort(inf, inf+line); //Sort in ascending order based on ending_day
	                     //끝나는 날을 기준으로 오름차순 정렬
	int index=0;
	long long int max_reward=0;
	
	max_reward = inf[0].reward; 
	inf[0].max_to_ending = inf[0].reward; //max reward to 0th ending day is 0th reward
                                          //0번째 ending_day까지의 최대 reward는 자신의 reward
	info *current, *previous; //pointer to current and previous info
	                          //현재와 이전의 info클래스에 대한 포인터
	                          
	for(int i=1; i<line; i++) { //start with index 1(인덱스 1부터 시작)
		index = 0; //index for info to get previous optimal reward
                   //이전의 겹치지 않는 대회에 대한 인덱스
		current = &inf[i]; //point current info(현재 info클래스에 대한 포인터)
		previous = &inf[i-1]; //point previous info(이전 info클래스에 대한 포인터)

		//If the dates of the competitions overlap(대회 날짜가 겹치는 경우, 2-1)
		if(current->starting_day <= previous->ending_day) { 
                                   
			for(int j=i-1; j>=0; j--) { //겹치지 않는 이전의 대회에 대한 인덱스의 최댓값 찾기
				if(inf[j].ending_day < current->starting_day) {
					index = j; break;
				}
			}
			
			if(index == 0 && i == 1) { //exception for 1th(i가 1인 경우, 2-1 예외)
				max_reward = max( inf[0].max_to_ending, (long long int)current->reward);
				current->max_to_ending = max_reward;
			}
			else{ //not an exception(예외가 아닌 경우, 2-1)
				max_reward = max( inf[index].max_to_ending + current->reward , previous->max_to_ending);
				current->max_to_ending = max_reward;
			}
		}
		else { //If the dates of the competition do not overlap(대회 날짜가 겹치지 않는 경우, 2-2)
			current->max_to_ending = previous->max_to_ending + current->reward;
		}
	}
	
	clock_t end = clock(); //stop clock(실행 시간 측정 종료)
	
	cout << endl << inf[line-1].max_to_ending; //print optimal reward(최대 reward 출력)
	
	//print time to get the optimal reward(최대 reward를 구하는데 걸린 시간 출력)
	cout << endl << "실행 시간 : " << (double)(end - start)/CLOCKS_PER_SEC;
	cout << "초(" << end - start << "ms)"; 
	
	delete inf;
	
	return 0;
}

