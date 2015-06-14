/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

This project virtually displays IKEA Dalfred Stools in a 
series of different environments. There are special features such as 
adjustable seats and debug modes which can be user controlled.
*/

#include <iostream>
#include <assert.h>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "background.h"
#include "cube.h"
#include "top.h"
#include "disc.h"
#include "sphere.h"
#include "cylinder.h"
#include "torus.h"
#include "square.h"
#include "ocean.h"
#include "stoolLeg.h"
#include "stool.h"
#include "table.h"
#include "tiger.h"
#include "bowl.h"
#include "bowlOfFruit.h"
#include "door.h"


using namespace std;
using namespace glm;

//Creates a class for maintaining the window information for easy access.
class Window
{
public:
	Window()
	{
		this->time_last_pause_began = this->total_time_paused = 0;
		this->normals = this->wireframe = this->paused = false;
		this->slices = 20;
		this->interval = 1000 / 120;
		this->window_handle = -1;
	}

	float time_last_pause_began;
	float total_time_paused;
	bool paused , wireframe, normals;
	int window_handle;
	int interval;
	int slices;
	ivec2 size;
	float window_aspect;
	vector<string> instructions;
} window;

Background background;
Top top;
Cube cube;
Sphere sphere;
Sphere sphere2;
Cylinder cylinder;
Disc disc;
Torus torus;
Square square;
Square square2;
Ocean ocean;
StoolLeg sL;
Stool stool;
Table table;
Tiger tiger;
Bowl bowl;
BowlOfFruit bof;
Door door;

//Counter for environment cycling
int environments = 0;
//Counter for debug mode cycling
int debugs = 0;
//Determines whether to go to debug mode or not
bool debugMode = false;

//Angles defining the rotation of the camera.
double RotatedX = 70;
double RotatedY = 0;
float transX = 0;
float transY = 0;
float transZ = 0;

//Moves the camera according to user inputs
glm::mat4 render(glm::mat4 Model){	
	Model = glm::translate(Model, glm::vec3(transX,0,0));
    Model = glm::rotate(Model, (GLfloat) RotatedX, glm::vec3(1,0,0));
	Model = glm::translate(Model, glm::vec3(0,0,transZ));
    Model = glm::rotate(Model, (GLfloat) RotatedY, glm::vec3(0,1,0));
	Model = glm::translate(Model, glm::vec3(0,transY,0));
	
	//transX = 0;
	glLoadMatrixf(glm::value_ptr(Model));
    return Model;
}

//Changes the value of the angle in which the camera should be rotated vertically.
void rotateX(double angle){
    if(!(RotatedX>=89 && angle>0) && !(RotatedX<=1 && angle<0)){
        RotatedX += angle;
    }
}

//Changes the value of the angle in which the camera should be rotated horizontally.
void rotateY(double angle){
    RotatedY += angle;
}

//Displays the text on the screen
void DisplayInstructions()
{
	if (window.window_handle == -1)
		return;

	vector<string> * s = &window.instructions;
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window.size.x, 0, window.size.y, 1, 10);
	glViewport(0, 0, window.size.x, window.size.y);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(10, 15 * s->size(), -5.5);
	glScaled(0.1, 0.1, 1.0);
	for (auto i = s->begin(); i < s->end(); ++i)
	{
		glPushMatrix();
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *) (*i).c_str());
		glPopMatrix();
		glTranslated(0, -150, 0);
	}
}

//Deletes all of the created objects here.s
void CloseFunc()
{
	window.window_handle = -1;
	background.TakeDown();
	cylinder.TakeDown();
	cube.TakeDown();
	ocean.TakeDown();
	torus.TakeDown();
	sL.TakeDown();
	square.TakeDown();
	square2.TakeDown();
	stool.TakeDown();
	disc.TakeDown();
	table.TakeDown();
	sphere.TakeDown();
	sphere2.TakeDown();
	tiger.TakeDown();
	bowl.TakeDown();
	bof.TakeDown();
	door.TakeDown();
}

//Maintains aspect ratio when window is resized.
void ReshapeFunc(int w, int h)
{
	if (h > 0)
	{
		window.size = ivec2(w, h);
		window.window_aspect = float(w) / float(h);
	}
}

//Variables used for timing and the bowling environment
bool stop = false;
float t, t2, t3, dt, dt2, wave;

int numDebugs = 10;

void KeyboardFunc(unsigned char c, int x, int y)
{
	float current_time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

	switch (c)
	{
	case 'e':  //Shifts backwards through environments
		if(debugMode){
			debugMode = false;
		}
		else{
			environments--;
			if(environments < 0){
				environments+=4;
			}
		}
		break;
	case 'r':  //Shifts forwards through environments
		if(debugMode){
			debugMode = false;
		}
		else{
			environments++;
		}
		break;

	case 'n':  //Shifts backwards through environments
		transY = transY + 1;
		break;

	case 'u':  //Shifts backwards through environments
		transY = transY - 1;
		break;

	case 'i':  //Shifts backwards through environments
		transZ = transZ + 1;
		break;

	case 'k':  //Shifts backwards through environments
		transZ = transZ - 1;
		break;

	case 'j':  //Shifts backwards through environments
		transX = transX + 1;
		break;

	case 'l':  //Shifts backwards through environments
		transX = transX - 1;
		break;

	case 's':  //Toggles shaders
		bowl.StepShader();
		cylinder.StepShader();
		cube.StepShader();
		ocean.StepShader();
		torus.StepShader();
		sL.StepShader();
		square.StepShader();
		square2.StepShader();
		stool.StepShader();
		disc.StepShader();
		table.StepShader();
		sphere.StepShader();
		sphere2.StepShader();
		tiger.StepShader();
		bowl.StepShader();
		bof.StepShader();
		door.StepShader();
		break;

	case 'w':  //Toggles wireframe mode
		window.wireframe = !window.wireframe;
		break;

	case 'x':  //Exit the program
	case 27:
		glutLeaveMainLoop();
		return;
	case '1':  //Raise the seat
		if(stool.adjustableSeat<0.75){
            stool.adjustableSeat+=0.01f;
        }		
		return;
	case '2':  //Lower the seat
		if(stool.adjustableSeat>0){
            stool.adjustableSeat-=0.01f;
        }
        if(stool.adjustableSeat<=0){
            stool.adjustableSeat = 0;
        }	
		return;
	case 32:   //space bar, starts the bowling stools
		if(environments%4 == 3){
			stop = true;
			t = float(glutGet(GLUT_ELAPSED_TIME)) / 350.0f;
			t2 = float(glutGet(GLUT_ELAPSED_TIME)) / 350.0f;
			t3 = float(glutGet(GLUT_ELAPSED_TIME)) / 350.0f;
		}
		else{
			t = 0;
			t2 = 0;
			t3 = 0;
		}
	}
	
}

void SpecialFunc(int c, int x, int y)
{
	switch(c){
        case GLUT_KEY_UP:
            rotateX(1);
            return;
        case GLUT_KEY_DOWN:
            rotateX(-1);
            return;
        case GLUT_KEY_RIGHT:
            rotateY(-1);
            return;
        case GLUT_KEY_LEFT:
            rotateY(1);
            return;
		case GLUT_KEY_F1:
			if(!debugMode){
				debugMode = true;
			}
			else{
				debugs--;
				if(debugs < 0){
					debugs+=numDebugs;
				}
			}			
			return;
		case GLUT_KEY_F2:
			if(!debugMode){
				debugMode = true;
			}
			else{
				debugs++;
			}		
			return;
    }
}

void DisplayFunc()
{
	//float current_time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;
	glEnable(GL_CULL_FACE);
	glClearColor(0.1f, 0.1f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, window.size.x, window.size.y);
	background.Draw(window.size);
	mat4 projection = perspective(25.0f, window.window_aspect, 0.01f, 60.0f);
	mat4 modelview = lookAt(vec3(0.0f, 0.0f, 30.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	modelview = render(modelview);
	glLoadMatrixf(value_ptr(modelview));
	glPolygonMode(GL_FRONT_AND_BACK, window.wireframe ? GL_LINE : GL_FILL);	
	
	//Time calculations for the bowling environment and waves
	dt = 4*(t2 - t);
	dt2 = 10*(t3 - t2);
	wave = float(glutGet(GLUT_ELAPSED_TIME)) / 350.0f;
	if(!stop){
		t = float(glutGet(GLUT_ELAPSED_TIME)) / 350.0f;
	}
	if(dt < 7.0){
		t2 = float(glutGet(GLUT_ELAPSED_TIME)) / 350.0f;
		t3 = float(glutGet(GLUT_ELAPSED_TIME)) / 350.0f;
	}
	if(dt >= 7.0 && dt2 < 6.9){
		t3 = float(glutGet(GLUT_ELAPSED_TIME)) / 350.0f;
	}

	if(!debugMode){
		//House and Table
		if(environments%4 == 0){
			modelview = rotate(modelview, 90.0f, vec3(1,0,0));
			modelview = translate(modelview, vec3(2.5,-14.90,0));
			door.Draw(projection, modelview, window.size, 0.0f);
			modelview = translate(modelview, vec3(-2.5,14.9,0));
			modelview = rotate(modelview, -90.0f, vec3(1,0,0));
			modelview = translate(modelview, vec3(-7,0,4));
			stool.Draw(projection, modelview, window.size,0);
			modelview = translate(modelview, vec3(14,0,0));
			stool.Draw(projection, modelview, window.size,0);
			modelview = translate(modelview, vec3(0,0,-8));
			stool.Draw(projection, modelview, window.size,0);
			modelview = translate(modelview, vec3(-14,0,0));
			stool.Draw(projection, modelview, window.size,0);
			modelview = translate(modelview, vec3(7,0,4));
			table.Draw(projection, modelview, window.size, 0);
			modelview = translate(modelview, vec3(0,4.51,0));
			bof.Draw(projection, modelview, window.size,0);
			modelview = translate(modelview, vec3(0,-4.51,0));
			modelview = translate(modelview, vec3(30,0,30));
	
			square.Draw(projection, modelview, window.size, 0);
	
			glCullFace(GL_FRONT);
			modelview = translate(modelview, vec3(-45,-5,-45));
			cube.Draw(projection, modelview, window.size, 0);
			glCullFace(GL_BACK);
		}
		//Life of Pi
		if(environments%4 == 1){
			modelview = translate(modelview, vec3(4 + (sin(wave)),3,4));
			modelview = rotate(modelview, 270.0f, vec3(1,0,0));
			modelview = rotate(modelview, 90.0f, vec3(0,1,0));
			tiger.Draw(projection, modelview, window.size, 0);
			modelview = rotate(modelview, -90.0f, vec3(0,1,0));
			modelview = rotate(modelview, -270.0f, vec3(1,0,0));
			modelview = translate(modelview, vec3(-7,-2,-2));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(modelview, vec3(5,0,0));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(modelview, vec3(0,0,-4));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(modelview, vec3(-2,0,2));
			modelview = translate(modelview, vec3(0,-1,0));
			modelview = translate(modelview, vec3(0,1,0));
			disc.Draw(projection, modelview, window.size, 0);
			modelview = translate(modelview, vec3(0,-1,0));
			modelview = rotate(modelview, 90.0f, vec3(1,0,0));
			torus.Draw(projection, modelview, window.size, 0);		
			modelview = rotate(modelview, -90.0f, vec3(1,0,0));
			modelview = translate(modelview, vec3(30 + (2*sin(wave)) - (sin(wave)),0,30));
	
			ocean.Draw(projection, modelview, window.size, 0);
		}
		//Stool World
		if(environments%4 == 2){
			mat4 a, b;
			a = modelview;
			b = modelview;
			modelview = translate(modelview, vec3(30,0,30));
			square2.Draw(projection, modelview, window.size, 0);
			modelview = translate(modelview, vec3(-30,0,-30));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = scale(modelview, vec3(1,2,1));
			modelview = translate(modelview, vec3(4,0,-4));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = scale(modelview, vec3(2,0.5,2));
			modelview = translate(modelview, vec3(-3,0,-5));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = scale(modelview, vec3(3,3,3));
			modelview = translate(modelview, vec3(-1,0,-1));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(a, vec3(0,4.0+stool.adjustableSeat,0));
			modelview = scale(modelview, vec3(0.2,0.2,0.2));		
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(a, vec3(-3,0,2));
			modelview = scale(modelview, vec3(0.5,1.5,0.5));
			modelview = rotate(modelview, 180.0f, vec3(1.0,0.0,0.0));
			modelview = translate(modelview, vec3(0.0,-4.0-stool.adjustableSeat,0.0));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(modelview, vec3(0.0,4.0+stool.adjustableSeat,0.0));
			modelview = rotate(modelview, -180.0f, vec3(1.0,0.0,0.0));
			modelview = scale(modelview, vec3(0.25,0.5,0.25));
			modelview = translate(modelview, vec3(8.0,0.0,3.0));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(a, vec3(-7,0,6));
			modelview = scale(modelview, vec3(1.5,1.5,1.5));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(a, vec3(8,0,10));
			modelview = scale(modelview, vec3(0.5,0.5,0.5));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(a, vec3(-4,0,11));
			modelview = scale(modelview, vec3(2.5,0.5,2.5));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(a, vec3(14,0,-21));
			modelview = scale(modelview, vec3(1.5,3.5,1.5));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(a, vec3(4,0,1));
			modelview = scale(modelview, vec3(0.5,0.75,0.5));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(a, vec3(14,0,21));
			modelview = scale(modelview, vec3(2.5,1.5,2.5));
			stool.Draw(projection, modelview, window.size, 0);
			modelview = translate(a, vec3(-14,0,21));
			modelview = scale(modelview, vec3(2.5,2.5,2.5));
			stool.Draw(projection, modelview, window.size, 0);
		}
		//Bowling with the stool
		if(environments%4 == 3){
			mat4 a;
			if(!stop){
				t = float(glutGet(GLUT_ELAPSED_TIME)) / 350.0f;
			}
			modelview = translate(modelview, vec3(30,0,30));
			square.Draw(projection, modelview, window.size, 0);
			modelview = translate(modelview, vec3(-30,0,-30));
			modelview = translate(modelview, vec3(-dt2*1.75/6.9,dt2*1.5/6.9,0));      // 1.5 y translate 
			modelview = rotate(modelview, (float)(dt2*98.0/6.9), vec3(0,0,1));   //100, z rotate

			stool.Draw(projection, modelview, window.size, 0);
			modelview = rotate(modelview, (float)(-dt2*98.0/6.9), vec3(0,0,1));
			modelview = translate(modelview, vec3(dt2*1.75/6.9,-dt2*1.5/6.9,0));
			modelview = translate(modelview, vec3(10-dt,2,0));
			sphere.Draw(projection, modelview, window.size, 0);
		}
	}
	else{
		if(debugs%numDebugs == 0){
			sphere2.Draw(projection, modelview, window.size, 0);
		}
		if(debugs%numDebugs == 1){
			stool.Draw(projection, modelview, window.size, 0);
		}
		if(debugs%numDebugs == 2){
			cylinder.Draw(projection, modelview, window.size, 0);
			cout << cylinder.shader_index << endl;
		}
		if(debugs%numDebugs == 3){
			torus.Draw(projection, modelview, window.size, 0);
		}
		if(debugs%numDebugs == 4){
			bowl.Draw(projection, modelview, window.size, 0);
		}
		if(debugs%numDebugs == 5){
			bof.Draw(projection, modelview, window.size, 0);
		}
		if(debugs%numDebugs == 6){
			door.Draw(projection, modelview, window.size, 0);
		}
		if(debugs%numDebugs == 7){
			tiger.Draw(projection, modelview, window.size, 0);
		}
		if(debugs%numDebugs == 8){
			table.Draw(projection, modelview, window.size, 0);
		}
		if(debugs%numDebugs == 9){
			sL.Draw(projection, modelview, window.size, 0);
		}
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DisplayInstructions();
	glFlush();
}

void TimerFunc(int value)
{
	if (window.window_handle != -1)
	{
		glutTimerFunc(window.interval, TimerFunc, value);
		glutPostRedisplay();
	}
}

int main(int argc, char * argv[])
{
	glewInit();
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 512);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

	//Initialize the object's colors
	torus.color = vec3(1.0f, 0.1f, 0.0f);
	square.color1 = vec3(1.0, 1.0, 1.0);
	square2.color1 = vec3(0.95f, 0.1f, 0.7f);
	square2.color2 = vec3(1.0f, 1.0f, 0.0f);
	disc.color = vec3(1.0f, 0.25f, 0.0f);
	sphere.color = vec3(0.45f, 0.0f, 0.0f);
	sphere2.color = vec3(0.25f, 0.0f, 0.0f);
	cylinder.color = vec3(0.0f, 0.5f, 0.0f);
	bowl.color = vec3(1.0f, 1.0f, 0.0f);

	window.window_handle = glutCreateWindow("Modern Stools");
	glutReshapeFunc(ReshapeFunc);
	glutCloseFunc(CloseFunc);
	glutDisplayFunc(DisplayFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutTimerFunc(window.interval, TimerFunc, 0);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	window.instructions.push_back("Clayton Suplinski - CS 559 Project 2");
	window.instructions.push_back("");
	window.instructions.push_back("IKEA Dalfred stools in various environments");
	window.instructions.push_back("with modern OpenGL.");
	window.instructions.push_back("");
	window.instructions.push_back("s - changes shaders");
	window.instructions.push_back("1/2 - changes seat height");
	window.instructions.push_back("F1/F2 - toggles debugs");
	window.instructions.push_back("e/r - toggles environment");
	window.instructions.push_back("w - toggles wireframe");
	window.instructions.push_back("x, ESC - exits");
	
	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW failed to initialize." << endl;
		return 0;
	}

	//Initialize the objects
	if (!background.Initialize())
		return 0;

	if (!bof.Initialize())
		return 0;

	if (!cylinder.Initialize(6,3,1.5,1.5))
		return 0;

	if (!cube.Initialize(30,30,30))
		return 0;

	if (!door.Initialize())
		return 0;

	if (!torus.Initialize(4,10,2))
		return 0;

	if (!disc.Initialize(4,10))
		return 0;

	if (!ocean.Initialize(45,90))
		return 0;

	if (!sL.Initialize())
		return 0;

	if (!stool.Initialize())
		return 0;

	if (!tiger.Initialize())
		return 0;

	if (!table.Initialize())
		return 0;

	if (!sphere.Initialize(9, 2))
		return 0;

	if (!sphere2.Initialize(5, 7))
		return 0;

	if (!bowl.Initialize(8, 2))
		return 0;

	if (!square.Initialize(60, 60)) 
		return 0;

	if (!square2.Initialize(10, 60))
		return 0;

	glutMainLoop();
}
