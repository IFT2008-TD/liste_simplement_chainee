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
ListeSimple<Cle_t>::ListeSimple() : sentinelle(new Cellule), premier(sentinelle), cardinal(0) {
    assert(invariant()) ;
}


/**
 * Constructeur avec liste d'initialisation.  L'ordre des éléments sera inversé!!!
 * @tparam Cle_t
 * @param inlis Liste des clés à insérer
 */
template<typename Cle_t>
ListeSimple<Cle_t>::ListeSimple(std::initializer_list<Cle_t> inlis) : sentinelle(new Cellule), premier(sentinelle), cardinal(0) {
    for (auto e: inlis) ajouter_premier(e) ;
    assert(invariant()) ;
}

/**
 * Méthode de Coplien: constructeur de copie
 * @tparam Cle_t
 * @param source Liste à copier
 */
template<typename Cle_t>
ListeSimple<Cle_t>::ListeSimple(const ListeSimple<Cle_t> &source) : sentinelle(nullptr), premier(aux_copier_liste(source.premier)), cardinal(source.cardinal) {
    auto s = premier ;
    while (s->prochain != nullptr) s = s->prochain ;
    sentinelle = s ;
    assert(invariant()) ;
}

/**
 * Constructeur de déplacement
 * @param source Liste à copier.  ATTENTION : source est inutilisable après déplacement!!!
 */
template<typename Cle_t>
ListeSimple<Cle_t>::ListeSimple(ListeSimple &&source) noexcept : sentinelle(source.sentinelle), premier(source.premier), cardinal(source.cardinal){
    source.sentinelle = nullptr ;
    source.premier = nullptr ;
    source.cardinal = 0 ;
    assert(invariant()) ;
}


/**
 * Vérifie si la liste contient des éléments.
 * @tparam Cle_t
 * @return Retourne true si la liste est vide.
 */
template <typename Cle_t>
bool ListeSimple<Cle_t>::est_vide() const {
    return taille() == 0 ;
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

// Retourne un itérateur sur la clé demandée, ou end()
template<typename Cle_t>
typename ListeSimple<Cle_t>::iterator ListeSimple<Cle_t>::trouver(const Cle_t &cle) const {
    return std::find(begin(), end(), cle) ;
}

/**
 * Retire l'élément pointé par l'itérateur.
 * @param it Localise l'élément à retirer
 * @return Un itérateur sur le prochain élément
 */
template<typename Cle_t>
typename ListeSimple<Cle_t>::iterator ListeSimple<Cle_t>::supprimer(iterator it) {
    auto p = it.courant ;

    p->cle = p->prochain->cle ;
    if (p->prochain == sentinelle) sentinelle = p ;
    auto r = p->prochain ;
    p->prochain = p->prochain->prochain ;
    delete r ;
    -- cardinal ;
    return iterator(p) ;
}

/**
 * Insérer à un itérateur
 * @param it Itérateur
 * @param cle Nouvelle clé à insérer
 * @return Un itérateur sur l'élément inséré
 */
template<typename Cle_t>
typename ListeSimple<Cle_t>::iterator ListeSimple<Cle_t>::inserer(iterator it, const Cle_t& cle) {
    auto p = it.courant ;
    auto n = new Cellule(*it) ;

    n->prochain = p->prochain ;
    p->prochain = n ;
    p->cle = cle ;

    return iterator(p) ;
}


/**
 * Ajoute une clé à la liste, celle-ci se retrouve à la position 0.
 * @tparam Cle_t
 * @param cle Clé à ajouter
 */
template<typename Cle_t>
void ListeSimple<Cle_t>::ajouter_premier(Cle_t cle) {
    auto* nouvelle = new Cellule(cle) ;
    nouvelle->prochain = premier ;
    premier = nouvelle ;
    cardinal += 1 ;

    assert(invariant()) ;
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

    assert(invariant()) ;
}

// true si la clé est trouvée
template<typename Cle_t>
bool ListeSimple<Cle_t>::cle_presente(const Cle_t &cle) const {
    return trouver(cle) != end() ;
}

// Représenter comme [e1, e2, e3, e4]
template<typename Cle_t>
std::string ListeSimple<Cle_t>::to_string() const {
    std::ostringstream s ;
    s << "[" ;
    auto p = premier ;
    while (p->prochain != nullptr) {
        s << p->cle ;
        p = p->prochain ;
        if (p->prochain != nullptr) s << ", " ;
    }
    s << "]" ;
    return s.str() ;
}

// Copier récursivement une sous-liste de gauche à droite
template<typename Cle_t>
typename ListeSimple<Cle_t>::Cellule *ListeSimple<Cle_t>::aux_copier_liste(Cellule* liste) {
    if (liste == nullptr) return nullptr ;
    auto nouveau = new Cellule(liste->cle) ;
    nouveau->prochain = aux_copier_liste(liste->prochain) ;
    return nouveau ;
}

// Good ole destructor
template<typename Cle_t>
ListeSimple<Cle_t>::~ListeSimple() {
    aux_detruire_liste(premier) ;
}

// Détruire récursivement de droite à gauche une liste
template<typename Cle_t>
void ListeSimple<Cle_t>::aux_detruire_liste(Cellule* liste) {
    if (liste == nullptr) return ;

    aux_detruire_liste(liste->prochain) ;
    delete liste ;
}

/**
 * Validité : lorsqu'on fait cardinal sauts à partir de premier, on se retrouve à la sentinelle.  Celle-ci pointe sur
 * nullptr.
 * @return Retourne true si la liste est valide
 */
template<typename Cle_t>
bool ListeSimple<Cle_t>::invariant() const {
    if (cardinal == 0) if (premier != sentinelle) return false ;
    size_t compteur = 0 ;
    auto current = premier ;
    while (current != sentinelle) {
        if (current == nullptr) return false ;
        current = current->prochain ;
        ++ compteur ;
    }
    if (compteur != cardinal) return false ;
    return sentinelle->prochain == nullptr ;
}

// Affectation copy-swap
template<typename Cle_t>
ListeSimple<Cle_t> &ListeSimple<Cle_t>::operator=(ListeSimple rhs) {
    std::swap(sentinelle, rhs.sentinelle) ;
    std::swap(cardinal, rhs.cardinal) ;
    std::swap(premier, rhs.premier) ;

    assert(invariant()) ;
    return *this ;
}


#endif //LISTE_SIMPLEMENT_CHAINEE_LISTESIMPLEMENTCHAINEEIMPLANTATION_H
