#include "test.hpp"

TEST(array, array_init)
{
    array_t* x = array_init(sizeof(double), 2);
    EXPECT_EQ(array_get_rows(x), 2);
    EXPECT_EQ(ARRAY_GET(x, 0, double), 0);
    EXPECT_EQ(ARRAY_GET(x, 0, double), 0);
    array_free(x);
}

TEST(array, array_move)
{
    array_t* x = array_init(sizeof(double), 10);
    ARRAY_GET(x, 0, double) = 1;
    ARRAY_GET(x, 1, double) = 2;
    ARRAY_GET(x, 2, double) = 3;
    ARRAY_GET(x, 3, double) = 4;
    ARRAY_GET(x, 4, double) = 5;
    ARRAY_GET(x, 5, double) = 6;
    ARRAY_GET(x, 6, double) = 7;
    ARRAY_GET(x, 7, double) = 8;
    ARRAY_GET(x, 8, double) = 9;
    ARRAY_GET(x, 9, double) = 10;

    array_t y = array_move(x, 1);
    EXPECT_EQ(array_get_rows(&y), 9);

    EXPECT_EQ(ARRAY_GET(&y, 0, double), 2);
    EXPECT_EQ(ARRAY_GET(&y, 1, double), 3);
    EXPECT_EQ(ARRAY_GET(&y, 2, double), 4);
    EXPECT_EQ(ARRAY_GET(&y, 3, double), 5);
    EXPECT_EQ(ARRAY_GET(&y, 4, double), 6);
    EXPECT_EQ(ARRAY_GET(&y, 5, double), 7);
    EXPECT_EQ(ARRAY_GET(&y, 6, double), 8);
    EXPECT_EQ(ARRAY_GET(&y, 7, double), 9);
    EXPECT_EQ(ARRAY_GET(&y, 8, double), 10);
    
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

TEST(array, array_set_with_get)
{
    array_t* x  = array_init(sizeof(double), 2);

    ARRAY_GET(x, 0, double) = 1;
    ARRAY_GET(x, 1, double) = 2;

    EXPECT_EQ(ARRAY_GET(x, 0, double), 1);
    EXPECT_EQ(ARRAY_GET(x, 1, double), 2);

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

TEST(array, array_2d_set_with_get)
{
    array_2d_t* x = array_2d_init(sizeof(double), 2, 2);

    ARRAY_2D_GET(x, 0, 0, double) = 1;
    ARRAY_2D_GET(x, 0, 1, double) = 2;
    ARRAY_2D_GET(x, 1, 0, double) = 3;
    ARRAY_2D_GET(x, 1, 1, double) = 4;

    EXPECT_EQ(ARRAY_2D_GET(x, 0, 0, double), 1);
    EXPECT_EQ(ARRAY_2D_GET(x, 0, 1, double), 2);
    EXPECT_EQ(ARRAY_2D_GET(x, 1, 0, double), 3);
    EXPECT_EQ(ARRAY_2D_GET(x, 1, 1, double), 4);

    array_2d_free(x);
}