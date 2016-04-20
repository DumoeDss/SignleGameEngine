#include"D3DInput.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define MOUSE_BUFF_SIZE 16




bool CreateDIInput(MyInputInterface **pObj, HWND hwnd, HINSTANCE hInst, bool exclusive)
{
   if(!*pObj) *pObj = new MyDirectInputSystem(hwnd, hInst, exclusive);
   else return false;
   
   return true;
}

MyKeyboard::MyKeyboard(LPDIRECTINPUT8 input, HWND hwnd)
{
   if(input->CreateDevice(GUID_SysKeyboard, &m_device, NULL) == DI_OK)
      {
         if(m_device->SetDataFormat(&c_dfDIKeyboard) == DI_OK)
            {
               if(m_device->SetCooperativeLevel(hwnd,
                  DISCL_BACKGROUND |DISCL_NONEXCLUSIVE) == DI_OK)
                  {
                     m_device->Acquire();
                  }
            }
   }

   memset(m_keys, 0, sizeof(m_keys));
}

int MyKeyboard::ButtonUp(unsigned int key)
{
   return (!(m_keys[key] & 0x80) && m_keys[key] != m_oldKeys[key]);
}


int MyKeyboard::ButtonDown(unsigned int key)
{
   return m_keys[key] & 0x80;
}


POINT MyKeyboard::GetPosition()
{
   POINT p = { 0, 0 };
   return p;
}


POINT MyKeyboard::GetZPosition()
{
   POINT p = { 0, 0 };
   return p;
}


bool MyKeyboard::UpdateDevice()
{
   if(m_device)
      {
         memcpy(m_oldKeys, m_keys, sizeof(m_keys));

         if(FAILED(m_device->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
            {
               if(FAILED(m_device->Acquire())) return false;
               if(FAILED(m_device->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
                  return false;
            }
       }

   return true;
}


void MyKeyboard::Shutdown()
{
   if(m_device)
      {
         m_device->Unacquire();
         m_device->Release();
         m_device = NULL;
      }
}


MyMouse::MyMouse(LPDIRECTINPUT8 input, HWND hwnd, bool exclusive)
{
   DWORD flags;

   if(input->CreateDevice(GUID_SysMouse, &m_device, NULL) == DI_OK)
      {
         if(m_device->SetDataFormat(&c_dfDIMouse) == DI_OK)
            {
               if(exclusive) flags = DISCL_BACKGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
               else flags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;

               if(m_device->SetCooperativeLevel(hwnd, flags) == DI_OK)
                  {
                     m_device->Acquire();
                  }
            }
      }
}


int MyMouse::ButtonUp(unsigned int button)
{
   return (!(m_mouseState.rgbButtons[button] & 0x80) &&
           m_mouseState.rgbButtons[button] != m_oldMouseState.rgbButtons[button]);
}


int MyMouse::ButtonDown(unsigned int button)
{
   return m_mouseState.rgbButtons[button] & 0x80;
}


bool MyMouse::UpdateDevice()
{
   if(m_device)
      {
         memcpy(&m_oldMouseState, &m_mouseState, sizeof(m_mouseState));

         if(FAILED(m_device->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
            {
               if(FAILED(m_device->Acquire())) return false;
               if(FAILED(m_device->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
                  return false;
            }

         m_xMPos += m_mouseState.lX;
         m_yMPos += m_mouseState.lY;
         m_zMPos = m_mouseState.lZ;
      }

   return true;
}

POINT MyMouse::GetPosition()
{
   POINT pos;

   pos.x = m_xMPos;
   pos.y = m_yMPos;
   return pos;
}


POINT MyMouse::GetZPosition()
{
   POINT p = { m_zMPos, m_zMPos };
   return p;
}


void MyMouse::Shutdown()
{
   if(m_device)
      {
         m_device->Unacquire();
         m_device->Release();
         m_device = NULL;
      }
}


MyDirectInputSystem::MyDirectInputSystem(HWND hwnd, HINSTANCE hInst, bool exclusive)
{
   m_keyboard = NULL;
   m_mouse = NULL;

   if(DirectInput8Create(hInst, DIRECTINPUT_VERSION,
      IID_IDirectInput8, (void **)&m_system, NULL) == DI_OK)
   {
      m_keyboard = new MyKeyboard(m_system, hwnd);
      m_mouse = new MyMouse(m_system, hwnd, exclusive);
   }
}


MyDirectInputSystem::~MyDirectInputSystem()
{
   Shutdown();
}


bool MyDirectInputSystem::Initialize()
{
   return (m_keyboard && m_mouse);
}


bool MyDirectInputSystem::UpdateDevices()
{
   int hr;

   if(m_mouse) hr = m_mouse->UpdateDevice();
   if(m_keyboard) hr = m_keyboard->UpdateDevice();

   return true;
}


int MyDirectInputSystem::IsKeyUp(unsigned int key)
{
   if(!m_keyboard) return 0;
   return m_keyboard->ButtonUp(key);
}


int MyDirectInputSystem::IsKeyDown(unsigned int key)
{
   if(!m_keyboard) return 0;
   return m_keyboard->ButtonDown(key);
}


int MyDirectInputSystem::MouseButtonUp(unsigned int button)
{
   if(!m_mouse) return 0;
   return m_mouse->ButtonUp(button);
}


int MyDirectInputSystem::MouseButtonDown(unsigned int button)
{
   if(!m_mouse) return 0;
   return m_mouse->ButtonDown(button);
}


POINT MyDirectInputSystem::GetMousePos()
{
   POINT null = {0, 0};
   if(!m_mouse) return null;

   return m_mouse->GetPosition();
}


long MyDirectInputSystem::GetMouseWheelPos()
{
   if(!m_mouse) return 0;

   POINT wheel =  m_mouse->GetZPosition();
   return wheel.y;
}

void MyDirectInputSystem::Shutdown()
{
   if(m_keyboard)
      {
         m_keyboard->Shutdown();
         delete m_keyboard;
         m_keyboard = NULL;
      }

   if(m_mouse)
      {
         m_mouse->Shutdown();
         delete m_mouse;
         m_mouse = NULL;
      }

   if(m_system)
      {
         m_system->Release();
         m_system = NULL;
      }
}