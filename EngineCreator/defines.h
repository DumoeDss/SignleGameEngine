#pragma once
//…æ≥˝∂‘œÛ÷∏’Î
#ifndef SAFE_DELETE					
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    
