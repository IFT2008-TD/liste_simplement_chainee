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
ListeSimple<Cle_t>::ListeSimple() : premier(nullptr) {

}


/**
 * Constructeur avec liste d'initialisation.  L'ordre des éléments sera inversé!!!
 * @tparam Cle_t
 * @param inlis Liste des clés à insérer
 */
template<typename Cle_t>
ListeSimple<Cle_t>::ListeSimple(std::initializer_list<Cle_t> inlis) : premier(nullptr) {
    for (auto e: inlis) ajouter_en_premier(e) ;
}


/**
 * Vérifie si la liste contient des éléments.
 * @tparam T
 * @return true si la liste est vide.
 */
template <typename T>
bool ListeSimple<T>::est_vide() const {
    return premier == nullptr ;
}


/**
 * Compte les éléments de la liste
 * @tparam Cle_t
 * @return Le nombre d'éléments dans la liste.  0 pour une liste vide.
 */
template<typename Cle_t>
size_t ListeSimple<Cle_t>::taille() const {
    return 0;
}


/**
 * Vérifie si une clé donnée est dans la liste.
 * @tparam Cle_t
 * @param cle Clé recherchée
 * @return true si la clé recherchée est dans la liste, sinon false.
 */
template<typename Cle_t>
bool ListeSimple<Cle_t>::cle_presente(Cle_t cle) const {
    return false ;
}


/**
 * Localise une clé dans la liste
 * @tparam Cle_t
 * @param cle Clé à localiser
 * @return La position de la clé dans la liste, 0 étant en premier.
 */
template<typename Cle_t>
size_t ListeSimple<Cle_t>::trouver_cle(Cle_t cle) const {
    return 0;
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
    return Cle_t() ;
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

}


#endif //LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEEIMPLANTATION_H
