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

TEST_F(ListeSimpleTest, to_string) {
    EXPECT_EQ("[]", lvide.to_string()) ;
    EXPECT_EQ("[42]", l1.to_string()) ;
    EXPECT_EQ("[23, 666]", l2.to_string()) ;
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

TEST_F(ListeSimpleTest, supprimer_premier) {
    EXPECT_THROW(lvide.supprimer_premier(), std::logic_error) ;
    l1.supprimer_premier() ;
    EXPECT_TRUE(l1.est_vide()) ;
    l2.supprimer_premier() ;
    EXPECT_EQ("[666]", l2.to_string()) ;
}

TEST_F(ListeSimpleTest, ajouter_a_position) {
    EXPECT_THROW(lvide.ajouter_a_position(1, 666), std::invalid_argument) ;
    lvide.ajouter_a_position(0, 666) ;
    EXPECT_EQ("[666]", lvide.to_string()) ;
    l2.ajouter_a_position(1, 888) ;
    EXPECT_EQ("[23, 888, 666]", l2.to_string()) ;
    l2.ajouter_a_position(3, 777) ;
    EXPECT_EQ("[23, 888, 666, 777]", l2.to_string()) ;
}

TEST_F(ListeSimpleTest, supprimer_a_position) {
    l2.supprimer_a_position(1) ;
    EXPECT_EQ("[23]", l2.to_string()) ;
    l2.supprimer_a_position(0) ;
    EXPECT_TRUE(l2.est_vide()) ;
}


TEST_F(ListeSimpleTest, constructeur_copie) {
    ListeSimple<int> cpvide(lvide) ;
    EXPECT_TRUE(cpvide.est_vide()) ;

    ListeSimple<int> cpl1(l1) ;
    EXPECT_EQ(l1.to_string(), cpl1.to_string()) ;

    ListeSimple<int> cpl2(l2) ;
    EXPECT_EQ(l2.to_string(), l2.to_string()) ;
}

TEST_F(ListeSimpleTest, affectation) {
    lvide = l2 ;
    EXPECT_EQ(lvide.to_string(), l2.to_string()) ;
}

