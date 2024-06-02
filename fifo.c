#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAX_PAGES 10
#define MAX_FRAMES 4
#define REFRESH_INTERVAL 1000 

int windowWidth = 800;
int windowHeight = 600;
int pageReference[MAX_PAGES];
int frames[MAX_FRAMES];
int currentPage = 0;
int currentFrame = 0;
int pageFaults = 0;
int pageReplacementComplete = 0; 
char pageFaultsString[] = "";
int pageQueueX[MAX_PAGES];
int pageQueueY[MAX_PAGES];
int pagequeueX[MAX_FRAMES];
int pagequeueY[MAX_FRAMES];

void drawText(float x, float y, char *text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}
void drawstring(float x, float y, char *text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void frontscreen(void)
{

glClearColor(0.0,0.0,0.0,1.0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0,0,1);
drawstring(195,575,"SRINIVAS INSTITUTE OF TECHNOLOGY VALACHIL, MANGALURU");
glColor3f(0.7,0,1);
drawstring(215,535,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
glColor3f(1,0,1);
drawstring(190,490,"COMPUTER GRAPHICS LABORATORY WITH MINI PROJECT (18CSL67) ");
glColor3f(0.7,0,1);
drawstring(322,445,"ACADEMIC YEAR 2022-23");
glColor3f(1,0.5,0);
drawstring(340,385,"MINI PROJECT ON");
glColor3f(1,1,1);
drawstring(340,355,"FIFO ALGORITHM");
glColor3f(1,0.5,0);
drawstring(348,295,"PRESENTED BY");
glColor3f(1,1,1);
drawstring(185,265,"SURAJ KRISHNA NAIK");
glColor3f(1,1,1);
drawstring(480,265,"SWATHI HEGDE");
glColor3f(1,1,1);
drawstring(221,235,"4SN20CS082");
glColor3f(1,1,1);
drawstring(501,235,"4SN20CS083");
glColor3f(1,0.5,0);
drawstring(308,170,"UNDER THE GUIDANCE OF");
glColor3f(1,1,1);
drawstring(332,140,"PROF. SUREGHA K.R");
glColor3f(1,1,1);
drawstring(322,110,"ASSISTANT PROFESSOR");
glColor3f(0,1,1);
drawstring(332,40,"PRESS 'S' TO START");
glFlush();

}

void drawQueue() {
    glColor3f(1.0, 1.0, 1.0);
    drawText(20, 560, "Page Queue:");

    int startX = 100;
    int startY = 550;

    for (int i = 0; i < MAX_PAGES; i++) {
        glColor3f(1.0, 1.0, 1.0);
        glRectf(pageQueueX[i], pageQueueY[i], pageQueueX[i] + 40, pageQueueY[i] + 40);
        glColor3f(0.0, 0.0, 0.0);
        char pageNumberStr[3];
        sprintf(pageNumberStr, "%d", pageReference[i]);
        drawText(pageQueueX[i] + 10, pageQueueY[i] + 20, pageNumberStr);
	if (i == currentPage) {
            glColor3f(0.0, 1.0, 0.0);
            glRectf(pageQueueX[i], pageQueueY[i], pageQueueX[i] + 40, pageQueueY[i] + 40);
        }
        if (i < MAX_PAGES - 1) {
            startX += 60;
        }
    }
}

void drawqueue() {
    glColor3f(1.0, 1.0, 1.0);
    drawText(20, 460, "Page Frames:");

    int startX = 100;
    int startY = 450;

    for (int i = 0; i < MAX_FRAMES; i++) {
        glColor3f(1.0, 1.0, 1.0);
        glRectf(pagequeueX[i], pagequeueY[i], pagequeueX[i] + 40, pagequeueY[i] + 40);
        glColor3f(0.0, 0.0, 0.0);
        drawText(pagequeueX[i] + 10, pagequeueY[i] + 20, " ");

        if (frames[i] != -1) {
            glColor3f(0.0, 0.0, 1.0);
            glRectf(pagequeueX[i], pagequeueY[i], pagequeueX[i] + 40, pagequeueY[i] + 40);
            glColor3f(1.0, 1.0, 1.0);
            char pageNumberStr[3];
            if (i == currentPage) {
                glColor3f(0.0, 1.0, 0.0);
            }
            sprintf(pageNumberStr, "%d", frames[i]);
            drawText(pagequeueX[i] + 10, pagequeueY[i] + 20, pageNumberStr);
        }

        if (i < MAX_FRAMES - 1) {
            startX += 60;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawQueue();
    drawqueue();

    glColor3f(1.0, 1.0, 1.0);
    char pageFaultsStr[100];
    sprintf(pageFaultsStr, "Page Faults: %s", pageFaultsString);
    drawText(20, 360, pageFaultsStr);

    if (pageReplacementComplete) {
        glColor3f(1.0, 1.0, 1.0);
    sprintf(pageFaultsStr, "Total Page Faults: %d", pageFaults);
    drawText(20, 320, pageFaultsStr);
        glColor3f(0.0, 1.0, 0.0);
        drawText(20, 280, "Page Replacement Complete!");
         glColor3f(1, 0, 1);
        drawstring(330,200,"PRESS 'E' TO EXIT");
    }

    glFlush();
}

void movePage(int srcX, int srcY, int destX, int destY) {
    float x = srcX;
    float y = srcY;

    while (x != destX || y != destY) {
        usleep(5000);
        glClear(GL_COLOR_BUFFER_BIT);
        drawQueue();
        drawqueue();

       
        glColor3f(1.0, 1.0, 1.0);
        char pageNumberStr[3];
        sprintf(pageNumberStr, "%d",pageReference[currentPage]);
        drawText(x + 10, y + 60, pageNumberStr);

        glColor3f(0.0, 1.0, 0.0);
        glRectf(x, y, x + 40, y + 40);
        glFlush();

        if (x < destX) {
            x += 1;
        } 
        else if (x > destX) 
        {
            x -= 1;
        }

        if (y < destY) {
            y += 1;
        } else if (y > destY) {
            y -= 1;
        }
    }
}


void initializePositions() {
    int startX = 100;
    int startY = 550;

    for (int i = 0; i < MAX_PAGES; i++) {
        pageQueueX[i] = startX;
        pageQueueY[i] = startY;
        startX += 60;
    }

    startX = 100;
    startY = 450;

    for (int i = 0; i < MAX_FRAMES; i++) {
        pagequeueX[i] = startX;
        pagequeueY[i] = startY;
        startX += 60;
    }
}

void fifoPageReplacement() {
    int pageFound = 0;

    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == pageReference[currentPage]) {
            pageFound = 1;
            strcat(pageFaultsString, "0");
            break;
        }
    }

    if (!pageFound) {
    movePage(pageQueueX[currentPage], pageQueueY[currentPage],
                 pagequeueX[currentFrame], pagequeueY[currentFrame]);
        frames[currentFrame] = pageReference[currentPage];
         strcat(pageFaultsString, "1");
        pageFaults++;
        currentFrame = (currentFrame + 1) % MAX_FRAMES;

    }

    currentPage++;

    if (currentPage >= MAX_PAGES) {
        pageReplacementComplete = 1;
    }
    else{
    strcat(pageFaultsString, "+");
    }
}

void timer(int value) {
    fifoPageReplacement();
    glutPostRedisplay();

    if (!pageReplacementComplete) {
        glutTimerFunc(REFRESH_INTERVAL, timer, 0);
    }
}


void keyAction(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'S':initializePositions();
			  glutTimerFunc(REFRESH_INTERVAL, timer, 0);
			  glutDisplayFunc(display);
			  break;
		case 'E': exit(0);
			  break;
		
	}
	glutPostRedisplay();
	
}

int main(int argc, char **argv) {
    printf("\n\n***** FIFO PAGE REPLACEMENT ALGORITHM *****\n\n");
    printf("Enter page references (maximum %d):\n", MAX_PAGES);
    for (int i = 0; i < MAX_PAGES; i++) {
        scanf("%d", &pageReference[i]);
    }
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("FIFO Page Replacement Algorithm");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutDisplayFunc(frontscreen);
    glutKeyboardFunc(keyAction);
    glutMainLoop();
    return 0;
}


