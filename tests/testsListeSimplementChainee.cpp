//
// Created by Pascal Charpentier on 2024-01-19.
//

#include "gtest/gtest.h"
#include "ListeSimplementChainee.h"

class ListeSimpleTest : public ::testing::Test {
public:
    ListeSimpleTest() : lvide(), l1({42}), l2({666, 23}) {}

protected:
    ListeSimple<int> lvide ;
    ListeSimple<int> l1 ;
    ListeSimple<int> l2 ;


};

TEST(ListeSimple, Constructeur_defaut_no_throw) {
    EXPECT_NO_THROW(ListeSimple<int> maListeVide) ;
}

TEST(ListeSimple, Liste_par_defaut_vide) {
    ListeSimple<int> l ;
    EXPECT_TRUE(l.est_vide()) ;
}

TEST(ListeSimple, ajouter_en_premier_liste_non_vide) {
    ListeSimple<int> l ;
    l.ajouter_en_premier(666) ;
    EXPECT_FALSE(l.est_vide()) ;
}

TEST(ListeSimple, ajouter_en_premier_cle_presente) {
    ListeSimple<int> l ;
    l.ajouter_en_premier(666) ;
    EXPECT_TRUE(l.cle_presente(666)) ;
    EXPECT_FALSE(l.cle_presente(665)) ;
}

TEST(ListeSimple, ajouter_en_premier_deux_cles) {
    ListeSimple<int> l ;
    l.ajouter_en_premier(666) ;
    l.ajouter_en_premier(1024) ;
    EXPECT_TRUE(l.cle_presente(666)) ;
    EXPECT_TRUE(l.cle_presente(1024)) ;
    EXPECT_FALSE(l.cle_presente(42)) ;
    EXPECT_FALSE(l.est_vide()) ;
}

TEST_F(ListeSimpleTest, est_vide) {
    EXPECT_TRUE(lvide.est_vide()) ;
    EXPECT_FALSE(l1.est_vide()) ;
    EXPECT_FALSE(l2.est_vide()) ;
}

TEST_F(ListeSimpleTest, lire_premier) {
    EXPECT_EQ(42, l1.lire_premier());
    EXPECT_EQ(23, l2.lire_premier());
}

