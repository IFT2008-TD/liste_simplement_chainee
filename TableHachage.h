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

private:

    //decltype(std::vector<ListeSimple<std::pair<K, V>>>::begin()) trouverCle(const K& cle) const ;

private:
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

    liste.ajouter_en_premier({cle, valeur}) ;
    ++ cardinal ;

    return true ;

}

template<typename K, typename V, typename H>
bool TableHachage<K, V, H>::supprimer(const K &cle) {
    auto index = hacher(cle) ;
    auto& liste = table.at(index) ;

    auto it = std::find(liste.begin(), liste.end(), [cle](const K& e) {
        return cle == e.first ;
    }) ;
    if (it == liste.end()) return false ;

    liste.at(index).erase(it) ;
    return true ;
}

// template<typename K, typename V, typename H>
// decltype(std::vector<ListeSimple<std::pair<K, V>>>::begin()) TableHachage<K, V, H>::trouverCle(const K& cle) const {
//     for (const auto& liste: table) {
//         auto it = std::find_if(liste.begin(), liste.end(), [cle](const K& elem){return elem.first == cle ; }) ;
//         if (it != liste.end()) return it ;
//     }
//     return table.at(0).end() ;
// }

#endif //TABLEHACHAGE_H
