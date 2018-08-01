#include "FspMonitor.hpp"
#include "Singleton.hpp"
#include "cppmemoryoperators.h"

#include "fspmon_trace.hpp"
#include "FspMonitor.cpp.tmh"

_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::FspmInitialize(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    PAGED_CODE();
    ::InitLogTrace("FSP::FspMonitor::FspmInitialize(0x%p, %wZ)", DriverObject, RegistryPath);

    const auto status = SMLib::Singleton<FSP::FspMonitor>::Instance().Initialize(DriverObject, RegistryPath);

    ::InitLogInfo("Exiting FSP::FspMonitor::FspmInitialize(0x%p, %wZ) with status 0x%x", DriverObject, RegistryPath, status);
    return status;
}


_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::FspmUnload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
)
{
    PAGED_CODE();

    ::UninitLogTrace("FSP::FspMonitor::FspmUnload(0x%x)", Flags);

    const auto status = SMLib::Singleton<FSP::FspMonitor>::Instance().Unload(Flags);

    ::UninitLogInfo("Exiting FSP::FspMonitor::FspmUnload(0x%x) with status 0x%x", Flags, status);
    return status;
}


_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::FspmInstanceSetup(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
)
{
    PAGED_CODE();

    ::FfLogTrace("FSP::FspMonitor::FspmInstanceSetup(0x%p, 0x%x, 0x%x, 0x%x)", FltObjects, Flags, VolumeDeviceType, VolumeFilesystemType);

    const auto status = SMLib::Singleton<FSP::FspMonitor>::Instance().InstanceSetup(
        FltObjects,
        Flags,
        VolumeDeviceType,
        VolumeFilesystemType
    );

    ::FfLogInfo("Exiting FSP::FspMonitor::FspmInstanceSetup(0x%p, 0x%x, 0x%x, 0x%x) with status 0x%x", FltObjects, Flags, VolumeDeviceType, VolumeFilesystemType, status);
    return status;
}

_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::FspmInstanceQueryTeardown(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
)
{
    PAGED_CODE();

    ::FfLogTrace("FSP::FspMonitor::FspmInstanceQueryTeardown(0x%p, 0x%x)", FltObjects, Flags);

    const auto status = SMLib::Singleton<FSP::FspMonitor>::Instance().InstanceQueryTeardown(
        FltObjects,
        Flags
    );

    ::FfLogInfo("Exiting FSP::FspMonitor::FspmInstanceQueryTeardown(0x%p, 0x%x) with status 0x%x", FltObjects, Flags, status);
    return status;
}

_Use_decl_annotations_
VOID
FLTAPI
FSP::FspMonitor::FspmInstanceTeardownStart(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
)
{
    PAGED_CODE();

    ::FfLogTrace("FSP::FspMonitor::FspmInstanceTeardownStart(0x%p, 0x%x)", FltObjects, Reason);

    SMLib::Singleton<FSP::FspMonitor>::Instance().InstanceTeardownStart(
        FltObjects,
        Reason
    );
}

_Use_decl_annotations_
VOID
FLTAPI
FSP::FspMonitor::FspmInstanceTeardownComplete(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
)
{
    PAGED_CODE();

    ::FfLogTrace("FSP::FspMonitor::FspmInstanceTeardownComplete(0x%p, 0x%x)", FltObjects, Reason);

    SMLib::Singleton<FSP::FspMonitor>::Instance().InstanceTeardownComplete(
        FltObjects,
        Reason
    );
}

_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::Initialize(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    PAGED_CODE();

    ::InitLogTrace("FSP::FspMonitor::Initialize(0x%p, 0x%p, %wZ)", this, DriverObject, RegistryPath);

    ::InitLogTrace("::FltRegisterFilter(0x%p, 0x%p, 0x%p)", DriverObject, &FSP::gFilterRegistration, &_Filter);
    auto status = ::FltRegisterFilter(
        DriverObject,
        &FSP::gFilterRegistration,
        &_Filter
    );
    if (!NT_SUCCESS(status))
    {
        ::InitLogCritical("::FltRegisterFilter(0x%p, 0x%p, 0x%p) failed with status 0x%x", DriverObject, &FSP::gFilterRegistration, &_Filter, status);
        return status;
    }

    return STATUS_SUCCESS;
}


_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::Unload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
)
{
    PAGED_CODE();

    ::UninitLogTrace("FSP::FspMonitor::Unload(0x%p, 0x%x)", this, Flags);

    ::UninitLogTrace("::FltUnregisterFilter(0x%p, 0x%p)", this, _Filter);
    ::FltUnregisterFilter(_Filter);

    return STATUS_SUCCESS;
}


_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::InstanceSetup(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
)
{
    PAGED_CODE();

    ::FfLogTrace("FSP::FspMonitor::InstanceSetup(0x%p, 0x%p, 0x%x, 0x%x, 0x%x)", this, FltObjects, Flags, VolumeDeviceType, VolumeFilesystemType);

    return STATUS_SUCCESS;
}

_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::InstanceQueryTeardown(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
)
{
    PAGED_CODE();

    ::FfLogTrace("FSP::FspMonitor::InstanceQueryTeardown(0x%p, 0x%p, 0x%x)", this, FltObjects, Flags);

    return STATUS_SUCCESS;
}

_Use_decl_annotations_
VOID
FLTAPI
FSP::FspMonitor::InstanceTeardownStart(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
)
{
    PAGED_CODE();
 
    ::FfLogTrace("FSP::FspMonitor::InstanceTeardownStart(0x%p, 0x%p, 0x%x)", this, FltObjects, Reason);
}

_Use_decl_annotations_
VOID
FLTAPI
FSP::FspMonitor::InstanceTeardownComplete(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
)
{
    PAGED_CODE();

    ::FfLogTrace("FSP::FspMonitor::InstanceTeardownComplete(0x%p, 0x%p, 0x%x)", this, FltObjects, Reason);
}
