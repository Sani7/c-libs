#include "test.hpp"

TEST(array, array_init)
{
    array_t* x = array_init(sizeof(double), 2);
    EXPECT_EQ(array_get_rows(x), 2);
    EXPECT_EQ(ARRAY_GET(x, 0, double), 0);
    EXPECT_EQ(ARRAY_GET(x, 0, double), 0);
    array_free(x);
}

TEST(array, Get_Set_array)
{
    array_t* x  = array_init(sizeof(double), 2);

    double _val = 1;
    array_set(x, 0, &_val);
    _val = 2;
    array_set(x, 1, &_val);
    EXPECT_EQ(ARRAY_GET(x, 0, double), 1);
    EXPECT_EQ(ARRAY_GET(x, 1, double), 2);

    testing::internal::CaptureStderr();
    _val = 3;
    array_set(x, 2, &_val);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "array_set: index out of bounds: 2 > 2\n");

    testing::internal::CaptureStderr();
    array_get(x, 2);
    output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "array_get: index out of bounds: 2 > 2\n");

    array_free(x);
}

TEST(array, array_2d_init)
{
    array_2d_t* x = array_2d_init(sizeof(double), 2, 2);
    EXPECT_EQ(array_2d_get_rows(x), 2);
    EXPECT_EQ(array_2d_get_cols(x), 2);
    EXPECT_EQ(ARRAY_2D_GET(x, 0, 0, double), 0);
    EXPECT_EQ(ARRAY_2D_GET(x, 0, 0, double), 0);
    EXPECT_EQ(ARRAY_2D_GET(x, 0, 0, double), 0);
    EXPECT_EQ(ARRAY_2D_GET(x, 0, 0, double), 0);
    array_2d_free(x);
}

TEST(array, Set_Get_array_2d)
{
    array_2d_t* x = array_2d_init(sizeof(double), 2, 2);

    double _val = 1;
    array_2d_set(x, 0, 0, &_val);
    _val = 2;
    array_2d_set(x, 0, 1, &_val);
    _val = 3;
    array_2d_set(x, 1, 0, &_val);
    _val = 4;
    array_2d_set(x, 1, 1, &_val);

    testing::internal::CaptureStderr();
    array_2d_set(x, 2, 0, &_val);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "array_2d_set: row index out of bounds: 2 > 2\n");

    testing::internal::CaptureStderr();
    array_2d_set(x, 0, 2, &_val);
    output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "array_2d_set: col index out of bounds: 2 > 2\n");

    EXPECT_EQ(ARRAY_2D_GET(x, 0, 0, double), 1);
    EXPECT_EQ(ARRAY_2D_GET(x, 0, 1, double), 2);
    EXPECT_EQ(ARRAY_2D_GET(x, 1, 0, double), 3);
    EXPECT_EQ(ARRAY_2D_GET(x, 1, 1, double), 4);

    testing::internal::CaptureStderr();
    array_2d_get(x, 2, 0);
    output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "array_2d_get: row index out of bounds: 2 > 2\n");

    testing::internal::CaptureStderr();
    array_2d_get(x, 0, 2);
    output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "array_2d_get: col index out of bounds: 2 > 2\n");

    array_2d_free(x);
}
