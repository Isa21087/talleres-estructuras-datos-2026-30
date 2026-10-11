#ifndef ARBOLRN_HXX
#define ARBOLRN_HXX

template <class T>
arbolRN<T>::arbolRN() {
}

template <class T>
bool arbolRN<T>::insert(T val) {

    //insert devuelve el iterador y si se pudo insertar
    std::pair<typename std::set<T>::iterator, bool> resultado;

    resultado = this->datos.insert(val);

    return resultado.second;
}

template <class T>
bool arbolRN<T>::erase(T val) {

    //erase devuelve cuantos elementos elimino
    return this->datos.erase(val) > 0;
}

template <class T>
void arbolRN<T>::inordenEnLista(std::list<T>& lista) {

    typename std::set<T>::iterator it;

    //set ya mantiene los datos ordenados
    for (it = this->datos.begin(); it != this->datos.end(); it++) {
        lista.push_back(*it);
    }
}

#endif