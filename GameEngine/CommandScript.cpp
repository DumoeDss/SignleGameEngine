#include"CommandScript.h"
#include<fstream>

using namespace std;


MyCommandScript::MyCommandScript() : totalScriptLines(0), currentLine(0),
                                   currentLineChar(0), m_script(0)
{

}


MyCommandScript::~MyCommandScript()
{
   Shutdown();
}

//加载脚本文件
bool MyCommandScript::LoadScriptFile(char *filename)
{
   ifstream input, input2;
   char tempLine[MAX_LINE_SIZE];
   
   input.open(filename);
   if(!input.is_open()) return false;
   
   Shutdown();

   while(!input.eof())
      {
         input.getline(tempLine, MAX_LINE_SIZE, '\n');
         totalScriptLines++;
      }
   
   input.close();
   
   input2.open(filename);
   if(!input2.is_open()) return false;
   
   m_script = new char*[totalScriptLines];
   
   for(int i = 0; i < totalScriptLines; i++)
      {
         m_script[i] = new char[MAX_LINE_SIZE + 1];
         input2.getline(m_script[i], MAX_LINE_SIZE, '\n');
      }
   
   input2.close();
   return true;
}

//读取命令
void MyCommandScript::ParseCommand(char *destCommand)
{
   int commandSize = 0;

   if(!destCommand) return;
   if(currentLine >= totalScriptLines) return;
   if(currentLineChar >= (int)strlen(m_script[currentLine])) return;

   destCommand[0] = '\0';
   
   if(IsLineComment())
      {
         destCommand[0] = '#';
         destCommand[1] = '\0';
         return;
      }

   while(currentLineChar < (int)strlen(m_script[currentLine]))
      {
         if(m_script[currentLine][currentLineChar] == ' ' ||
            m_script[currentLine][currentLineChar] == '\n')
            break;

         destCommand[commandSize] = m_script[currentLine][currentLineChar];
         commandSize++;
         currentLineChar++;
      }

   currentLineChar++;
   destCommand[commandSize] = '\0';
}

//读取String类型值
void MyCommandScript::ParseStringParam(char *destString)
{

   int paramSize = 0;
   bool endQuoteFound = false;

   if(!destString) return;
   if(currentLine >= totalScriptLines) return;
   if(currentLineChar >= (int)strlen(m_script[currentLine])) return;

   destString[0] = '\0';

   currentLineChar++;

   while(currentLineChar < (int)strlen(m_script[currentLine]))
      {
         if(m_script[currentLine][currentLineChar] == '"')
            {
               endQuoteFound = true;
               break;
            }

         if(m_script[currentLine][currentLineChar] == '\n')
            break;

         destString[paramSize] = m_script[currentLine][currentLineChar];
         paramSize++;
         currentLineChar++;
      }

   if(endQuoteFound) currentLineChar += 2;
   else currentLineChar++;

   destString[paramSize] = '\0';
}

//读取Bool类型值
bool MyCommandScript::ParseBoolParam()
{

   char string[MAX_PARAM_SIZE];
   int paramSize = 0;

   if(currentLine >= totalScriptLines) return 0;
   if(currentLineChar >= (int)strlen(m_script[currentLine])) return 0;

   while(currentLineChar < (int)strlen(m_script[currentLine]))
      {
         if(m_script[currentLine][currentLineChar] == ' ' ||
            m_script[currentLine][currentLineChar] == '\n')
            break;

         string[paramSize] = m_script[currentLine][currentLineChar];
         paramSize++;
         currentLineChar++;
      }

   currentLineChar++;
   string[paramSize] = '\0';

   if(_stricmp(string, "true") == 0) return true;
   return false;
}

//读取Int类型值
int MyCommandScript::ParseIntParam()
{

   char string[MAX_PARAM_SIZE];
   int paramSize = 0;

   if(currentLine >= totalScriptLines) return 0;
   if(currentLineChar >= (int)strlen(m_script[currentLine])) return 0;

   while(currentLineChar < (int)strlen(m_script[currentLine]))
      {
         if(m_script[currentLine][currentLineChar] == ' ' ||
            m_script[currentLine][currentLineChar] == '\n')
            break;

         string[paramSize] = m_script[currentLine][currentLineChar];
         paramSize++;
         currentLineChar++;
      }

   currentLineChar++;
   string[paramSize] = '\0';
   return atoi(string);
}

//读取Float类型值
float MyCommandScript::ParseFloatParam()
{

   char string[MAX_PARAM_SIZE];
   int paramSize = 0;

   if(currentLine >= totalScriptLines) return 0;
   if(currentLineChar >= (int)strlen(m_script[currentLine])) return 0;

   while(currentLineChar < (int)strlen(m_script[currentLine]))
      {
         if(m_script[currentLine][currentLineChar] == ' ' ||
            m_script[currentLine][currentLineChar] == '\n')
            break;

         string[paramSize] = m_script[currentLine][currentLineChar];
         paramSize++;
         currentLineChar++;
      }

   currentLineChar++;
   string[paramSize] = '\0';
   return (float)atof(string);
}

//移动开始部分
void MyCommandScript::MoveToStart()
{
   currentLine = 0;
   currentLineChar = 0;
}

//移动到下一行
void MyCommandScript::MoveToNextLine()
{
   currentLine++;
   currentLineChar = 0;
}

//返回当前行数
int MyCommandScript::GetCurrentLineNum()
{
   return currentLine;
}

//获取总行数
int MyCommandScript::GetTotalLines()
{
   return totalScriptLines;
}

//注释
bool MyCommandScript::IsLineComment()
{
   if(m_script[currentLine][0] == '#') return true;
   return false;
}

//释放对象资源
void MyCommandScript::Shutdown()
{
   if(m_script)
      {
         for(int i = 0; i < totalScriptLines; i++)
            {
               if(m_script[i])
                  {
                     delete[] m_script[i];
                     m_script[i] = 0;
                  }
            }
         
         delete m_script;
         m_script = 0;
      }
 
   totalScriptLines = 0;
   currentLineChar = 0;
   currentLine = 0;
}