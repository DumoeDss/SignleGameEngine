#pragma once

#define MAX_COMMAND_SIZE   32
#define MAX_LINE_SIZE      3072
#define MAX_PARAM_SIZE     2048


struct myVector_xyz
{
   myVector_xyz() : x(0), y(0), z(0) {}
   float x, y, z;
};

class MyCommandScript
{
   public:
      MyCommandScript();
      ~MyCommandScript();
      
      bool LoadScriptFile(char *filename);
      void ParseCommand(char *destCommand);
      void ParseStringParam(char *destString);
      bool ParseBoolParam();
      int ParseIntParam();
      float ParseFloatParam();
      void Shutdown();

      void MoveToStart();
      void MoveToNextLine();
      int GetCurrentLineNum();
      int GetTotalLines();
      bool IsLineComment();

   private:
      int totalScriptLines;
      int currentLine;
      int currentLineChar;
      char **m_script;
};
