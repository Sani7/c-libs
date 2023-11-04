#define LOGGER_LEVEL_ALL
#include "test.hpp"

TEST(LOGGER, logger)
{
    testing::internal::CaptureStdout();
    LOG_DEBUG("LOGGER", "Debug message\n");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "[Debug]    [LOGGER]: Debug message\n");

    testing::internal::CaptureStdout();
    LOG_INFO("LOGGER", "Info message\n");
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "[Info]     [LOGGER]: Info message\n");

    testing::internal::CaptureStdout();
    LOG_WARN("LOGGER", "Warning message\n");
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "[Warning]  [LOGGER]: Warning message\n");

    testing::internal::CaptureStdout();
    LOG_CRIT("LOGGER", "Critical message\n");
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "[Critical] [LOGGER]: Critical message\n");

    testing::internal::CaptureStdout();
    LOG_FATAL("LOGGER", "Fatal message\n");
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "[Fatal]    [LOGGER]: Fatal message\n");
}