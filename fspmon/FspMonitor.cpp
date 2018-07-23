#include "FspMonitor.hpp"
#include "Singleton.hpp"

_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::FspmInitialize(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    PAGED_CODE();
    return SMLib::Singleton<FSP::FspMonitor>::Instance().Initialize(DriverObject, RegistryPath);
}


_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::FspmUnload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
)
{
    PAGED_CODE();
    return SMLib::Singleton<FSP::FspMonitor>::Instance().Unload(Flags);
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
    return SMLib::Singleton<FSP::FspMonitor>::Instance().InstanceSetup(
        FltObjects,
        Flags,
        VolumeDeviceType,
        VolumeFilesystemType
    );
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
    return SMLib::Singleton<FSP::FspMonitor>::Instance().InstanceQueryTeardown(
        FltObjects,
        Flags
    );
}

_Use_decl_annotations_
VOID
FLTAPI
FSP::FspMonitor::FspmInstanceTeardownStart(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
)
{
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
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);
    PAGED_CODE();
    return STATUS_SUCCESS;
}


_Use_decl_annotations_
NTSTATUS
FLTAPI
FSP::FspMonitor::Unload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
)
{
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();
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
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    UNREFERENCED_PARAMETER(VolumeDeviceType);
    UNREFERENCED_PARAMETER(VolumeFilesystemType);
    PAGED_CODE();
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
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();
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
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Reason);
}

_Use_decl_annotations_
VOID
FLTAPI
FSP::FspMonitor::InstanceTeardownComplete(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
)
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Reason);
}
