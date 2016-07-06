//#include "GUI.h"
////添加控件
//int MyGUISystem::AddControls()
//{
//	if(!m_controls)
//	{
//		m_controls = new myGUIControl[1];
//		if(!m_controls) return RE_FAIL;
//		memset(&m_controls[0],0,sizeof(myGUIControl));
//	}
//	else
//	{
//		myGUIControl *temp;
//		temp = new myGUIControl[m_totalControls+1];
//		if(!temp) return RE_FAIL;
//		memset(temp,0,sizeof(myGUIControl)*(m_totalControls+1));
//		memcpy(temp,m_controls,sizeof(myGUIControl)*m_totalControls);
//
//		delete[] m_controls;
//		m_controls = temp;
//	}
//	return RE_OK;
//}
////添加背景
//bool MyGUISystem::AddBackdrop(int texID, int sID)
//{
//	if(texID < 0 || sID < 0) return false;
//
//	if(m_backDropID < 0)
//	{
//		if(!AddControls()) return false;
//		m_controls[m_totalControls].m_type = GAME_GUI_BACKDROP;
//		m_controls[m_totalControls].m_upTex = texID;
//		m_controls[m_totalControls].m_listID = sID;
//
//		m_backDropID = m_totalControls;
//
//		m_totalControls++;
//	}
//	else
//	{
//		m_controls[m_backDropID].m_upTex = texID;
//		m_controls[m_backDropID].m_listID = sID;
//	}	
//	return true;
//}
////添加静态文本
//bool MyGUISystem::AddStaticText(int id, char *text, int x, int y, unsigned long color, int fontID)
//{
//	if(!text || fontID < 0) return false;
//
//	if(!AddControls()) return false;
//
//	m_controls[m_totalControls].m_type = GAME_GUI_STATICTEXT;
//	m_controls[m_totalControls].m_id = id;
//	m_controls[m_totalControls].m_color = color;
//	m_controls[m_totalControls].m_xPos = x;
//	m_controls[m_totalControls].m_yPos = y;
//	m_controls[m_totalControls].m_listID = fontID;
//
//	int len = strlen(text);
//	m_controls[m_totalControls].m_text = new char[len+1];
//	if(!m_controls[m_totalControls].m_text) return false;
//	memcpy(m_controls[m_totalControls].m_text, text, len);
//	m_controls[m_totalControls].m_text[len] = '\0';
//
//	m_totalControls++;
//	return true;
//}
////添加按钮
//bool MyGUISystem::AddButton(int id, int x, int y, int width, int height, int upID, int overID, int downID, unsigned int staticID)
//{
//	if(!AddControls()) return false;
//
//	m_controls[m_totalControls].m_type = GAME_GUI_BUTTON;
//	m_controls[m_totalControls].m_id = id;
//	m_controls[m_totalControls].m_xPos = x;
//	m_controls[m_totalControls].m_yPos = y;
//	m_controls[m_totalControls].m_width = width;
//	m_controls[m_totalControls].m_height = height;
//	m_controls[m_totalControls].m_upTex = upID;
//	m_controls[m_totalControls].m_overTex = overID;
//	m_controls[m_totalControls].m_downTex = downID;
//	m_controls[m_totalControls].m_listID = staticID;
//
//	m_totalControls++;
//
//	return true;
//}
////删除静态文本
//bool MyGUISystem::DelStaticText(int id) {
//
//}
////删除按钮
//bool MyGUISystem::DelButton(int id) {
//
//}
////释放资源
//void MyGUISystem::Shutdown()
//{
//	for(int s=0; s<m_totalControls; s++)
//	{
//		if(m_controls[s].m_text)
//		{
//			delete[] m_controls[s].m_text;
//			m_controls[s].m_text = NULL;
//		}
//	}
//
//	m_totalControls = 0;
//	if(m_controls) delete[] m_controls;
//	m_controls = NULL;
//}

#include "GUI.h"
//添加控件
int MyGUISystem::AddControls()
{
	m_controls.push_back(myGUIControl());
	return RE_OK;
}
//添加背景
bool MyGUISystem::AddBackdrop(int texID, int sID)
{
	if (texID < 0 || sID < 0) 
		return false;

	if (m_backDropID < 0)
	{
		myGUIControl temp;
		temp.m_type = GAME_GUI_BACKDROP;
		temp.m_upTex = texID;
		temp.m_listID = sID;
		m_controls.push_back(temp);
		m_backDropID = m_controls.size();
	}
	else
	{
		m_controls[m_backDropID].m_upTex = texID;
		m_controls[m_backDropID].m_listID = sID;
	}
	return true;
}
//添加静态文本
bool MyGUISystem::AddStaticText(int id, char *text, int x, int y, unsigned long color, int fontID)
{
	if (!text || fontID < 0) return false;

	myGUIControl temp;
	temp.m_type = GAME_GUI_STATICTEXT;
	temp.m_id = id;
	temp.m_color = color;
	temp.m_xPos = x;
	temp.m_yPos = y;
	temp.m_listID = fontID;

	int len = strlen(text);
	temp.m_text = new char[len + 1];
	if (!temp.m_text) 
		return false;
	memcpy(temp.m_text, text, len);
	temp.m_text[len] = '\0';
	m_controls.push_back(temp);
	return true;
}
//添加按钮
bool MyGUISystem::AddButton(int id, int x, int y, int width, int height, int upID, int overID, int downID, unsigned int staticID)
{
	myGUIControl temp;
	temp.m_type = GAME_GUI_BUTTON;
	temp.m_id = id;
	temp.m_xPos = x;
	temp.m_yPos = y;
	temp.m_width = width;
	temp.m_height = height;
	temp.m_upTex = upID;
	temp.m_overTex = overID;
	temp.m_downTex = downID;
	temp.m_listID = staticID;
	m_controls.push_back(temp);
	return true;
}
//删除静态文本
bool MyGUISystem::DelStaticText(int id) {
	m_controls.erase(m_controls.begin() + id);
	return true;
}
//删除按钮
bool MyGUISystem::DelButton(int id) {
	m_controls.erase(m_controls.begin() + id);
	return true;
}
//释放资源
void MyGUISystem::Shutdown()
{
	for (int s = 0; s<m_controls.size(); s++)
	{
		if (m_controls[s].m_text)
		{
			delete[] m_controls[s].m_text;
			m_controls[s].m_text = NULL;
		}
	}
}