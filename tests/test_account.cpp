#include <gtest/gtest.h>
#include "Account.hpp"

TEST(AccountTest, InitialBalanceIsZero) {
    Account acc;
    EXPECT_EQ(acc.getBalance(), 0.0);
}

TEST(AccountTest, InitialBalanceWithValue) {
    Account acc(500.0);
    EXPECT_EQ(acc.getBalance(), 500.0);
}

TEST(AccountTest, DepositIncreasesBalance) {
    Account acc;
    acc.deposit(100.0);
    EXPECT_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, DepositMultipleTimes) {
    Account acc(100.0);
    acc.deposit(50.0);
    acc.deposit(25.0);
    EXPECT_EQ(acc.getBalance(), 175.0);
}

TEST(AccountTest, DepositZero) {
    Account acc(100.0);
    acc.deposit(0.0);
    EXPECT_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, WithdrawDecreasesBalance) {
    Account acc(200.0);
    acc.withdraw(50.0);
    EXPECT_EQ(acc.getBalance(), 150.0);
}

TEST(AccountTest, WithdrawMultipleTimes) {
    Account acc(500.0);
    acc.withdraw(100.0);
    acc.withdraw(50.0);
    EXPECT_EQ(acc.getBalance(), 350.0);
}

TEST(AccountTest, WithdrawZero) {
    Account acc(200.0);
    acc.withdraw(0.0);
    EXPECT_EQ(acc.getBalance(), 200.0);
}

TEST(AccountTest, WithdrawAll) {
    Account acc(100.0);
    acc.withdraw(100.0);
    EXPECT_EQ(acc.getBalance(), 0.0);
}

TEST(AccountTest, WithdrawMoreThanBalance) {
    Account acc(100.0);
    acc.withdraw(150.0);
    EXPECT_EQ(acc.getBalance(), -50.0);
}

TEST(AccountTest, DepositAndWithdraw) {
    Account acc(100.0);
    acc.deposit(50.0);
    acc.withdraw(30.0);
    EXPECT_EQ(acc.getBalance(), 120.0);
}
