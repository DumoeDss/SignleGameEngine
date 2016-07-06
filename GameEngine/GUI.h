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
	//类型
   int m_type;
   //索引
   int m_id;
   //颜色（用于字体）
   unsigned long m_color;
   //列表索引
   int m_listID;
   //位置
   float m_xPos, m_yPos;
   //大小
   float m_width, m_height;
   //贴图文件
   char *m_text;
   //按键贴图
   int m_upTex, m_downTex, m_overTex;
};


class MyGUISystem
{
   public:
	   /*MyGUISystem():m_controls(0),m_totalControls(0),m_backDropID(-1){}*/
	   MyGUISystem() : m_backDropID(-1) {}
      ~MyGUISystem() { Shutdown(); }
	  //添加控件
	  int AddControls();
	  //添加背景
      bool AddBackdrop(int texID, int staticID);
	  //添加静态文本
      bool AddStaticText(int id, char *text, int x, int y, unsigned long color, int fontID);
	  //添加按钮
      bool AddButton(int id, int x, int y, int width, int height, int upID, int overID, int downID, unsigned int staticID);
	  //删除静态文本
	  bool DelStaticText(int id);
	  //删除按钮
	  bool DelButton(int id);

	  //释放资源
      void Shutdown();
	  //创建控件
      myGUIControl *GetGUIControl(int id)
      {
       /*  if(id < 0 || id >= m_totalControls) 
			 return NULL;
         return &m_controls[id];*/

		 if (id < 0 || id >= m_controls.size())
			 return NULL;
		 return &m_controls.at(id);
      }
	  //控件总数
      int GetTotalControls() { 
		 /* return m_totalControls;*/
		  return m_controls.size();
	  }
	  //背景
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

