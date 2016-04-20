#pragma once



enum enVarType { NULL_VAR = 0, INT_VAR, FLOAT_VAR,
                 STRING_VAR, VECTOR_VAR };


struct myVector_xyz
{
   myVector_xyz() : x(0), y(0), z(0) {}
   float x, y, z;
};


class MyVariable
{
   public:
      MyVariable() : type(0), floatVal(0), intVal(0), stringVal(0)
      {
         name[0] = '\0';
         vecVal.x = vecVal.y = vecVal.z = 0;
      }
      ~MyVariable()
      {
         if(stringVal) delete[] stringVal; stringVal = 0;
      }

      void SetData(int t, char* n, void *data);
      void SetData(int t, void *data);

      char *GetName() { return name; }
      int GetType() { return type; }
      int GetDataAsInt() { return intVal; }
      float GetDataAsFloat() { return floatVal; }
      char *GetDataAsString() { return stringVal; }
      myVector_xyz GetDataAsVector() { return vecVal; }

   private:
      char name[128];
      int type;

      int intVal;
      float floatVal;
      char *stringVal;
      myVector_xyz vecVal;
};


class MyPropertyScript
{
   public:
      MyPropertyScript();
      ~MyPropertyScript();

      bool IncreaseVariableList();
      bool LoadScriptFile(char *filename);

   private:
      void ParseNext(char *tempLine, char *varName);

   public:
      bool AddVariable(char *name, int t, void *val);
      bool SetVariable(char *name, int t, void *val);
      int GetVariableAsInt(char *name);
      float GetVariableAsFloat(char *name);
      char *GetVariableAsString(char *name);
      myVector_xyz GetVariableAsVector(char *name);

      void Shutdown();

   private:
      MyVariable *variableList;
      int m_totalVars;
      int currentLineChar;
};
