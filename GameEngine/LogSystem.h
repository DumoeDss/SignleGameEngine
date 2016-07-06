#pragma once
#include <fstream>
#include <stdarg.h>
#include <ctime>
#include <string>
class MyLogSystem
{
   public:
	   MyLogSystem(std::string filename);
	  //�����־
      bool ClearLog();
	  //д����־�����ǣ�
      bool WriteLog(const char *message, ...);
	  //д����־��׷�ӣ�
      bool AppendLog(const char *message, ...);
      
   protected:
      bool Write(std::ofstream &file, const char *message);
      bool Write(std::ofstream &file, const char *message, va_list &args);

   protected:
      std::ofstream logStream;  
	  std::string m_filename;
};

