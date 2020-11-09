#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

int main(){
	char line[100];
	
	FILE* file = fopen("data.txt","r");
	int age = 0;
	int location = 0;
	
	int age_arr[8] ={0,};
	int name_arr[26][26][26] = {0,};
	int location_arr[15] = {0,};
	
	int i, j, k;
	int cnt = 0;
	int whole_cnt = 0;
	if(file == NULL){
		printf("파일열기 실패\n");
		return 1;
	}
	
	while(fgets(line, sizeof(line),file)!=NULL){
		whole_cnt++;
		age = (line[0]-'0')*10 + (line[1]-'0');
		age = age/10;
		age_arr[age-1]++;
		
		location = (line[10]-'0')*10 + (line[11]-'0');
		location_arr[location-1]++;
		
		i = line[3]-'A';
		j = line[4]-'A';
		k = line[5]-'A';
		
		//printf("%d %d %d",i ,j ,k);
		
		if(name_arr[i][j][k]==0){
			name_arr[i][j][k]++;
			cnt++;
		}	
	}
	
	fclose(file);
	
	int int1, w_int1;
	int int2, w_int2, w_int3;
	int num_of=0;	
	int1 = cnt/1000;
	int2 = cnt%1000;
	//whole_cnt
	if(whole_cnt<1000) num_of=1;
	else if(whole_cnt<1000000) num_of=2;
	else num_of=3;
	
	if(num_of==1){
	
		if(int1>0&&int1<1000){
			printf("전체 데이터 갯수 %d개 중 이름은 %d,%03d개\n",whole_cnt,int1,int2);
		}
		else if(int1>=1000)	printf("전체 데이터 갯수 %d개 중 이름은 %d,%03d개\n",whole_cnt,int1,int2);
		else	printf("전체 데이터 갯수 %d개 중 이름은 %d개\n",whole_cnt,int2);
	}
	
	else if(num_of==2){
	   w_int1 = whole_cnt/1000;	   
	   w_int2 = whole_cnt%1000;
	
		if(int1>0&&int1<1000){
			printf("전체 데이터 갯수 %d,%03d개중 이름은 %d,%03d개\n",w_int1,w_int2,int1,int2);
		}
		else if(int1>=1000)	printf("전체 데이터 갯수 %d,%03d개 중 이름은 %d,%03d개\n",w_int1,w_int2,int1,int2);
		else	printf("전체 데이터 갯수 %d,%03d개 중 이름은 %d개\n",w_int1,w_int2,int2);
	}
	
	else { //1234567
	   w_int1 = whole_cnt/1000000;	   
	   w_int2 = (whole_cnt/1000) - 1000;
	   w_int3 = whole_cnt%1000;
		if(int1>0&&int1<1000){
			printf("전체 데이터 갯수 %d,%03d,%03d개중 이름은 %d,%03d개\n",w_int1,w_int2,w_int3,int1,int2);
		}
		else if(int1>=1000)	printf("전체 데이터 갯수 %d,%03d,%03d개 중 이름은 %d,%03d개\n",w_int1,w_int2,w_int3,int1,int2);
		else	printf("전체 데이터 갯수 %d,%03d,%03d개 중 이름은 %d개\n",w_int1,w_int2,w_int3,int2);
		
	}
	
	printf("\n나이:\n");
	int a;
	for(a = 1; a<9; a++){
		
		int1 = age_arr[a-1]/1000;
		int2 = age_arr[a-1]%1000;
		
		if(int1>0){
			printf("%d ~ %d : %d,%03d명\n",a*10, a*10+9,int1,int2);
		
		}
		else	printf("%d ~ %d : %d명\n",a*10, a*10+9,int2);
		
	}
	printf("\nZip code\n");
	for(a = 1; a<16; a++){
		int1 = location_arr[a-1]/1000;
		int2 = location_arr[a-1]%1000;
		
		if(int1>0){
			printf("%KS0%02d: %d,%03d명\n",a,int1,int2);
		}
		else	printf("%KS0%02d: %d명\n",a,int2);
		
	}
	return 0;
}
