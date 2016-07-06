#pragma once
#include <fstream>
#include <stdarg.h>
#include <ctime>
#include <string>
class MyLogSystem
{
   public:
	   MyLogSystem(std::string filename);
	  //清空日志
      bool ClearLog();
	  //写入日志（覆盖）
      bool WriteLog(const char *message, ...);
	  //写入日志（追加）
      bool AppendLog(const char *message, ...);
      
   protected:
      bool Write(std::ofstream &file, const char *message);
      bool Write(std::ofstream &file, const char *message, va_list &args);

   protected:
      std::ofstream logStream;  
	  std::string m_filename;
};

