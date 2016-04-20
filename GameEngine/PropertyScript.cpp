#include"PropertyScript.h"
#include<fstream>

using std::ifstream;


int DetermineType(int startIndex, char *buffer)
{
   int numComponents = 0;
   int type = NULL_VAR;
   bool decimalFound = false;
   bool charFound = false;
   int index = startIndex;

   while(index < (int)strlen(buffer))
      {
         if(numComponents == 0) numComponents++;
         if(buffer[index] == ' ') numComponents++;

         if(buffer[index] == '.') decimalFound = true;

         if((buffer[index] >= 'a' && buffer[index] <= 'z') ||
            (buffer[index] >= 'A' && buffer[index] <= 'Z') ||
            buffer[index] == '_') charFound = true;

         index++;
         
      }

   switch(numComponents)
      {
         case 1:
            if(charFound) type = STRING_VAR;
            else type = INT_VAR;

            if(decimalFound == true && charFound == false) type = FLOAT_VAR;
            break;

         case 3:
            if(charFound) type = STRING_VAR;
            else type = VECTOR_VAR;
            break;

         default:

            if(numComponents > 0) type = STRING_VAR;
            break;
      }
   
   return type;
}


void MyVariable::SetData(int t, char *n, void *data)
{
   if(!name) return;

   memcpy(name, n, strlen(n));
   name[strlen(n)] = '\0';
   SetData(t, data);
}


void MyVariable::SetData(int t, void *data)
{
   myVector_xyz *vec = NULL;
   int len = 0;

   switch(t)
      {
         case INT_VAR:
            intVal = (int)data;
            break;

         case FLOAT_VAR:
            floatVal = *(float*)data;
            break;

         case STRING_VAR:
            len = strlen((char*)data);
            stringVal = new char[len + 1];
            memcpy(stringVal, (char*)data, len);
            stringVal[len] = '\0';
            break;

         case VECTOR_VAR:
            vec = (myVector_xyz*)data;
            vecVal.x = vec->x;
            vecVal.y = vec->y;
            vecVal.z = vec->z;
            break;

         default:
            return;
            break;
      };

   type = t;
}


MyPropertyScript::MyPropertyScript() : variableList(NULL),
   m_totalVars(0), currentLineChar(0)
{

}


MyPropertyScript::~MyPropertyScript()
{
   Shutdown();
}


bool MyPropertyScript::IncreaseVariableList()
{
   if(!variableList)
      {
         variableList = new MyVariable[1];
         if(!variableList) return false;
      }
   else
      {
         MyVariable *temp;
         temp = new MyVariable[m_totalVars + 1];
         if(!temp) return false;

         memcpy(temp, variableList,
               sizeof(MyVariable) * m_totalVars);

         delete[] variableList;
         variableList = temp;
      }

   return true;
}


bool MyPropertyScript::LoadScriptFile(char *filename)
{
   int totalScriptLines = 0;
   ifstream input, input2;
   char tempLine[256];
   char varName[128];
   char param[3072];
   int type = 0;

   input.open(filename);
   if(!input.is_open()) return false;
 
   Shutdown();

   while(!input.eof())
      {
         input.getline(tempLine, 256, '\n');
         totalScriptLines++;
      }
   
   input.close();

   input2.open(filename);
   if(!input2.is_open()) return false;

   for(int i = 0; i < totalScriptLines; i++)
      {
         currentLineChar = 0;

         input2.getline(tempLine, 256, '\n');
         tempLine[strlen(tempLine)] = '\0';
         
         if(tempLine[0] != '#')
            {
               ParseNext(tempLine, varName);
               type = DetermineType(currentLineChar, tempLine);

               if(type == INT_VAR)
                  {
                     if(IncreaseVariableList())
                        {
                           ParseNext(tempLine, param);
                           variableList[m_totalVars].SetData(INT_VAR, varName, (void*)atoi(param));
                           m_totalVars++;
                        }
                  }
               else if(type == FLOAT_VAR)
                  {
                     if(IncreaseVariableList())
                        {
                           float fVal = 0;
                           ParseNext(tempLine, param);
                           fVal = (float)atof(param);
                           variableList[m_totalVars].SetData(FLOAT_VAR, varName, &fVal);
                           m_totalVars++;
                        }
                  }
               else if(type == STRING_VAR)
                  {
                     if(IncreaseVariableList())
                        {
                           ParseNext(tempLine, param);
                           variableList[m_totalVars].SetData(STRING_VAR, varName, (void*)param);
                           m_totalVars++;
                        }
                  }
               else if(type == VECTOR_VAR)
                  {
                     if(IncreaseVariableList())
                        {
                           myVector_xyz vecVal;

                           ParseNext(tempLine, param);
                           vecVal.x = (float)atof(param);
                           ParseNext(tempLine, param);
                           vecVal.y = (float)atof(param);
                           ParseNext(tempLine, param);
                           vecVal.z = (float)atof(param);

                           variableList[m_totalVars].SetData(VECTOR_VAR, varName, &vecVal);
                           m_totalVars++;
                        }
                  }
            }
      }

   input2.close();
   return true;
}


void MyPropertyScript::ParseNext(char *tempLine, char *outData)
{
   int commandSize = 0;
   int paramSize = 0;

   if(!tempLine || !outData) return;

   outData[0] = '\0';

   while(currentLineChar < (int)strlen(tempLine))
      {
         if(tempLine[currentLineChar] == ' ' || tempLine[currentLineChar] == '\n')
            break;

         outData[paramSize] = tempLine[currentLineChar];
         paramSize++;
         currentLineChar++;
      }

   outData[paramSize] = '\0';
   currentLineChar++;
}


bool MyPropertyScript::AddVariable(char *name, int t, void *val)
{
   if(!SetVariable(name, t, val))
      {
         if(!IncreaseVariableList()) return false;

         variableList[m_totalVars].SetData(t, name, val);
         m_totalVars++;
      }

   return true;
}


bool MyPropertyScript::SetVariable(char *name, int t, void *val)
{
   for(int i = 0; i < m_totalVars; i++)
      {
         if(_stricmp(variableList[i].GetName(), name) == 0)
            {
               variableList[i].SetData(t, val);
               return true;
            }
      }

   return false;
}


int MyPropertyScript::GetVariableAsInt(char *name)
{
   for(int i = 0; i < m_totalVars; i++)
      {
         if(_stricmp(variableList[i].GetName(), name) == 0)
            return variableList[i].GetDataAsInt();
      }

   return 0;
}


float MyPropertyScript::GetVariableAsFloat(char *name)
{
   for(int i = 0; i < m_totalVars; i++)
      {
         if(_stricmp(variableList[i].GetName(), name) == 0)
            return variableList[i].GetDataAsFloat();
      }

   return 0;
}


char *MyPropertyScript::GetVariableAsString(char *name)
{
   for(int i = 0; i < m_totalVars; i++)
      {
         if(_stricmp(variableList[i].GetName(), name) == 0)
            return variableList[i].GetDataAsString();
      }

   return NULL;
}


myVector_xyz MyPropertyScript::GetVariableAsVector(char *name)
{
   myVector_xyz null;

   for(int i = 0; i < m_totalVars; i++)
      {
         if(_stricmp(variableList[i].GetName(), name) == 0)
            return variableList[i].GetDataAsVector();
      }

   return null;
}


void MyPropertyScript::Shutdown()
{
   if(variableList) delete[] variableList;
   variableList = NULL;
}