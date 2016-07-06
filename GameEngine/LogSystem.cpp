#include "LogSystem.h"

MyLogSystem::MyLogSystem(std::string filename) {
	m_filename = filename;
}

//清空日志
bool MyLogSystem::ClearLog()
{
	const char *filename = m_filename.data();
	logStream.open(filename, std::ios::out);
	if (!Write(logStream, ""))
		return false;
	logStream.close();
	return true;
 
}

//写入日志（覆盖）
bool MyLogSystem::WriteLog(const char *message, ...)
{
	const char *filename = m_filename.data();
	va_list args;
	va_start(args, message);
	logStream.open(filename, std::ios::out);//覆盖
	if (!Write(logStream, message, args))
		return false;
	logStream.close();
	return true;
   
}

////写入日志（追加）
bool MyLogSystem::AppendLog(const char *message, ...)
{
	const char *filename = m_filename.data();
	va_list args;
	va_start(args, message);
	logStream.open(filename, std::ios::app);//追加
	if (!Write(logStream, message, args))
		return false;
	logStream.close();
	return true;
}

//写入文件
bool MyLogSystem::Write(std::ofstream &file, const char *message)
{	
	char timebuf[1024];
	time_t curtime = time(0);
	tm tim = *localtime(&curtime);
	sprintf_s(timebuf, "%d-%02d-%02d %02d:%02d:%02d",
		tim.tm_year + 1900,
		tim.tm_mon + 1,
		tim.tm_mday,
		tim.tm_hour,
		tim.tm_min,
		tim.tm_sec);
	file << timebuf << " : LOG: " <<  message << std::endl;
    return true;
}

//写入文件（带参数列表）
bool MyLogSystem::Write(std::ofstream &file, const char *message, va_list &args)
{
   char buffer[1024];  
   char timebuf[1024];
   time_t curtime = time(0);
   tm tim = *localtime(&curtime);
   sprintf_s(timebuf, "%d-%02d-%02d %02d:%02d:%02d",
	   tim.tm_year+1900, 
	   tim.tm_mon + 1,
	   tim.tm_mday,
	   tim.tm_hour,
	   tim.tm_min,
	   tim.tm_sec);
   if(!file.is_open()) return false; 
   vsprintf(buffer, message, args);
   file << timebuf << " : " << buffer << std::endl;
   return true;
}