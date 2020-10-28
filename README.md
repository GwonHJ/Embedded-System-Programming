# Embedded-System-Programming
임베디드시스템 프로그래밍

## 1주차 과제

과제설명

	나이별, 이름별, 지역별(zip code) 분포를 구하시오.


	순서는 숫자, 알파벳 오름차순으로 정리



	나이 : 10 ~ 89

	zip code : 001 ~ 015




	파일 내용



	24,ABC,KS003

	32,BCD,KS005

	...




	결과 출력 예제



	전체 데이터 갯수 1,000,000개 중 이름은 xx,xxx개



	나이:

	10 ~ 19 : 3,423명

	20 ~ 29 : 5,333명

	..

	80 ~ 89 : xxx명



	Zip code

	KS001: xxxxx명

	KS002: xxxxx명

	...

	KS015: xxxxx명

### 실행화면

![임베디드 과제 캡쳐 (1)](https://user-images.githubusercontent.com/45057466/97445516-af1ee080-1970-11eb-8dd7-d07efaee4189.png)

### 설명


나이분포

<pre><code>
	age = (line[0]-'0')*10 + (line[1]-'0'); //char를 int로
	age = age/10; //나이대는 십의자리만 판별하면 되니까
	age_arr[age-1]++; //해당하는 나이대에 ++
</code></pre>

중복하지 않은 이름 개수 세아리기
  <pre><code>
	// 이름이 무조건 3자리니까 3차원 배열에 이름이 존재하지않으면 cnt++
  
	location = (line[10]-'0')*10 + (line[11]-'0');
	location_arr[location-1]++;

	i = line[3]-'A';
	j = line[4]-'A';
	k = line[5]-'A';

	if(name_arr[i][j][k]==0){
	name_arr[i][j][k]++;
	cnt++;
}	
 
</code></pre>
지역분포
 <pre><code>
	//범위가 1~15이기 때문에 크기가 15인 배열을 만들고 해당 하는 곳에 ++
	location = (line[10]-'0')*10 + (line[11]-'0');
	location_arr[location-1]++;
</code></pre>

-----------------------------------------------------------------
## 2주차 과제

RPI : 
 행렬의 곱셈을 연산할 때 걸리는 시간,
 쓰레드를 이용해서 행렬의 곱셈을 연산할 때 걸리는 시간
![라즈베리_실행시간](https://user-images.githubusercontent.com/45057466/97439853-0e2d2700-196a-11eb-8364-df1013842678.png)
데스크탑 : 

  행렬의 곱셈을 연산할 때 걸리는 시간,
 쓰레드를 이용해서 행렬의 곱셈을 연산할 때 걸리는 시간

![데스크탑_실행시간](https://user-images.githubusercontent.com/45057466/97439846-0cfbfa00-196a-11eb-959a-3a7c25073775.png)

------------------------------------------------------------------
