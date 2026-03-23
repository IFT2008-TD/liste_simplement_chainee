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
    auto index = hacher(cle) ;
    auto& liste = table.at(index) ;

    auto it = std::find(liste.begin(), liste.end(), [cle](const K& e) {
        return cle == e.first ;
    }) ;
    if (it != liste.end()) return false ;

    liste.inserer(it, {cle, valeur}) ;
    ++ cardinal ;

    if (doitRehacher()) rehacher() ;

    return true ;

}

template<typename K, typename V, typename H>
bool TableHachage<K, V, H>::supprimer(const K &cle) {
    auto index = hacher(cle) ;
    auto& liste = table.at(index) ;

    auto it = std::find_if(liste.begin(), liste.end(), [cle](const K& e) {
        return cle == e.first ;
    }) ;
    if (it == liste.end()) return false ;

    liste.at(index).erase(it) ;
    return true ;
}

template<typename K, typename V, typename H>
const V & TableHachage<K, V, H>::lire(const K &cle) const {
    auto index = hacher(cle) ;
    auto& liste = table.at(index) ;

    auto it = std::find_if(liste.begin(), liste.end(), [cle](const K& e) {
        return cle == e.first ;
    }) ;
    if (it == liste.end()) throw std::invalid_argument("lire: clé absente") ;

    return it->second ;
}

template<typename K, typename V, typename H>
bool TableHachage<K, V, H>::doitRehacher() const {
    return cardinal >= DEF_LOAD_FACTOR * table.size() ;
}

template<typename K, typename V, typename H>
void TableHachage<K, V, H>::rehacher() {

}


#endif //TABLEHACHAGE_H
