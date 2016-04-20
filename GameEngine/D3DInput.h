#pragma once

#include<dinput.h>
#include"InputInterface.h"
#include"Defines.h"


class MyKeyboard : public MyDeviceInterface
{
   public:
      MyKeyboard(LPDIRECTINPUT8 input, HWND hwnd);
      ~MyKeyboard() { Shutdown(); }

      bool UpdateDevice();

      int ButtonUp(unsigned int key);
      int ButtonDown(unsigned int key);

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

      bool UpdateDevice();

      int ButtonUp(unsigned int key);
      int ButtonDown(unsigned int key);

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

      bool Initialize();
      bool UpdateDevices();
      
      int IsKeyUp(unsigned int key);
      int IsKeyDown(unsigned int key);

      int MouseButtonUp(unsigned int button);
      int MouseButtonDown(unsigned int button);

      POINT GetMousePos();
      long GetMouseWheelPos();

      void Shutdown();

   protected:
      LPDIRECTINPUT8 m_system;

      MyKeyboard *m_keyboard;
      MyMouse *m_mouse;
};

bool CreateDIInput(MyInputInterface **pObj, HWND hwnd, HINSTANCE hInst, bool exclusive);
