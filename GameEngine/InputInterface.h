#pragma once

class MyInputInterface
{
   public:
      MyInputInterface(){}
      virtual ~MyInputInterface(){}

      virtual bool Initialize() = 0;
      virtual bool UpdateDevices() = 0;

      virtual int IsKeyUp(unsigned int key) = 0;
      virtual int IsKeyDown(unsigned int key) = 0;

      virtual int MouseButtonUp(unsigned int button) = 0;
      virtual int MouseButtonDown(unsigned int button) = 0;
      virtual POINT GetMousePos() = 0;
      virtual long GetMouseWheelPos() = 0;

      virtual void Shutdown() = 0;
};


class MyDeviceInterface
{
   public:
      MyDeviceInterface() {}
      virtual ~MyDeviceInterface(){}

      virtual bool UpdateDevice() = 0;

      virtual int ButtonUp(unsigned int key) = 0;
      virtual int ButtonDown(unsigned int key) = 0;
	  
      virtual POINT GetPosition() = 0;
      virtual POINT GetZPosition() = 0;

      virtual void Shutdown() = 0;
};
