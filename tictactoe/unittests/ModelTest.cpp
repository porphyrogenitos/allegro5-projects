#include <gtest/gtest.h>
#include "../src/Model.h"

class ModelPlayTest : public testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    ModelPlayTest() {
        // You can do set-up work for each test here.

    }
/*
    ~ModelPlayTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
*/

    void WinTesterAcross(char symbol) {

    }

    void WinTesterDown(char symbol) {

    }

    void WinTesterDiagonal(char symbol) {

    }
};

TEST(ModelTest, GetSymbol) {
    Model model {};
    char symbol = model.get_cur_player();
    model.play(0, 2);
    EXPECT_EQ(symbol, model.get_symbol(0, 2));
}

TEST(ModelTest, GetSymbolEmpty) {
    Model model {};
    char player = model.get_symbol(0, 0);
    EXPECT_EQ(player, ' ');
}

TEST(ModelTest, GetBoardSize) {
    Model model {};
    EXPECT_EQ(9, model.get_board_size());
}

TEST(ModelTest, PlayWinner) {

}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}