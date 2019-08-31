// Include b&b.h file
#include"bandb.h"

// Render the scene
void Render(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

    if(beginFlag == 0){
        beginGame();
    }

    if(beginFlag != 0){
        // Draw the scores of the players in the rendering window
        sprintf(string, "BAT & BALL GAME");
        drawText(string, 350, 30);
        sprintf(string, "Difficulty Level : %d ", difficulty);
        drawText(string, 10, 80);
        sprintf(string, "Player : %d ", score);
        drawText(string, 10, 120);

        // Render the window of the playing screen/wall
        wall.left = wall.top = 0;
        wall.right = WINDOW_WIDTH;
        wall.bottom = WINDOW_HEIGHT;

        // Draw the ball
        DrawRectangle(ball);

        // Change the direction of movement of ball by detecting collisions using the wallCollision function
        if(wallCollision(ball, wall) == RIGHT){
            // Change X direction to minus change
            X =- change;
        }    
        if(wallCollision(ball, wall) == LEFT){
            // Change X direction to plus change
            X = change;
        }
        if(wallCollision(ball, wall) == TOP){
            // Change Y direction to plus change
            Y = change;
        }   
        if(wallCollision(ball, wall) == BOTTOM){   
            // Change Y direction to minus change
            Y =- change; 
            // If the ball is hitting bottom change strike to 1
            strike = 1;
        }

        // Draw the bat
        DrawRectangle(bat); 
        bat.left = mouse_x - 40; 
        bat.right = mouse_x + 40; 

        // Change direction if bat hits the ball using batCollision function
        if(batCollision(ball, bat) == true){
            Y =- change; 
        }   
    }
    
	glutSwapBuffers();
}

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (795, 500); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("BAT & BALL");
    Setting ();
   glutDisplayFunc(Render); 
   glutIdleFunc(Render);
   glutTimerFunc(1, Timer, 1);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(inputKey);
   glutPassiveMotionFunc(MouseMotion);
   glutMainLoop();

   return 0;
}
