//
// Created by Pascal Charpentier on 2026-03-23.
//

#include "gtest/gtest.h"

#include "TableHachage.h"

#include <string>
#include <stdexcept>

namespace {

    TEST(TableHachageTest, TableVideLanceExceptionALecture) {
        TableHachage<int, std::string> table;

        EXPECT_THROW(table.lire(42), std::invalid_argument);
    }

    TEST(TableHachageTest, InsertionEtLectureFonctionnent) {
        TableHachage<int, std::string> table;

        EXPECT_TRUE(table.inserer(7, "sept"));
        EXPECT_EQ(table.lire(7), "sept");
    }

    TEST(TableHachageTest, RefuseLesDoublons) {
        TableHachage<int, std::string> table;

        EXPECT_TRUE(table.inserer(7, "sept"));
        EXPECT_FALSE(table.inserer(7, "sete"));
        EXPECT_EQ(table.lire(7), "sept");
    }

    TEST(TableHachageTest, SuppressionFonctionne) {
        TableHachage<int, std::string> table;

        EXPECT_TRUE(table.inserer(7, "sept"));
        EXPECT_TRUE(table.supprimer(7));
        EXPECT_THROW(table.lire(7), std::invalid_argument);
    }

    TEST(TableHachageTest, SuppressionDuneCleAbsenteRetourneFalse) {
        TableHachage<int, std::string> table;

        EXPECT_FALSE(table.supprimer(99));
    }

    TEST(TableHachageTest, PlusieursInsertionsRestentLisiblesApresRehaching) {
        TableHachage<int, std::string> table;

        for (int i = 0; i < 50; ++i) {
            EXPECT_TRUE(table.inserer(i, "valeur_" + std::to_string(i)));
        }

        for (int i = 0; i < 50; ++i) {
            EXPECT_EQ(table.lire(i), "valeur_" + std::to_string(i));
        }
    }

    TEST(TableHachageTest, CleAbsenteApresInsertionsRetourneException) {
        TableHachage<int, std::string> table;

        table.inserer(1, "un");
        table.inserer(2, "deux");

        EXPECT_THROW(table.lire(3), std::invalid_argument);
    }

}  // namespace