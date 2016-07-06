#pragma once

#include<dinput.h>
#include"InputInterface.h"
#include"Defines.h"


class MyKeyboard : public MyDeviceInterface
{
   public:
      MyKeyboard(LPDIRECTINPUT8 input, HWND hwnd);
      ~MyKeyboard() { Shutdown(); }
	  //更新设备状态
      bool UpdateDevice();
	  //按键按下
      int ButtonUp(unsigned int key);
      int ButtonDown(unsigned int key);
	  //获取位置
      POINT GetPosition();	  
      POINT GetZPosition();

      void Shutdown();

      LPDIRECTINPUTDEVICE8 m_device;
      char m_keys[keySize];
      char m_oldKeys[keySize];
};


class MyMouse : public MyDeviceInterface
{
   public:
      MyMouse(LPDIRECTINPUT8 input, HWND hwnd, bool exclusive);
      ~MyMouse() { Shutdown(); }
	  //更新设备状态
      bool UpdateDevice();
	  //按键按下
      int ButtonUp(unsigned int key);
      int ButtonDown(unsigned int key);
	  //获取位置
      POINT GetPosition();
      POINT GetZPosition();

      void Shutdown();

      LPDIRECTINPUTDEVICE8 m_device;
      DIMOUSESTATE m_mouseState;
      DIMOUSESTATE m_oldMouseState;
      bool m_button[3];

      long m_xMPos;
      long m_yMPos;
      long m_zMPos;

      bool m_restrict;
      int m_width;
      int m_height;
};



class MyDirectInputSystem : public MyInputInterface
{
   public:
      MyDirectInputSystem(HWND hwnd, HINSTANCE hInst, bool exclusive);
      ~MyDirectInputSystem();
	  //初始化
      bool InitInput();
	  //更新设备状态
      bool UpdateDevices();
      //键盘按键
      int IsKeyUp(unsigned int key);
      int IsKeyDown(unsigned int key);
	  //鼠标按键
      int MouseButtonUp(unsigned int button);
      int MouseButtonDown(unsigned int button);
	  //获取鼠标位置
      POINT GetMousePos();
	  //获取鼠标滑轮值
      long GetMouseWheelPos();

      void Shutdown();

   protected:
      LPDIRECTINPUT8 m_system;

      MyKeyboard *m_keyboard;
      MyMouse *m_mouse;
};
//创建输入引擎对象
bool CreateInput(MyInputInterface **pObj, HWND hwnd, HINSTANCE hInst, bool exclusive);
