#include<iostream>//Lib. que maneja entrada y salida cout/cin
#include<exception> //Lib. que me permite abortar el juego
using namespace std;
#define NO_JUGAR 0
#define ESPACIO_VACIO 1
#define FICHAS_BLANCAS 2
#define FICHAS_NEGRAS 3
//Aniadimos los nuevos tipos de ficha, dama blanca y dama negra.
#define DAMA_BLANCA 4
#define DAMA_NEGRA 5
#define FILAS 8
#define COLUMNAS 8

int intro();// Funcion que pinta y colorea a la Universidad Europea
void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino);//Intercambia fichas
int turno(int matrix[FILAS][COLUMNAS], int jugador, int filaOrigen, int colOrigen, int filaDestino, int colDestino);//Gestiona los turno y movimientos
char simbolos(int i);//Me ayuda a rellenar mi matrix, convierte los numeros en simbolos
void tablero(int matrix[FILAS][COLUMNAS], int ficha_turno);//Dibuja el tablero en base al turno del jugador

int intro() {
	int op = 0;
	do {
		do {
			system("cls");
			cout << "\t\t_____________________________________________________________________" << endl;
			cout << "\t\t                                                                    " << endl;
			cout << "\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISE�O" << endl;
			cout << "\t\t_____________________________________________________________________" << endl << endl;
			cout << "\t\tProf.:Christian Sucuzhanay.                  Alumno : xxxxxxxxx" << endl << endl << endl;
			cout << "\t\t              << JUEGO DE LAS DAMAS ESPANOLAS >>" << endl << endl;
			cout << "\t\t\t    ** Seleccione una opcion del menu [ 0-9] **" << endl << endl;
			cout << "\t\t\t\t  [ 1 ] Ver reglas del juego " << endl;
			cout << "\t\t\t\t  [ 2 ] Jugar" << endl;
			cout << "\t\t\t\t  [ 0 ] SALIR" << endl << endl;
			cout << "\t\t\t              Ingrese su opcion ? : ";
			cin >> op;
		} while (op<0 || op>2);
		switch (op) {
			case 1:
				system("cls");
				cout << "\t\t_____________________________________________________________________" << endl;
				cout << "\t\t                                                                    " << endl;
				cout << "\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISE�O" << endl;
				cout << "\t\t_____________________________________________________________________" << endl << endl;
				cout << "\t\tProf.Christian Sucuzhanay.                  Alumno: " << endl << endl << endl;
				cout << "\t\t            << REGLAS DEL JUEGO DE LAS DAMAS ESPANOLAS >>\n";
				cout << "\t\t           ----------------------------------------------\n\n";
				cout << "\t\t1.- Inician el juego las fichas blancas por defecto" << endl << endl;
				cout << "\t\t2.- Las fichas SOLO se mueven 1 casilla hacia ADELANTE y en DIAGONAL\n ";
				cout << "\t\t    excepto al comer FICHA que pueden saltar\n\n";
				cout << "\t\t3.- Las fichas SALTAN mas de una casilla  SOLO cuando haya una ficha\n ";
				cout << "\t\t    contaria y la siguiente este vacia\n\n ";
				cout << "\t\t4.- Si alcanzamos la ultima fila opuesta a nuestro turno con una ficha\n";
				cout << "\t\t    esta se convierte en dama\n\n ";
				cout << "\t\t5.- Las damas solo se pueden mover en diagonal pero pueden moverse tantas\n\n";
				cout << "\t\t    casillas como quieran, eso si, no pueden ni comer fichas propias, ni\n\n ";
				cout << "\t\t    dos fichas contrarias seguidas. Es decir, si se mueve N posiciones\n\n ";
				cout << "\t\t    en diagonal y se encuentra una ficha contraria, se la come y se queda\n\n ";
				cout << "\t\t    una posicion tras la ficha comida\n\n ";
				cout << "\t\t6.- Gana quien coma mas fichas \n\n";
				cout << "\t\t7.- Si pasan mas de 2 horas sin que nadie gane se declara EMPATE\n\n\n\n ";
				cout << "\t\t\t\t PULSE [ 0 ] para SALIR: ";
				cin >> op;
				intro();
			case 2:
				break;
			case 0:
				system("cls");
				abort();
		}
		return 0;
	} while (op != 0);
	abort();

}

int turno(int matrix[FILAS][COLUMNAS], int jugador, int filaOrigen, int colOrigen, int filaDestino, int colDestino)//Gestiona movimientos y turnos
{
	int comerFichaBlancas;
	int comerFichaNegras;

	if ((filaOrigen < 0 && FILAS <= filaOrigen) && (colOrigen < 0 && COLUMNAS <= colOrigen)) { // Comprueba filas y col esten dentro del tablero
		cout << "\n No ves que el tablero no tiene esa posicion ? Estas fuera del tablero\n";
		return -1;
	}
	if ((filaDestino < 0 && FILAS <= filaDestino) && (colDestino < 0 && COLUMNAS <= colDestino)) {// Comprueba filas y col esten dentro del tablero
		cout << "\n No ves que el tablero no tiene esa posicion ? Estas fuera del tablero\n";
		return -1;
	}
	if (jugador == -1) { //Si el jugador no es un jugador valido
		cout << "Ficha no valida";
		return -1;
	}

	if (matrix[filaDestino][colDestino] != ESPACIO_VACIO) {//Comprueba que muevas solo espacios vacios.
		cout << "\nSolo puedes mover a un espacios VACIOS!!";
		return -1;
	}

	if (jugador == FICHAS_BLANCAS) {//Comprueba que el movimiento de las BLANCAS no sea hacia atras
		if (filaOrigen <= filaDestino) {
			cout << "\nNo te da o que ??? No puedes mover hacia atras o quedarte en el mismo lugar\n";
			return -1;
		}
	}
	if(jugador == FICHAS_NEGRAS){//Comprueba que el movimiento de las NEGRAS no sea hacia atras
		if (filaOrigen >= filaDestino) {
			cout << "\nNo te da o que ??? No puedes mover hacia atras o quedarte en el mismo lugar\n";
			return -1;
		}
	}

	if ((jugador == FICHAS_BLANCAS) || (jugador == FICHAS_NEGRAS)) { //Si se esta jugando con fichas blancas o negras
		//Comprueba si es un movimiento normal, una sola posicion
		if (filaOrigen - filaDestino == -1 || filaOrigen - filaDestino == 1) {
			if (colOrigen - colDestino == 1 || colOrigen - colDestino == -1) {
				intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
				return 0;
			}
		}

		//Comprueba si ha comido ficha de adversario
		if (filaOrigen - filaDestino == -2 || filaOrigen - filaDestino == 2) {
			if (colOrigen - colDestino == -2 || colOrigen - colDestino == 2) {
				// Comprueba si en la posicion del salto hay ficha contraria
				if (filaOrigen < filaDestino) { // Movimiento hacia abajo
					comerFichaBlancas = filaOrigen + 1;
				}
				else { // Movimiento hacia arriba
					comerFichaBlancas = filaOrigen - 1;
				}
				if (colOrigen < colDestino) { // Movimiento hacia abajo
					comerFichaNegras = colOrigen + 1;
				}
				else { // Movimiento hacia arriba
					comerFichaNegras = colOrigen - 1;
				}

				if (jugador == FICHAS_BLANCAS) //Comprobamos que la ficha de delante es una ficha negra o dama negra
				{
					if ((matrix[comerFichaBlancas][comerFichaNegras] != FICHAS_NEGRAS) && (matrix[comerFichaBlancas][comerFichaNegras] != DAMA_NEGRA)) {
						cout << "\nSolo puedes saltar si COMES FICHA NEGRA\n";
						return -1;
					}
				}
				if (jugador == FICHAS_NEGRAS) { //Comprobamos que la ficha de delante es una ficha blanca o dama blanca
					if ((matrix[comerFichaBlancas][comerFichaNegras] != FICHAS_BLANCAS) && (matrix[comerFichaBlancas][comerFichaNegras] != DAMA_BLANCA)) {
						cout << "\nSolo puedes saltar si COMES FICHA BLANCA\n";
						return -1;
					}
				}
				matrix[comerFichaBlancas][comerFichaNegras] = 1;
				intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
				return 0;
			}
		}
	}

	if ((jugador == DAMA_BLANCA) || (jugador == DAMA_NEGRA)) { //Si se esta jugando con damas blancas o damas negras

		if ((filaOrigen + colOrigen) == (filaDestino + colDestino)) { //Comprobamos que este en la diagonal cuyos i,j origen sumados sean iguales a sus i,j destinos sumados (diagonal derecha de subida y diagonal izquierda de bajada)

			if ((filaOrigen > filaDestino) && (colOrigen < colDestino)) { //Diagonal derecha de subida
				for (int i = filaOrigen-1, j = colOrigen+1; i >= filaDestino && j <= colDestino; i--, j++) { //Recorremos hasta la posicion destino, empezando una casilla por delante de la posicion original
					if (jugador == DAMA_BLANCA) { //Si es una dama blanca
						if ((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA)) {
							cout << "No puedes sobrepasar Fichas Blancas o Damas Blancas" << endl; //Comprobamos que en ningun momento haya una ficha o dama blanca por el camino
							return -1;
						}
						if (((matrix[i][j] == FICHAS_NEGRAS) && (matrix[i - 1][j + 1] == FICHAS_NEGRAS))||((matrix[i][j] == DAMA_NEGRA)&&(matrix[i - 1][j + 1] == DAMA_NEGRA))) {
							//Si nos encontramos con dos fichas o damas negras seguidas, no podemos saltarlas
							cout << "Imposible moverte hasta alli, dos fichas negras seguidas en tu camino" << endl;
							return -1;
						}
						if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMA_NEGRA))&&(matrix[i - 1][j + 1] == ESPACIO_VACIO)) {
							//Si nos encontramos con una ficha o dama negra en el camino y la siguiente posicion es un espacio vacio, nos la comemos y nos vemos obligados a quedarnos una posicion despues de ella, es decir, en el espacio vacio
							matrix[i][j] = ESPACIO_VACIO;
							intercambio(matrix, filaOrigen, colOrigen, i - 1, j + 1);
							return 0;
						}
						if ((i == filaDestino) && (j == colDestino)) {
							//Si hemos llegado hasta la posicion elegida sin encontrarnos con nada por delante llegamos hasta la posicion destino
							intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
							return 0;
						}
					}
					else { //Si es una dama negra
						if ((matrix[i][j] == FICHAS_NEGRAS) || (matrix[i][j] == DAMA_NEGRA)) {
							cout << "No puedes sobrepasar fichas negras" << endl; //Comprobamos que en ningun momento haya una ficha negra o dama negra por el camino
							return -1;
						}
						if (((matrix[i][j] == FICHAS_BLANCAS) && (matrix[i - 1][j + 1] == FICHAS_BLANCAS))||((matrix[i][j] == DAMA_BLANCA)&&(matrix[i - 1][j + 1] == DAMA_BLANCA))) {
							//Si nos encontramos con dos fichas blacas seguidas o dos damas blancas seguidas, no podemos saltarlas
							cout << "Imposible moverte hasta alli, dos fichas blancas seguidas en tu camino" << endl;
							return -1;
						}
						if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA)) && (matrix[i - 1][j + 1] == ESPACIO_VACIO)) {
							//Si nos encontramos con una ficha blanca o dama blanca en el camino y la siguiente posicion es un espacio vacio, nos la comemos y nos vemos obligados a quedarnos una posicion despues de ella, es decir, en el espacio vacio
							matrix[i][j] = ESPACIO_VACIO;
							intercambio(matrix, filaOrigen, colOrigen, i - 1, j + 1);
							return 0;
						}
						if ((i == filaDestino) && (j == colDestino)) {
							//Si hemos llegado hasta la posicion elegida sin encontrarnos con nada por delante
							intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
							return 0;
						}
					}
				}
			}

			if ((filaOrigen < filaDestino) && (colOrigen > colDestino)) { //Diagonal izquierda de bajada
				for (int i = filaOrigen+1, j = colOrigen-1; i <= filaDestino && j >= colDestino; i++, j--) {
					if (jugador == DAMA_BLANCA) { //Si es una dama blanca
						if ((matrix[i][j] == FICHAS_BLANCAS) || (matrix[i][j] == DAMA_BLANCA)) {
							cout << "No puedes sobrepasar Fichas Blancas o Damas Blancas" << endl; //Comprobamos que en ningun momento haya una ficha blanca o dama blanca por el camino
							return -1;
						}
						if (((matrix[i][j] == FICHAS_NEGRAS) && (matrix[i + 1][j - 1] == FICHAS_NEGRAS)) || ((matrix[i][j] == DAMA_NEGRA) && (matrix[i + 1][j - 1] == DAMA_NEGRA))) {
							//Si nos encontramos con dos fichas o damas negras seguidas, no podemos saltarlas
							cout << "Imposible moverte hasta alli, dos fichas negras seguidas en tu camino" << endl;
							return -1;
						}
						if (((matrix[i][j] == FICHAS_NEGRAS) || (matrix[i][j] == DAMA_NEGRA)) && (matrix[i + 1][j - 1] == ESPACIO_VACIO)) {
							//Si nos encontramos con una ficha o dama negra en el camino y la siguiente posicion es un espacio vacio, nos la comemos y nos vemos obligados a quedarnos una posicion despues de ella, es decir, en el espacio vacio
							matrix[i][j] = ESPACIO_VACIO;
							intercambio(matrix, filaOrigen, colOrigen, i + 1, j - 1);
							return 0;
						}
						if ((i == filaDestino) && (j == colDestino)) {
							//Si hemos llegado hasta la posicion elegida sin encontrarnos con nada por delante
							intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
							return 0;
						}
					}
					else { //Si es una dama negra
						if ((matrix[i][j] == FICHAS_NEGRAS) || (matrix[i][j] == DAMA_NEGRA)) {
							cout << "No puedes sobrepasar fichas negras" << endl; //Comprobamos que en ningun momento haya una ficha negra o dama negra por el camino
							return -1;
						}
						if (((matrix[i][j] == FICHAS_BLANCAS) && (matrix[i + 1][j - 1] == FICHAS_BLANCAS)) || ((matrix[i][j] == DAMA_BLANCA) && (matrix[i + 1][j - 1] == DAMA_BLANCA))) {
							//Si nos encontramos con dos fichas blacas seguidas o dos damas blancas seguidas, no podemos saltarlas
							cout << "Imposible moverte hasta alli, dos fichas blancas seguidas en tu camino" << endl;
							return -1;
						}
						if (((matrix[i][j] == FICHAS_BLANCAS) || (matrix[i][j] == DAMA_BLANCA)) && (matrix[i + 1][j - 1] == ESPACIO_VACIO)) {
							//Si nos encontramos con una ficha blanca o dama blanca en el camino y la siguiente posicion es un espacio vacio, nos la comemos y nos vemos obligados a quedarnos una posicion despues de ella, es decir, en el espacio vacio
							matrix[i][j] = ESPACIO_VACIO;
							intercambio(matrix, filaOrigen, colOrigen, i + 1, j - 1);
							return 0;
						}
						if ((i == filaDestino) && (j == colDestino)) {
							//Si hemos llegado hasta la posicion elegida sin encontrarnos con nada por delante
							intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
							return 0;
						}
					}
				}
			}

		}

		if ((filaOrigen - colOrigen) == (filaDestino - colDestino)) { //Comprobamos que este en la diagonal cuyos i,j origen restados sean iguales a sus i,j destinos restados (diagonal derecha de bajada y diagonal izquierda de subida)

			if ((filaOrigen < filaDestino) && (colOrigen < colDestino)) { //Diagonal derecha de bajada
				for (int i = filaOrigen+1, j = colOrigen+1; i <= filaDestino && j <= colDestino; i++, j++) {
					if (jugador == DAMA_BLANCA) { //Si es una dama blanca
						if ((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA)) {
							cout << "No puedes sobrepasar Fichas Blancas o Damas Blancas" << endl; //Comprobamos que en ningun momento haya una ficha o dama blanca por el camino
							return -1;
						}
						if (((matrix[i][j] == FICHAS_NEGRAS) && (matrix[i + 1][j + 1] == FICHAS_NEGRAS))||((matrix[i][j] == DAMA_NEGRA)&&(matrix[i + 1][j + 1] == DAMA_NEGRA))) {
							//Si nos encontramos con dos fichas o damas negras seguidas, no podemos saltarlas
							cout << "Imposible moverte hasta alli, dos fichas negras seguidas en tu camino" << endl;
							return -1;
						}
						if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMA_NEGRA))&&(matrix[i + 1][j + 1] == ESPACIO_VACIO)) {
							//Si nos encontramos con una ficha o dama negra en el camino y la siguiente posicion es un espacio vacio, nos la comemos y nos vemos obligados a quedarnos una posicion despues de ella, es decir, en el espacio vacio
							matrix[i][j] = ESPACIO_VACIO;
							intercambio(matrix, filaOrigen, colOrigen, i + 1, j + 1);
							return 0;
						}
						if ((i == filaDestino) && (j == colDestino)) {
							//Si hemos llegado hasta la posicion elegida sin encontrarnos con nada por delante
							intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
							return 0;
						}
					}
					else { //Si es una dama negra
						if ((matrix[i][j] == FICHAS_NEGRAS) || (matrix[i][j] == DAMA_NEGRA)) {
							cout << "No puedes sobrepasar fichas negras" << endl; //Comprobamos que en ningun momento haya una ficha negra o dama negra por el camino
							return -1;
						}
						if (((matrix[i][j] == FICHAS_BLANCAS) && (matrix[i + 1][j + 1] == FICHAS_BLANCAS))||((matrix[i][j] == DAMA_BLANCA)&&(matrix[i + 1][j + 1] == DAMA_BLANCA))) {
							//Si nos encontramos con dos fichas blacas seguidas o dos damas blancas seguidas, no podemos saltarlas
							cout << "Imposible moverte hasta alli, dos fichas blancas seguidas en tu camino" << endl;
							return -1;
						}
						if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA)) && (matrix[i + 1][j + 1] == ESPACIO_VACIO)) {
							//Si nos encontramos con una ficha blanca o dama blanca en el camino y la siguiente posicion es un espacio vacio, nos la comemos y nos vemos obligados a quedarnos una posicion despues de ella, es decir, en el espacio vacio
							matrix[i][j] = ESPACIO_VACIO;
							intercambio(matrix, filaOrigen, colOrigen, i + 1, j + 1);
							return 0;
						}
						if ((i == filaDestino) && (j == colDestino)) {
							//Si hemos llegado hasta la posicion elegida sin encontrarnos con nada por delante
							intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
							return 0;
						}
					}
				}
			}

			if ((filaOrigen > filaDestino) && (colOrigen > colDestino)) { //Diagonal izquierda de subida
				for (int i = filaOrigen-1, j = colOrigen-1; i >= filaDestino && j >= colDestino; i--, j--) {
					if (jugador == DAMA_BLANCA) { //Si es una dama blanca
						if ((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA)) {
							cout << "No puedes sobrepasar Fichas Blancas o Damas Blancas" << endl; //Comprobamos que en ningun momento haya una ficha o dama blanca por el camino
							return -1;
						}
						if (((matrix[i][j] == FICHAS_NEGRAS) && (matrix[i - 1][j - 1] == FICHAS_NEGRAS))||((matrix[i][j] == DAMA_NEGRA)&&(matrix[i - 1][j - 1] == DAMA_NEGRA))) {
							//Si nos encontramos con dos fichas o damas negras seguidas, no podemos saltarlas
							cout << "Imposible moverte hasta alli, dos fichas negras seguidas en tu camino" << endl;
							return -1;
						}
						if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMA_NEGRA))&&(matrix[i - 1][j - 1] == ESPACIO_VACIO)) {
							//Si nos encontramos con una ficha o dama negra en el camino y la siguiente posicion es un espacio vacio, nos la comemos y nos vemos obligados a quedarnos una posicion despues de ella, es decir, en el espacio vacio
							matrix[i][j] = ESPACIO_VACIO;
							intercambio(matrix, filaOrigen, colOrigen, i - 1, j - 1);
							return 0;
						}
						if ((i == filaDestino) && (j == colDestino)) {
							//Si hemos llegado hasta la posicion elegida sin encontrarnos con nada por delante
							intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
							return 0;
						}
					}
					else { //Si es una dama negra
						if ((matrix[i][j] == FICHAS_NEGRAS) || (matrix[i][j] == DAMA_NEGRA)) {
							cout << "No puedes sobrepasar fichas negras" << endl; //Comprobamos que en ningun momento haya una ficha negra o dama negra por el camino
							return -1;
						}
						if (((matrix[i][j] == FICHAS_BLANCAS) && (matrix[i - 1][j - 1] == FICHAS_BLANCAS))||((matrix[i][j] == DAMA_BLANCA)&&(matrix[i - 1][j - 1] == DAMA_BLANCA))) {
							//Si nos encontramos con dos fichas blacas seguidas o dos damas blancas seguidas, no podemos saltarlas
							cout << "Imposible moverte hasta alli, dos fichas blancas seguidas en tu camino" << endl;
							return -1;
						}
						if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA)) && (matrix[i - 1][j - 1] == ESPACIO_VACIO)) {
							//Si nos encontramos con una ficha blanca o dama blanca en el camino y la siguiente posicion es un espacio vacio, nos la comemos y nos vemos obligados a quedarnos una posicion despues de ella, es decir, en el espacio vacio
							matrix[i][j] = ESPACIO_VACIO;
							intercambio(matrix, filaOrigen, colOrigen, i - 1, j - 1);
							return 0;
						}
						if ((i == filaDestino) && (j == colDestino)) {
							//Si hemos llegado hasta la posicion elegida sin encontrarnos con nada por delante
							intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
							return 0;
						}
					}
				}
			}
		}
	}

	cout << "Las fichas solo se pueden mover DIAGONALMENTE\n";
	return -1;

}


void tablero(int matrix[FILAS][COLUMNAS], int turno)//Pintar tablero
{
	int pintarFilas, pintarCol;
	system("cls");
	cout << "\t\t_____________________________________________________________________" << endl;
	cout << "\t\t                                                                    " << endl;
	cout << "\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISE�O" << endl;
	cout << "\t\t_____________________________________________________________________" << endl << endl;
	cout << "\t\tProf.: Christian Sucuzhanay                  Alumno: xxxxxxxxx" << endl << endl << endl;
	cout << "\t\t                << TABLERO DE LAS DAMAS ESPANOLAS >>" << endl << endl;
	cout << "\n\t\t\t\t     B = fichas BLANCAS";
	cout << "\n\t\t\t\t     N = fichas NEGRAS";
	cout << "\n\t\t\t\t     v = espacios VACIOS jugables";
	cout << "\n\t\t\t\t     X = fichas DAMAS BLANCAS";
	cout << "\n\t\t\t\t     Y = fichas DAMAS NEGRAS";
	cout << "\n\n\t\t\t\t   +---+---+---+---+---+---+---+---+\n";
	if (turno == FICHAS_BLANCAS) { //Vista turno blancas
		for (pintarFilas = 0; pintarFilas < FILAS; ++pintarFilas)
		{
			cout << "\t\t\t\t" << pintarFilas + 1 << "  | "; // Pinto filas
			for (pintarCol = 0; pintarCol < COLUMNAS; ++pintarCol)
			{
				cout << simbolos(matrix[pintarFilas][pintarCol]) << " | ";//Rellenamos tablero
				if ((pintarFilas == 3) && (pintarCol == 7)) {
					cout << "\t VISTA DEL JUGADOR CON FICHAS BLANCAS"; //Aniadimos un mensaje para aclarar el punto de vista del jugador que tiene el turno, y que asi pueda visualizar mejor su jugada en el tablero
				}
			}
			cout << "\n";
			cout << "\t\t\t\t   +---+---+---+---+---+---+---+---+\n";
		}
		cout << "\n\t\t\t\t     a   b   c   d   e   f   g   h\n\n\n";//Imprime leyenda para de colunmnas
	}
	else { //Vista turno negras
		for (pintarFilas = FILAS-1; pintarFilas >= 0; --pintarFilas)
		{
			cout << "\t\t\t\t" << pintarFilas + 1 << "  | "; // Pinto filas
			for (pintarCol = 0; pintarCol < COLUMNAS; ++pintarCol)
			{
				cout << simbolos(matrix[pintarFilas][pintarCol]) << " | ";//Rellenamos tablero
				if ((pintarFilas == 3) && (pintarCol == 7)) {
					cout << "\t VISTA DEL JUGADOR CON FICHAS NEGRAS"; //Aniadimos un mensaje para aclarar el punto de vista del jugador que tiene el turno, y que asi pueda visualizar mejor su jugada en el tablero
				}
			}
			cout << "\n";
			cout << "\t\t\t\t   +---+---+---+---+---+---+---+---+\n";
		}
		cout << "\n\t\t\t\t     a   b   c   d   e   f   g   h\n\n\n";//Imprime leyenda para de colunmnas
	}
}


void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino)//Cambia fichas en la matrix
{
	int temp;// Para almacenar mientras intercambio las coordenadas

	if ((matrix[filaOrigen][colOrigen] == FICHAS_BLANCAS)&&(filaDestino == 0)) { //Si es una ficha blanca y alcanza la fila destino donde llega a hacerse dama blanca
		matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino]; //La posicion del tipo ficha se convierte en vacio
		matrix[filaDestino][colDestino] = DAMA_BLANCA; //La ficha se convierte en dama blanca
	}
	else if ((matrix[filaOrigen][colOrigen] == FICHAS_NEGRAS) && (filaDestino == 7)) { //Si es una ficha negra y alcanza la fila destino donde llega a hacerse dama negra
		matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino]; //La posicion del tipo ficha se convierte en vacio
		matrix[filaDestino][colDestino] = DAMA_NEGRA; //La ficha se convierte en dama negra
	}
	else {
		temp = matrix[filaOrigen][colOrigen]; //Almacenamos tipo_ficha
		matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino]; //La posicion del tipo ficha se convierte en vacio
		matrix[filaDestino][colDestino] = temp; //Actualizamos la nueva posicion de nuestro tipo_ficha temporalmente almacenado
	}
}


char simbolos(int i)//Cambia letras por numeros
{
	switch (i)
	{
		case 0:
			return ' ';//no jugable
		case 1:
			return 'v';//espacio vacio
		case 2:
			return 'B';//blancas
		case 3:
			return 'N';//negras
		case 4:
			return 'X';//dama blanca
		case 5:
			return 'Y';//dama negra
	}
	return ('?');
}


int main()//Programa principal
{
	int filaOrigen, filaDestino;//Para almacernar las filas 1-8
	char colOrigen, colDestino;//Para almacenar el valor de las columnas que son a-h
	int matrix[FILAS][COLUMNAS] = { //Matrix de fichas
			 { 0,3,0,3,0,3,0,3 },
			 { 3,0,3,0,3,0,3,0 },
			 { 0,3,0,3,0,3,0,3 },
			 { 1,0,1,0,1,0,1,0 },
			 { 0,1,0,1,0,1,0,1 },
			 { 2,0,2,0,2,0,2,0 },
			 { 0,2,0,2,0,2,0,2 },
			 { 2,0,2,0,2,0,2,0 } };//Tablero 0= vacio, 2=Blancas, 3=Negras
	intro();//Funcion que pinta y colorea Universidad Europea
	system("cls");//Limpia pantalla
	for (;;)
	{//Bucle infinito para captura y validacion de coordenada de ficha
		tablero(matrix, 2);//Dibujo el tablero, TURNO BLANCAS, le paso la matrix d para dibujar el tablero
		while (1) {//Mientras no sean validas las coordenadas no sale de este while
			cout << "\nTURNO de las  * BLANCAS *  Ingrese FILA 1-8 y COLUMNA a-h de la ficha que desea mover, por ejemplo 3b\n";
			cin >> filaOrigen >> colOrigen;//Capturo coordenada de origen Blancas
			colOrigen = tolower(colOrigen);//Permite que el usuario meta las columnas en MAYUSCULAS o minusculas
			cout << "Introduzca FILA 1-8 y COLUMNA a-h del destino de la ficha a mover,  por ejemplo 4a \n";
			cin >> filaDestino >> colDestino;//Capturo coordenada de destino Blancas
			colDestino = tolower(colDestino);

			int tipo_ficha;
			if (matrix[filaOrigen-1][colOrigen - 'a'] == FICHAS_BLANCAS) { //Si la posicion elegida es una ficha blanca, el tipo de ficha a jugar es una ficha blanca
				tipo_ficha = FICHAS_BLANCAS;
			}
			else if (matrix[filaOrigen-1][colOrigen - 'a'] == DAMA_BLANCA) { //Si la posicion elegida es una dama blanca, el tipo de ficha a jugar es una dama blanca
				tipo_ficha = DAMA_BLANCA;
			}
			else { //Si no es ni una ficha blanca o una dama blanca y estamos en el turno de las blancas, la ficha a jugar no es valida.
				tipo_ficha = -1; //Ficha no valida
			}

			if (turno(matrix, tipo_ficha, filaOrigen - 1, colOrigen - 'a', filaDestino - 1, colDestino - 'a') == 0)//Compruebo que sean validos las coordenadas, cuando devuelve un 0 es que el turno ha sido valido
				break;
			cout << "\nINTENTA de nuevo :\n";
		}
		system("cls");
		tablero(matrix,3);//Dibujo el tablero, TURNO NEGRAS, le paso la matrix d para dibujar el tablero
		while (1) {//Mientras no sean validas las coordenadas no sale de este while
			cout << "\nTURNO de las  * NEGRAS *  Ingrese FILA 1-8 y COLUMNA a-h de la ficha que desea mover, por ejemplo 6g\n";
			cin >> filaOrigen >> colOrigen;//Capturo coordenada de origen Negras
			colOrigen = tolower(colOrigen);
			cout << "Introduzca FILA 1-8 y COLUMNA a-h del destino de la ficha a mover,  por ejemplo 5h \n";
			cin >> filaDestino >> colDestino;//Capturo coordenada de destino Negras
			colDestino = tolower(colDestino);//Permite que el usuario meta las columnas en MAYUSCULAS o minusculas

			int tipo_ficha;
			if (matrix[filaOrigen-1][colOrigen - 'a'] == FICHAS_NEGRAS) { //Si la posicion elegida es una ficha negra, el tipo de ficha a jugar es una ficha negra
				tipo_ficha = FICHAS_NEGRAS;
			}
			else if (matrix[filaOrigen-1][colOrigen - 'a'] == DAMA_NEGRA) { //Si la posicion elegida es una dama negra, el tipo de ficha a jugar es una dama negra
				tipo_ficha = DAMA_NEGRA;
			}
			else {//Si no es ni una ficha negra o una dama negra y estamos en el turno de las negras, la ficha a jugar no es valida.
				tipo_ficha = -1; //Ficha no valida
			}

			if (turno(matrix, tipo_ficha, filaOrigen - 1, colOrigen - 'a', filaDestino - 1, colDestino - 'a') == 0)//Comprueba que sean validos las coordenadas, cuando devuelve un 0 es que el turno ha sido valido
				break;
			cout << "\nINTENTA de nuevo :\n)";
		}
	}
	return 0;
}
