//
// Created by Pascal Charpentier on 2026-03-20.
//

#include "gtest/gtest.h"
#include "max_heap.h"

TEST(MaxHeap, constructeur_par_defaut_vide) {
    MaxHeap<int> m ;
    EXPECT_EQ(0, m.taille()) ;
}

TEST(MaxHeap, inserer_recuperer_un_element) {
    MaxHeap<int> m ;
    m.inserer(1) ;
    EXPECT_EQ(1, m.taille()) ;
    EXPECT_EQ(1, m.max()) ;
    m.extract_max() ;
    EXPECT_EQ(0, m.taille()) ;
}

TEST(MaxHeap, inserer_recuperer_deux_elements_ordre_ok) {
    MaxHeap<int> m ;
    m.inserer(42) ;
    m.inserer(666) ;
    EXPECT_EQ(2, m.taille()) ;
    EXPECT_EQ(666, m.max()) ;
    m.extract_max() ;
    EXPECT_EQ(1, m.taille()) ;
    EXPECT_EQ(42, m.max()) ;
    m.extract_max() ;
    EXPECT_EQ(0, m.taille()) ;
}

TEST(MaxHeap, build_heap) {
    std::vector<int> source {60, 20, 70, 10, 0, 100, 30, 20} ;
    std::vector<int> expected_order {0, 10, 20, 20, 30, 60, 70, 100} ;
    MaxHeap<int> m(source) ;

    while (m.taille() > 0) {
        EXPECT_EQ(m.max(), expected_order.at(m.taille() - 1)) ;
        m.extract_max() ;
    }
    EXPECT_EQ(0, m.taille()) ;
}
