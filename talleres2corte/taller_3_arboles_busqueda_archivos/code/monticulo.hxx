#ifndef MONTICULO_HXX
#define MONTICULO_HXX

template <class T>
monticulo<T>::monticulo() {
}

template <class T>
bool monticulo<T>::insert(T val) {

    //el dato nuevo se agrega al final
    this->datos.push_back(val);

    //se reorganiza para mantener el monticulo
    std::push_heap(this->datos.begin(), this->datos.end());

    return true;
}

template <class T>
bool monticulo<T>::erase(T val) {

    //se busca el dato que se quiere eliminar
    typename std::deque<T>::iterator it =
        std::find(this->datos.begin(), this->datos.end(), val);

    if (it == this->datos.end())
        return false;

    //se elimina y se vuelve a organizar el monticulo
    this->datos.erase(it);
    std::make_heap(this->datos.begin(), this->datos.end());

    return true;
}

template <class T>
void monticulo<T>::inordenEnLista(std::list<T>& lista) {

    //se hace una copia para no modificar el monticulo
    std::deque<T> copia = this->datos;

    //la salida del monticulo debe quedar ordenada
    std::sort(copia.begin(), copia.end());

    typename std::deque<T>::iterator it;

    for (it = copia.begin(); it != copia.end(); it++) {
        lista.push_back(*it);
    }
}

#endif
