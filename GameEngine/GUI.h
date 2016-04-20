#pragma once

#include "Defines.h"

struct myGUIControl
{
   int m_type;
   int m_id;
   unsigned long m_color;

   int m_listID;

   float m_xPos, m_yPos;

   float m_width, m_height;

   char *m_text;

   int m_upTex, m_downTex, m_overTex;
};


class MyGUISystem
{
   public:
	   MyGUISystem():m_controls(0),m_totalControls(0),m_backDropID(-1){}
      ~MyGUISystem() { Shutdown(); }

	  int IncreaseControls();

      bool AddBackdrop(int texID, int staticID);
      bool AddStaticText(int id, char *text, int x, int y, unsigned long color, int fontID);
      bool AddButton(int id, int x, int y, int width, int height, int upID, int overID, int downID, unsigned int staticID);
      void Shutdown();

      myGUIControl *GetGUIControl(int id)
      {
         if(id < 0 || id >= m_totalControls) return NULL;
         return &m_controls[id];
      }
	        
      int GetTotalControls() { return m_totalControls; }

      myGUIControl *GetBackDrop() 
	  { 
		  if(m_backDropID >= 0 && m_totalControls)
			  return &m_controls[m_backDropID];

		  return NULL; 
	  }

   private:
      myGUIControl *m_controls;
      int m_totalControls;
      int m_backDropID;
};

