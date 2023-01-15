/*
***************************************************************************************************************
* 제목 : 랜덤을 이용한 란체스터 법칙 증명                                                                     * 
* 작성자 : 2315정윤지                                                                                         *
* 근거논문(무인전투기 물리적 전투력 분석) : https://www.dbpia.co.kr/journal/articleDetail?nodeId=NODE11050188 *
* 입력샘플 : 5 / 6000 / 2 / 3000 / 6                                                                          * 
***************************************************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <time.h>

//키보드 값 
#define UP 0
#define DOWN 1
#define ENTER 2


//그래픽함수들
void titleDraw(); //란체스터 법칙 타이틀을 출력
void gotoxy(int x, int y);
int keyControl(); //키보드 조작 함수  
int menuDraw(); //시작, 정보, 종료 메뉴 출력 
void infoDraw(); //정보 출력 
void init(); //기본설정 (창 크기, 제목, 커서 숨김) 

//시뮬레이션 함수들 
void input(); //BLUE, RED 시뮬레이션 횟수를 입력받음 
int myrand(int n, int loss); //확률 
double pred(); //예측값을 계산해 반환함 
void simulation(); //시뮬레이션 반복 
void pr(int BLUE_temp, int RED_temp); //무인 전투기수 업데이트
void finish(); //반복횟수, 승리팀, 결과값, 오차율을 출력함 

double prediction; //예측값을 담을 변수 
int military[10]; //무인전투기 수를 입력 받음 [0] = BLUE [1] = RED 
float loss[10]; //전력손실률을 입력 받음 
int winner; //pred()함수에서 승리팀을 예측해 winner에 넣는다 (BLUE=0, RED=1, 무승부=2) 
int winner_data[100]; //각각의 시뮬레이션별로 승리팀을 저장하는 배열 
int simulation_data[100]; //각각의 시뮬레이션이 끝난후 승리팀의 잔존병력을 저장하는 배열 
char name[10][10] = {"BLUE", "RED", "무승부"}; //BLUE, RED, 무승부를 꺼내쓰기위한 배열 
int n, cnt; //n은 시뮬레이션 반복횟수, cnt는 현재 시뮬레이션의 반복횟수를 저장 

int main() {
	init(); //초기화 
	
	//종료할 때까지 무한반복 
	while(1){
		titleDraw(); //란체스터 법칙 메인화면 출력 
    	int menuCode = menuDraw(); //메뉴선택화면에서 선택(0=시작, 1=정보, 2=종료) 
    	//새로운 시뮬레이션 시작을 위한 cnt 변수, simulation_data, winner_data 초기화 
		cnt = 0;  
    	for (int i = 0; i<100; i++){
    		simulation_data[i] = 0;
    		winner_data[i] = 0;
		}
		
		//각 메뉴별 실행 
    	if(menuCode == 0){
    		input(); //초기화 
			prediction = pred(); // prediciton  = 예측값 
			pr(military[0], military[1]); //처음상태 출력 
    		simulation(); //시뮬레이션 
    		finish(); //최종결화 출력 
		} else if(menuCode == 1){
			infoDraw(); //정보나타내기 
		} else if(menuCode == 2){
			return 0; //종료 
		} 
		system("cls");
	} 
    return 0;
}

//그래픽 관련 함수들 
void titleDraw(){
	printf("\n\n");
	printf("       ##              ##      ###      ##   #######  ##    ##  ########   ######  ######### ########  #######\n");
	printf("       ##             #  #     ## ##    ##  ########  ##    ##  ########  #######  ######### ########  ##    ##\n");
	printf("       ##            ##  ##    ##  ##   ##  ###       ##    ##  ##        ####        ###    ##        ##    ##\n");
	printf("       ##           ########   ##   ##  ##  ###       ########  ########   #####      ###    ########  #######\n");
	printf("       ##          ##     ##   ##    ## ##  ###       ########  ##           ####     ###    #         ##  ##\n");
	printf("       #########  ##       ##  ##     ####  ########  ##    ##  ########  #######     ###    ########  ##   ##\n");
	printf("       ######### ##         ## ##      ###   #######  ##    ##  ########  ######      ###    ########  ##    ##\n");
}
void gotoxy(int x, int y){
	HANDLE consoleHanle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int keyControl(){
	while(1) {
		if (kbhit()) {
		int pressedKey = getch();
		switch (pressedKey) {
			case 72:
				return UP;
				
			case 80:
				return DOWN;
				
			case 13:
				return ENTER;
				
			default:
				break;
		}
	}
}
}
int menuDraw(){
	int x = 55;
	int y = 12;
	gotoxy(x-2, y);
	printf("> 시작");
	gotoxy(x, y+1);
	printf("프로그램 정보");
	gotoxy(x, y+2);
	printf("종료"); 
	
	while(1){
		int n =keyControl();
		switch(n){
			case UP: {
				if(y > 12){
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, --y);
					printf(">");
				}
				break;
			}
			
			case DOWN: {
				if(y < 14){
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, ++y);
					printf(">");
				}
				break;
			}
			
			case ENTER: {
				return y-12;
				break;
			}
		}
	} 
	
	return 0;
}
void infoDraw(){
	system("cls");
	printf("\n\n");
	printf(" 란체스터 법칙의 증명\n\n 사용자에게 시뮬레이션 횟수와 BLUE, RED의 무인전투기 수와 전력손실률을 입력받는다.\n\n");
	printf(" 전력손실률은 상대팀 무인전투기 한대당 우리팀 병력이 손실되는 비율이다\n\n");
	printf(" 이때 정확도를 위해 무인전투기의 수는 1000~10000사이에 있게 한다.\n\n");
	printf(" 만약 RED의 전력손실률이 5라면 BLUE의 남은 무인전투기 한대당 랜덤함수를 이용한  1/2의 확률을 곱하고\n\n");
	printf(" 각각 곱한 것을 모두 더해 RED의 무인전투기 수에서 빼준다.\n\n");
	printf(" 한 팀의 무인전투기 수가 0개가 될 때까지 각각의 과정을 반복해주고 란체스터 법칙을 이용해 예측한 값이랑 비교한다.\n\n\n");
	
	printf("_______________엔터를 누르면 메인화면으로 돌아갑니다_______________\n\n");
	
	while(1){
		if(keyControl() == ENTER){
			break;
		}
	} 
}
void init(){
	system("mode con cols=200 lines=50 | title 란체스터법칙 시뮬레이션 "); 
	printf("\n                란체스터 법칙 증명 시뮬레이션 프로그램입니다. 방향키와 엔터를 이용해 메뉴를 선택해주세요\n");
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


//시뮬레이션 함수들 

//BLUE, RED 시뮬레이션 횟수를 입력받음 
void input(){
	system("cls"); //화면초기화 
	
	//시뮬레이션 횟수 입력받기 
	while(1){
	printf("시뮬레이션 횟수를 입력하세요1~100 : ");
	scanf("%d", &n);
	if (1>0 && n<101) break;
	else printf("입력 형식에 맞지 않습니다. 다시 입력해주세요 1~100\n");
	}
	
	//각 팀 무인전투기 수 입력받기 
	for (int i=0; i<2; i++){
		int check = 1;
		while(check==1)
		{
			printf("%s팀 무인전투기 수를 입력하세요 1000<= (무인전투기 수) <=10000 : ", name[i]);
			scanf("%d", &military[i]);
			
			printf("%s팀 전력손실률을 입력하세요 0< (전력손실률) <10 ", name[i]);
			scanf("%f", &loss[i]);
			
			if((1000<=military[i] && military[i]<=10000) && (0<loss[i] && loss[i]<10)) check=0; 
			else{
				printf("\n입력 형식에 맞지 않습니다. 다시 입력해주세요 ex) 6000 / 2 / 3000 / 6\n\n");
				continue; 
			}
		}
	}
}

//확률 
int myrand(int n, int loss){ //현재 무인전투기 수(n)와 전력손실률(loss)을 입력받는다 
	int number = 0 , save = 0;
	srand(time(NULL));
	for (int i=0; i<n; i++){ //남은 무인전투기 수만큼 반복 
		save = rand()%10; //0~9까지의 난수 생성 
		if (save < loss) number ++; //만약 전력손실률이 5라면 0.5의 확률로 상대팀 무인전투기를 하나 없앤다 
	}
	return number;
 }
 
//예측값을 계산해 반환함
double pred(){
	int pr = (0.1*military[0]*loss[1]) - (0.1*military[1]*loss[0]);
	
	if (pr>0) {
		winner = 0; //승리팀 BLUE 
		return (military[0] - loss[0]/loss[1]*military[1]);
	}
	
	else if (pr==0) {
		winner = 2; //무승부 
		return 0; 
	}
	else{ //승리팀 RED 
		winner = 1;
		return (military[1] - loss[1]/loss[0]*military[0]);
	}
}
//시뮬레이션 반복 
void simulation(){
	int BLUE_attack = 0 , RED_attack = 0; //공격력을 저장할 변수 
	for(int j=0; j<n; j++){
		int BLUE_temp = military[0], RED_temp = military[1]; //다음 시뮬레이션을 위해 military 배열은 보존 
		while(BLUE_temp>0 && RED_temp>0){ //어느 한 팀이 0이하가 될 때까지 
			BLUE_attack = myrand(BLUE_temp, loss[1]); //BLUE 공격력 
			Sleep(1000); //랜덤의 시간차이를 위해 Slepp 
			RED_attack = myrand(RED_temp, loss[0]); //RED 공격력 
			BLUE_temp -= RED_attack; //각 팀 공격 
			RED_temp -= BLUE_attack; //각 팀 공격 
			if(BLUE_temp <= 0 && RED_temp <= 0){ //두 팀이 동시에 0이하가 될 경우(무승부) 
				BLUE_temp = 0; //음수 방지 
				RED_temp = 0; //음수 방지 
				winner_data[cnt] = 2; //결과에 무승부를 나타내는 2저장 
				simulation_data[cnt] = 0; //시뮬레이션 결과에 0 저장 
			}
			else if(BLUE_temp<=0){ //RED팀 우승 
				BLUE_temp = 0; //음수 방지 
				winner_data[cnt] = 1; //RED 우승(1) 
				simulation_data[cnt] = RED_temp; //잔존병력에 우승팀 저장 
			}
			else if(RED_temp<=0){
				RED_temp = 0; //음수 방지 
				winner_data[cnt] = 0;
				simulation_data[cnt] = BLUE_temp;
			}
			
			pr(BLUE_temp, RED_temp); //무인전투기 수 업데이트 
		}
		cnt++; //반복회수 증가 
	}
}

//무인 전투기수 업데이트
void pr(int BLUE_temp, int RED_temp){
	system("cls");
	int i,j;
	//정보출력 
	printf("현재 실행 횟수 : %d\n", cnt+1);
	printf("승리 예측 : %s                              잔존 병력 예측: %lf\n", name[winner], prediction);
	printf("현재 BLUE 무인전투기수 : %d                  현재 RED 무인전투기수 : %d\n\n",BLUE_temp, RED_temp);
	for (i=0; i<BLUE_temp; i++){ //BLUE팀 무인전투기 수 출력 
		if (i%10==0) printf("#"); //무인전투기 수 10개 당 #하나 출력 
	}
	printf("\n\n");
	for (j=0; j<RED_temp; j++){ //RED팀 무인전투기 수 출력 
		if (j%10==0) printf("*"); //무인전투기 수 10개 당 *하나 출력 
	}
	
} 
//반복횟수, 승리팀, 결과값, 오차율을 출력함
void finish(){
	system("cls");
	printf("횟수    승리팀     결과값    오차율\n");
	printf("------------------------------------------------------------------\n");
	for(int i=0; i<n; i++){
		if (winner==2){ //무승부일 때 오차율 계산이 불가하기 때문에 걸러준다 
			printf("|%2d |%8s |%8d",i+1, name[winner_data[i]], simulation_data[i]);
			printf("   이론값 0으로 오차율 계산 불가\n"); 
		}
		else {
			printf("|%2d |%8s |%8d |%10f |\n",i+1, name[winner_data[i]], simulation_data[i], fabs(simulation_data[i]-prediction)/prediction*100);
		}
	}
	printf("------------------------------------------------------------------");
	printf("\n\n\n________________엔터를 누르면 메인화면으로 돌아갑니다________________");
	while(1){
		if(keyControl() == ENTER){
			break;
		}
	} 
}


