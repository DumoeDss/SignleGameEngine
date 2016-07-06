#pragma once

#include "Defines.h"
#include <vector>
struct myGUIControl
{
	myGUIControl() {
		m_type = 0;
		m_id = 0;
		m_color = 0;
		m_listID = 0;
		m_xPos = 0;
		m_yPos = 0;
		m_width = 0;
		m_height = 0;
		m_text = 0;
		m_upTex = 0;
		m_downTex = 0;
		m_overTex = 0;
	}
	//����
   int m_type;
   //����
   int m_id;
   //��ɫ���������壩
   unsigned long m_color;
   //�б�����
   int m_listID;
   //λ��
   float m_xPos, m_yPos;
   //��С
   float m_width, m_height;
   //��ͼ�ļ�
   char *m_text;
   //������ͼ
   int m_upTex, m_downTex, m_overTex;
};


class MyGUISystem
{
   public:
	   /*MyGUISystem():m_controls(0),m_totalControls(0),m_backDropID(-1){}*/
	   MyGUISystem() : m_backDropID(-1) {}
      ~MyGUISystem() { Shutdown(); }
	  //��ӿؼ�
	  int AddControls();
	  //��ӱ���
      bool AddBackdrop(int texID, int staticID);
	  //��Ӿ�̬�ı�
      bool AddStaticText(int id, char *text, int x, int y, unsigned long color, int fontID);
	  //��Ӱ�ť
      bool AddButton(int id, int x, int y, int width, int height, int upID, int overID, int downID, unsigned int staticID);
	  //ɾ����̬�ı�
	  bool DelStaticText(int id);
	  //ɾ����ť
	  bool DelButton(int id);

	  //�ͷ���Դ
      void Shutdown();
	  //�����ؼ�
      myGUIControl *GetGUIControl(int id)
      {
       /*  if(id < 0 || id >= m_totalControls) 
			 return NULL;
         return &m_controls[id];*/

		 if (id < 0 || id >= m_controls.size())
			 return NULL;
		 return &m_controls.at(id);
      }
	  //�ؼ�����
      int GetTotalControls() { 
		 /* return m_totalControls;*/
		  return m_controls.size();
	  }
	  //����
      myGUIControl *GetBackDrop() 
	  { 
		/*  if(m_backDropID >= 0 && m_totalControls)
			  return &m_controls[m_backDropID];*/
		  if (m_backDropID >= 0 && m_controls.size())
			  return &m_controls[m_backDropID];

		  return NULL; 
	  }

   private:
      //myGUIControl *m_controls;
	  std::vector<myGUIControl> m_controls;
      //int m_totalControls;
      int m_backDropID;
};

