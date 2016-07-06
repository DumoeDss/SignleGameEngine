#pragma once

#define MAX_COMMAND_SIZE   32
#define MAX_LINE_SIZE      3072
#define MAX_PARAM_SIZE     2048


struct myVector_xyz
{
   myVector_xyz() : x(0), y(0), z(0) {}
   float x, y, z;
};
//����ű�
class MyCommandScript
{
   public:
      MyCommandScript();
      ~MyCommandScript();
      //���ؽű��ļ�
      bool LoadScriptFile(char *filename);
	  //��ȡ����
      void ParseCommand(char *destCommand);
	  //��ȡString����ֵ
      void ParseStringParam(char *destString);
	  //��ȡBool����ֵ
      bool ParseBoolParam();
	  //��ȡInt����ֵ
      int ParseIntParam();
	  //��ȡFloat����ֵ
      float ParseFloatParam();
	  //�ͷ���Դ
      void Shutdown();
	  //�ƶ���ʼ����
      void MoveToStart();
	  //�ƶ�����һ��
      void MoveToNextLine();
	  //���ص�ǰ����
      int GetCurrentLineNum();
	  //��ȡ������
      int GetTotalLines();
	  //�Ƿ���ע��
      bool IsLineComment();

   private:
      int totalScriptLines;
      int currentLine;
      int currentLineChar;
      char **m_script;
};
