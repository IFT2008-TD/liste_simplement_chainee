//
// Created by Pascal Charpentier on 2024-01-19.
//

#ifndef LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEE_H
#define LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEE_H

#include <initializer_list>

/**
 * Ce patron de classe, sert à implanter une liste avec ses primitives de base.  Il s'agira ici d'une liste chaînée
 * permettant un accès séquentiel aux diverses clés contenues.
 *
 * Dans notre modèle, le dernier élément à être inséré dans la liste aura la position 0.  Les positions valides iront
 * donc de 0 à n-1 où n est le nombre d'éléments dans la liste.
 *
 * Pour l'insertion, par-contre, on pourra insérer de 0 à n, n correspondra à insérer un élément en dernière position.
 *
 * Les primitives suivantes seront implantées:
 *
 * Construction d'une liste vide
 * Construction d'une liste à partir d'une liste de clés prédéterminée.
 * Insérer une clé en premier (position 0)
 * Lire la première clé
 * Supprimer la première clé
 * Insérer à une position donnée
 * Lire la clé à une position donnée
 * Supprimer la clé se trouvant à une position donnée
 *
 * @tparam Cle_t Type des éléments contenus dans la liste.
 */
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
    ListeSimple(const ListeSimple<Cle_t>& source) ;
    ListeSimple<Cle_t>& operator = (ListeSimple<Cle_t> rhs) ;
    ~ListeSimple() ;

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

    // Formattage

    std::string to_string() const ;

private:
    Cellule* trouverAdresseDeLaPosition(size_t n) const ;
    Cellule* aux_copier_liste(Cellule* liste) ;
    void aux_detruire_liste(Cellule* liste) ;



private:
    Cellule* premier ;
    size_t cardinal ;

};



#include "ListeSimplementChaineeImplantation.h"


#endif //LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEE_H
