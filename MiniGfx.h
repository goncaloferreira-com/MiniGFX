/******************************************************
MIT License
Copyright (c) 2025 Gonçalo Ferreira (www.goncalo.pt)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************/

/*  How to use? Just put this on your .cpp file and you're done!...
	//Demo controls: Q+A+O+P and mouse buttons...
	#include "MiniGfx.h"
	int main(int argc,char** argv){
		SDLWindow::demo();
		return 0;
	}
*/

#ifndef MINIGFX_H_INCLUDED
#define MINIGFX_H_INCLUDED

/************************************/
/*********** LIBRARIES... ***********/
/************************************/
#include <iostream>
#include <array>
#include <chrono>
#include <cmath>
#include <functional>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

/************************************/
/*********** CONSTANTS... ***********/
/************************************/
//Constant used to convert degrees to radians...
constexpr float DEG2RAD=3.14159265359f/180.0f;
//Number of segments, the more I have the smoother are the circles but slower...
constexpr int CIRCLE_SEGMENTS=4;

/************************************/
/*** C++ STYLE KEY/MOUSE EVENTS... **/
/************************************/
enum class SDLButton:int{LEFT=SDL_BUTTON_LEFT,MIDDLE=SDL_BUTTON_MIDDLE,RIGHT=SDL_BUTTON_RIGHT,X1=SDL_BUTTON_X1,X2=SDL_BUTTON_X2};
enum class SDLKey:int{UNKNOWN=SDL_SCANCODE_UNKNOWN,A=SDL_SCANCODE_A,B=SDL_SCANCODE_B,C=SDL_SCANCODE_C,D=SDL_SCANCODE_D,E=SDL_SCANCODE_E,F=SDL_SCANCODE_F,G=SDL_SCANCODE_G,H=SDL_SCANCODE_H,I=SDL_SCANCODE_I,J=SDL_SCANCODE_J,K=SDL_SCANCODE_K,L=SDL_SCANCODE_L,M=SDL_SCANCODE_M,N=SDL_SCANCODE_N,O=SDL_SCANCODE_O,P=SDL_SCANCODE_P,Q=SDL_SCANCODE_Q,R=SDL_SCANCODE_R,S=SDL_SCANCODE_S,T=SDL_SCANCODE_T,U=SDL_SCANCODE_U,V=SDL_SCANCODE_V,W=SDL_SCANCODE_W,X=SDL_SCANCODE_X,Y=SDL_SCANCODE_Y,Z=SDL_SCANCODE_Z,_1=SDL_SCANCODE_1,_2=SDL_SCANCODE_2,_3=SDL_SCANCODE_3,_4=SDL_SCANCODE_4,_5=SDL_SCANCODE_5,_6=SDL_SCANCODE_6,_7=SDL_SCANCODE_7,_8=SDL_SCANCODE_8,_9=SDL_SCANCODE_9,_0=SDL_SCANCODE_0,RETURN=SDL_SCANCODE_RETURN,ESCAPE=SDL_SCANCODE_ESCAPE,BACKSPACE=SDL_SCANCODE_BACKSPACE,TAB=SDL_SCANCODE_TAB,SPACE=SDL_SCANCODE_SPACE,MINUS=SDL_SCANCODE_MINUS,EQUALS=SDL_SCANCODE_EQUALS,LEFTBRACKET=SDL_SCANCODE_LEFTBRACKET,RIGHTBRACKET=SDL_SCANCODE_RIGHTBRACKET,BACKSLASH=SDL_SCANCODE_BACKSLASH,NONUSHASH=SDL_SCANCODE_NONUSHASH,SEMICOLON=SDL_SCANCODE_SEMICOLON,APOSTROPHE=SDL_SCANCODE_APOSTROPHE,GRAVE=SDL_SCANCODE_GRAVE,COMMA=SDL_SCANCODE_COMMA,PERIOD=SDL_SCANCODE_PERIOD,SLASH=SDL_SCANCODE_SLASH,CAPSLOCK=SDL_SCANCODE_CAPSLOCK,F1=SDL_SCANCODE_F1,F2=SDL_SCANCODE_F2,F3=SDL_SCANCODE_F3,F4=SDL_SCANCODE_F4,F5=SDL_SCANCODE_F5,F6=SDL_SCANCODE_F6,F7=SDL_SCANCODE_F7,F8=SDL_SCANCODE_F8,F9=SDL_SCANCODE_F9,F10=SDL_SCANCODE_F10,F11=SDL_SCANCODE_F11,F12=SDL_SCANCODE_F12,PRINTSCREEN=SDL_SCANCODE_PRINTSCREEN,SCROLLLOCK=SDL_SCANCODE_SCROLLLOCK,PAUSE=SDL_SCANCODE_PAUSE,INSERT=SDL_SCANCODE_INSERT,HOME=SDL_SCANCODE_HOME,PAGEUP=SDL_SCANCODE_PAGEUP,DELETE=SDL_SCANCODE_DELETE,END=SDL_SCANCODE_END,PAGEDOWN=SDL_SCANCODE_PAGEDOWN,RIGHT=SDL_SCANCODE_RIGHT,LEFT=SDL_SCANCODE_LEFT,DOWN=SDL_SCANCODE_DOWN,UP=SDL_SCANCODE_UP,NUMLOCKCLEAR=SDL_SCANCODE_NUMLOCKCLEAR,KP_DIVIDE=SDL_SCANCODE_KP_DIVIDE,KP_MULTIPLY=SDL_SCANCODE_KP_MULTIPLY,KP_MINUS=SDL_SCANCODE_KP_MINUS,KP_PLUS=SDL_SCANCODE_KP_PLUS,KP_ENTER=SDL_SCANCODE_KP_ENTER,KP_1=SDL_SCANCODE_KP_1,KP_2=SDL_SCANCODE_KP_2,KP_3=SDL_SCANCODE_KP_3,KP_4=SDL_SCANCODE_KP_4,KP_5=SDL_SCANCODE_KP_5,KP_6=SDL_SCANCODE_KP_6,KP_7=SDL_SCANCODE_KP_7,KP_8=SDL_SCANCODE_KP_8,KP_9=SDL_SCANCODE_KP_9,KP_0=SDL_SCANCODE_KP_0,KP_PERIOD=SDL_SCANCODE_KP_PERIOD,NONUSBACKSLASH=SDL_SCANCODE_NONUSBACKSLASH,APPLICATION=SDL_SCANCODE_APPLICATION,POWER=SDL_SCANCODE_POWER,KP_EQUALS=SDL_SCANCODE_KP_EQUALS,F13=SDL_SCANCODE_F13,F14=SDL_SCANCODE_F14,F15=SDL_SCANCODE_F15,F16=SDL_SCANCODE_F16,F17=SDL_SCANCODE_F17,F18=SDL_SCANCODE_F18,F19=SDL_SCANCODE_F19,F20=SDL_SCANCODE_F20,F21=SDL_SCANCODE_F21,F22=SDL_SCANCODE_F22,F23=SDL_SCANCODE_F23,F24=SDL_SCANCODE_F24,EXECUTE=SDL_SCANCODE_EXECUTE,HELP=SDL_SCANCODE_HELP,MENU=SDL_SCANCODE_MENU,SELECT=SDL_SCANCODE_SELECT,STOP=SDL_SCANCODE_STOP,AGAIN=SDL_SCANCODE_AGAIN,UNDO=SDL_SCANCODE_UNDO,CUT=SDL_SCANCODE_CUT,COPY=SDL_SCANCODE_COPY,PASTE=SDL_SCANCODE_PASTE,FIND=SDL_SCANCODE_FIND,MUTE=SDL_SCANCODE_MUTE,VOLUMEUP=SDL_SCANCODE_VOLUMEUP,VOLUMEDOWN=SDL_SCANCODE_VOLUMEDOWN,KP_COMMA=SDL_SCANCODE_KP_COMMA,KP_EQUALSAS400=SDL_SCANCODE_KP_EQUALSAS400,ALTERASE=SDL_SCANCODE_ALTERASE,SYSREQ=SDL_SCANCODE_SYSREQ, CANCEL=SDL_SCANCODE_CANCEL,CLEAR=SDL_SCANCODE_CLEAR,PRIOR=SDL_SCANCODE_PRIOR,RETURN2=SDL_SCANCODE_RETURN2,SEPARATOR=SDL_SCANCODE_SEPARATOR,OUT=SDL_SCANCODE_OUT,OPER=SDL_SCANCODE_OPER,CLEARAGAIN=SDL_SCANCODE_CLEARAGAIN,CRSEL=SDL_SCANCODE_CRSEL,EXSEL=SDL_SCANCODE_EXSEL,LEFTCTRL=SDL_SCANCODE_LCTRL,LEFTSHIFT=SDL_SCANCODE_LSHIFT,LEFTALT=SDL_SCANCODE_LALT,LEFTGUI=SDL_SCANCODE_LGUI,RIGHTCTRL=SDL_SCANCODE_RCTRL,RIGHTSHIFT=SDL_SCANCODE_RSHIFT,RIGHTALT=SDL_SCANCODE_RALT,RIGHTGUI=SDL_SCANCODE_RGUI,AC_BACK=SDL_SCANCODE_AC_BACK,AC_BOOKMARKS=SDL_SCANCODE_AC_BOOKMARKS,AC_FORWARD=SDL_SCANCODE_AC_FORWARD,AC_HOME=SDL_SCANCODE_AC_HOME,AC_REFRESH=SDL_SCANCODE_AC_REFRESH,AC_SEARCH=SDL_SCANCODE_AC_SEARCH,AC_STOP=SDL_SCANCODE_AC_STOP,APP1=SDL_SCANCODE_APP1,APP2=SDL_SCANCODE_APP2,AUDIOFASTFORWARD=SDL_SCANCODE_AUDIOFASTFORWARD,AUDIOMUTE=SDL_SCANCODE_AUDIOMUTE,AUDIONEXT=SDL_SCANCODE_AUDIONEXT,AUDIOPLAY=SDL_SCANCODE_AUDIOPLAY,AUDIOPREV=SDL_SCANCODE_AUDIOPREV,AUDIOREWIND=SDL_SCANCODE_AUDIOREWIND,AUDIOSTOP=SDL_SCANCODE_AUDIOSTOP,BRIGHTNESSDOWN=SDL_SCANCODE_BRIGHTNESSDOWN,BRIGHTNESSUP=SDL_SCANCODE_BRIGHTNESSUP,CALCULATOR=SDL_SCANCODE_CALCULATOR,COMPUTER=SDL_SCANCODE_COMPUTER,DISPLAYSWITCH=SDL_SCANCODE_DISPLAYSWITCH,EJECT=SDL_SCANCODE_EJECT,KBDILLUMDOWN=SDL_SCANCODE_KBDILLUMDOWN,KBDILLUMTOGGLE=SDL_SCANCODE_KBDILLUMTOGGLE,KBDILLUMUP=SDL_SCANCODE_KBDILLUMUP,MAIL=SDL_SCANCODE_MAIL,MEDIASELECT=SDL_SCANCODE_MEDIASELECT,MODE=SDL_SCANCODE_MODE,SLEEP=SDL_SCANCODE_SLEEP,WWW=SDL_SCANCODE_WWW};

/************************************/
/************ STRUCTS... ************/
/************************************/
struct Vec2D{float x=0.0;float y=0.0;};
struct SDLColor{Uint8 r,g,b,a;constexpr SDLColor(Uint8 r=255,Uint8 g=255,Uint8 b=255, Uint8 a=255):r(r),g(g),b(b),a(a){}};
struct SDLPoint{int x=0,y=0;SDLPoint(int x=0,int y=0):x(x),y(y){}};
struct MouseState{bool leftDown=false;bool rightDown=false;bool middleDown=false;bool wheelUp=false;bool wheelDown=false;bool leftPressed=false;bool prevLeftDown=false;bool rightPressed=false;bool prevRightDown=false;bool middlePressed=false;bool prevMiddleDown=false;int x=0,y=0;void updateButtonPresses(){this->leftPressed=this->leftDown && !this->prevLeftDown;this->prevLeftDown=this->leftDown;this->middlePressed=this->middleDown && !this->prevMiddleDown;this->prevMiddleDown=this->middleDown;this->rightPressed=this->rightDown && !this->prevRightDown;this->prevRightDown=this->rightDown;}};
enum class EnumColor{White,Black,Grey,Red,Green,Blue,Yellow,Orange,Purple,Cyan,Pink};
constexpr std::array<SDLColor,11> colors={{{255,255,255},/*White...*/{0,0,0},/*Black...*/{128,128,128},/*Grey...*/{255,0,0},/*Red...*/{0,255,0},/*Green...*/{0,0,255},/*Blue...*/{255,255,0},/*Yellow...*/{255,128,0},/*Orange...*/{128,0,128},/*Purple...*/{0,255,255},/*Cyan...*/{255,128,128}/*Pink...*/}};

/************************************/
/*********** "ALIASES"... ***********/
/************************************/
using Texture=SDL_Texture*;

/************************************/
/*** THE MAIN SDL WINDOW CLASS... ***/
/************************************/
class SDLWindow{

	public:

		/***********************************************/
		/********* STATIC DEMO - TEST IT OUT... ********/
		/***********************************************/
		//Just put SDLWindow::demo(); on your .cpp file and test it out, the controls are q+a+o+p and +- and the mouse buttons...
		static void demo();

	private:

		/****************************/
		/*** WORKING VARIABLES... ***/
		/****************************/
		SDL_Window* window;SDL_Renderer* renderer;
		int windowWidth=0,windowHeight=0;SDLColor backColor;SDLColor foreColor;
		std::mt19937 rng;MouseState mouse;
		bool keysDown[SDL_NUM_SCANCODES]={false},keysPressed[SDL_NUM_SCANCODES]={false},keysReleased[SDL_NUM_SCANCODES]={false};

	public:

		/****************************/
		/**** CONS/DESTRUCTORS... ***/
		/****************************/
		SDLWindow(int windowWidth,int windowHeight,const std::string &windowTitle,SDLColor backColor,SDLColor foreColor){
			if(windowWidth<=0||windowHeight<=0){std::cerr<<"Invalid Window size!"<<std::endl;this->quitRequested=true;return;}
			this->windowWidth=windowWidth;this->windowHeight=windowHeight;
			this->backColor=backColor;this->foreColor=foreColor;
			SDL_Init(SDL_INIT_VIDEO);
			int flags=IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);
			if((flags&IMG_INIT_PNG)==0){std::cout<<"PNG initialization failed: "<<IMG_GetError()<<std::endl;this->quitRequested=true;}
			if((flags&IMG_INIT_JPG)==0){std::cout<<"JPG initialization failed: "<<IMG_GetError()<<std::endl;this->quitRequested=true;}
			this->window=SDL_CreateWindow(windowTitle.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
			this->renderer=SDL_CreateRenderer(this->window,-1,SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawBlendMode(this->renderer,SDL_BLENDMODE_BLEND);
			this->rng=std::mt19937(static_cast<uint32_t>(std::chrono::steady_clock::now().time_since_epoch().count()));
		}
		~SDLWindow(){if(this->renderer){SDL_DestroyRenderer(this->renderer);this->renderer=nullptr;}if(this->window){SDL_DestroyWindow(this->window);this->window=nullptr;}IMG_Quit();SDL_Quit();}

		/****************************/
		/**** INPUT FUNCTIONS... ****/
		/****************************/
		bool quitRequested=false;
		void updateInputs(){
			this->mouse.wheelUp=false;this->mouse.wheelDown=false;
			std::fill(std::begin(this->keysPressed),std::end(this->keysPressed),false);std::fill(std::begin(this->keysReleased),std::end(this->keysReleased),false);
			SDL_Event e;
			while(SDL_PollEvent(&e)){
				switch(e.type){
					case SDL_MOUSEBUTTONDOWN:if(e.button.button==SDL_BUTTON_LEFT)this->mouse.leftDown=true;if(e.button.button==SDL_BUTTON_RIGHT)this->mouse.rightDown=true;if(e.button.button==SDL_BUTTON_MIDDLE)this->mouse.middleDown=true;break;
					case SDL_MOUSEBUTTONUP:if(e.button.button==SDL_BUTTON_LEFT)this->mouse.leftDown=false;if(e.button.button==SDL_BUTTON_RIGHT)this->mouse.rightDown=false;if(e.button.button==SDL_BUTTON_MIDDLE)this->mouse.middleDown=false;break;
					case SDL_MOUSEWHEEL:if(e.wheel.y>0)this->mouse.wheelUp=true;else if(e.wheel.y<0)this->mouse.wheelDown=true;break;
					case SDL_MOUSEMOTION:this->mouse.x=e.motion.x;this->mouse.y=e.motion.y;break;
					case SDL_QUIT:this->quitRequested=true;break;
					case SDL_KEYDOWN:if(!this->keysDown[e.key.keysym.scancode])this->keysPressed[e.key.keysym.scancode]=true;this->keysDown[e.key.keysym.scancode]=true;break;
					case SDL_KEYUP:this->keysDown[e.key.keysym.scancode]=false;this->keysReleased[e.key.keysym.scancode]=true;break;
				}
			}
			this->mouse.updateButtonPresses();
		}
		constexpr MouseState getMouseState()const{return this->mouse;}
		bool isMouseButtonDown(SDLButton button)const{if(static_cast<int> (button)==SDL_BUTTON_LEFT)return this->mouse.leftDown;if(static_cast<int> (button)==SDL_BUTTON_RIGHT)return this->mouse.rightDown;if(static_cast<int> (button)==SDL_BUTTON_MIDDLE)return this->mouse.middleDown;return false;}
		bool mouseButtonPressed(SDLButton button)const{if(static_cast<int> (button)==SDL_BUTTON_LEFT)return this->mouse.leftPressed;if(static_cast<int> (button)==SDL_BUTTON_RIGHT)return this->mouse.rightPressed;if(static_cast<int> (button)==SDL_BUTTON_MIDDLE)return this->mouse.middlePressed;return false;}
		bool keyDown(SDLKey key){return keysDown[static_cast<int>(key)];}
		bool keyPressed(SDLKey key){return keysPressed[static_cast<int>(key)];}
		bool keyReleased(SDLKey key){return keysReleased[static_cast<int>(key)];}
		SDLPoint getMousePosition()const{int x=0,y=0;SDL_GetMouseState(&x,&y);return SDLPoint{x,y};}

		/****************************/
		/**** WINDOW FUNCTIONS... ***/
		/****************************/
		constexpr int getWidth()const{return this->windowWidth;}
		constexpr int getHeight()const{return this->windowHeight;}
		SDLPoint getCenter()const{return {(int)round(this->getWidth()*0.5f),(int)round(this->getHeight()*0.5f)};}
		void clearWindow(){SDL_SetRenderDrawColor(this->renderer,this->backColor.r,this->backColor.g,this->backColor.b,this->backColor.a);SDL_RenderClear(this->renderer);}
		void clearWindow(SDLColor &backColor){SDL_SetRenderDrawColor(this->renderer,backColor.r,backColor.g,backColor.b,backColor.a);SDL_RenderClear(this->renderer);}

		/****************************/
		/**** COLOR FUNCTIONS... ****/
		/****************************/
		void setColor(SDLColor color){this->setColor(color.r,color.g,color.b,color.a);}
		void setColor(int r,int g,int b,int a){this->foreColor=SDLColor{(Uint8)r,(Uint8)g,(Uint8)b,(Uint8)a};SDL_SetRenderDrawColor(this->renderer,r,g,b,a);}
		void setBackColor(SDLColor color){this->setBackColor(color.r,color.g,color.b,color.a);}
		void setBackColor(int r,int g,int b,int a){this->backColor=SDLColor{(Uint8)r,(Uint8)g,(Uint8)b,(Uint8)a};SDL_SetRenderDrawColor(this->renderer,r,g,b,a);}
		static SDL_Color convertColor(SDLColor c){return SDL_Color{c.r,c.g,c.b,c.a};}
		static SDLColor getColorFromEnum(EnumColor color){return colors[static_cast<int>(color)];}

		/****************************/
		/**** RANDOM FUNCTIONS... ***/
		/****************************/
		SDLColor randomColor(){std::uniform_int_distribution<int> dist(0,(int)colors.size()-1);return colors[dist(this->rng)];}
		int randomInt(int min,int max){std::uniform_int_distribution<int> dist(min,max);return dist(this->rng);}

		/****************************/
		/** RENDERING FUNCTIONS... **/
		/****************************/
		void render(){SDL_RenderPresent(this->renderer);}

		/****************************/
		/*** GEOMETRY FUNCTIONS... **/
		/****************************/
		void drawPoint(SDL_Point pos){this->drawPoint(pos.x,pos.y);}
		void drawPoint(int x,int y){SDL_RenderDrawPoint(this->renderer,x,y);}
		void drawPoints(const std::vector<SDLPoint> &points){for(const SDLPoint &p:points)SDL_RenderDrawPoint(this->renderer,p.x,p.y);}
		void drawLine(SDLPoint p1,SDLPoint p2){this->drawLine(p1.x,p1.y,p2.x,p2.y);}
		void drawLine(int x1,int y1,int x2,int y2){SDL_RenderDrawLine(this->renderer,x1,y1,x2,y2);}
		void drawRect(SDLPoint pos,int w,int h){this->drawRect(pos.x,pos.y,w,h);}
		void drawRect(int x,int y,int w,int h){SDL_Rect rect={x,y,w,h};SDL_RenderDrawRect(this->renderer,&rect);}
		void drawRectCentered(SDLPoint pos,int w,int h){this->drawRectCentered(pos.x,pos.y,w,h);}
		void drawRectCentered(int x,int y,int w,int h){SDL_Rect rect={(int)round(x-w*0.5f),(int)round(y-h*0.5f),w,h};SDL_RenderDrawRect(this->renderer,&rect);}
		void drawFilledRect(SDLPoint pos,int w,int h){this->drawFilledRect(pos.x,pos.y,w,h);}
		void drawFilledRect(int x,int y,int w,int h){SDL_Rect rect={x,y,w,h};SDL_RenderFillRect(this->renderer,&rect);}
		void drawFilledRectCentered(SDLPoint pos,int w,int h){this->drawFilledRectCentered(pos.x,pos.y,w,h);}
		void drawFilledRectCentered(int x,int y,int w,int h){SDL_Rect rect={(int)round(x-w*0.5f),(int)round(y-h*0.5f),w,h};SDL_RenderFillRect(this->renderer,&rect);}
		void drawTriangle(SDLPoint a,SDLPoint b,SDLPoint c){this->drawLine(a,b);this->drawLine(b,c);this->drawLine(c,a);}
		void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3){this->drawLine(x1,y1,x2,y2);this->drawLine(x2,y2,x3,y3);this->drawLine(x3,y3,x1,y1);}
		void drawTriangleCentered(int x,int y,int base,int h,float angle=0){SDLPoint a={x,(int)round(y-h*0.5f)};SDLPoint b={(int)round(x-base*0.5f),(int)round(y+h*0.5f)};SDLPoint c={(int)round(x+base*0.5f),(int)round(y+h*0.5f)};float rad=angle*DEG2RAD;int cx=x,cy=y;std::function<SDLPoint(SDLPoint)> rotate=[cx,cy,rad](SDLPoint p){float dx=p.x-cx,dy=p.y-cy;return SDLPoint{(int)round(cx+dx*cos(rad)-dy*sin(rad)),(int)round(cy+dx*sin(rad)+dy*cos(rad)),};};a=rotate(a);b=rotate(b);c=rotate(c);this->drawTriangle(a,b,c);}
		void drawTriangleCentered(SDLPoint pos,int base,int h,float angle=0){this->drawTriangleCentered(pos.x,pos.y,base,h,angle);}
		void drawPolygon(const std::vector<SDLPoint> &points){if(points.size()<2)return;for(size_t i=0;i<points.size()-1;++i)this->drawLine(points[i].x,points[i].y,points[i+1].x,points[i+1].y);this->drawLine(points.back().x,points.back().y,points[0].x,points[0].y);}
		void drawCircle(SDLPoint pos,int radius){this->drawCircle(pos.x,pos.y,radius);}
		void drawCircle(int x,int y,int radius){for(int w=0;w<360;w+=CIRCLE_SEGMENTS){int dx=(int)(radius*cos(w*DEG2RAD)),dy=(int)(radius*sin(w*DEG2RAD));this->drawPoint(x+dx,y+dy);}}
		void drawEllipse(SDLPoint pos,int rx,int ry){this->drawEllipse(pos.x,pos.y,rx,ry);}
		void drawEllipse(int x,int y,int rx,int ry){for(int angle=0;angle<360;++angle){int dx=(int)(rx*cos(angle*DEG2RAD)),dy=(int)(ry*sin(angle*DEG2RAD));this->drawPoint(x+dx,y+dy);}}
		void drawArc(int x,int y,int radius,float startAngle,float endAngle){for(float w=startAngle;w<=endAngle;w+=1.0f){int dx=(int)(radius*cos(w*DEG2RAD)),dy=(int)(radius*sin(w*DEG2RAD));this->drawPoint(x+dx,y+dy);}}

		/****************************/
		/***** TIME FUNCTIONS... ****/
		/****************************/
		void pause(int ms){SDL_Delay(ms);}
		Uint64 getTimeMicroSecs(){using namespace std::chrono;std::chrono::time_point<std::chrono::high_resolution_clock> now=high_resolution_clock::now();return duration_cast<microseconds>(now.time_since_epoch()).count();}

		/****************************/
		/**** IMAGE FUNCTIONS... ****/
		/****************************/
		Texture readFile(const std::string &fileName){SDL_Surface* surf=IMG_Load(fileName.c_str());if(!surf){std::cerr<<"Error reading file "<<fileName<<IMG_GetError()<<std::endl;return nullptr;}Texture tex=SDL_CreateTextureFromSurface(this->renderer,surf);SDL_FreeSurface(surf);return tex;}
		static Vec2D getTextureSize(Texture tex){int w=0,h=0;SDL_QueryTexture(tex,NULL,NULL,&w,&h);return{(float)w,float(h)};}
		void renderTexture(Texture tex,int x,int y,int opacity,float angle){if(!tex){std::cerr<<"Error reading texture..."<<std::endl;return;}SDL_SetTextureAlphaMod(tex,opacity);int w=0,h=0;SDL_QueryTexture(tex,nullptr,nullptr,&w,&h);SDL_Rect dest={x,y,w,h};SDL_RenderCopyEx(this->renderer,tex,nullptr,&dest,angle,nullptr,SDL_FLIP_NONE);}
		void destroyTexture(Texture tex){if(tex)SDL_DestroyTexture(tex);}

};

/***********************************************/
/***********************************************/
/********* STATIC DEMO - TEST IT OUT... ********/
/***********************************************/
/***********************************************/
//Just put SDLWindow::demo(); on your .cpp file and test it out, the controls are q+a+o+p and +- and the mouse buttons...
void SDLWindow::demo(){

	/***********************************************/
	/********** INITIAL CONFIGURATIONS... **********/
	/***********************************************/
	//Window size...
	int windowWidth=1280;
	int windowHeight=960;
	//Colors...
	SDLColor backColor(0,0,0,255);
	SDLColor foreColor(255,255,255,255);
	//Title...
	std::string windowTitle="MiniGFX - A simple and easy-to-use SDL2 frontend...";
	//Limit the number of FPS...
	int numberFPS=100000;

	/***********************************************/
	/*************** CREATE WINDOW... **************/
	/***********************************************/
	SDLWindow window(windowWidth,windowHeight,windowTitle,backColor,foreColor);

	/***********************************************/
	/********* WORKING EXAMPLE VARIABLES... ********/
	/***********************************************/
	//These are just for the demo examples below...
	float clockRadius=200.0f;
	float angle=0.0f;

	/***********************************************/
	/******* DEMO RESOURCES - READ IMAGES... *******/
	/***********************************************/
	Texture spriteTex=window.readFile("sprite.png");
	Texture spriteTexFixed=window.readFile("sprite.png");

	/***********************************************/
	/************ START THE GAME LOOP... ***********/
	/***********************************************/
	bool running=true;
	while(running){

		/*****************************************/
		/******** CLEAR WINDOW AS BLACK... *******/
		/*****************************************/
		//We must call this on each loop for the window to be rendered...
		window.clearWindow(backColor);

		/*****************************************/
		/********** READ USER INPUTS... **********/
		/*****************************************/
		//We must run this on each loop if we want to get the inputs...
		window.updateInputs();
		//Did I exit...
		if(window.quitRequested){
			running=false;
		}

		/*****************************************/
		/*****************************************/
		/****** SEVERAL TESTING EXAMPLES... ******/
		/*****************************************/
		/*****************************************/

		/*****************************************/
		/************* DRAW LINE... **************/
		/*****************************************/
		window.setColor(foreColor);
		window.drawLine(0,0,100,100);

		/*****************************************/
		/******* RANDOM COLORED SQUARES... *******/
		/*****************************************/
		//Fill the window with 1001*2 squares!... :D
		for(int i=0;i<1001*2;i++){
			//First, the square position and size...
			int w=window.randomInt(5,50);
			int h=window.randomInt(5,50);
			int x=window.randomInt(w*0.5,window.getWidth()-w*0.5);
			int y=window.randomInt(h*0.5,window.getHeight()-h*0.5);
			//Now get a random color...
			SDLColor color=window.randomColor();
			color.b=255;
			color.a=64;
			window.setColor(color);
			window.drawFilledRect(x-w*0.5,y-h*0.5,w,h);
		}

		/*****************************************/
		/******* EMPTY SQUARES ON CENTER... ******/
		/*****************************************/
		//Configuration...
		int maxSize=500;
		//Draw squares...
		int posX=window.getCenter().x;
		int posY=window.getCenter().y;
		for(int length=maxSize;length>10;length-=20){
			SDLColor color((Uint8)(length*0.5f),(Uint8)(length*0.5f),128,255);
			window.setColor(color);
			window.drawRectCentered(posX,posY,length,length);
		}

		/*****************************************/
		/******** VISUAL CLOCK EXAMPLE... ********/
		/*****************************************/
		//Configuration...
		int numberRadius=20;
		int numSmallCircles=12;
		//Resize the clock object...
		if(window.mouseButtonPressed(SDLButton::LEFT)||window.keyPressed(SDLKey::KP_PLUS))
			clockRadius+=25;
		if(window.mouseButtonPressed(SDLButton::RIGHT)||window.keyPressed(SDLKey::KP_MINUS))
			clockRadius-=25;
		//Draw the clock on screen...
		int bigRadius=clockRadius;
		window.setColor(255,255,255,255);
		window.drawCircle(posX,posY,bigRadius);
		//Working variable...
		int arrowSize=0;
		//Draw a certain number of circles on screen...
		for(int i=0;i<numSmallCircles;++i){
			float angleDeg=i*(360.0f/numSmallCircles);
			float rad=angleDeg*DEG2RAD;
			int cx=posX+(int)(bigRadius*cos(rad));
			int cy=posY+(int)(bigRadius*sin(rad));
			window.setColor(SDLColor{(Uint8)(i*20),(Uint8)(255-i*15),200,255});
			window.drawFilledRectCentered(cx,cy,numberRadius*2,numberRadius*2);
			arrowSize=(int)(bigRadius*sin(rad))*2;
		}

		/*****************************************/
		/***** ROTATING TRIANGLE ON SCREEN... ****/
		/*****************************************/
		//Create a triangle rotating in the center of the clock...
		window.setColor(SDLColor{255,128,0,255});//Orange...
		window.drawTriangleCentered(posX,posY,50,arrowSize,angle);
		//Increments the angle on each FPS...
		angle+=1.0f;
		if(angle>=360)angle=0;

		/*****************************************/
		/****** DRAW AN ELLIPSE ON SCREEN... *****/
		/*****************************************/
		window.setColor(SDLColor{128,0,128,255});
		window.drawEllipse(posX,posY-400,100,50);

		/*****************************************/
		/****** DRAW A POLYGON ON SCREEN... ******/
		/*****************************************/
		std::vector<SDLPoint> polygonDots{
			{100,500},
			{140,450},
			{180,480},
			{170,530},
			{120,550}
		};
		window.setColor(SDLColor{0,255,0,255});
		window.drawPolygon(polygonDots);

		/*****************************************/
		/******** DRAW AN ARC ON SCREEN... *******/
		/*****************************************/
		window.setColor(SDLColor{255,0,0,255});
		window.drawArc(maxSize/4,maxSize/4,80,0,180);

		/*****************************************/
		/**** DRAW A LIST OF DOTS ON SCREEN... ***/
		/*****************************************/
		window.setColor(SDLColor{255,255,255,255});
		std::vector<SDLPoint> points{
			{150,50},
			{160,60},
			{170,50},
			{180,60},
			{190,50},
		};
		window.drawPoints(points);

		/*****************************************/
		/**** USING MOUSE FUNCTIONS EXAMPLE... ***/
		/*****************************************/
		//Configuration...
		int cursorSize=15;
		EnumColor cursorColor=EnumColor::Yellow;
		//Get the mouse position...
		SDLPoint mousePos=window.getMousePosition();
		//Draw something in the cursor...
		window.setColor(SDLWindow::getColorFromEnum(cursorColor));
		window.drawFilledRectCentered(mousePos,cursorSize,cursorSize);

		/*****************************************/
		/******* RENDER IMAGES ON SCREEN... ******/
		/*****************************************/
		//Attention!!! You must put an image on the folder to load it later and render it...
		/***********************************/
		/*** RENDER SPRITE1 ON SCREEN... ***/
		/***********************************/
		static SDLPoint spritePos={
			(int)round(window.getCenter().x-SDLWindow::getTextureSize(spriteTex).x*0.5f),
			(int)round(window.getCenter().y-clockRadius-SDLWindow::getTextureSize(spriteTex).y-20)
		};
		if(spriteTex){//Texture was created successfuly...
			if(window.keyDown(SDLKey::O))spritePos.x--;
			if(window.keyDown(SDLKey::P))spritePos.x++;
			if(window.keyDown(SDLKey::Q))spritePos.y--;
			if(window.keyDown(SDLKey::A))spritePos.y++;
			window.renderTexture(spriteTex,spritePos.x,spritePos.y,255,0);
		}
		/***********************************/
		/*** RENDER SPRITE2 ON SCREEN... ***/
		/***********************************/
		window.renderTexture(
			spriteTexFixed,
			window.getCenter().x-SDLWindow::getTextureSize(spriteTex).x*0.5/*x*/,
			window.getCenter().y-clockRadius-SDLWindow::getTextureSize(spriteTex).y-20/*y*/,
			255,0
		);

		/*****************************************/
		/*****************************************/
		/*** END OF SEVERAL TESTING EXAMPLES... **/
		/*****************************************/
		/*****************************************/

		/*****************************************/
		/********** FPS CALCULATIONS... **********/
		/*****************************************/
		/***********************************/
		/***** WRITE FPS ON TERMINAL... ****/
		/***********************************/
		//Configuration...
		bool printFpsOnEachLoop=false;//If true we'll get a lot less FPS as it will waste CPU on each loop writing on the terminal...
		int numberFPSToWrite=100;//The number of FPS that must pass to write the FPS on the terminal...
		//Working variables...
		static int c=0;
		static int maxMs=0;
		//How much time did this FPS (Frame Per Second) last?...
		static Uint64 lastMs=window.getTimeMicroSecs();
		Uint64 duration=window.getTimeMicroSecs()-lastMs;
		//Calculate fps but avoiding crashes or unexpected behavior...
		int fps=0;
		if(duration==0){
			duration=1;//Avoid div/0...
		}else{
			fps=(int)round(1000000.0f/(float)duration);
		}
		//Do we have a new FPS maximum?...
		if(fps>maxMs)maxMs=fps;
		//Increment FPS counter to write the FPS on terminal only once per x times, to be faster...
		c++;
		//Write...
		if(printFpsOnEachLoop || c==numberFPSToWrite){
			std::cout<<"FPS: "<<fps<<" (Max: "<<maxMs<<")"<<std::endl;
			c=0;
		}
		//Store the last time...
		lastMs=window.getTimeMicroSecs();
		/***********************************/
		/****** LIMIT THE GAME FPS... ******/
		/***********************************/
		//Limit FPS...
		int msLeftToFPSMinimum=(int)round(1000.0f/numberFPS);
		int howMuchMsLeft=msLeftToFPSMinimum-((int)round(duration/1000.0f));
		if(howMuchMsLeft<0){
			howMuchMsLeft=0;
		}
		//Make the game pause for x ms to keep the FPS low (60 FPS instead of 1000 FPS) and save CPU...
		window.pause(howMuchMsLeft);

		/***********************************/
		/****** RENDER THIS WINDOW... ******/
		/***********************************/
		window.render();
	}

	/***********************************************/
	/************ DESTROY THE TEXTURES... **********/
	/***********************************************/
	if(spriteTex)window.destroyTexture(spriteTex);
	if(spriteTexFixed)window.destroyTexture(spriteTex);
}

/***********************************************/
/***********************************************/
/***** END OF STATIC DEMO - TEST IT OUT... *****/
/***********************************************/
/***********************************************/

#endif//MINIGFX_H_INCLUDED...
