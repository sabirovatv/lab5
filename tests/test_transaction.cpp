#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.hpp"


class IAccount {
public:
    virtual ~IAccount() = default;
    virtual void deposit(double) = 0;
    virtual void withdraw(double) = 0;
};


class MockAccount : public IAccount {
public:
    MOCK_METHOD(void, deposit, (double), (override));
    MOCK_METHOD(void, withdraw, (double), (override));
};

class AdapterAccount : public IAccount {
public:
    AdapterAccount(Account& acc) : account(acc) {}

    void deposit(double amt) override { account.deposit(amt); }
    void withdraw(double amt) override { account.withdraw(amt); }

private:
    Account& account;
};

TEST(TransactionTest, TransferMovesMoney) {
    Account a(100);
    Account b;

    Transaction t;
    t.transfer(a, b, 60.0);

    EXPECT_EQ(a.getBalance(), 40.0);
    EXPECT_EQ(b.getBalance(), 60.0);
}

TEST(TransactionTest, TransferZeroAmount) {
    Account a(100);
    Account b(50);

    Transaction t;
    t.transfer(a, b, 0.0);

    EXPECT_EQ(a.getBalance(), 100.0);
    EXPECT_EQ(b.getBalance(), 50.0);
}

TEST(TransactionTest, TransferAllBalance) {
    Account a(100);
    Account b;

    Transaction t;
    t.transfer(a, b, 100.0);

    EXPECT_EQ(a.getBalance(), 0.0);
    EXPECT_EQ(b.getBalance(), 100.0);
}

TEST(TransactionTest, TransferMultipleTransactions) {
    Account a(200);
    Account b(100);

    Transaction t;
    t.transfer(a, b, 50.0);
    t.transfer(b, a, 30.0);

    EXPECT_EQ(a.getBalance(), 180.0);
    EXPECT_EQ(b.getBalance(), 120.0);
}

TEST(TransactionTest, TransferMoreThanBalance) {
    Account a(50);
    Account b;

    Transaction t;
    t.transfer(a, b, 100.0);

    EXPECT_EQ(a.getBalance(), -50.0);
    EXPECT_EQ(b.getBalance(), 100.0);
}

TEST(TransactionTest, TransferSmallAmount) {
    Account a(100);
    Account b;

    Transaction t;
    t.transfer(a, b, 0.5);

    EXPECT_EQ(a.getBalance(), 99.5);
    EXPECT_EQ(b.getBalance(), 0.5);
}
