/*NomProgramadores> Oscar Martinez, Armando Prado
  NomPrograma> juego de domino
  Fecha> 07/noviembre/2018
  DP> juego de domino para un maximo de 4 jugadores
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define p printf
#define s scanf
#define SOPA 0
#define PYR1 1
#define PYR2 2
#define PYR3 3
#define PYR4 4
#define BOARD 5
#define MACHINE 6
#define NUMFICHAS 28
//___________________________________________________________________Prototipos___________________________________________________________________________
int player_take_ficha(int);
void player_put_ficha(int, int, int);
//________________________________________________________________________________________________________________________________________________________


//___________________________________________________________________Variables globales___________________________________________________________________
int numPlayers; //Numero de jugadores 
int val_left;   //ultimo valor de la ficha del tablero en la izquierda
int val_right;	//ultimo valor de la ficha del tablero en la derecha
int posX_left;  //Posicion de la ultima ficha del tablero de la izquierda
int posX_right; //Posicion de la ultima ficha del tablero de la derecha

struct ficha
{
    int val1, 
		val2,
		posX,
		posY,
		pos, //si pos == 0 imprime val1 y val2, si pos != 0 imprime val2, val1
		isIn; //Sirve para saber en donde se encuentra la ficha: 0=sopa, 1=player1, 2=player2, 3=player3, 4=player4, 5=board, 6=machine
}fichas[NUMFICHAS];

struct player
{
    char name[50];
    int numFichas;
}players[MACHINE];

//________________________________________________________________________________________________________________________________________________________


//___________________________________________________________________Funciones generales__________________________________________________________________

void cursorPos(int x,int y){  
    //Establece la posicion del cursor en las coordenadas "x" y "y"
	HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
 }

int menu(){
	int opc;
	system("cls");
	p("\n\n\n\t\t\t\t\t\t\t\t\t\t  DOMINOC\n");// la c es la referencia de que esta hecho en c
	p("\n\n\t\t\t\t\t\t\t\t\t\t............\n\t\t\t\t\t\t\t\t\t\t..*......*..\n\t\t\t\t\t\t\t\t\t\t.***....***.\n\t\t\t\t\t\t\t\t\t\t.***....***.\n\t\t\t\t\t\t\t\t\t\t..*......*..\n\t\t\t\t\t\t\t\t\t\t............\n\t\t\t\t\t\t\t\t\t\t............\n\t\t\t\t\t\t\t\t\t\t############\n\t\t\t\t\t\t\t\t\t\t............\n\t\t\t\t\t\t\t\t\t\t............\n\t\t\t\t\t\t\t\t\t\t.....*......\n\t\t\t\t\t\t\t\t\t\t....***.....\n\t\t\t\t\t\t\t\t\t\t....***.....\n\t\t\t\t\t\t\t\t\t\t.....*......\n\t\t\t\t\t\t\t\t\t\t............\n");
	p("\n\n\t\t\t\t\t\t\t\t\tBinvenido al super domino CUCEI\n");
	p("\n\n\n\t\t\t\t\t\t\t\t\t\t1-Jugar (1 jugador)\n\n\t\t\t\t\t\t\t\t\t\t2-Jugar (Multijugador)\n\n\t\t\t\t\t\t\t\t\t\t3-Reglas\n\n\t\t\t\t\t\t\t\t\t\t4-Creditos\n\n\t\t\t\t\t\t\t\t\t\t5-Dejar de jugar\n\n\t\t\t\t\t\t\t\t\t\tOpcion --> ");
	scanf("%i",&opc);
	return opc;
}


void reglas(){
system("cls");
	p("\n\t\t\t\t\t\t\t\tReglas super domino");//cunado sepamos como funciona poner las reglas chidas
	p("\n\t\t1-Primero se ingreseran los nombres de los jugadores [maximo 4], si desean menos se debe ingresar una s para dejar de hacerlo");
	p("\n\t\t2-Esperar a que se repartan las fichas y posteriormente comenzara quien tenga la ficha doble mas alta");
	p("\n\t\t3-Despues cada jugador pondra fichas que sus numeros sean iguales al ultimo numero de las ultimas fichas puestas ya sea izquierda o derecha");
	p("\n\t\tlas fichas se colocoran ingresando el numero que se indica en la parte inferior de la ficha, posteriormente se selecciona el lado donde ponerla");
	p("\n\t\t0 para derecha y 1 para izquierda");
	p("\n\t\t4-En caso de no tener fichas para poner se debe ingresar 0 para comer fichas o -1 para pasar turno en caso de que ya no se tenga fichas para");
	p("\n\t\tcomer");
	p("\n\t\t5-Ganara quien termine sus fichas y si no es posible poner mas fichas ganara el jugador que tenga menos puntos en sus fichas");
	p("\n\n\t\tEs hora de jugar");
	p("\n\t\t\t\t\tPresione una tecla para continuar... ");
	getch();
}

void creditos(){
	system("cls");
	p("\n\n\n\t\t\t\t\t\t\t\t\t\tCreditos");
	p("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tCUCEI\n\t\t\t\t\t\t\t\tCentro Universitario De Ciencias Exactas e Ingenierias\n\n");
	p("\n\t\t\t\t\t\t\t\t\t\tMateria\n\t\t\t\t\t\t\t\tSeminario De Solucion De Problemas De Programacion\n\n\t\t\t\t\t\t\t\t\t\tSeccion: D12\n\n");
	p("\n\n\t\t\t\t\t\t\t\t\t\tCreadores\n\t\t\t\t\t\t\t\tOscar Martinez, codigo: 208699291\n\t\t\t\t\t\t\t\tArmando Prado,  codigo: 218292564");//poner los codigos 
	p("\n\n\t\t\t\t\t\t\t\t\t\tMaestra\n\t\t\t\t\t\t\t\tSandra Elizabet Quiñones Covarrubias");
	p("\n\n\t\t\t\t\t\t\t\t\tPresione una tecla para continuar... ");
	getch();
}

//________________________________________________________________________________________________________________________________________________________


//___________________________________________________________________Funciones de ficha___________________________________________________________________

void ficha_print(int index){
	//Imprime una ficha en el tablero segun sean los atributos de la ficha
	
	cursorPos(fichas[index].posX, fichas[index].posY);
	if (fichas[index].pos)
		p("[%i|%i]",fichas[index].val2, fichas[index].val1);
	else
		p("[%i|%i]",fichas[index].val1, fichas[index].val2);
}

void ficha_info(int index){
	//Muestra la informacion de la ficha
	p("\n\nFicha [%i]",index);
	p("\nVal1: %i",fichas[index].val1);
	p("\nVal2: %i",fichas[index].val2);
	p("\nPosX: %i",fichas[index].posX);
	p("\nPosY: %i",fichas[index].posY);
	p("\nPos:  %i",fichas[index].pos);
	p("\nIsIn: %i",fichas[index].isIn);
}

int ficha_mula(){
	//Busca que jugador tiene la mula mas alta y retorna el numero de jugador, si niniguno tiene mula se va por la ficha mas alta
	int pyr;
	
	posX_left = 80;
	posX_right = 80;
	//Busca la mula mas alta en la mano de los jugadores
	for(int i=NUMFICHAS; i>=0; i--)
		if(fichas[i].val1==fichas[i].val2 && fichas[i].isIn != 0){
			pyr = fichas[i].isIn;
			cursorPos(60,26);
			p("El jugador %s inicia la partida con la ficha [%i|%i]",players[fichas[i].isIn-1].name, fichas[i].val1, fichas[i].val2);
			player_put_ficha(i,80,0);
			cursorPos(60,27);
			val_left = fichas[i].val1;
			val_right = val_left;
			p("Presione una tecla para continuar... ");
			getch();
			system("cls");
			return pyr;
		}
			
	//
	
	//Busca la ficha mas alta en la mano de los jugadores
	for(int i=NUMFICHAS; i>=0; i--)
		if(fichas[i].isIn != 0){
			pyr = fichas[i].isIn;
			cursorPos(60,26);
			p("El jugador %s inicial la partida con la ficha [%i|%i]",players[fichas[i].isIn-1].name, fichas[i].val1, fichas[i].val2);
			player_put_ficha(i,80,0);
			cursorPos(60,27);
			val_left = fichas[i].val1;
			val_right = fichas[i].val2;
			p("Presione una tecla para continuar... ");
			getch();
			system("cls");
			return pyr;
		}
	//

}

//________________________________________________________________________________________________________________________________________________________


//___________________________________________________________________Funciones de fichas__________________________________________________________________
void fichas_inicialize(){
	//Inicializa los valores de las fichas
	int k=0;
    for(int i=0; i<=6; i++)
        for(int j=i; j<=6; j++){
        	fichas[k].val1=i;
        	fichas[k].val2=j;
        	fichas[k].pos=0;
        	fichas[k].isIn=0;
			k++;
		}
}

void fichas_info(){
	//Muestra la informacion de las fichas
	for(int index=0; index<NUMFICHAS; index++)
		ficha_info(index);
}

void fichas_repartir(){
	//Reparte las fichas entre los n jugadores y/o la maquina
	
	p("\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tIniciando Juego... espere un momento por favor.");
	if (numPlayers==1){
		//Repartir las fichas con la maquina
		srand(time(NULL));
		int fichaRepartida, numPzs=7,i,j,pyr; 
		for(i=0; i<numPzs; i++)
			for(j=0; j<2; j++){
				fichaRepartida=0;
				if(j)
					pyr=PYR1;
				else
					pyr=MACHINE;  
				while (!fichaRepartida)
					fichaRepartida = player_take_ficha(pyr);
			}
			
		players[PYR1-1].numFichas=numPzs;
		players[MACHINE-1].numFichas=numPzs;
	}
		
	else{
		srand(time(NULL));
		int fichaRepartida, numPzs=7,i,j; 
		for(i=0; i<numPzs; i++)
			for(j=0; j<numPlayers; j++){
				fichaRepartida=0;
				while (!fichaRepartida)
					fichaRepartida = player_take_ficha(j+1);
			}
			
		for(i=0; i<numPlayers; i++)
			players[i].numFichas=numPzs;
	}
	system("cls");
}


void fichas_player_show(int pyr){
	//Muestra las fichas que tiene un jugador
	
	 //Imprime las etiquetas de la mano del jugador
	int posX=70, posY=5, numFicha=1;
	cursorPos(posX+3,posY-3);
	p("Turno de: %s",players[pyr-1].name);
	cursorPos(posX-8,posY);
	p("fichas");
	cursorPos(posX-17,posY+2);
	p("numero de ficha");
	//
	
	//Imprime los comandos
	cursorPos(13,38);
	p("COMANDOS");
	cursorPos(9,40);
	p("-1 = pasar turno");
	cursorPos(10,42);
	p("0 = comer ficha");
	cursorPos(8,44);
	p("1-%i = poner ficha",players[pyr-1].numFichas);
	//
	
	//Imprime las fichas y el numero de ficha que tiene el jugador pyr
	for(int i=0; i<NUMFICHAS; i++){
		if(fichas[i].isIn==pyr){
			cursorPos(posX+1,posY+2);
			p("(%i)",numFicha);
			fichas[i].posX=posX;
			fichas[i].posY=posY;
			posX+=6;
			ficha_print(i);
			numFicha++;
		}
	}
	//
}

void fichas_board(){
	//Imprime las fichas en el tablero
	cursorPos(80,22);
	p("TABLERO");
	for(int i=0; i<NUMFICHAS; i++)
		if(fichas[i].isIn==5)
			ficha_print(i);
}

void fichas_left(int nPos){
	//Recorre todas las fichas del tablero a la izquierda n posiciones
	
	for(int i=0; i<NUMFICHAS; i++)
		if (fichas[i].isIn==BOARD)
			fichas[i].posX-=nPos*5;
			
	posX_left-=nPos*5;
	posX_right-=nPos*5;
}

void fichas_right(int nPos){
	//Recorre todas las fichas del tablero a la derecha n posiciones
	
	for(int i=0; i<NUMFICHAS; i++)
		if (fichas[i].isIn==BOARD)
			fichas[i].posX+=nPos*5;
	
	posX_left+=nPos*5;
	posX_right+=nPos*5;
}

//________________________________________________________________________________________________________________________________________________________


//___________________________________________________________________Funciones de player__________________________________________________________________
int player_take_ficha(int pyr){
	//Toma una ficha de la sopa, y se la asigana al parametro pyr, regresa 0 si no hay fichas en SOPA, regresa 1 pyr tomo ficha
	
	int existFicha=0;
	
	//Verifica que existan fichas disponibles en la sopa
	for(int k=0; k<NUMFICHAS; k++)
		if (fichas[k].isIn == SOPA)
			existFicha = 1;
	//
	
	//Si existen fichas disponibles busca una al azar y se la asigna a pyr 
	if (existFicha){
		
		while (1){
			srand(time(NULL));
			int index = rand()%NUMFICHAS;
			if (fichas[index].isIn == SOPA){
				fichas[index].isIn = pyr;
				players[pyr-1].numFichas++;
				return 1;	
			}
		}
	}
	return 0;
}

int player_win(){
	//Evalua si un jugador se ha quedado sin fichas, devuelve 1 si hay ganador, devuelve 0 si no lo hay
	for(int i=0; i<numPlayers; i++)
		if(players[i].numFichas==0){
			cursorPos(42,13);
			for(int j=0; j<100; j++)
				p("X");
			cursorPos(42,19);
			for(int j=0; j<100; j++)
				p("X");
			cursorPos(80,16);
			p("%s ha ganado la partida",players[i].name);
			return 1;
		}
	//

	//Evalua si hay fichas en SOPA
	for(int i=0; i<NUMFICHAS; i++)
		if(fichas[i].isIn==SOPA)
			return 0;
	//
	
	//Si no hay fichas en SOPA, evalua si jugadores pueden poner alguna ficha
	for(int i=0; i<NUMFICHAS; i++)
		if(fichas[i].isIn!=BOARD)
			if(fichas[i].val1==val_left || fichas[i].val2==val_left || fichas[i].val1==val_right || fichas[i].val2==val_right )
				return 0;
	//
	
	//Cuenta los puntos de las fichas
	int pyrWin, pts=500,cont_pts,i;
	for(i=1; i<=numPlayers; i++){
		cont_pts=0;
		for(int j=0; j<NUMFICHAS; j++){
			if(fichas[j].isIn==i)
				cont_pts+= fichas[j].val1 + fichas[j].val2;
		}
		if(cont_pts<pts){
			pts=cont_pts;
			pyrWin=i-1;
		}		
	}
	//
	cursorPos(42,13);
	for(int j=0; j<100; j++)
		p("X");
	cursorPos(42,19);
	for(int j=0; j<100; j++)
		p("X");
	cursorPos(80,16);
	p("%s ha ganado la partida",players[pyrWin].name);
	return 1;
}

int player_winM(){
	//Evalua si la maquina o el jugador se ha quedado sin fichas, devuelve 1 si hay ganador, devuelve 0 si no lo hay
	if(players[PYR1-1].numFichas==0){
		cursorPos(42,13);
		for(int j=0; j<100; j++)
			p("X");
		cursorPos(42,19);
		for(int j=0; j<100; j++)
			p("X");
		cursorPos(80,16);
		p("%s ha ganado la partida",players[PYR1-1].name);
		return 1;
	}
	
	if(players[MACHINE-1].numFichas==0){
		cursorPos(42,13);
		for(int j=0; j<100; j++)
			p("X");
		cursorPos(42,19);
		for(int j=0; j<100; j++)
			p("X");
		cursorPos(80,16);
		p("%s ha ganado la partida",players[MACHINE-1].name);
		return 1;
	}
	
	//
	
	//Evalua si hay fichas en SOPA
	for(int i=0; i<NUMFICHAS; i++)
		if(fichas[i].isIn==SOPA)
			return 0;
	//
	
	//Si no hay fichas en SOPA, evalua si jugadores pueden poner alguna ficha
	for(int i=0; i<NUMFICHAS; i++)
		if(fichas[i].isIn!=BOARD)
			if(fichas[i].val1==val_left || fichas[i].val2==val_left || fichas[i].val1==val_right || fichas[i].val2==val_right )
				return 0;
	//
	
	//Cuenta los puntos de las fichas
	int pyrWin, pts=500,cont_pts,i;
	for(i=1; i<=MACHINE; i++){
		cont_pts=0;
		for(int j=0; j<NUMFICHAS; j++){
			if(fichas[j].isIn==i)
				cont_pts+= fichas[j].val1 + fichas[j].val2;
		}
		if(cont_pts<pts && cont_pts!=0){
			pts=cont_pts;
			pyrWin=i-1;
		}		
	}
	//
	cursorPos(42,13);
	for(int j=0; j<100; j++)
		p("X");
	cursorPos(42,19);
	for(int j=0; j<100; j++)
		p("X");
	cursorPos(80,16);
	p("%s ha ganado la partida",players[pyrWin].name);
	return 1;
	
	
}

void player_put_ficha(int index, int pos_x, int pos){
	//Se debe usar cuando un jugador o la maquina pone ficha en el tablero, ya que cambia el lugar en el que se encuentra
	//guarda la infomacion de la posicion de la ficha, "index" es el numero de ficha en el arreglo fichas, "x" y "y" son la posicion donde imprimira la ficha,
	//si pos == 0 el orden de impresion es val1 y val2, si pos != 0 el orden de impresion es val2, val1
	players[fichas[index].isIn-1].numFichas--;
	fichas[index].isIn = BOARD;
	fichas[index].posX = pos_x;
	fichas[index].posY = 26;
	fichas[index].pos = pos;
}

int player_next_turno(int turno){
	//Devuelve el turno del siguiente jugador
	turno++;
	if(turno>numPlayers)
		turno=1;
	return turno;
}

int player_next_turnoM(int turno){
	//Devuelve el turno jugador o la maquina
	if(turno==1)
		turno=6;
	else
		turno=1;
	return turno;
}

int player_select_ficha(int pyr){
	//El jugador selecciona una ficha de su mano y la posicion en donde sera colocada la ficha en el tablero
	int numFicha, fichaInvalid, auxFicha, i;
	
	//Leer numero de ficha 
	do{
		//Imprime etiquetas y lee comando
		cursorPos(98,40);
		p("       ");//Limpiar numero ingresado
		cursorPos(75,40);
		p("Poner la ficha numero: ");
		s("%i",&numFicha);
		cursorPos(75,42);
		p("                                                                        ");//Limpiar mensaje de error
		//
		
		//Busca la ficha seleccionada en todas las fichas y evalua si es una ficha valida para poner en el tablero
		fichaInvalid=1;
		auxFicha=0;
		for(i=0; i<NUMFICHAS; i++){//Recorre las 28 fichas
			if(fichas[i].isIn == pyr){ 
				auxFicha++;
				if(auxFicha==numFicha)//Evalua el numero de ficha seleccionada
					if(fichas[i].val1==val_left || fichas[i].val1== val_right || fichas[i].val2==val_left || fichas[i].val2==val_right){
						fichaInvalid=0;
						break;
					}
					else
						break;
			}	
		}
		//
		
		//Evalua el comando ingresado
		if (numFicha==0){ //Toma una ficha
			if(player_take_ficha(pyr))
				fichas_player_show(pyr);
			else{
				cursorPos(75,42);
				p("No hay fichas disponibles para comer");
			}
		}
		else
			if(numFicha==-1)//Pasa turno
				return 0;
			else//Si no se puede poner la ficha por que no coincide con las fichas de las orillas o el numero de ficha es invalido
				if(fichaInvalid){
					cursorPos(75,42);
					p("No es posible poner la ficha seleccionada. Intenta de nuevo");
				}
		//
		
		
	}while(numFicha<1 || numFicha>players[pyr-1].numFichas || fichaInvalid);
	//
	
	//Limpia e imprime los comandos
	cursorPos(9,40);
	p(" 0 = derecha    ");
	cursorPos(9,42);
	p("1 = izquierda   ");
	cursorPos(8,44);
	p("                    ");
	//
	
	//Selecciona si poner en la parte izquierda o derecha del tablero
	int res, posX, posInvalid;
	do{
		//ingresar si es a la derecha o a la izquierda la ficha
		cursorPos(75,40);
		p("Posicion en el tablero:      ");
		cursorPos(99,40);
		s("%i",&res);
		
		//Evalua respuesta
		posInvalid = 1;
		if(res==1 && (fichas[i].val1==val_left || fichas[i].val2== val_left))
			posInvalid = 0;
		if(!res && (fichas[i].val1==val_right || fichas[i].val2== val_right))
			posInvalid = 0;
		//
		
		if (posInvalid){
			cursorPos(75,42);
			p("No es posible colocar esa posicion. Intenta de nuevo");//mensaje de error
		}
		else{
			cursorPos(75,42);
			p("                                                          "); //Limpiar mensaje de error
		}
		
	}while(posInvalid);
	//
	
	//Cambia los atributos de la ficha seleccionada (poner en el tablero)
	
	///Poner ficha en la izquierda
	if(res){
		posX_left-=5;
		if(fichas[i].val2==val_left){//Posicion de la ficha (normal)
			val_left = fichas[i].val1;
			player_put_ficha(i,posX_left,0);
		}
		else{//Posicion de la ficha (inversa)
			val_left = fichas[i].val2;
			player_put_ficha(i,posX_left,1);
		}		
	}
	///
	
	///Poner ficha en la derecha
	else{
		posX_right+=5;
		if(fichas[i].val1==val_right){//Posicion de la ficha (normal)
			val_right = fichas[i].val2;
			player_put_ficha(i,posX_right,0);
		}
		else{//Posicion de la ficha (inversa)
			val_right = fichas[i].val1;
			player_put_ficha(i,posX_right,1);
		}		
	}
	///
	//
}


int player_select_fichaM(int pyr){
	//El Boot selecciona una ficha de su mano y la posicion en donde sera colocada la ficha en el tablero
	int numFicha, fichaInvalid, auxFicha, i;
	
	//Poner ficha en tablero
	do{
		fichaInvalid=1;
		//Busca una ficha en todas las fichas y evalua si es una ficha valida para poner en el tablero y la pone
		for(i=0; i<NUMFICHAS; i++){//Recorre las 28 fichas
			if(fichas[i].isIn == pyr){ 
				if(fichas[i].val1==val_left){
					posX_left-=5;
					player_put_ficha(i,posX_left,1);
					val_left = fichas[i].val2;
					fichaInvalid=0;
					break;
				}
				else 
				if (fichas[i].val2==val_left){
					posX_left-=5;
					player_put_ficha(i,posX_left,0);
					val_left = fichas[i].val1;
					fichaInvalid=0;
					break;
				}
				else
				if(fichas[i].val1==val_right){
					posX_right+=5;
					player_put_ficha(i,posX_right,0);
					val_right = fichas[i].val2;
					fichaInvalid=0;
					break;
				}
				else
				if(fichas[i].val2==val_right){
					posX_right+=5;
					player_put_ficha(i,posX_right,1);
					val_right = fichas[i].val1;
					fichaInvalid=0;
					break;
				}
					
			}	
		}
		//
		
		//Come ficha si no tiene suficientes fichas
		if (fichaInvalid){
			cursorPos(75,42);
			p("Espera un mometo por favor");
			if(!player_take_ficha(pyr))
				fichaInvalid=0;	
		}
		//
	}while(fichaInvalid);
	//
}

//________________________________________________________________________________________________________________________________________________________


//___________________________________________________________________Funciones de players_________________________________________________________________

void players_read_names(){
	//Lee el nombre de los jugadores
	
	system("cls");
	p("\n\n\n\t\t\t\t\t\t\t\t\tIngrese el nombre de los jugadores");
	p("\n\n\t\t\t\t\t\t\tpresione s para dejar de ingresar jugadores, (min 1 jugador, max 4 jugadores)\n");
	
	int i= 0;
	char nom[50]="a"; //asegura la entrada al bucle
	while((strcmp(nom,"s") || i < 1) && i < 4){
		p("\n\t\t\t\t\t\t\tNombre del jugador %i: ",i+1);
	    fflush(stdin);
		gets(nom);
	    
		if(strcmp(nom,"s")){
	    	strcpy(players[i].name,nom);
			i++;
		}
	}
	numPlayers = i;
	p("\n\n\t\t\t\t\t\t\t\t\tLos jugadores fueron registrados");
	p("\n\n\t\t\t\t\t\t\t\t\tPresione una tecla para continuar... ");
	getch();
	system("cls");
}

void player_read_name(){
	//Lee el nombre del jugador
	
	system("cls");
	p("\n\n\n\t\t\t\t\t\t\t\t\tIngrese su nombre: ");
	fflush(stdin);
	gets(players[0].name);
	numPlayers=1;
	strcpy(players[MACHINE-1].name,"Micro_Bot");

	p("\n\n\t\t\t\t\t\t\t\t\tEl registro fue un exito");
	p("\n\n\t\t\t\t\t\t\t\t\tPresione una tecla para continuar... ");
	getch();
	system("cls");
}

//________________________________________________________________________________________________________________________________________________________

int main(){
	int opc;
	do{
		int turno;
		
		opc=menu();
		switch(opc)
		{
			case 1:
				fichas_inicialize();
				player_read_name();
				fichas_repartir();
				turno = player_next_turnoM(ficha_mula());
				
				while(!player_winM()){ //Pendiente
					system("cls");
					fichas_board();
					if (turno==PYR1){
						fichas_player_show(PYR1);
						player_select_ficha(PYR1);
						fichas_board();
						//Crea una pausa
						for (int c = 1; c <= 7767; c++)
       						for (int d = 1; d <= 32767; d++)
       							{}
       					//
					}
					else{
						player_select_fichaM(MACHINE);
					}
						

					turno = player_next_turnoM(turno);
					
					//Evalua si las fichas del tablero estan en los limites de la pantalla, y los recorre  
					if (posX_left<10)
						fichas_right(2);
					if(posX_right>160)
						fichas_left(2);
					//
				}
				
				getch();
				
				
				break;
			case 2:
				fichas_inicialize();
				players_read_names();
				fichas_repartir();
				turno = player_next_turno(ficha_mula());
				
				while(!player_win()){
					system("cls");
					fichas_board();
					fichas_player_show(turno);
					player_select_ficha(turno);
					turno = player_next_turno(turno);
					
					//Evalua si las fichas del tablero estan el los limites de la pantalla, y los recorre  
					if (posX_left<10)
						fichas_right(2);
					if(posX_right>160)
						fichas_left(2);
					//
				}
				getch();

				break;
			case 3:
				reglas();
				break;
			case 4:
				creditos();
				break;
			case 5:
				printf("\n\n\n\t\t\t\t\t\t\t\t\t\tGracias por jugar");
				p("\n\t\t\t\t\t\t\t\t\tPresione una tecla para continuar... ");
				getch();
				break;
			default:
				printf("\n\t\t\t\t\t\t\t\t\t\t\tOpcion no definida");
				p("\n\t\t\t\t\t\t\t\t\t\tPresione una tecla para continuar... ");
				getch();
		}
	}while(opc!=5);
}
