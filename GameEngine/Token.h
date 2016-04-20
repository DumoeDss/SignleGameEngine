#pragma once


class MyToken
{
   public:
      MyToken() : m_length(0), m_startIndex(0), m_endIndex(0), m_data(0) {}
      ~MyToken() { Shutdown(); }

      void Reset(){ m_startIndex = m_endIndex = 0; }

      void SetTokenStream(char *data);

      bool GetNextToken(char *buffer);
      bool GetNextToken(char *token, char *buffer);

      bool MoveToNextLine(char *buffer);

      void Shutdown();

   private:
      int m_length;
      int m_startIndex, m_endIndex;
      char *m_data;
};

