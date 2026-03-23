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
    l.ajouter_premier(666) ;
    EXPECT_FALSE(l.est_vide()) ;
}

TEST(ListeSimple, ajouter_en_premier_cle_presente) {
    ListeSimple<int> l ;
    l.ajouter_premier(666) ;
    EXPECT_NE(l.end(), std::find(l.begin(), l.end(), 666)) ;
    EXPECT_EQ(l.end(), std::find(l.begin(), l.end(), 665)) ;
}

TEST(ListeSimple, ajouter_en_premier_deux_cles) {
    ListeSimple<int> l ;
    l.ajouter_premier(666) ;
    l.ajouter_premier(1024) ;
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


TEST_F(ListeSimpleTest, supprimer_premier) {
    EXPECT_THROW(lvide.supprimer_premier(), std::logic_error) ;
    l1.supprimer_premier() ;
    EXPECT_TRUE(l1.est_vide()) ;
    l2.supprimer_premier() ;
    EXPECT_EQ("[666]", l2.to_string()) ;
}

TEST_F(ListeSimpleTest, insert_dans_vide) {
    lvide.inserer(lvide.begin(), 23) ;
    EXPECT_EQ("[23]", lvide.to_string()) ;
}

TEST_F(ListeSimpleTest, insert_en_premier) {
    l1.inserer(l1.begin(), 23) ;
    EXPECT_EQ("[23, 42]", l1.to_string()) ;
}

TEST_F(ListeSimpleTest, insert_en_dernier) {
    l1.inserer(l1.end(), 23) ;
    EXPECT_EQ("[42, 23]", l1.to_string()) ;
}

TEST_F(ListeSimpleTest, insert_au_milieu) {
    auto it = std::find(l2.begin(), l2.end(), 666) ;
    l2.inserer(it, 1) ;
    EXPECT_EQ("[23, 1, 666]", l2.to_string()) ;
}

TEST_F(ListeSimpleTest, supprimer_en_premier) {
    l1.supprimer(l1.begin()) ;
    EXPECT_TRUE(l1.est_vide()) ;
}

TEST_F(ListeSimpleTest, trouver_et_supprimer) {
    auto it = l2.trouver(666) ;
    l2.supprimer(it) ;
    EXPECT_EQ("[23]", l2.to_string()) ;
}

TEST_F(ListeSimpleTest, trouver_second_et_supprimer) {
    auto it = l2.trouver(23) ;
    l2.supprimer(it) ;
    EXPECT_EQ("[666]", l2.to_string()) ;
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
    EXPECT_EQ(2, lvide.taille()) ;
    EXPECT_EQ(lvide.to_string(), l2.to_string()) ;
}

TEST_F(ListeSimpleTest, déplacement) {
    std::string attendue = l2.to_string() ;
    lvide = std::move(l2) ;
    EXPECT_EQ(2, lvide.taille()) ;

    // Attention, ici l2 est inutilisable
    EXPECT_EQ(lvide.to_string(), attendue) ;
}

TEST_F(ListeSimpleTest, utilisation_de_find) {
    auto it = std::find(l2.begin(), l2.end(), 23) ;
    EXPECT_EQ(23, *it) ;
}

TEST_F(ListeSimpleTest, utilisation_de_find_if) {
    auto it = std::find_if(l2.begin(), l2.end(), [](int x) {
        return x - 1 == 665 ;
    }) ;
    EXPECT_EQ(666, *it) ;
}

TEST_F(ListeSimpleTest, utilisation_de_find_absent) {
    auto it = std::find(l2.begin(), l2.end(), 0) ;
    EXPECT_EQ(l2.end(), it) ;
}

TEST_F(ListeSimpleTest, utilisation_de_find_if_absent) {
    auto it = std::find_if(l2.begin(), l2.end(), [](int x) {
        return x - 1 == 2000 ;
    }) ;
    EXPECT_EQ(l2.end(), it) ;
}

