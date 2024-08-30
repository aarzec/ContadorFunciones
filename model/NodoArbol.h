/*************************
 * UFA-ESPE
 * ALUMNOS: Andrés Romero
 *************************/
#ifndef NODO_ARBOL_H
#define NODO_ARBOL_H

#include <iostream>
#include <string>

using namespace std;

class NodoArbol {
    private:
        std::string valor;
        NodoArbol* izquierda = nullptr;
        NodoArbol* derecha = nullptr;
        NodoArbol* padre = nullptr;
    public:
        NodoArbol();
        NodoArbol(std::string val);
        std::string getValor();
        NodoArbol* getIzquierda();
        NodoArbol* getDerecha();
        NodoArbol* getPadre();
        void setValor(std::string val);
        void setIzquierda(NodoArbol* nodo);
        void setDerecha(NodoArbol* nodo);
        void setPadre(NodoArbol* nodo);

        static void recorrerInOrden(NodoArbol* nodo);
        static void recorrerPreOrden(NodoArbol *nodo);
        static void recorrerPostOrden(NodoArbol *nodo);

        static void insertar(NodoArbol* nodo, std::string val);
        static bool buscar(NodoArbol* nodo, std::string val);
        static int tamano(NodoArbol* nodo);

        static void imprimir(NodoArbol* nodo);
};

#endif