#include "matrix.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <utility>

TEST(MatrixLifecycleTest, DefaultConstructorCreatesEmptyMatrix) {
    Matrix m;

    EXPECT_EQ(m.rows(), 0);
    EXPECT_EQ(m.cols(), 0);
    EXPECT_THROW(m.get(0, 0), std::out_of_range);
}

TEST(MatrixLifecycleTest, ParameterizedConstructorInitializesElements) {
    Matrix m(2, 3, 4.5);

    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 3);

    for (std::size_t r = 0; r < m.rows(); ++r) {
        for (std::size_t c = 0; c < m.cols(); ++c) {
            EXPECT_DOUBLE_EQ(m.get(r, c), 4.5);
        }
    }
}

TEST(MatrixLifecycleTest, ZeroDimensionCreatesEmptyMatrix) {
    Matrix m1(0, 5, 1.0);

    EXPECT_EQ(m1.rows(), 0);
    EXPECT_EQ(m1.cols(), 0);

    Matrix m2(5, 0, 1.0);

    EXPECT_EQ(m2.rows(), 0);
    EXPECT_EQ(m2.cols(), 0);
}

TEST(MatrixAccessTest, SetAndGetModifyCorrectCell) {
    Matrix m(2, 2, 0.0);

    m.set(0, 0, 1.5);
    m.set(0, 1, -2.0);
    m.set(1, 0, 3.25);
    m.set(1, 1, 7.0);

    EXPECT_DOUBLE_EQ(m.get(0, 0), 1.5);
    EXPECT_DOUBLE_EQ(m.get(0, 1), -2.0);
    EXPECT_DOUBLE_EQ(m.get(1, 0), 3.25);
    EXPECT_DOUBLE_EQ(m.get(1, 1), 7.0);
}

TEST(MatrixAccessTest, OutOfRangeThrowsException) {
    Matrix m(2, 3, 1.0);

    EXPECT_THROW(m.get(2, 0), std::out_of_range);
    EXPECT_THROW(m.get(0, 3), std::out_of_range);

    EXPECT_THROW(m.set(2, 2, 5.0), std::out_of_range);
    EXPECT_THROW(m.set(1, 3, 5.0), std::out_of_range);
}

TEST(MatrixRuleOfFiveTest, CopyConstructorPerformsDeepCopy) {
    Matrix original(2, 2, 1.0);
    Matrix copy(original);

    copy.set(0, 0, 99.0);

    EXPECT_DOUBLE_EQ(original.get(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(copy.get(0, 0), 99.0);
}

TEST(MatrixRuleOfFiveTest, MoveConstructorTransfersOwnershipAndNullifiesSource) {
    Matrix original(2, 3, 5.0);
    original.set(1, 2, 42.0);

    Matrix moved(std::move(original));

    EXPECT_EQ(moved.rows(), 2);
    EXPECT_EQ(moved.cols(), 3);
    EXPECT_DOUBLE_EQ(moved.get(1, 2), 42.0);

    EXPECT_EQ(original.rows(), 0);
    EXPECT_EQ(original.cols(), 0);
    EXPECT_THROW(original.get(0, 0), std::out_of_range);
}

TEST(MatrixRuleOfFiveTest, CopyAssignmentReplacesDataSafely) {
    Matrix a(2, 2, 1.0);
    Matrix b(3, 1, 7.0);

    a = b;
    b.set(0, 0, -100.0);

    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 1);

    EXPECT_DOUBLE_EQ(a.get(0, 0), 7.0);
    EXPECT_DOUBLE_EQ(b.get(0, 0), -100.0);
}

TEST(MatrixRuleOfFiveTest, MoveAssignmentTransfersData) {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 3, 9.0);

    a = std::move(b);

    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_DOUBLE_EQ(a.get(1, 2), 9.0);

    EXPECT_EQ(b.rows(), 0);
    EXPECT_EQ(b.cols(), 0);
}

TEST(MatrixRuleOfFiveTest, SelfAssignmentPreservesObject) {
    Matrix a(2, 2, 3.0);
    a.set(0, 1, 8.0);

    a = a;

    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);

    EXPECT_DOUBLE_EQ(a.get(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(a.get(0, 1), 8.0);
}

TEST(MatrixOperationsTest, AdditionWorksAndValidatesDimensions) {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);
    a.add(b);

    for (std::size_t r = 0; r < 2; ++r) {
        for (std::size_t c = 0; c < 2; ++c) {
            EXPECT_DOUBLE_EQ(a.get(r, c), 3.0);
        }
    }

    Matrix wrong_size(2, 3, 1.0);
    EXPECT_THROW(a.add(wrong_size), std::invalid_argument);
}

TEST(MatrixOperationsTest, MultiplicationWorksForValidDimensions) {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);
    a.mul(b);

    EXPECT_DOUBLE_EQ(a.get(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 4.0);

    Matrix rect1(2, 3, 1.0);
    Matrix rect2(3, 2, 2.0);
    rect1.mul(rect2);

    EXPECT_EQ(rect1.rows(), 2);
    EXPECT_EQ(rect1.cols(), 2);
    EXPECT_DOUBLE_EQ(rect1.get(0, 0), 6.0);

    Matrix incompatible(3, 2, 1.0);
    EXPECT_THROW(rect1.mul(incompatible), std::invalid_argument);
}

TEST(MatrixOperationsTest, PrintOutputsExpectedFormat) {
    Matrix m(2, 2, 1.0);
    m.set(0, 1, 2.0);
    m.set(1, 0, 3.0);
    m.set(1, 1, 4.0);

    std::ostringstream oss;
    m.print(oss);

    EXPECT_EQ(oss.str(), "[[1, 2], [3, 4]]\n");
}

TEST(MatrixIsSymmetricTest, DetectingSymmetricAndAsymmetricMatrices) {
    // [[1, 2], [2, 1]] -> true
    Matrix sym(2, 2, 0.0);
    sym.set(0, 0, 1.0);
    sym.set(0, 1, 2.0);
    sym.set(1, 0, 2.0);
    sym.set(1, 1, 1.0);
    EXPECT_TRUE(sym.is_symmetric());

    // [[1, 2], [3, 4]] -> false
    Matrix asym(2, 2, 0.0);
    asym.set(0, 0, 1.0);
    asym.set(0, 1, 2.0);
    asym.set(1, 0, 3.0);
    asym.set(1, 1, 4.0);
    EXPECT_FALSE(asym.is_symmetric());
}

TEST(MatrixIsSymmetricTest, HandlingEdgeCases) {
    Matrix rect(2, 3, 1.0);
    EXPECT_FALSE(rect.is_symmetric());

    Matrix single(1, 1, 42.0);
    EXPECT_TRUE(single.is_symmetric());

    Matrix empty;
    EXPECT_TRUE(empty.is_symmetric());
}
