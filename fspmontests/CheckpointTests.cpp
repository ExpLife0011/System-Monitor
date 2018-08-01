#include "pch.h"
#include "Checkpoint.hpp"

class CheckpointTests
    : public ::testing::Test
{
public:
    FSP::Checkpoint _Checkpoint;
};

TEST_F(
    CheckpointTests,
    Exhaustive
)
{
    ASSERT_EQ(_Checkpoint.GetState(), FSP::State::uninitialized);
    
    auto status = _Checkpoint.SetCheckpoint(FSP::State::uninitialized);
    ASSERT_TRUE(!NT_SUCCESS(status));
    status = _Checkpoint.SetCheckpoint(FSP::State::initialized);
    ASSERT_TRUE(!NT_SUCCESS(status));
    status = _Checkpoint.SetCheckpoint(FSP::State::uninitializing);
    ASSERT_TRUE(!NT_SUCCESS(status));

    status = _Checkpoint.SetCheckpoint(FSP::State::initializing);
    ASSERT_TRUE(NT_SUCCESS(status));
    ASSERT_EQ(_Checkpoint.GetState(), FSP::State::initializing);

    status = _Checkpoint.SetCheckpoint(FSP::State::initializing);
    ASSERT_TRUE(!NT_SUCCESS(status));
    status = _Checkpoint.SetCheckpoint(FSP::State::uninitializing);
    ASSERT_TRUE(!NT_SUCCESS(status));
    status = _Checkpoint.SetCheckpoint(FSP::State::initialized);
    ASSERT_TRUE(!NT_SUCCESS(status));

    status = _Checkpoint.SetCheckpoint(FSP::State::initialized);
    ASSERT_TRUE(NT_SUCCESS(status));
    ASSERT_EQ(_Checkpoint.GetState(), FSP::State::initialized);

    status = _Checkpoint.SetCheckpoint(FSP::State::initialized);
    ASSERT_TRUE(!NT_SUCCESS(status));
    status = _Checkpoint.SetCheckpoint(FSP::State::initializing);
    ASSERT_TRUE(!NT_SUCCESS(status));
    status = _Checkpoint.SetCheckpoint(FSP::State::uninitialized);
    ASSERT_TRUE(!NT_SUCCESS(status));

    status = _Checkpoint.SetCheckpoint(FSP::State::uninitializing);
    ASSERT_TRUE(NT_SUCCESS(status));
    ASSERT_EQ(_Checkpoint.GetState(), FSP::State::uninitializing);

    status = _Checkpoint.SetCheckpoint(FSP::State::uninitializing);
    ASSERT_TRUE(!NT_SUCCESS(status));
    status = _Checkpoint.SetCheckpoint(FSP::State::initializing);
    ASSERT_TRUE(!NT_SUCCESS(status));
    status = _Checkpoint.SetCheckpoint(FSP::State::initialized);
    ASSERT_TRUE(!NT_SUCCESS(status));

    status = _Checkpoint.SetCheckpoint(FSP::State::uninitialized);
    ASSERT_TRUE(NT_SUCCESS(status));
    ASSERT_EQ(_Checkpoint.GetState(), FSP::State::uninitialized);
}
