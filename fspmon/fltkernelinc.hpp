#ifndef _FLTKERNEL_INC_HPP_
#define _FLTKERNEL_INC_HPP_

#ifdef TESTS
//#define WIN32_NO_STATUS
//#include <Windows.h>
//#undef WIN32_NO_STATUS
//#include <ntstatus.h>
//#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#include "fltKernel.h"
#else
#include <fltKernel.h>
#endif // TESTS

#endif // _FLTKERNEL_INC_HPP_