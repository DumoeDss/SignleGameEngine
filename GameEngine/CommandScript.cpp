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


void MyCommandScript::MoveToStart()
{
   currentLine = 0;
   currentLineChar = 0;
}


void MyCommandScript::MoveToNextLine()
{
   currentLine++;
   currentLineChar = 0;
}


int MyCommandScript::GetCurrentLineNum()
{
   return currentLine;
}


int MyCommandScript::GetTotalLines()
{
   return totalScriptLines;
}


bool MyCommandScript::IsLineComment()
{
   if(m_script[currentLine][0] == '#') return true;
   return false;
}


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