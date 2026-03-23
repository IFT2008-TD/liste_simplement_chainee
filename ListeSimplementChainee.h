//
// Created by Pascal Charpentier on 2024-01-19.
//

#ifndef LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEE_H
#define LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEE_H

#include <initializer_list>
#include <sstream>
#include <cassert>

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

        // Le constructeur par défaut est nécessaire pour la sentinelle.
        Cellule() : cle(), prochain(nullptr) {}
        explicit Cellule(Cle_t nouvelleCle) : cle(nouvelleCle), prochain(nullptr) {}
    };

public:

    class iterator {
        friend class ListeSimple ;

        Cellule* courant ;

    public:
        using value_type = Cle_t ;
        using difference_type = std::ptrdiff_t ;
        using pointer = Cle_t* ;
        using reference = Cle_t& ;
        using iterator_category = std::forward_iterator_tag ;

        explicit iterator(Cellule* cell) : courant(cell) {}

        reference operator*() {return courant->cle ; }
        pointer operator -> () {return &(courant->cle) ; }

        iterator& operator ++() {
            courant = courant->prochain ;
            return *this ;
        }

        iterator operator ++(int) {
            iterator temp = *this ;
            courant = courant->prochain ;
            return temp ;
        }

        bool operator == (const iterator& autre) const {
            return courant == autre.courant ;
        }

        bool operator != (const iterator& autre) const {
            return courant != autre.courant ;
        }
    };


    iterator begin() const {return iterator(premier) ; }
    iterator end() const {return iterator(sentinelle) ; }

    explicit ListeSimple() ;
    ListeSimple(std::initializer_list<Cle_t> inlis) ;

    // Coplien...

    ListeSimple(const ListeSimple<Cle_t>& source) ;
    ListeSimple(ListeSimple&& source) noexcept ;
    ListeSimple<Cle_t>& operator = (ListeSimple<Cle_t> rhs) ;
    ~ListeSimple() ;

    bool est_vide() const ;
    size_t taille() const ;

    // Méthodes utilisant les itérateurs

    iterator trouver(const Cle_t& cle) const ;
    iterator supprimer(iterator it) ;
    iterator inserer(iterator it, const Cle_t &cle) ;

    // Manipulations du premier élément

    void ajouter_premier(Cle_t cle) ;
    void supprimer_premier() ;

    // Débogage

    bool cle_presente(const Cle_t& cle) const ;
    std::string to_string() const ;

private:
    Cellule* aux_copier_liste(Cellule* liste) ;
    void aux_detruire_liste(Cellule* liste) ;

    bool invariant() const ;



private:
    Cellule* sentinelle ;
    Cellule* premier ;
    size_t cardinal ;

};



#include "ListeSimplementChaineeImplantation.h"


#endif //LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEE_H
