#ifndef _FSP_MONITOR_HPP_
#define _FSP_MONITOR_HPP_

#include <fltKernel.h>

namespace FSP
{
    class FspMonitor
    {
    public:
        __declspec(code_seg("PAGE"))
        static
        _Must_inspect_result_
        _IRQL_requires_max_(PASSIVE_LEVEL)
        NTSTATUS
        FspmInitialize(
            _In_ PDRIVER_OBJECT DriverObject,
            _In_ PUNICODE_STRING RegistryPath
        );

        __declspec(code_seg("PAGE"))
        static
        _Function_class_(PFLT_FILTER_UNLOAD_CALLBACK)
        _IRQL_requires_max_(APC_LEVEL)
        NTSTATUS
        FLTAPI
        FspmUnload(
            _In_ FLT_FILTER_UNLOAD_FLAGS Flags
        );

        __declspec(code_seg("PAGE"))
        static
        _Function_class_(PFLT_INSTANCE_SETUP_CALLBACK)
        _IRQL_requires_max_(PASSIVE_LEVEL)
        NTSTATUS
        FLTAPI
        FspmInstanceSetup(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
            _In_ DEVICE_TYPE VolumeDeviceType,
            _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
        );

        __declspec(code_seg("PAGE"))
        static
        _Function_class_(PFLT_INSTANCE_QUERY_TEARDOWN_CALLBACK)
        _IRQL_requires_max_(PASSIVE_LEVEL)
        NTSTATUS
        FLTAPI
        FspmInstanceQueryTeardown(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
        );

        __declspec(code_seg("PAGE"))
        static
        _IRQL_requires_max_(PASSIVE_LEVEL)
        VOID
        FLTAPI
        FspmInstanceTeardownStart(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
        );

        __declspec(code_seg("PAGE"))
        static
        _IRQL_requires_max_(PASSIVE_LEVEL)
        VOID
        FLTAPI
        FspmInstanceTeardownComplete(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
        );
    
    public:
        __declspec(code_seg("PAGE"))
        _Must_inspect_result_
        _IRQL_requires_max_(PASSIVE_LEVEL)
        NTSTATUS
        FLTAPI
        Initialize(
            _In_ PDRIVER_OBJECT DriverObject,
            _In_ PUNICODE_STRING RegistryPath
        );

        __declspec(code_seg("PAGE"))
        _Function_class_(PFLT_FILTER_UNLOAD_CALLBACK)
        _IRQL_requires_max_(APC_LEVEL)
        NTSTATUS
        FLTAPI
        Unload(
            _In_ FLT_FILTER_UNLOAD_FLAGS Flags
        );

        __declspec(code_seg("PAGE"))
        _Function_class_(PFLT_INSTANCE_SETUP_CALLBACK)
        _IRQL_requires_max_(PASSIVE_LEVEL)
        NTSTATUS
        FLTAPI
        InstanceSetup(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
            _In_ DEVICE_TYPE VolumeDeviceType,
            _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
        );

        __declspec(code_seg("PAGE"))
        _Function_class_(PFLT_INSTANCE_QUERY_TEARDOWN_CALLBACK)
        _IRQL_requires_max_(PASSIVE_LEVEL)
        NTSTATUS
        FLTAPI
        InstanceQueryTeardown(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
        );

        __declspec(code_seg("PAGE"))
        _IRQL_requires_max_(PASSIVE_LEVEL)
        VOID
        FLTAPI
        InstanceTeardownStart(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
        );

        __declspec(code_seg("PAGE"))
        _IRQL_requires_max_(PASSIVE_LEVEL)
        VOID
        FLTAPI
        InstanceTeardownComplete(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
        );

        _Must_inspect_result_
        PFLT_FILTER
        Filter()
        {
            return _Filter;
        }

    private:
        PFLT_FILTER _Filter;
    };
}

#endif // _FSP_MONITOR_HPP_