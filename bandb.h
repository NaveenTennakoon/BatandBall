// Including libraries
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Definitions for boundary variables
#define RIGHT      1 
#define LEFT       2 
#define TOP        3 
#define BOTTOM     4 
 
// Initializing and declaring variables
static int WINDOW_WIDTH, WINDOW_HEIGHT;
int score = 0, strike = 0, beginFlag = 0, difficulty = 3;
static float X = 0.3, Y = 0.3;
char string [100]; 
static float change = 0.3; 

// Structure for a rectangle
struct RECTANGLE{ 
        float left, top, right, bottom; 
};

// Ball, wall and the bat coordinates for the RECTANGLE Structure
RECTANGLE ball = {0, 0, 20, 20};
RECTANGLE wall;
RECTANGLE bat = {0, 490, 40, 500}; 

// Drawing a rectangle of RECTANGLE structure
void DrawRectangle(RECTANGLE rect){ 
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS); 
        glVertex2f(rect.left,rect.bottom); //Left - Bottom 
        glVertex2f(rect.right,rect.bottom); //Right - Bottom 
        glVertex2f(rect.right,rect.top); //Right - Top 
        glVertex2f(rect.left,rect.top); //Left - Top 
        glEnd(); 
}

// Movement of the ball
void Timer(int v){
        ball.left += X; 
        ball.right += X; 
        ball.top += Y; 
        ball.bottom += Y; 
 
        // Callback function to call Timer function every 1 mili second
        glutTimerFunc(1, Timer, 1);
}

// Function to draw the Text to show scores in the window
void drawText(char*string, int x, int y){
	glColor3f(0.0, 1.0, 0.0);
        char *c;
        glPushMatrix();
        // Translate to the drawing position and scale the text accordingly
        glTranslatef(x, y, 0);
        glScalef(0.1, -0.1, 1);

        for (c = string; *c != '\0'; c++){
                // Draw a single character with STROKE ROMAN font
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
        }
        glPopMatrix();
}

// Start game splash screen
void beginGame(){
        if(beginFlag == 0){
                sprintf(string,"LET'S START THE GAME");
                drawText(string,305,200);
                sprintf(string,"Press ENTER to begin");
                drawText(string,305,300);
                sprintf(string,"A game by 404");
                drawText(string, WINDOW_WIDTH-150, WINDOW_HEIGHT-10);
        }
}

// Get the movement of mouse and change the bat position along the X-axis
static int mouse_x = 0; 
void MouseMotion(int x, int y){
	mouse_x = x;
}

// End the game
void endGame(){
        // Stop the ball
        X = 0;
        Y = 0;

        // Draw the game over screen
        sprintf(string,"GAME OVER");
	drawText(string,370,200);
        sprintf(string,"Score : %d ", score);
	drawText(string,370,270);
        sprintf(string,"Press ESC to exit the game");
	drawText(string,285,300);
        sprintf(string,"Press SPACE to restart the game");
	drawText(string,262,330);

        mouse_x = 100000;
}

// Check the collision of the ball with the wall 
int wallCollision(RECTANGLE ball, RECTANGLE wall){ 
        if(ball.right >= wall.right){
                return RIGHT;  
        }
        if(ball.left <= wall.left){
                return LEFT;  
        }
        if(ball.top <= wall.top){
                return TOP;  
        }
        if(ball.bottom >= wall.bottom){
                if(strike == 0 || score == 0){
                        return BOTTOM;  
                }
                // End game if the ball hits the bottom and player has scored more than one
                else{
                        endGame();
                }
        }
        else return 0 ; 
}

// Return true if the ball collides with the bat/player
bool batCollision(RECTANGLE ball, RECTANGLE player){ 
        if(ball.bottom >= player.top && ball.left >= player.left && ball.left <= player.right ){
                score += 1;
                return true;  
        }
        if(ball.bottom >= player.top && ball.right >= player.left && ball.right <= player.right ){
                score += 1;
                return true;  
        }
        else return false;          
}
 
// Gets keyboard input to manipulate the game
void keyboard(unsigned char key, int x, int y){
   switch (key) {
        // ENTER key to start the game
        case 13:
                beginFlag = 1;
                break;
        // ESC to exit the game 
        case 27:
                exit(0);
                break;
        // SPACE button to restart the game
        case 32:
                beginFlag = 0, score = 0, strike = 0, beginFlag = 0, difficulty = 3, X = 0.3, Y = 0.3, change = 0.3;
                break;
   }
}

//Increase or Decrease Difficulty level
void inputKey(int key, int x, int y){
	switch (key){
                // Decrease difficulty
		case GLUT_KEY_LEFT : 
                        if(change > 0.2){
                                change -= 0.1;
                                difficulty--;
                        } 
                        break;
                // Increase Difficulty
		case GLUT_KEY_RIGHT : 
                        change += 0.1;
                        difficulty++;
                        break;
	}
}

// OpenGL Setting
void Setting(void) {
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

// OnWindowResize 
void reshape(int w, int h){
        WINDOW_WIDTH = w ;
        WINDOW_HEIGHT = h ;

        glViewport(0, 0, (GLsizei) w, (GLsizei) h);
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluOrtho2D (0, w, h, 0);
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();
}
