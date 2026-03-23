//
// Created by Pascal Charpentier on 2026-03-17.
//

#ifndef TABLEHACHAGE_H
#define TABLEHACHAGE_H

#include "ListeSimplementChainee.h"

template<typename K, typename V, typename H = std::hash<K> >
class TableHachage {
public:
    TableHachage() ;
    bool inserer(const K& cle, const V& valeur) ;
    bool supprimer(const K& cle) ;
    const V& lire(const K& cle) const ;

private:
    static bool estPremier(size_t n) ;
    static size_t prochainPremier(size_t n) ;
    bool ajouterElement(const K& cle, const V& valeur) ;
    bool doitRehacher() const ;
    void rehacher() ;


private:
    static constexpr float DEF_LOAD_FACTOR = 1.0 ;
    static constexpr size_t DEF_INIT_CAP = 13 ;
    size_t cardinal ;
    std::vector<ListeSimple<std::pair<K, V>>> table ;
    H hacher ;

};

template<typename K, typename V, typename H>
TableHachage<K, V, H>::TableHachage() : cardinal(0), table(DEF_INIT_CAP) {
}

template<typename K, typename V, typename H>
bool TableHachage<K, V, H>::inserer(const K &cle, const V &valeur) {

    if (!ajouterElement(cle, valeur)) return false ;
    if (doitRehacher()) rehacher() ;

    return true ;
}

template<typename K, typename V, typename H>
bool TableHachage<K, V, H>::supprimer(const K &cle) {
    auto index = hacher(cle) % table.size();
    auto& liste = table.at(index) ;

    auto it = std::find_if(liste.begin(), liste.end(), [cle](const std::pair<K, V>& e) {
        return cle == e.first ;
    }) ;
    if (it == liste.end()) return false ;

    liste.supprimer(it) ;
    return true ;
}

template<typename K, typename V, typename H>
const V & TableHachage<K, V, H>::lire(const K &cle) const {
    auto index = hacher(cle) % table.size() ;
    const auto& liste = table.at(index) ;

    auto it = std::find_if(liste.begin(), liste.end(), [cle](const std::pair<K, V> &e) {
        return cle == e.first ;
    }) ;
    if (it == liste.end()) throw std::invalid_argument("lire: clé absente") ;

    return it->second ;
}

template<typename K, typename V, typename H>
bool TableHachage<K, V, H>::estPremier(size_t n) {
    if (n < 2) return false ;
    if (n % 2 == 0) return false ;
    size_t i = 3 ;
    while (i * i <= n) {
        if (n % i == 0) return false ;
        i += 2 ;
    }
    return true ;
}

template<typename K, typename V, typename H>
size_t TableHachage<K, V, H>::prochainPremier(size_t n) {
    size_t p = n + 1 ;
    while (!estPremier(p)) p += 2 ;
    return p ;
}

template<typename K, typename V, typename H>
bool TableHachage<K, V, H>::ajouterElement(const K &cle, const V &valeur) {
    auto index = hacher(cle) % table.size();
    auto& liste = table.at(index) ;

    auto it = std::find_if(liste.begin(), liste.end(), [cle](const std::pair<K, V>& e) {
        return cle == e.first ;
    }) ;
    if (it != liste.end()) return false ;

    liste.inserer(it, {cle, valeur}) ;
    ++ cardinal ;
    return true ;
}

template<typename K, typename V, typename H>
bool TableHachage<K, V, H>::doitRehacher() const {
    return cardinal >= DEF_LOAD_FACTOR * table.size() ;
}

template<typename K, typename V, typename H>
void TableHachage<K, V, H>::rehacher() {
    auto backup = std::move(table) ;

    size_t nouvelleCapacite = prochainPremier(2 * backup.size()) ;
    table = std::vector<ListeSimple<std::pair<K, V>>>(nouvelleCapacite) ;

    cardinal = 0 ;
    for (auto& liste: backup) for (auto& e: liste) ajouterElement(e.first, e.second) ;
}


#endif //TABLEHACHAGE_H
