//201824520_������
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

class info  //class for information about input(��ȸ ���� ������ ���� class)
{
public:
	int starting_day;
	int ending_day;
	int reward;
	long long int max_to_ending; //optimal reward to ending_day(������ �������� �ִ� reward)
  
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
	
	clock_t start = clock(); //start clock(���� �ð� ���� ����)
	
	sort(inf, inf+line); //Sort in ascending order based on ending_day
	                     //������ ���� �������� �������� ����
	int index=0;
	long long int max_reward=0;
	
	max_reward = inf[0].reward; 
	inf[0].max_to_ending = inf[0].reward; //max reward to 0th ending day is 0th reward
                                          //0��° ending_day������ �ִ� reward�� �ڽ��� reward
	info *current, *previous; //pointer to current and previous info
	                          //����� ������ infoŬ������ ���� ������
	                          
	for(int i=1; i<line; i++) { //start with index 1(�ε��� 1���� ����)
		index = 0; //index for info to get previous optimal reward
                   //������ ��ġ�� �ʴ� ��ȸ�� ���� �ε���
		current = &inf[i]; //point current info(���� infoŬ������ ���� ������)
		previous = &inf[i-1]; //point previous info(���� infoŬ������ ���� ������)

		//If the dates of the competitions overlap(��ȸ ��¥�� ��ġ�� ���, 2-1)
		if(current->starting_day <= previous->ending_day) { 
                                   
			for(int j=i-1; j>=0; j--) { //��ġ�� �ʴ� ������ ��ȸ�� ���� �ε����� �ִ� ã��
				if(inf[j].ending_day < current->starting_day) {
					index = j; break;
				}
			}
			
			if(index == 0 && i == 1) { //exception for 1th(i�� 1�� ���, 2-1 ����)
				max_reward = max( inf[0].max_to_ending, (long long int)current->reward);
				current->max_to_ending = max_reward;
			}
			else{ //not an exception(���ܰ� �ƴ� ���, 2-1)
				max_reward = max( inf[index].max_to_ending + current->reward , previous->max_to_ending);
				current->max_to_ending = max_reward;
			}
		}
		else { //If the dates of the competition do not overlap(��ȸ ��¥�� ��ġ�� �ʴ� ���, 2-2)
			current->max_to_ending = previous->max_to_ending + current->reward;
		}
	}
	
	clock_t end = clock(); //stop clock(���� �ð� ���� ����)
	
	cout << endl << inf[line-1].max_to_ending; //print optimal reward(�ִ� reward ���)
	
	//print time to get the optimal reward(�ִ� reward�� ���ϴµ� �ɸ� �ð� ���)
	cout << endl << "���� �ð� : " << (double)(end - start)/CLOCKS_PER_SEC;
	cout << "��(" << end - start << "ms)"; 
	
	delete inf;
	
	return 0;
}

