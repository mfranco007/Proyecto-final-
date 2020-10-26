#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

//PROTOTIPO DE LAS FUNCIONES
void ingresarPalabra();
void menu();
void actualizarPalabra();
void leerPalabras();
void buscarPalabra();
void borrarPalabra();
void gotoxy(int x,int y);
void dibujarCuadro(int x1,int y1,int x2,int y2);
void limpia();
void limpiarPantalla(int ultimo);

//ESTRUCTURA PRINCIPAL QUE CONTIENE LAS PALABRAS Y  LA FUNCIONALIDAD
typedef struct{
	char palabra_esp[40];
	char palabra_ing[40];
	char funcionalidad[80];
}palabra;


//FUNCION PRINCIPAL MAIN, ES LA PRIMER FUNCION QUE EL PROGRAMA LEE
int main(){
	system("COLOR 70");
	dibujarCuadro(0,1,119,3); //DIBUJA CUADRO DEL TITULO
	gotoxy(55,2); cout << "TRADUCTOR";
	menu();
	system("pause");
	return 0;
}

//ESTA FUNCION IMPRIME EL MENU EN PANTALLA
void menu(){
	int op;
	do{
		gotoxy(1,6); cout <<"MENU PRINCIPAL";
		gotoxy(1,8); cout <<"1. Ingresar palabras";
		gotoxy(1,9); cout <<"2. Leer Palabras";
		gotoxy(1,10); cout <<"3. Actualizar Palabras";
		gotoxy(1,11); cout <<"4. Borrar Palabras";
		gotoxy(1,12); cout <<"5. Buscar Palabras";
		gotoxy(1,14); cout <<"Ingrse opcion: ";
		cin >> op;
	}while(op < 0 || op > 6);
	
	if (op == 1) ingresarPalabra();
	if (op == 2) leerPalabras();
	if (op == 3) actualizarPalabra();
	if (op == 4) borrarPalabra();
	if (op == 5) buscarPalabra();
}

//ESTA FUNCION PERMITE INGRESAR LAS PALABRAS Y FUNCIONALIDAD Y LAS ALMACENA EN EL ARCHIVO BINARIO Y EN EL ARHIVO DE TEXTO PALABRAS
void ingresarPalabra(){
	FILE *pa, *pa2;
	palabra p1;
	
	if (((pa = fopen("Archivo Binario","a+b"))==NULL) || ((pa2 = fopen("Palabras.txt","a+b"))==NULL)){ 
		printf("No se puede abrir el archivo.\n");
		return ;
	}
	
	fflush(stdin);
	limpia();
	
	gotoxy(1,6); cout <<"INGRESO DE PALABRAS";
	gotoxy(1,8);  cout <<"Ingrese Palabra:       ";
	gets(p1.palabra_ing);
	gotoxy(1,10); cout <<"Ingrese Traduccion:    ";
	gets(p1.palabra_esp);
	gotoxy(1,12); cout <<"Ingrese Funcionalidad: ";
	gets(p1.funcionalidad);
	
	fwrite(&p1, sizeof(palabra),1,pa);         
	fprintf(pa2, "%s %s %s\n", p1.palabra_ing, p1.palabra_esp, p1.funcionalidad);
	fclose(pa);
	fclose(pa2);
	gotoxy(1,28); printf("PALABRA GUARDADA CORRECTAMENTE. PRESIONE UNA TECLA PARA VOLVER..");
	getch();
	limpia();
	menu();
}

//ESTA FUNCION PERMITE BUSCAR UNA PALABRA
void buscarPalabra(){
	FILE *pa, *pa2;
	palabra p1, listaP[100];
	int i, encontro=1, ultimo;
	
	if (((pa = fopen("Archivo Binario","a+b"))==NULL)){ 
		cout << "No se puede abrir el archivo.\n";
		return ;
	}
	
	rewind(pa);  //COLOCA EL CURSOR AL INICIO DEL ARCHIVO
	i=0;
	
	while(!feof(pa)){     //RECORRE TODO EL ARCHIVO
		if(fread(&p1, sizeof(palabra), 1, pa)){               
			listaP[i]=p1;                                        
			i++;
		}                                               
	}
	fclose(pa);
	
	fflush(stdin);
	limpia();
	gotoxy(1,6); cout <<"BUSCAR PALABRA";
	gotoxy(1,8); cout <<"Ingrese palabra: ";
	gets(p1.palabra_ing);
	gotoxy(1,8); cout <<"                                                               ";
	
	//PROCESO DE BUSQUEDA DE INFORMACION 
	ultimo=i;
	i=0;
	while (i < ultimo && encontro){
		if (strcmpi(listaP[i].palabra_ing,p1.palabra_ing)==0) 
			encontro=0;           
		else 
			i++;
	}
	
	
	if (encontro == 0){
		gotoxy(1,8); cout <<"Palabra:       " << listaP[i].palabra_ing;
		gotoxy(1,10); cout <<"Traduccion:    " << listaP[i].palabra_esp;
		gotoxy(1,12); cout <<"Funcionalidad: " << listaP[i].funcionalidad;
		gotoxy(1,28); cout <<"PRESIONE UNA TECLA PARA VOLVER..";
	}
	
	else{
		gotoxy(1,28); cout <<"NO SE ENCONTRO LA PALABRA! PRESIONE UNA TECLA PARA VOLVER..";	
	}
		
	
	getch();
	limpia();
	menu();	
}

//ESTA FUNCION PERMITE ACTUALIZAR LA PALABRA, TRADUCCION O LA FUNCIONALIDAD
void actualizarPalabra(){
	FILE *pa, *pa2;
	palabra p1, listaP[100];
	int i, encontro=1, ultimo, opc;
	
	if (((pa = fopen("Archivo Binario","a+b"))==NULL)){ 
		printf("No se puede abrir el archivo.\n");
		return ;
	}
	
	rewind(pa);  //COLOCA EL CURSOR AL INICIO DEL ARCHIVO
	i=0;
	
	while(!feof(pa)){     //RECORRE TODO EL ARCHIVO
		if(fread(&p1, sizeof(palabra), 1, pa)){               
			listaP[i]=p1;                                        
			i++;
		}                                               
	}
	fclose(pa);
	
	fflush(stdin);
	limpia();
	gotoxy(1,6); cout <<"ACTUALIZAR PALABRA";
	gotoxy(1,8); cout <<"Ingrese palabra a buscar: ";
	gets(p1.palabra_ing);
	
	//PROCESO DE BUSQUEDA DE INFORMACION 
	ultimo=i;
	i=0;
	while (i < ultimo && encontro){
		if (strcmp(listaP[i].palabra_ing,p1.palabra_ing)==0) 
			encontro=0;           
		else 
			i++;
	}
	
	if (encontro == 0){
		gotoxy(1,8); cout << "                                                                     ";
		gotoxy(1,8); cout <<"1. Palabra:       " << listaP[i].palabra_ing;
		gotoxy(1,10); cout <<"2. Traduccion:    " << listaP[i].palabra_esp;
		gotoxy(1,12); cout <<"3. Funcionalidad: " << listaP[i].funcionalidad;
		gotoxy(1,15); cout << "Ingrese opcion a actualizar: ";
		cin >> opc;
		fflush(stdin);
		
		switch(opc){
			case 1:
				gotoxy(1,8); cout <<"                                    ";
				gotoxy(1,8); cout <<"1. Palabra:       ";
				gets(listaP[i].palabra_ing);
				break;
				
			case 2:
				gotoxy(1,10); cout <<"                                    ";
				gotoxy(1,10); cout <<"2. Traduccion:    ";
				gets(listaP[i].palabra_esp);
				break;
				
			case 3:
				gotoxy(1,12); cout <<"                                                                                ";
				gotoxy(1,12); cout <<"3. Funcionalidad: ";
				gets(listaP[i].funcionalidad);
				break;
		}
		
		// Abre el archivo para Sobrescribir
		if (((pa = fopen("Archivo Binario", "wb"))== NULL) || ((pa2 = fopen("Palabras.txt","wb"))==NULL)){	
			cout <<"No se puede abrir el archivo.\n";
			return;
		}
		
		i=0;
					
		while(i < ultimo){
			fwrite(&listaP[i], sizeof(palabra),1,pa);         
			fprintf(pa2, "%s %s %s\n", listaP[i].palabra_ing,listaP[i].palabra_esp, listaP[i].funcionalidad);
		  	i++;
		}
		
		fclose(pa);
		fclose(pa2);
		gotoxy(1,28); cout << "PALABRA ACTUALIZADA CORRECTAMENTE. PRESIONE UNA TECLA PARA VOLVER..";
			
	}
	
	else{
		gotoxy(1,28); cout << "NO SE ENCONTRO LA PALABRA! PRESIONE UNA TECLA PARA VOLVER..";	
	}
		
	
	getch();
	limpia();
	menu();	
}


//ESTA FUNCION MUESTAR TODAS LAS PALABRAS CON SU RESPECTIVA FUNCIONALIDAD EN PANTALLA
void leerPalabras(){
	FILE *pa, *pa2;
	palabra p1, listaP[100];
	int i, ultimo,f=10;
	limpia();
	
	if (((pa = fopen("Archivo Binario","a+b"))==NULL)){ 
		printf("No se puede abrir el archivo.\n");
		return ;
	}
	
	rewind(pa);  //COLOCA EL CURSOR AL INICIO DEL ARCHIVO
	i=0;
	
	while(!feof(pa)){     //RECORRE TODO EL ARCHIVO
		if(fread(&p1, sizeof(palabra), 1, pa)){               
			listaP[i]=p1;                                        
			i++;
		}                                               
	}
	fclose(pa);
	
	fflush(stdin);
	gotoxy(1,6); cout <<"LEER PALABRAS";
	gotoxy(1,8); cout << "PALABRA          TRADUCCION               FUNCIONALIDAD";
	gotoxy(1,9); cout << "-----------------------------------------------------------------------------------------------------------------";
	
	//PROCESO DE BUSQUEDA DE INFORMACION 
	ultimo=i;
	i=0;
	
	while (i < ultimo){
		gotoxy(1,f); cout << listaP[i].palabra_ing;
		gotoxy(18,f); cout << listaP[i].palabra_esp;
		gotoxy(43,f); cout << listaP[i].funcionalidad;
		i++;
		f++;
	}
	
	gotoxy(1,11+ultimo); cout << "PRESIONE UNA TECLA PARA VOLVER..";
	
	getch();
	limpiarPantalla(ultimo);
	menu();	
}

//ESTA FUNCION PERMITE ELIMINAR UNA PALABRA QUE SE INGRESE , SE ELIMINA CON SU RESPECTIVA TRADUCCION Y FUNCIONALIDAD
void borrarPalabra(){
	FILE *pa, *pa2;
	palabra p1, listaP[100];
	int i, encontro=1, ultimo;
	limpia();
	
	if (((pa = fopen("Archivo Binario","a+b"))==NULL)){ 
		cout <<"No se puede abrir el archivo.\n";
		return ;
	}
	
	rewind(pa);  //COLOCA EL CURSOR AL INICIO DEL ARCHIVO
	i=0;
	
	while(!feof(pa)){     //RECORRE TODO EL ARCHIVO
		if(fread(&p1, sizeof(palabra), 1, pa)){               
			listaP[i]=p1;                                        
			i++;
		}                                               
	}
	fclose(pa);
	
	fflush(stdin);

	gotoxy(1,6); cout <<"ELIMINAR PALABRA";
	gotoxy(1,8); cout <<"Ingrese palabra a eliminar: ";
	gets(p1.palabra_ing);
	
	
	//PROCESO DE BUSQUEDA DE INFORMACION 
	ultimo=i;
	i=0;
	while (i < ultimo && encontro){
		if (strcmp(listaP[i].palabra_ing,p1.palabra_ing)==0) 
			encontro=0;           
		else 
			i++;
	}
	
	if (encontro == 0){
		gotoxy(1,8); cout <<"                                                 ";
		gotoxy(1,8); cout <<"1. Palabra:       " << listaP[i].palabra_ing;
		gotoxy(1,10); cout <<"2. Traduccion:    " << listaP[i].palabra_esp;
		gotoxy(1,12); cout <<"3. Funcionalidad: " << listaP[i].funcionalidad;
		
		while (i < ultimo-1) {
			    listaP[i]=listaP[i+1];
			    i++;
		}
		
		// Abre el archivo para Sobrescribir
		if (((pa = fopen("Archivo Binario", "wb"))== NULL) || ((pa2 = fopen("Palabras.txt","wb"))==NULL)){	
			printf("No se puede abrir el archivo.\n");
			return;
		}
		
		i=0;
					
		while(i < ultimo-1){
			fwrite(&listaP[i], sizeof(palabra),1,pa);         
			fprintf(pa2, "%s %s %s\n", listaP[i].palabra_ing,listaP[i].palabra_esp, listaP[i].funcionalidad);
		  	i++;
		}
		
		fclose(pa);
		fclose(pa2);
		gotoxy(1,28); cout << "PALABRA ELIMINADA CORRECTAMENTE. PRESIONE UNA TECLA PARA VOLVER..";
			
	}
	
	else{
		gotoxy(1,28); cout << "NO SE ENCONTRO LA PALABRA! PRESIONE UNA TECLA PARA VOLVER..";	
	}
		
	
	getch();
	limpia();
	menu();	
}


//FUNCION GOTOXY, SIRVE PARA POSICIONAR LOS MENSAJES EN UNA DETERMINADA ZONA DE LA PANTALLA, SE INGRESA COLUMNA Y FILA DE LA PANTALLA, EJEMPLO: gotoxy(4,10); printf("HOla"); ESTE MENSAJE SE IMPRIMIRÁ EN LA POSICIÓN COLUMNA 4, FILA 10
void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }


//FUNCION QUE DIBUJA UN CUADRO, SE PASAN LOS VALORES DONDE QUEREMOS QUE SE FORME EL CUADRO, EJEMPLO dibujarCuadro(1,1,78,24);
void dibujarCuadro(int x1,int y1,int x2,int y2)
{

    int i;
    for (i=x1;i<x2;i++)
    {
	gotoxy(i,y1);printf("Ä") ;//linea horizontal superior
	gotoxy(i,y2);printf("Ä") ;//linea horizontal inferior
    }

    for (i=y1;i<y2;i++)
    {
	gotoxy(x1,i);printf("³") ;//linea vertical izquierda
	gotoxy(x2,i);printf("³") ;//linea vertical derecha
    }
    gotoxy(x1,y1);printf("Ú");
    gotoxy(x1,y2);printf("À");
    gotoxy(x2,y1);printf("¿");
    gotoxy(x2,y2);printf("Ù");
}


//FUNCION LIMPIAR AREA
void limpia(){
	int i,j;
	for(i=6;i<=28;i++){
		for(j=0;j<=117;j++){
			gotoxy(j,i); printf(" ");}}
}

//FUNCION QUE LIMPIA TODA LE AREA DE LAS LISTAS DE PALABRAS
void limpiarPantalla(int ultimo){
	int i,j;
	for(i=6;i<= (11+ultimo);i++){
		for(j=0;j<=117;j++){
			gotoxy(j,i); printf(" ");}}
}
