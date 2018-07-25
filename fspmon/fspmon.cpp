#include <fltKernel.h>
#include "staticclassessupport.h"
#include "Singleton.hpp"
#include "FspMonitor.hpp"

#pragma prefast(disable:__WARNING_ENCODE_MEMBER_FUNCTION_POINTER, "Not valid for kernel mode drivers")

PFLT_FILTER gFilterHandle;
ULONG_PTR OperationStatusCtx = 1;

#define PTDBG_TRACE_ROUTINES            0x00000001
#define PTDBG_TRACE_OPERATION_STATUS    0x00000002

ULONG gTraceFlags = 0;

#define PT_DBG_PRINT( _dbgLevel, _string )          \
    (FlagOn(gTraceFlags,(_dbgLevel)) ?              \
        DbgPrint _string :                          \
        ((int)0))

EXTERN_C_START

DRIVER_INITIALIZE DriverEntry;
NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
);

EXTERN_C_END

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#endif

//
//  operation registration
//

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
    {
        IRP_MJ_CREATE,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_CREATE_NAMED_PIPE,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_CLOSE,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_READ,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_WRITE,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_QUERY_INFORMATION,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_SET_INFORMATION,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_QUERY_EA,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_SET_EA,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_FLUSH_BUFFERS,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_QUERY_VOLUME_INFORMATION,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_SET_VOLUME_INFORMATION,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_DIRECTORY_CONTROL,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_FILE_SYSTEM_CONTROL,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_DEVICE_CONTROL,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_INTERNAL_DEVICE_CONTROL,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_SHUTDOWN,
        0,
        nullptr,
        nullptr
    },                                         //post operations not supported
    {
        IRP_MJ_LOCK_CONTROL,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_CLEANUP,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_CREATE_MAILSLOT,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_QUERY_SECURITY,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_SET_SECURITY,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_QUERY_QUOTA,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_SET_QUOTA,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_PNP,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_ACQUIRE_FOR_SECTION_SYNCHRONIZATION,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_RELEASE_FOR_SECTION_SYNCHRONIZATION,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_ACQUIRE_FOR_MOD_WRITE,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_RELEASE_FOR_MOD_WRITE,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_ACQUIRE_FOR_CC_FLUSH,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_RELEASE_FOR_CC_FLUSH,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_FAST_IO_CHECK_IF_POSSIBLE,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_NETWORK_QUERY_OPEN,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_MDL_READ,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_MDL_READ_COMPLETE,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_PREPARE_MDL_WRITE,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_MDL_WRITE_COMPLETE,
        0,
        nullptr,
        nullptr,
    },
    {
        IRP_MJ_VOLUME_MOUNT,
        0,
        nullptr,
        nullptr
    },
    {
        IRP_MJ_VOLUME_DISMOUNT,
        0,
        nullptr,
        nullptr,
    },
    { IRP_MJ_OPERATION_END }
};

CONST FLT_REGISTRATION FilterRegistration = {

    sizeof( FLT_REGISTRATION ),         //  Size
    FLT_REGISTRATION_VERSION,           //  Version
    0,                                  //  Flags

    nullptr,                               //  Context
    Callbacks,                          //  Operation callbacks

    FSP::FspMonitor::FspmUnload,

    FSP::FspMonitor::FspmInstanceSetup,
    FSP::FspMonitor::FspmInstanceQueryTeardown,
    FSP::FspMonitor::FspmInstanceTeardownStart,
    FSP::FspMonitor::FspmInstanceTeardownComplete,

    nullptr,                               //  GenerateFileName
    nullptr,                               //  GenerateDestinationFileName
    nullptr                                //  NormalizeNameComponent

};

NTSTATUS
DriverEntry (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    CppInitExitDescriptorsList();
    CppCallStaticConstructors(__crtXca, __crtXcz);
    if (!CppWereAllDestructorsRegistered())
    {
        return STATUS_FLT_NOT_INITIALIZED;
    }

    return FSP::FspMonitor::FspmInitialize(DriverObject, RegistryPath);
}
