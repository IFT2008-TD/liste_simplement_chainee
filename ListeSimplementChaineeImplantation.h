//
// Created by Pascal Charpentier on 2024-01-19.
//

#ifndef LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEEIMPLANTATION_H
#define LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEEIMPLANTATION_H

#include "ListeSimplementChainee.h"


/**
 * Constructeur de base, crée une liste vide.
 * @tparam Cle_t
 */
template<typename Cle_t>
ListeSimple<Cle_t>::ListeSimple() : premier(nullptr), cardinal(0) {

}


/**
 * Constructeur avec liste d'initialisation.  L'ordre des éléments sera inversé!!!
 * @tparam Cle_t
 * @param inlis Liste des clés à insérer
 */
template<typename Cle_t>
ListeSimple<Cle_t>::ListeSimple(std::initializer_list<Cle_t> inlis) : premier(nullptr), cardinal(0) {
    for (auto e: inlis) ajouter_en_premier(e) ;
}

/**
 * Méthode de Coplien: constructeur de copie
 * @tparam Cle_t
 * @param source Liste à copier
 */
template<typename Cle_t>
ListeSimple<Cle_t>::ListeSimple(const ListeSimple<Cle_t> &source) : premier(nullptr), cardinal(0) {
   premier = aux_copier_liste(source.premier) ;
}


/**
 * Vérifie si la liste contient des éléments.
 * @tparam T
 * @return true si la liste est vide.
 */
template <typename T>
bool ListeSimple<T>::est_vide() const {
    return cardinal == 0 ;
}


/**
 * Compte les éléments de la liste
 * @tparam Cle_t
 * @return Le nombre d'éléments dans la liste.  0 pour une liste vide.
 */
template<typename Cle_t>
size_t ListeSimple<Cle_t>::taille() const {
    return cardinal ;
}


/**
 * Vérifie si une clé donnée est dans la liste.
 * @tparam Cle_t
 * @param cle Clé recherchée
 * @return true si la clé recherchée est dans la liste, sinon false.
 */
template<typename Cle_t>
bool ListeSimple<Cle_t>::cle_presente(Cle_t cle) const {
    return trouver_cle(cle) != taille() ;
}


/**
 * Localise une clé dans la liste
 * @tparam Cle_t
 * @param cle Clé à localiser
 * @return La position de la clé dans la liste, 0 étant en premier. Si la clé cherchée n'est pas dans la liste
 * le cardinal de la liste sera retourné.
 */
template<typename Cle_t>
size_t ListeSimple<Cle_t>::trouver_cle(Cle_t cle) const {
    if (est_vide()) throw std::logic_error("trouver_cle: liste vide") ;

    Cellule* p = premier ;
    size_t index = 0 ;
    while (p != nullptr) {
        if (p->cle == cle) break ;
        index += 1 ;
        p = p->prochain ;
    }
    return index ;
}


/**
 * Ajoute une clé à la liste, celle-ci se retrouve à la position 0.
 * @tparam Cle_t
 * @param cle Clé à ajouter
 */
template<typename Cle_t>
void ListeSimple<Cle_t>::ajouter_en_premier(Cle_t cle) {
    auto* nouvelle = new Cellule(cle) ;
    nouvelle->prochain = premier ;
    premier = nouvelle ;
    cardinal += 1 ;
}


/**
 * Lis la première clé de la liste
 * @tparam Cle_t
 * @return La valeur de la clé en position 0
 * @pre La liste est non vide
 * @throw std::logic_error si la liste est vide
 */
template<typename Cle_t>
Cle_t ListeSimple<Cle_t>::lire_premier() const {
    return premier->cle ;
}


/**
 * Retire la clé présente en tête de liste.
 * @tparam Cle_t
 * @pre La liste est non-vide
 * @throw std::logic_error si la liste est vide
 */
template<typename Cle_t>
void ListeSimple<Cle_t>::supprimer_premier() {
    if (est_vide()) throw std::logic_error("supprimer_premier: liste vide") ;
    auto temp = premier->prochain ;
    delete premier ;
    premier = temp ;
    cardinal -= 1 ;
}


/**
 * Ajoute une clé à la position demandée.
 * @tparam Cle_t
 * @param n Position dans la liste, 0 étant le premier élément
 * @param cle Clé à rajouter.
 * @pre 0 <= n <= cardinal de la liste.  Lorsque n correspond au cardinal de la liste, l'insertion est en dernier.
 * @throw std::logic_error si n est hors-limite
 */
template <typename Cle_t>
void ListeSimple<Cle_t>::ajouter_a_position(size_t n, Cle_t cle) {
    if (n > taille()) throw std::invalid_argument("ajouter_a_position: index invalide") ;
    if (n == 0) ajouter_en_premier(cle) ;
    else {
        auto nouveau = new Cellule(cle) ;
        auto p = trouverAdresseDeLaPosition(n - 1) ;
        nouveau->prochain = p->prochain ;
        p->prochain = nouveau ;
        cardinal += 1 ;
    }
}


/**
 * Lit la clé à la position demandée.
 * @tparam Cle_t
 * @param pos Position
 * @return Valeur de la clé
 * @pre  0 <= pos < cardinal de la liste
 * @throw std::logic_error si la position est hors-limites ou la liste est vide
 */
template<typename Cle_t>
Cle_t ListeSimple<Cle_t>::lire_a_position(size_t pos) const {
    if (pos >= taille()) throw std::invalid_argument("lire_a_position: index non-valide") ;
    auto p = trouverAdresseDeLaPosition(pos) ;
    return p->cle ;
}


/**
 * Supprime la clé à la position demandée
 * @tparam Cle_t
 * @param pos Position où faire la suppression
 * @pre 0 <= pos < cardinal de la liste
 * @throw std::logic_error si la position est hors-limite ou la liste est vide
 */
template<typename Cle_t>
void ListeSimple<Cle_t>::supprimer_a_position(size_t pos) {
    if (pos >= taille()) throw std::invalid_argument("supprimer_a_position: index non valide") ;
    if (pos == 0) supprimer_premier() ;
    else {
        auto p = trouverAdresseDeLaPosition(pos-1) ;
        auto suivant = p->prochain ;
        p->prochain = suivant->prochain ;
        delete suivant ;
        cardinal -= 1 ;
    }
}

template<typename Cle_t>
std::string ListeSimple<Cle_t>::to_string() const {
    std::ostringstream s ;
    s << "[" ;
    auto p = premier ;
    while (p != nullptr) {
        s << p->cle ;
        p = p->prochain ;
        if (p != nullptr) s << ", " ;
    }
    s << "]" ;
    return s.str() ;
}

template<typename Cle_t>
typename ListeSimple<Cle_t>::Cellule *ListeSimple<Cle_t>::trouverAdresseDeLaPosition(size_t n) const {
    auto p = premier ;
    size_t i = 0 ;
    while (i < n) {
        p = p->prochain ;
        ++i ;
    }
    return p ;
}

template<typename Cle_t>
typename ListeSimple<Cle_t>::Cellule *ListeSimple<Cle_t>::aux_copier_liste(Cellule* liste) {
    if (liste == nullptr) return nullptr ;
    auto nouveau = new Cellule(liste->cle) ;
    nouveau->prochain = aux_copier_liste(liste->prochain) ;
    return nouveau ;
}

template<typename Cle_t>
ListeSimple<Cle_t>::~ListeSimple() {
    aux_detruire_liste(premier) ;
}

template<typename Cle_t>
void ListeSimple<Cle_t>::aux_detruire_liste(Cellule* liste) {
    if (liste == nullptr) return ;
    aux_detruire_liste(liste->prochain) ;
    delete liste ;
}

template<typename Cle_t>
ListeSimple<Cle_t> &ListeSimple<Cle_t>::operator=(ListeSimple<Cle_t> rhs) {
    std::swap(cardinal, rhs.cardinal) ;
    std::swap(premier, rhs.premier) ;
    return *this ;
}


#endif //LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEEIMPLANTATION_H
