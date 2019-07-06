#include<GL\glew.h>
#include<GL\glut.h>
#include <iostream>
#include<string.h>
#include<stdlib.h>
#include <vector>

using namespace std;

int matrix[6][6];
int occupy_h[6][6];
int occupy_v[6][6];
int occupy_d1[6][6];
int occupy_d2[6][6];
int flag, p1 = 0, p2 = 0, click_count = 0;
bool gameover;

void NewGame();
void GameStart(int,int,int,int);
void GameWin();
void DrawString(void* ,float,float,char*);
void GameBox();
void symbols();
void Display();
void reshape(int, int);
void DrawBars(int,int,int);


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 100);											
	glutInitWindowSize(1010, 910);
	glutCreateWindow("Tak Tik Tuk");

	NewGame();

	glutMainLoop();
	return 0;
}

void NewGame() {
	flag = 1;
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 6; y++) {
			matrix[x][y] = 0;
			occupy_h[x][y] = 0;
			occupy_v[x][y] = 0;
			occupy_d1[x][y] = 0;
			occupy_d2[x][y] = 0;
		}
	}
	glutReshapeFunc(reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(GameStart);
}

void GameStart(int button, int state, int x, int y) {
	if (gameover == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (flag == 1) {
			if ( x > 305 && x<930 && y>205 && y<830 && matrix[(x - 305) / 105][(y - 205) / 105] == 0) {
				matrix[(x - 305) / 105][(y - 205) / 105] = 1;
				flag = 2;
				click_count++;
				GameWin();
			}
		}

		else if(flag == 2) {
			if (x > 305 && x<930 && y>205 && y<830 && matrix[(x - 305) / 105][(y - 205) / 105] == 0) {
				matrix[(x - 305) / 105][(y - 205) / 105] = 2;
				flag = 1;
				click_count++;
				GameWin();
			}
		}

		if(x<260 && x>60 && y < 700 && y>660) {
			NewGame();
			p1 = 0;
			p2 = 0;
			click_count = 0;

		}
	}
}

void GameWin() {
	int x, y;

	//Winning Vertically
	for (x=0 ; x<6 ; x++) {
		for (y=0; y<=3; y++) {
			if (matrix[x][y] == matrix[x][y+1] && matrix[x][y] == matrix[x][y+2] && matrix[x][y]!=0 && occupy_v[x][y]!=1 && occupy_v[x][y+1]!=1 && occupy_v[x][y+2]!=1){
				occupy_v[x][y]   = 1;
				occupy_v[x][y+1] = 1;
				occupy_v[x][y+2] = 1;

				if (flag == 1) {
					p2 = p2 + 10;
					printf("Verticle(%d,%d) : p2 = %d \n",x,y,p2);
					DrawBars(x,y,1);
					}
				else if (flag == 2) {
					p1 = p1 + 10;
					printf("Verticle(%d,%d) : p1 = %d \n", x, y, p1);
					DrawBars(x, y, 1);
				}
				//return true;
			}
			else {
				continue;
			}
		}
	}

	//Winning Horizontally
	for (y=0 ; y<6 ; y++){
		for (x = 0; x<=3; x++) {
			if (matrix[x][y] == matrix[x+1][y] && matrix[x][y] == matrix[x+2][y] && matrix[x][y]!=0 && occupy_h[x][y]!=2 && occupy_h[x+1][y]!=2 && occupy_h[x+2][y]!=2) {
				occupy_h[x][y] = 2 ;
				occupy_h[x+1][y] = 2 ;
				occupy_h[x+2][y] = 2 ;

				if (flag == 1) {
					p2 = p2 + 10;
					printf("Horizontal(%d,%d) : p2 = %d \n", x, y, p2);
					DrawBars(x, y, 2);
				}
				else if (flag == 2) {
					p1 = p1 + 10;
					printf("Horizontal(%d,%d) : p1 = %d \n", x, y, p1);
					DrawBars(x, y, 2);
				}

				//return true;
			}
			else {
				continue;
			}
		}
	}
	
	//Win Diagonally
	for (x=0 ; x<4 ; x++) {
		for (y=0 ; y<4 ; y++) {
			if (matrix[x][y] != 0 && matrix[x][y] == matrix[x+1][y+1] && matrix[x][y] == matrix[x+2][y+2] && occupy_d1[x][y]!=1 && occupy_d1[x+1][y+1]!=1 && occupy_d1[x+2][y+2]!=1) {
				occupy_d1[x][y] = 1;
				occupy_d1[x+1][y+1] = 1;
				occupy_d1[x+2][y+2] = 1;

				if (flag == 1) {
					p2 = p2 + 10;
					printf("diagonal forward(%d,%d) : p2 = %d \n", x, y, p2);
					DrawBars(x, y, 3);
					
				}
				else if (flag == 2) {
					p1 = p1 + 10;
					printf("diagonal forward(%d,%d) : p1 = %d \n", x, y, p1);
					DrawBars(x, y, 3);
				}
				//return true;
			}
			else {
				continue;
			}
		}
	}
	for (x=2 ; x<6 ; x++) {
		for (y=0 ; y<4 ; y++) {
			if (matrix[x][y]!=0 && matrix[x][y] == matrix[x-1][y+1] && matrix[x][y] == matrix[x-2][y+2] && occupy_d2[x][y]!=3 && occupy_d2[x-1][y+1]!=3 && occupy_d2[x-2][y+2]!=3) {
				occupy_d2[x][y] = 3;
				occupy_d2[x-1][y+1] = 3;
				occupy_d2[x-2][y+2] = 3;

				if (flag == 1) {
					p2 = p2 + 10;
					printf("diagonal backward(%d,%d) : p2 = %d \n", x, y, p2);
					DrawBars(x, y, 4);
					//return true;
				}
				else if (flag == 2) {
					p1 = p1 + 10;
					printf("diagonal backward(%d,%d) : p1 = %d \n",x,y, p1);
					DrawBars(x, y, 4);
					//return true;
				}
			}

			else {
				continue;
			}
		}
	}
	if (click_count == 36) {
		printf("game over!");
		//return true;
	}
}

void DrawString(void *font, float x, float y, char *word) {
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i < strlen(word); i++)
		glutBitmapCharacter(font, word[i]);
}

void GameBox() {
	//Topic Box
	glBegin(GL_POLYGON);
	glColor3f(0.039, 0.129, 0.149);
	glVertex3f(60, 30, -1);
	glVertex3f(60, 130, -1);
	glVertex3f(950, 130, -1);
	glVertex3f(950, 30, -1);
	glEnd();
	glColor3f(0.596, 0.886, 0.556);
	DrawString(GLUT_BITMAP_HELVETICA_18, 400, 100, "Tak Tik Tuk");

	//Large box
	glBegin(GL_POLYGON);
	glColor3f(0.039, 0.129, 0.149);
	glVertex2f(290, 190);
	glVertex2f(945, 190);
	glVertex2f(945, 845);
	glVertex2f(290, 845);
	glEnd();

	//First Row 
	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(305, 205);
	glVertex2f(405, 205);
	glVertex2f(405, 305);
	glVertex2f(305, 305);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(410, 205);
	glVertex2f(510, 205);
	glVertex2f(510, 305);
	glVertex2f(410, 305);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(515, 205);
	glVertex2f(615, 205);
	glVertex2f(615, 305);
	glVertex2f(515, 305);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(620, 205);
	glVertex2f(720, 205);
	glVertex2f(720, 305);
	glVertex2f(620, 305);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(725, 205);
	glVertex2f(825, 205);
	glVertex2f(825, 305);
	glVertex2f(725, 305);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(830, 205);
	glVertex2f(930, 205);
	glVertex2f(930, 305);
	glVertex2f(830, 305);
	glEnd();


	//Second Row
	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(305, 310);
	glVertex2f(405, 310);
	glVertex2f(405, 410);
	glVertex2f(305, 410);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(410, 310);
	glVertex2f(510, 310);
	glVertex2f(510, 410);
	glVertex2f(410, 410);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(515, 310);
	glVertex2f(615, 310);
	glVertex2f(615, 410);
	glVertex2f(515, 410);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(620, 310);
	glVertex2f(720, 310);
	glVertex2f(720, 410);
	glVertex2f(620, 410);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(725, 310);
	glVertex2f(825, 310);
	glVertex2f(825, 410);
	glVertex2f(725, 410);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(830, 310);
	glVertex2f(930, 310);
	glVertex2f(930, 410);
	glVertex2f(830, 410);
	glEnd();


	//Third Row
	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(305, 415);
	glVertex2f(405, 415);
	glVertex2f(405, 515);
	glVertex2f(305, 515);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(410, 415);
	glVertex2f(510, 415);
	glVertex2f(510, 515);
	glVertex2f(410, 515);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(515, 415);
	glVertex2f(615, 415);
	glVertex2f(615, 515);
	glVertex2f(515, 515);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(620, 415);
	glVertex2f(720, 415);
	glVertex2f(720, 515);
	glVertex2f(620, 515);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(725, 415);
	glVertex2f(825, 415);
	glVertex2f(825, 515);
	glVertex2f(725, 515);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(830, 415);
	glVertex2f(930, 415);
	glVertex2f(930, 515);
	glVertex2f(830, 515);
	glEnd();


	//Forth Row
	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(305, 520);
	glVertex2f(405, 520);
	glVertex2f(405, 620);
	glVertex2f(305, 620);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(410, 520);
	glVertex2f(510, 520);
	glVertex2f(510, 620);
	glVertex2f(410, 620);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(515, 520);
	glVertex2f(615, 520);
	glVertex2f(615, 620);
	glVertex2f(515, 620);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(620, 520);
	glVertex2f(720, 520);
	glVertex2f(720, 620);
	glVertex2f(620, 620);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(725, 520);
	glVertex2f(825, 520);
	glVertex2f(825, 620);
	glVertex2f(725, 620);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(830, 520);
	glVertex2f(930, 520);
	glVertex2f(930, 620);
	glVertex2f(830, 620);
	glEnd();


	//Fifth Row
	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(305, 625);
	glVertex2f(405, 625);
	glVertex2f(405, 725);
	glVertex2f(305, 725);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(410, 625);
	glVertex2f(510, 625);
	glVertex2f(510, 725);
	glVertex2f(410, 725);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(515, 625);
	glVertex2f(615, 625);
	glVertex2f(615, 725);
	glVertex2f(515, 725);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(620, 625);
	glVertex2f(720, 625);
	glVertex2f(720, 725);
	glVertex2f(620, 725);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(725, 625);
	glVertex2f(825, 625);
	glVertex2f(825, 725);
	glVertex2f(725, 725);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(830, 625);
	glVertex2f(930, 625);
	glVertex2f(930, 725);
	glVertex2f(830, 725);
	glEnd();


	//Sixth Row
	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(305, 730);
	glVertex2f(405, 730);
	glVertex2f(405, 830);
	glVertex2f(305, 830);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(410, 730);
	glVertex2f(510, 730);
	glVertex2f(510, 830);
	glVertex2f(410, 830);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(515, 730);
	glVertex2f(615, 730);
	glVertex2f(615, 830);
	glVertex2f(515, 830);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(620, 730);
	glVertex2f(720, 730);
	glVertex2f(720, 830);
	glVertex2f(620, 830);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(725, 730);
	glVertex2f(825, 730);
	glVertex2f(825, 830);
	glVertex2f(725, 830);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.596, 0.886, 0.556);
	glVertex2f(830, 730);
	glVertex2f(930, 730);
	glVertex2f(930, 830);
	glVertex2f(830, 830);
	glEnd();

	//Player Box 1
	glBegin(GL_POLYGON);
	glColor3f(0.039, 0.129, 0.149);
	glVertex2f(60, 270);
	glVertex2f(260, 270);
	glVertex2f(260, 360);
	glVertex2f(60, 360);
	glEnd();
	DrawString(GLUT_BITMAP_HELVETICA_18, 65, 260, "Player 1");


	//Player Box 2
	glBegin(GL_POLYGON);
	glColor3f(0.039, 0.129, 0.149);
	glVertex2f(60, 430);
	glVertex2f(260, 430);
	glVertex2f(260, 520);
	glVertex2f(60, 520);
	glEnd();
	DrawString(GLUT_BITMAP_HELVETICA_18, 65, 420, "Player 2");


	//How to Play
	glBegin(GL_POLYGON);
	glColor3f(0.039, 0.129, 0.149);
	glVertex2f(60, 600);
	glVertex2f(260, 600);
	glVertex2f(260, 640);
	glVertex2f(60, 640);
	glEnd();
	glColor3f(0.596, 0.886, 0.556);
	//DrawString(GLUT_BITMAP_HELVETICA_18, 105, 628, "How To Play");

	//New Game
	glBegin(GL_POLYGON);
	glColor3f(0.039, 0.129, 0.149);
	glVertex2f(60, 660);
	glVertex2f(260, 660);
	glVertex2f(260, 700);
	glVertex2f(60, 700);
	glEnd();
	glColor3f(0.596, 0.886, 0.556);
	DrawString(GLUT_BITMAP_HELVETICA_18, 115, 688, "New Game");


}

void symbols() {
	for (int x = 0; x <= 5; x++) {
		for (int y = 0; y <= 5; y++) {
			if (matrix[x][y] == 1) {
				glBegin(GL_POLYGON);
				glColor3f(0.039, 0.129, 0.149);
				glVertex2f(320 + x * 105, 220 + y * 105);
				glVertex2f(390 + x * 105, 220 + y * 105);
				glVertex2f(390 + x * 105, 290 + y * 105);
				glVertex2f(320 + x * 105, 290 + y * 105);
				glEnd();

				glBegin(GL_POLYGON);
				glColor3f(0.596, 0.886, 0.556);
				glVertex2f(326 + x * 105, 226 + y * 105);
				glVertex2f(384 + x * 105, 226 + y * 105);
				glVertex2f(384 + x * 105, 284 + y * 105);
				glVertex2f(326 + x * 105, 284 + y * 105);
				glEnd();

			}
			else if (matrix[x][y] == 2) {
				glBegin(GL_POLYGON);
				glColor3f(0.039, 0.129, 0.149);
				glVertex2f(320 + x * 105, 226 + y * 105);
				glVertex2f(326 + x * 105, 220 + y * 105);
				glVertex2f(390 + x * 105, 284 + y * 105);
				glVertex2f(384 + x * 105, 290 + y * 105);
				glEnd();

				glBegin(GL_POLYGON);
				glColor3f(0.039, 0.129, 0.149);
				glVertex2f(320 + x * 105, 284 + y * 105);
				glVertex2f(326 + x * 105, 290 + y * 105);
				glVertex2f(390 + x * 105, 226 + y * 105);
				glVertex2f(384 + x * 105, 220 + y * 105);
				glEnd();
				
			}
		}
	}
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.152, 0.498, 0.568, 1.0);

	if (flag == 1) {
		glColor3f(0.039, 0.129, 0.149);
		DrawString(GLUT_BITMAP_HELVETICA_18, 1000, 570, "Player 1's Turn");
	}
	else {
		DrawString(GLUT_BITMAP_HELVETICA_18, 1000, 570, "Player 2's Turn");
	}

	GameBox();
	symbols();
	/*
	if (GameWin() == true) {
		gameover = true;

		glBegin(GL_POLYGON);
		glColor3f(0.039, 0.129, 0.149);
		glVertex2f(290, 325);
		glVertex2f(630, 325);
		glVertex2f(630, 355);
		glVertex2f(290, 355);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.039, 0.129, 0.149);
		glVertex2f(290, 365);
		glVertex2f(630, 365);
		glVertex2f(630, 395);
		glVertex2f(290, 395);
		glEnd();

		glColor3f(0.596, 0.886, 0.556);
		DrawString(GLUT_BITMAP_HELVETICA_18, 420, 345, "Game Over!!!");

		if (flag == 1) {
			DrawString(GLUT_BITMAP_HELVETICA_18, 380, 385, "Player 2 wins this round");
		}
		else {
			DrawString(GLUT_BITMAP_HELVETICA_18, 380, 385, "Player 1 wins this round");
		}

	}
	*/
	glutSwapBuffers();
}

void reshape(int x, int y){
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

void DrawBars(int x,int y, int z) {
	if (z == 1) {
		printf("vertical");
		glBegin(GL_POLYGON);
		glColor3f(0.539, 0.129, 0.149);
		glVertex2f(355,(255 + (y* 105)));
		glVertex2f(355,(255 + (y* 105)));
		glVertex2f(355,(265 + ((y+2)* 105)));
		glVertex2f(355, (265 + ((y + 2) * 105))); 
		glEnd();
	}
	else if (z == 2){
		glBegin(GL_POLYGON);
		glColor3f(0.539, 0.129, 0.149);
		glVertex2f((305 + (x * 105)), 250);
		glVertex2f((305 + (x * 105)), 260);
		glVertex2f((305 + ((x + 3) * 105)), 260);
		glVertex2f((305 + ((x + 3) * 105)), 250);
		glEnd();
		printf("horizontal");
	}
	else if (z == 3) {

		printf("df");
	}
	else if (z == 4) {

		printf("db");
	}

}