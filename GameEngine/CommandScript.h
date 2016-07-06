#pragma once

#define MAX_COMMAND_SIZE   32
#define MAX_LINE_SIZE      3072
#define MAX_PARAM_SIZE     2048


struct myVector_xyz
{
   myVector_xyz() : x(0), y(0), z(0) {}
   float x, y, z;
};
//命令脚本
class MyCommandScript
{
   public:
      MyCommandScript();
      ~MyCommandScript();
      //加载脚本文件
      bool LoadScriptFile(char *filename);
	  //读取命令
      void ParseCommand(char *destCommand);
	  //读取String类型值
      void ParseStringParam(char *destString);
	  //读取Bool类型值
      bool ParseBoolParam();
	  //读取Int类型值
      int ParseIntParam();
	  //读取Float类型值
      float ParseFloatParam();
	  //释放资源
      void Shutdown();
	  //移动开始部分
      void MoveToStart();
	  //移动到下一行
      void MoveToNextLine();
	  //返回当前行数
      int GetCurrentLineNum();
	  //获取总行数
      int GetTotalLines();
	  //是否是注释
      bool IsLineComment();

   private:
      int totalScriptLines;
      int currentLine;
      int currentLineChar;
      char **m_script;
};
