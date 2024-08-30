#include <iostream>
#include "NodoArbol.h"

NodoArbol::NodoArbol() {}

NodoArbol::NodoArbol(std::string val) {
    valor = val;
}

std::string NodoArbol::getValor() {
    return valor;
}

void NodoArbol::setValor(std::string val) {
    valor = val;
}

NodoArbol* NodoArbol::getIzquierda() {
    return izquierda;
}

void NodoArbol::setIzquierda(NodoArbol* nodo) {
    izquierda = nodo;
}

NodoArbol* NodoArbol::getDerecha() {
    return derecha;
}

void NodoArbol::setDerecha(NodoArbol* nodo) {
    derecha = nodo;
}

NodoArbol* NodoArbol::getPadre() {
    return derecha;
}

void NodoArbol::setPadre(NodoArbol* nodo) {
    derecha = nodo;
}

void NodoArbol::recorrerInOrden(NodoArbol* nodo) {
    if (nodo == nullptr) {
        return;
    }

    recorrerInOrden(nodo->getIzquierda());
    std::cout << nodo->getValor() << " ";
    recorrerInOrden(nodo->getDerecha());
}

void NodoArbol::recorrerPreOrden(NodoArbol* nodo) {
    if (nodo == nullptr) {
        return;
    }

    std::cout << nodo->getValor() << " ";
    recorrerPreOrden(nodo->getIzquierda());
    recorrerPreOrden(nodo->getDerecha());
}

void NodoArbol::recorrerPostOrden(NodoArbol* nodo) {
    if (nodo == nullptr) {
        return;
    }

    recorrerPostOrden(nodo->getIzquierda());
    recorrerPostOrden(nodo->getDerecha());
    std::cout << nodo->getValor() << " ";
}

void NodoArbol::insertar(NodoArbol *nodo, std::string val) {
    NodoArbol* nodoInsertar;
    if (val < nodo->getValor()) {
        nodoInsertar = nodo->getIzquierda();
        if (nodoInsertar == nullptr) {
            nodoInsertar = new NodoArbol(val);
            nodo->setIzquierda(nodoInsertar);
        } else {
            insertar(nodoInsertar, val);
        }
    } else {
        nodoInsertar = nodo->getDerecha();
        if (nodoInsertar == nullptr) {
            nodoInsertar = new NodoArbol(val);
            nodo->setDerecha(nodoInsertar);
        } else {
            insertar(nodoInsertar, val);
        }
    }
}

bool NodoArbol::buscar(NodoArbol *nodo, std::string val) {
    if (nodo == nullptr) {
        return false;
    }

    if (nodo->getValor() == val) {
        return true;
    }

    if (val < nodo->getValor()) {
        return buscar(nodo->getIzquierda(), val);
    } else {
        return buscar(nodo->getDerecha(), val);
    }
}

int NodoArbol::tamano(NodoArbol *nodo){
    if (nodo == nullptr) {
        return 0;
    }

    return 1 + tamano(nodo->getIzquierda()) + tamano(nodo->getDerecha());
}

void NodoArbol::imprimir(NodoArbol *nodo) {
    if (nodo == nullptr) {
        return;
    }

    imprimir(nodo->getIzquierda());
    std::cout << nodo->getValor() << " -> ";
    imprimir(nodo->getDerecha());
}
