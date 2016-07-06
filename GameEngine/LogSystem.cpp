#include "LogSystem.h"

MyLogSystem::MyLogSystem(std::string filename) {
	m_filename = filename;
}

//�����־
bool MyLogSystem::ClearLog()
{
	const char *filename = m_filename.data();
	logStream.open(filename, std::ios::out);
	if (!Write(logStream, ""))
		return false;
	logStream.close();
	return true;
 
}

//д����־�����ǣ�
bool MyLogSystem::WriteLog(const char *message, ...)
{
	const char *filename = m_filename.data();
	va_list args;
	va_start(args, message);
	logStream.open(filename, std::ios::out);//����
	if (!Write(logStream, message, args))
		return false;
	logStream.close();
	return true;
   
}

////д����־��׷�ӣ�
bool MyLogSystem::AppendLog(const char *message, ...)
{
	const char *filename = m_filename.data();
	va_list args;
	va_start(args, message);
	logStream.open(filename, std::ios::app);//׷��
	if (!Write(logStream, message, args))
		return false;
	logStream.close();
	return true;
}

//д���ļ�
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

//д���ļ����������б�
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