/*
 * Main.cpp
 *
 *  Created on: 27-dic-2012
 *      Author: Alvaro
 */

#include "LectorNoticias.h"
#include "Articulo.h"
#include "Analizador.h"
#include "PresentadorAgrupacionesTxt.h"
#include "PresentadorAgrupacionesJson.h"
#include <iostream>
#include <fstream>

int main() {

  LectorNoticias lectorNoticias{"data"};
	Analizador a1{};
	a1.setNoticas(lectorNoticias.leerNoticias());

	std::cout << "Título noticias\n\n";
	std::cout << a1.toString();
	std::cout << "\n\n";

	PresentadorAgrupacionesTxt presentadorTxt(std::cout);
	std::cout << "Agrupación 1\n\n";
	presentadorTxt.presentar (a1.agruparNoticias());
	std::cout << "\n\n";

	std::cout << "Agrupación 2\n\n";
	presentadorTxt.presentar (a1.agruparNoticiasGeneral());

	std::ofstream f;
	f.open("agrupacion1.json", std::ofstream::out);
	if (f.is_open()) {
      PresentadorAgrupacionesJson presentadorJson(f);
      presentadorJson.presentar (a1.agruparNoticias());
	}
	f.close();

    f.open("agrupacion2.json", std::ofstream::out);
    if (f.is_open()) {
      PresentadorAgrupacionesJson presentadorJson(f);
      presentadorJson.presentar (a1.agruparNoticiasGeneral());
    }
    f.close();

	return 0;
}

