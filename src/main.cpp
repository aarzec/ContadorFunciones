/**
UNIVERSIDAD DE LAS FUERZAS ARMADAS - ESPE
Autor: Andrés Romero
Materia: Estructura de Datos - 2024
*/

#include <fstream>
#include <iostream>
#include <filesystem>
#include "../model/ListasSimples.h"

void obtenerListaArchivos(ListaSimple<std::string>& listaArchivos, std::string directorio) {
    for (const auto& entrada : std::filesystem::directory_iterator(directorio)) {
        if (entrada.is_directory()) {
            obtenerListaArchivos(listaArchivos, entrada.path());
        } else {
            std::string entradaStr = entrada.path().string();
            std::string ext = entradaStr.substr(entradaStr.find_last_of("."));
            if (ext == ".h" || ext == ".c" || ext == ".cpp" || ext == ".hpp") {
                listaArchivos.Insertar(entradaStr);
            }
        }
    }
}

void limpiarLinea(std::istream& linea) {
    char ch;
    bool enComentario;

    while (linea.get(ch)) {
        if (enComentario) {
            if (ch == '*' && linea.peek() == '/') {
                linea.get();
                enComentario = false;
            }
        } else {
            if (ch == '/') {
                if (linea.peek() == '/') {
                    // Comentarios de una linea
                    while (linea.get(ch) && ch != '\n');
                } else if (linea.peek() == '*') {
                    // Comentarios de multiples lineas
                    linea.get();
                    enComentario = true;
                } else {
                    linea.putback(ch);
                    break;
                }
            } else if (ch != ' ') {
                linea.putback(ch);
                break;
            }
        }
    }
}

bool procesarIdentificador(std::istream& linea, std::string& identificador) {
    limpiarLinea(linea);
    identificador.clear();
    char ch;
    while (linea.get(ch) && (std::isalnum(ch) || ch == '_' || ch == ':')) {
        identificador += ch;
    }
    if (!identificador.empty()) {
        linea.putback(ch);
        return true;
    }
    return false;
}

bool esDefinicionDeFuncion(std::istream& linea) {
    limpiarLinea(linea);
    char ch;
    if (linea.get(ch) && ch == '(') {
        int nParentesis = 1;
        // Identificar paréntesis (eg. fn(((cosasQueEvaluar) + 1).algo()) + 1)
        while (linea.get(ch)) {
            if (ch == '(') nParentesis++;
            if (ch == ')') nParentesis--;
            if (nParentesis == 0) break;
        }
        limpiarLinea(linea);
        // Identificar inicio de función
        if (linea.get(ch) && ch == '{') {
            linea.putback(ch);
            return true;
        }
    }
    return false;
}

void procesarArchivo(const std::string& rutaArchivo, ListaSimple<std::string>& listaFunciones) {
    std::ifstream archivo{rutaArchivo};
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo " << rutaArchivo << std::endl;
        return;
    }

    std::string palabraClave;

    while (archivo) {
        std::string tipoRetorno, nombreFuncion;
        if (procesarIdentificador(archivo, tipoRetorno) && procesarIdentificador(archivo, nombreFuncion)) {
            // Tenemos un tipo de retorno y un identificador, es una definición de función?
            if (esDefinicionDeFuncion(archivo) && tipoRetorno != "else" && tipoRetorno != ":") {
                listaFunciones.Insertar(tipoRetorno + " " + nombreFuncion);

                // Antes de seguir, saltar todo el cuerpo de la función
                char ch;
                int nLlaves;
                while (archivo.get(ch)) {
                    if (ch == '{') nLlaves++;
                    if (ch == '}') nLlaves--;
                    if (nLlaves == 0) break;
                }
            }
        }
    }
}

int main(int argc, const char** argv) {
    ListaSimple<std::string> listaArchivos, listaFunciones;
    obtenerListaArchivos(listaArchivos, "/home/kmd/Downloads/proyecto_v21-jun/");

    listaArchivos.recorrer([&](Nodo<std::string>* nodo){
        std::cout << "Procesando: " << nodo->getDato() << std::endl;
        procesarArchivo(nodo->getDato(), listaFunciones);
    });

    std::cout << "\nFunciones encontradas " << "(" << listaFunciones.Tamano() << "): " << std::endl;
    listaFunciones.Mostrar();

    return 0;
}
