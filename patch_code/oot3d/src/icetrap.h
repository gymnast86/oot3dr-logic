#ifndef _ICETRAP_H_
#define _ICETRAP_H_

#include "z3D/z3D.h"

void IceTrap_Push(u32 key);
void IceTrap_Give(void);
u32 IceTrap_IsPending(void);
void IceTrap_Update(void);

#endif //_ICETRAP_H_
