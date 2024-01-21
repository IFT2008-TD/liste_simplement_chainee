//
// Created by Pascal Charpentier on 2024-01-19.
//

#ifndef LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEE_H
#define LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEE_H

#include <initializer_list>

template <typename Cle_t>
class ListeSimple {

private:
    struct Cellule {

        Cle_t cle ;
        Cellule* prochain ;

        explicit Cellule(Cle_t nouvelleCle) : cle(nouvelleCle), prochain(nullptr) {} ;
    };

public:
    explicit ListeSimple() ;
    ListeSimple(std::initializer_list<Cle_t> inlis) ;

    bool est_vide() const ;
    size_t taille() const ;
    bool cle_presente(Cle_t cle) const ;
    size_t trouver_cle(Cle_t cle) const ;

    // Manipulations du premier élément

    void ajouter_en_premier(Cle_t cle) ;
    Cle_t lire_premier() const ;
    void supprimer_premier() ;

    // Manipulations de l'élément en position n

    void ajouter_a_position(size_t n, Cle_t cle) ;
    Cle_t lire_a_position(size_t pos) const ;
    void supprimer_a_position(size_t pos) ;



private:
    Cellule* premier ;

};

#include "ListeSimplementChaineeImplantation.h"


#endif //LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEE_H
