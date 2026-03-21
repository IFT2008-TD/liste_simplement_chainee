//
// Created by Pascal Charpentier on 2026-03-20.
//

#ifndef MAX_HEAP_H
#define MAX_HEAP_H

template <typename K, typename G = std::greater<K>>
class MaxHeap {
public:
    explicit MaxHeap(size_t cap = CAP_DEFAULT) ;
    explicit MaxHeap(const std::vector<K>& vect) ;
    size_t taille() const ;

    void inserer(const K& cle) ;
    const K& max() const ;
    void extract_max() ;

private:
    static size_t parent(size_t n) {return (n - 1) / 2 ; }
    static size_t enfantGauche(size_t n) {return 2 * n  + 1 ; }

    void percUp(size_t n) ;
    void percDown(size_t n) ;

    bool invariant() const ;

private:
    static constexpr size_t CAP_DEFAULT = 9 ;
    size_t capacite ;
    size_t cardinal ;
    std::vector<K> table ;
    G comparateur ;

};

/**
 * Construit un max-heap vide
 * @param cap Capacité maximale du heap.
 */
template<typename K, typename G>
MaxHeap<K, G>::MaxHeap(size_t cap) : capacite(cap), cardinal(0), table(capacite), comparateur() {
    assert(invariant()) ;
}

/**
 * Construit un max-heap à partir d'un vecteur quelconque.  Le heap résultat a une capacité ET un cardinal égaux à la taille
 * du vecteur.
 * @param vect Vecteur source.  Il est copié pour créer le heap, donc l'original sera inchangé.
 */
template<typename K, typename G>
MaxHeap<K, G>::MaxHeap(const std::vector<K>& vect) : capacite(vect.size()), cardinal(vect.size()), table(vect), comparateur() {
    for (auto n = (cardinal - 2) / 2; n > 0; --n) percDown(n) ;
    percDown(0) ;

    assert(invariant()) ;
}

/**
 *
 * @return Le nombre d'éléments contenus dans le heap
 */
template<typename K, typename G>
size_t MaxHeap<K, G>::taille() const {
    return cardinal ;
}

/**
 * Insérer une nouvelle clé dans le heap. Les doublons sont acceptés.
 * @param cle
 * @throw std::runtime_error Si le heap est rempli à capacité.
 */
template<typename K, typename G>
void MaxHeap<K, G>::inserer(const K &cle) {
    if (cardinal == capacite) throw std::runtime_error("Insertion impossible!") ;

    table.at(cardinal) = cle ;
    ++ cardinal ;
    percUp(cardinal - 1) ;

    assert(invariant()) ;
}

/**
 *
 * @return Ref à l'élément maximal
 */
template<typename K, typename G>
const K & MaxHeap<K, G>::max() const {
    return table.at(0) ;
}

/**
 * Retire l'élément maximal du max-heap.  Percolation s'il y a au-moins un élément.
 */
template<typename K, typename G>
void MaxHeap<K, G>::extract_max() {
    assert(taille() > 0) ;

    table.at(0) = table.at(cardinal - 1) ;
    -- cardinal ;
    if (cardinal > 0) percDown(0) ;

    assert(invariant()) ;
}

/**
 * Percolation vers le haut.  Échange avec le parent tant que l'enfant est plus grand que le parent, ou lorsque
 * l'élément est parvenu en root (n = 0).
 * @param n Position de l'élément à percoler
 */
template<typename K, typename G>
void MaxHeap<K, G>::percUp(size_t n) {
    while (n > 0 && comparateur(table.at(n), table.at(parent(n)))) {
        std::swap(table.at(n), table.at(parent(n))) ;
        n = parent(n) ;
    }
}

/**
 * Percolation vers le bas : tant que la clé courante est un parent, tester si elle est plus petite qu'un de ses
 * enfants.  Si oui, échanger avec le plus grand enfant, et recommencer.  Attention : il est possible que la clé
 * n'ait qu'un seul enfant, il faut donc tester cette condition.
 * Si la clé courante respecte les propriétés du heap : sortir de la boucle.
 * @param n
 */
template<typename K, typename G>
void MaxHeap<K, G>::percDown(size_t n) {
    auto dernierParent = ( cardinal - 2) / 2 ;
    while (n <= dernierParent) {
        auto indexMax = enfantGauche(n) ;
        auto enfantMax = table.at(indexMax) ;
        if (indexMax < cardinal - 1) if (comparateur(table.at(indexMax + 1) ,enfantMax)) {
            enfantMax = table.at(indexMax + 1) ;
            indexMax = indexMax + 1 ;
        }
        if (comparateur(enfantMax, table.at(n))) {
            std::swap(table.at(n), table.at(indexMax)) ;
            n = indexMax ;
        }
        else  break ;
    }
}

/**
 *
 * @return true si le heap est valide: la capacité ne peut être nulle, et le cardinal ne peut jamais excéder la
 * capacité.  Si le heap n'a qu'un seul élément il est toujours valide.  Sinon, chaque parent doit être plus
 * grand que ses deux enfants.
 */
template<typename K, typename G>
bool MaxHeap<K, G>::invariant() const {

    if (capacite == 0) return false ;
    if (cardinal > capacite) return false ;

    // Si le heap a un seul élément, il est trivialement valide
    if (cardinal < 2) return true ;

    // Si un enfant précède un parent : le heap n'est pas valide.
    for (auto i = 0 ; i < (cardinal - 2) / 2; i++) {
        auto ienfant = enfantGauche(i) ;
        if (comparateur(table.at(ienfant), table.at(i))) return false ;
        if (ienfant < cardinal - 1) if (comparateur(table.at(ienfant + 1), table.at(i))) return false ;
    }
    return true ;
}

#endif //MAX_HEAP_H
