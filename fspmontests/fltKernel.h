#ifndef _FLTKERNEL_H_
#define _FLTKERNEL_H_

#define WIN32_NO_STATUS
#include <Windows.h>
#undef WIN32_NO_STATUS
#include <ntstatus.h>
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

#endif // _FLTKERNEL_H_