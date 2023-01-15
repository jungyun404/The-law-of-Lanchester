/*
***************************************************************************************************************
* ���� : ������ �̿��� ��ü���� ��Ģ ����                                                                     * 
* �ۼ��� : 2315������                                                                                         *
* �ٰų�(���������� ������ ������ �м�) : https://www.dbpia.co.kr/journal/articleDetail?nodeId=NODE11050188 *
* �Է»��� : 5 / 6000 / 2 / 3000 / 6                                                                          * 
***************************************************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <time.h>

//Ű���� �� 
#define UP 0
#define DOWN 1
#define ENTER 2


//�׷����Լ���
void titleDraw(); //��ü���� ��Ģ Ÿ��Ʋ�� ���
void gotoxy(int x, int y);
int keyControl(); //Ű���� ���� �Լ�  
int menuDraw(); //����, ����, ���� �޴� ��� 
void infoDraw(); //���� ��� 
void init(); //�⺻���� (â ũ��, ����, Ŀ�� ����) 

//�ùķ��̼� �Լ��� 
void input(); //BLUE, RED �ùķ��̼� Ƚ���� �Է¹��� 
int myrand(int n, int loss); //Ȯ�� 
double pred(); //�������� ����� ��ȯ�� 
void simulation(); //�ùķ��̼� �ݺ� 
void pr(int BLUE_temp, int RED_temp); //���� ������� ������Ʈ
void finish(); //�ݺ�Ƚ��, �¸���, �����, �������� ����� 

double prediction; //�������� ���� ���� 
int military[10]; //���������� ���� �Է� ���� [0] = BLUE [1] = RED 
float loss[10]; //���¼սǷ��� �Է� ���� 
int winner; //pred()�Լ����� �¸����� ������ winner�� �ִ´� (BLUE=0, RED=1, ���º�=2) 
int winner_data[100]; //������ �ùķ��̼Ǻ��� �¸����� �����ϴ� �迭 
int simulation_data[100]; //������ �ùķ��̼��� ������ �¸����� ���������� �����ϴ� �迭 
char name[10][10] = {"BLUE", "RED", "���º�"}; //BLUE, RED, ���ºθ� ������������ �迭 
int n, cnt; //n�� �ùķ��̼� �ݺ�Ƚ��, cnt�� ���� �ùķ��̼��� �ݺ�Ƚ���� ���� 

int main() {
	init(); //�ʱ�ȭ 
	
	//������ ������ ���ѹݺ� 
	while(1){
		titleDraw(); //��ü���� ��Ģ ����ȭ�� ��� 
    	int menuCode = menuDraw(); //�޴�����ȭ�鿡�� ����(0=����, 1=����, 2=����) 
    	//���ο� �ùķ��̼� ������ ���� cnt ����, simulation_data, winner_data �ʱ�ȭ 
		cnt = 0;  
    	for (int i = 0; i<100; i++){
    		simulation_data[i] = 0;
    		winner_data[i] = 0;
		}
		
		//�� �޴��� ���� 
    	if(menuCode == 0){
    		input(); //�ʱ�ȭ 
			prediction = pred(); // prediciton  = ������ 
			pr(military[0], military[1]); //ó������ ��� 
    		simulation(); //�ùķ��̼� 
    		finish(); //������ȭ ��� 
		} else if(menuCode == 1){
			infoDraw(); //������Ÿ���� 
		} else if(menuCode == 2){
			return 0; //���� 
		} 
		system("cls");
	} 
    return 0;
}

//�׷��� ���� �Լ��� 
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
	printf("> ����");
	gotoxy(x, y+1);
	printf("���α׷� ����");
	gotoxy(x, y+2);
	printf("����"); 
	
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
	printf(" ��ü���� ��Ģ�� ����\n\n ����ڿ��� �ùķ��̼� Ƚ���� BLUE, RED�� ���������� ���� ���¼սǷ��� �Է¹޴´�.\n\n");
	printf(" ���¼սǷ��� ����� ���������� �Ѵ�� �츮�� ������ �սǵǴ� �����̴�\n\n");
	printf(" �̶� ��Ȯ���� ���� ������������ ���� 1000~10000���̿� �ְ� �Ѵ�.\n\n");
	printf(" ���� RED�� ���¼սǷ��� 5��� BLUE�� ���� ���������� �Ѵ�� �����Լ��� �̿���  1/2�� Ȯ���� ���ϰ�\n\n");
	printf(" ���� ���� ���� ��� ���� RED�� ���������� ������ ���ش�.\n\n");
	printf(" �� ���� ���������� ���� 0���� �� ������ ������ ������ �ݺ����ְ� ��ü���� ��Ģ�� �̿��� ������ ���̶� ���Ѵ�.\n\n\n");
	
	printf("_______________���͸� ������ ����ȭ������ ���ư��ϴ�_______________\n\n");
	
	while(1){
		if(keyControl() == ENTER){
			break;
		}
	} 
}
void init(){
	system("mode con cols=200 lines=50 | title ��ü���͹�Ģ �ùķ��̼� "); 
	printf("\n                ��ü���� ��Ģ ���� �ùķ��̼� ���α׷��Դϴ�. ����Ű�� ���͸� �̿��� �޴��� �������ּ���\n");
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


//�ùķ��̼� �Լ��� 

//BLUE, RED �ùķ��̼� Ƚ���� �Է¹��� 
void input(){
	system("cls"); //ȭ���ʱ�ȭ 
	
	//�ùķ��̼� Ƚ�� �Է¹ޱ� 
	while(1){
	printf("�ùķ��̼� Ƚ���� �Է��ϼ���1~100 : ");
	scanf("%d", &n);
	if (1>0 && n<101) break;
	else printf("�Է� ���Ŀ� ���� �ʽ��ϴ�. �ٽ� �Է����ּ��� 1~100\n");
	}
	
	//�� �� ���������� �� �Է¹ޱ� 
	for (int i=0; i<2; i++){
		int check = 1;
		while(check==1)
		{
			printf("%s�� ���������� ���� �Է��ϼ��� 1000<= (���������� ��) <=10000 : ", name[i]);
			scanf("%d", &military[i]);
			
			printf("%s�� ���¼սǷ��� �Է��ϼ��� 0< (���¼սǷ�) <10 ", name[i]);
			scanf("%f", &loss[i]);
			
			if((1000<=military[i] && military[i]<=10000) && (0<loss[i] && loss[i]<10)) check=0; 
			else{
				printf("\n�Է� ���Ŀ� ���� �ʽ��ϴ�. �ٽ� �Է����ּ��� ex) 6000 / 2 / 3000 / 6\n\n");
				continue; 
			}
		}
	}
}

//Ȯ�� 
int myrand(int n, int loss){ //���� ���������� ��(n)�� ���¼սǷ�(loss)�� �Է¹޴´� 
	int number = 0 , save = 0;
	srand(time(NULL));
	for (int i=0; i<n; i++){ //���� ���������� ����ŭ �ݺ� 
		save = rand()%10; //0~9������ ���� ���� 
		if (save < loss) number ++; //���� ���¼սǷ��� 5��� 0.5�� Ȯ���� ����� ���������⸦ �ϳ� ���ش� 
	}
	return number;
 }
 
//�������� ����� ��ȯ��
double pred(){
	int pr = (0.1*military[0]*loss[1]) - (0.1*military[1]*loss[0]);
	
	if (pr>0) {
		winner = 0; //�¸��� BLUE 
		return (military[0] - loss[0]/loss[1]*military[1]);
	}
	
	else if (pr==0) {
		winner = 2; //���º� 
		return 0; 
	}
	else{ //�¸��� RED 
		winner = 1;
		return (military[1] - loss[1]/loss[0]*military[0]);
	}
}
//�ùķ��̼� �ݺ� 
void simulation(){
	int BLUE_attack = 0 , RED_attack = 0; //���ݷ��� ������ ���� 
	for(int j=0; j<n; j++){
		int BLUE_temp = military[0], RED_temp = military[1]; //���� �ùķ��̼��� ���� military �迭�� ���� 
		while(BLUE_temp>0 && RED_temp>0){ //��� �� ���� 0���ϰ� �� ������ 
			BLUE_attack = myrand(BLUE_temp, loss[1]); //BLUE ���ݷ� 
			Sleep(1000); //������ �ð����̸� ���� Slepp 
			RED_attack = myrand(RED_temp, loss[0]); //RED ���ݷ� 
			BLUE_temp -= RED_attack; //�� �� ���� 
			RED_temp -= BLUE_attack; //�� �� ���� 
			if(BLUE_temp <= 0 && RED_temp <= 0){ //�� ���� ���ÿ� 0���ϰ� �� ���(���º�) 
				BLUE_temp = 0; //���� ���� 
				RED_temp = 0; //���� ���� 
				winner_data[cnt] = 2; //����� ���ºθ� ��Ÿ���� 2���� 
				simulation_data[cnt] = 0; //�ùķ��̼� ����� 0 ���� 
			}
			else if(BLUE_temp<=0){ //RED�� ��� 
				BLUE_temp = 0; //���� ���� 
				winner_data[cnt] = 1; //RED ���(1) 
				simulation_data[cnt] = RED_temp; //�������¿� ����� ���� 
			}
			else if(RED_temp<=0){
				RED_temp = 0; //���� ���� 
				winner_data[cnt] = 0;
				simulation_data[cnt] = BLUE_temp;
			}
			
			pr(BLUE_temp, RED_temp); //���������� �� ������Ʈ 
		}
		cnt++; //�ݺ�ȸ�� ���� 
	}
}

//���� ������� ������Ʈ
void pr(int BLUE_temp, int RED_temp){
	system("cls");
	int i,j;
	//������� 
	printf("���� ���� Ƚ�� : %d\n", cnt+1);
	printf("�¸� ���� : %s                              ���� ���� ����: %lf\n", name[winner], prediction);
	printf("���� BLUE ����������� : %d                  ���� RED ����������� : %d\n\n",BLUE_temp, RED_temp);
	for (i=0; i<BLUE_temp; i++){ //BLUE�� ���������� �� ��� 
		if (i%10==0) printf("#"); //���������� �� 10�� �� #�ϳ� ��� 
	}
	printf("\n\n");
	for (j=0; j<RED_temp; j++){ //RED�� ���������� �� ��� 
		if (j%10==0) printf("*"); //���������� �� 10�� �� *�ϳ� ��� 
	}
	
} 
//�ݺ�Ƚ��, �¸���, �����, �������� �����
void finish(){
	system("cls");
	printf("Ƚ��    �¸���     �����    ������\n");
	printf("------------------------------------------------------------------\n");
	for(int i=0; i<n; i++){
		if (winner==2){ //���º��� �� ������ ����� �Ұ��ϱ� ������ �ɷ��ش� 
			printf("|%2d |%8s |%8d",i+1, name[winner_data[i]], simulation_data[i]);
			printf("   �̷а� 0���� ������ ��� �Ұ�\n"); 
		}
		else {
			printf("|%2d |%8s |%8d |%10f |\n",i+1, name[winner_data[i]], simulation_data[i], fabs(simulation_data[i]-prediction)/prediction*100);
		}
	}
	printf("------------------------------------------------------------------");
	printf("\n\n\n________________���͸� ������ ����ȭ������ ���ư��ϴ�________________");
	while(1){
		if(keyControl() == ENTER){
			break;
		}
	} 
}


