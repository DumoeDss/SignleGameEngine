#include<string.h>
#include"Token.h"


bool isValidIdentifier(char c)
{
   if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
      (c >= 'A' && c <= 'Z') || c == '_' || c =='"' || c =='/' ||
      c =='(' || c ==')' || c =='-' || c=='.')
      return true;
      
   return false;
}


void MyToken::SetTokenStream(char *data)
{
   Shutdown();

   m_length = strlen(data);
   m_data = new char[(m_length + 1) * sizeof(char)];
   strcpy(m_data, data);
   m_data[m_length] = '\0';
}


bool MyToken::GetNextToken(char *buffer)
{
   bool inString = false;
   m_startIndex = m_endIndex;

   if(buffer) buffer[0] = '\0';

   while(m_startIndex < m_length && ((m_data[m_startIndex] == ' ' || m_data[m_startIndex] == '\t') ||
         inString))
      {
         if(m_data[m_startIndex] == '"') inString = !inString;
         m_startIndex++;
      }

   m_endIndex = m_startIndex + 1;

   if(m_startIndex < m_length)
      {
         bool valid = true;

         if(isValidIdentifier(m_data[m_startIndex]))
            while(isValidIdentifier(m_data[m_endIndex]) || m_data[m_endIndex] == '.') m_endIndex++;
         else valid = false;

         if(buffer != NULL)
            {
               if(valid)
                  {
                     strncpy(buffer, m_data + m_startIndex, m_endIndex - m_startIndex);
                     buffer[m_endIndex - m_startIndex] = '\0';
                     
                     if(strcmp(buffer, "\n") == 0) buffer[0] = '\0';
                  }
               else buffer[0] = '\0';
            }

         return true;
      }

   return false;
}


bool MyToken::GetNextToken(char *token, char *buffer)
{
   char tok[256];

   while(GetNextToken(tok))
      if(_stricmp(tok, token) == 0) return GetNextToken(buffer);

	return false;
}


bool MyToken::MoveToNextLine(char *buffer)
{
   if(m_startIndex < m_length && m_endIndex < m_length)
      {
         m_startIndex = m_endIndex;

         while(m_endIndex < m_length && (m_data[m_endIndex] != '\n' &&
               m_data[m_endIndex] != '\r' && m_data[m_endIndex] != '\0')) m_endIndex++;

         if(m_endIndex - m_startIndex >= 511) return false;

         if(buffer != NULL)
            {
               strncpy(buffer, m_data + m_startIndex, m_endIndex - m_startIndex);
               buffer[m_endIndex - m_startIndex] = '\0';
            }
      }
   else return false;

   return true;
}


void MyToken::Shutdown()
{
   if(m_data) delete[] m_data;
   m_data = NULL;

   m_length = m_startIndex = m_endIndex = 0;
}