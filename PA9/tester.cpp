#include <gtest/gtest.h>
#include <limits.h>
#include <string>
#include "Stemmer.h"
#include "Exceptions.h"
#include "Lexeme.h"

    TEST(Stemmer, regions) {
        Stemmer stem;
        string s = "circumference";
        EXPECT_EQ(stem.getRegion1(s), "cumference");
		EXPECT_EQ(stem.getRegion2(s), "ferencs");
    }
    
    TEST(Exceptions, isException) {
        Exceptions exc;
        string s = "knife";
        EXPECT_FALSE(exc.isException(s));
    }
    
    TEST(Lexeme, containsDigit) {
        Lexeme lex;
        string s = "wow123";
        EXPECT_TRUE(lex.containsDigit(s));
    }
    
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
