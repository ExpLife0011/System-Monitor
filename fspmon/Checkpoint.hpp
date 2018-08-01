#ifndef _CHECKPOINT_HPP_
#define _CHECKPOINT_HPP_

#include "fltkernelinc.hpp"

namespace FSP
{
    enum class State : long
    {
        __firstState,
        uninitializing = __firstState,
        uninitialized,
        initializing,
        initialized,
        __lastState = initialized
    };

    class Checkpoint
    {
    public:
        Checkpoint()
            : _State{ State::uninitialized }
        {}

        State
        GetState()
        {
            auto state = InterlockedCompareExchange(
                reinterpret_cast<volatile LONG*>(&_State),
                0,
                0
            );
            return static_cast<State>(state);
        }

        //_Must_inspect_result_
        //NTSTATUS
        //SetUninitializing()
        //{
        //    return SetState<State::uninitializing, State::initialized>();
        //}

        //_Must_inspect_result_
        //NTSTATUS
        //SetUninitialized()
        //{
        //    return SetState<State::uninitialized, State::uninitializing>();
        //}

        //_Must_inspect_result_
        //NTSTATUS
        //SetInitializing()
        //{
        //    return SetState<State::initializing, State::uninitialized>();
        //}

        //_Must_inspect_result_
        //NTSTATUS
        //SetInitialized()
        //{
        //    return SetState<State::initialized, State::initializing>();
        //}

        _Must_inspect_result_
        NTSTATUS
        SetCheckpoint(
            _In_ State NewState
        )
        {
            auto status = STATUS_UNSUCCESSFUL;
            LONG expected = 0;

            switch (NewState)
            {
            case State::initialized:
                expected = static_cast<LONG>(State::initializing);
                break;
            case State::initializing:
                expected = static_cast<LONG>(State::uninitialized);
                break;
            case State::uninitialized:
                expected = static_cast<LONG>(State::uninitializing);
                break;
            case State::uninitializing:
                expected = static_cast<LONG>(State::initialized);
                break;
            default:
                return STATUS_INVALID_PARAMETER;
            }

            auto old = InterlockedCompareExchange(
                reinterpret_cast<volatile LONG*>(&_State),
                static_cast<LONG>(NewState),
                expected
            );

            if (old != expected)
            {
                return STATUS_INVALID_STATE_TRANSITION;
            }
            return STATUS_SUCCESS;

            return status;
        }

    private:
        __interlocked volatile State _State;
    };
}

#endif // _CHECKPOINT_HPP_