#pragma once

#include<dinput.h>
#include"InputInterface.h"
#include"Defines.h"


class MyKeyboard : public MyDeviceInterface
{
   public:
      MyKeyboard(LPDIRECTINPUT8 input, HWND hwnd);
      ~MyKeyboard() { Shutdown(); }
	  //�����豸״̬
      bool UpdateDevice();
	  //��������
      int ButtonUp(unsigned int key);
      int ButtonDown(unsigned int key);
	  //��ȡλ��
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
	  //�����豸״̬
      bool UpdateDevice();
	  //��������
      int ButtonUp(unsigned int key);
      int ButtonDown(unsigned int key);
	  //��ȡλ��
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
	  //��ʼ��
      bool InitInput();
	  //�����豸״̬
      bool UpdateDevices();
      //���̰���
      int IsKeyUp(unsigned int key);
      int IsKeyDown(unsigned int key);
	  //��갴��
      int MouseButtonUp(unsigned int button);
      int MouseButtonDown(unsigned int button);
	  //��ȡ���λ��
      POINT GetMousePos();
	  //��ȡ��껬��ֵ
      long GetMouseWheelPos();

      void Shutdown();

   protected:
      LPDIRECTINPUT8 m_system;

      MyKeyboard *m_keyboard;
      MyMouse *m_mouse;
};
//���������������
bool CreateInput(MyInputInterface **pObj, HWND hwnd, HINSTANCE hInst, bool exclusive);
