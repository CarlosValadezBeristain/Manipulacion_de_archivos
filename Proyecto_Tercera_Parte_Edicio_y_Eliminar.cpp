#include <windows.h>//libreria utilizada la limpieza de pantalla 
#include <iostream>  //libreria utlizada para imprimir y guardar datos 
#include <locale.h>//libreria utilizada para el idioma del programa 
#include <string.h>//libreria utilizada para  manipular cadenas
#include <conio.h>//libreria para utilizar getch
#include <stdio.h>
#include <regex>
#include <stdlib.h>  

using namespace std;
//Creadores Bryan Josue Flores Gonzalez, Carlos Ernesto Valadez Beristain  y Julio Leonel Rubio Ramirez 12/03/2021
FILE *pf;
FILE *pc;

char nombreArchivo[30];

bool archivoCreado=false;

struct agenda
{
	char id[5];	
	char nombre[30];
	char ap[30];	
	char am[30];
	char tel[12];
	int edad;
	char correo[100];
	int ban;
};

struct agenda practica;

regex validarc("^[^|+/#=:;*-._,!�""%()?�''{}]+[^@]+@[^@]+[a-z0-9]");

char menu(void);

bool crear();

int validarNombre(char nombreArchivo[]);//Utilizamos esta funcion para validar datos 
int validarNom(char nombre[]);
int validarap(char ap[]);
int validaram(char am[]);
int validartel(char tel[]);
int validaredad(char edad[]);

/*Prototipos de funciones */
void alta();
void mostrar();
void consulta();
void editar();
void eliminar();


//funciones nuevas
int num_contactos();
char *generar_id(int);
void limpieza();
char YN();
void gotoxy(int x,int y) //funcion necesaria para usar gotoxy
{  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  


	main()
	{
	
		char opc;
		
		setlocale(LC_CTYPE,"");//para poner el programa en espa�ol
	
	do
	{
	     
		opc=menu();
	
	
		switch(opc)
		
		{//inicio switch
		
			char o;
			
			case 59://f1
			
					system("cls"); //limpiar pantalla 
				
					archivoCreado=crear();//se manada a llamar la funcion 
					
					printf("Archivo creado...\n");
					
					Sleep(2000);	
					
					break;
					
			
			case 60: //f2
			
					system("cls");
					
					if(archivoCreado==false)
					
					{
						
					Beep(500,200);
					
					printf("Favor de crear primero el archivo...");
					
					o=getch();
					
					}
					
					else
					
					{
					  alta();
					}
					
						break;
		
						
			case 61://f3
				
					system("cls");
					
					if(archivoCreado==false)
					
					{
						Beep(500,200);
						
						printf("Favor de crear o vincular un archivo...");
						
						o=getch();
					}
					
					else
					
					{
						mostrar();
					}
					
					break;
					
			case 62://f4
				
					system("cls");
					
					if(archivoCreado==false)
					
					{
						Beep(500,200);
						
						printf("Favor de crear o vincular un archivo...");
						
						o=getch();
					}
					
					else
					
					{
						consulta();
					}
					
					break;
						
							
			case 63: //f5
			
					system("cls");
					
					if(archivoCreado==false)
					
					{
						
					Beep(500,200);
					
					printf("Favor de crear o vincular un archvio....");
					
					o=getch();
					
					}
					
					else
					{
					 editar();
					}              
					break;
					
					
			case 64: //f6
			
					system("cls");
					
				   	if(archivoCreado == false)
				   	
					{
						
					Beep(500,200);
					
					printf("Favor de crear o vincular un archvio....");
					
					o=getch();
					}
					
					else
					{
					eliminar();
					}              
					break;
						                             
					
			case 27: //ESC
			
					system("cls");
				   	printf("Programa Terminado");	                             
					exit(0);			
			
			default:
					if(opc !=27)
					{
					Beep(500,200);//Pusimos el beep, para evitar que saliera un mensaje de error 	
					}
					break;
			
			
		}//fin switch
		
		
	}while(opc!=27);
			
	return 0;
	
}//fin del main 


char menu()//Identifica la tecla que se presiono en el teclado 
{
	
	system ("color 09");

	char opc1='\0';
	
	system("cls");
	
	gotoxy(13,1);
	printf("Menu\n");//Mostrara el menu 
	gotoxy(3,3);
	printf("[F1] Crear o abrir archivo\n");
	gotoxy(3,4);
	printf("[F2] Agregar nuevo registro\n");
	gotoxy(3,5);	
	printf("[F3] Mostrar Registro\n");
	gotoxy(3,6);	
	printf("[F4] Consulta\n");
	gotoxy(3,7);
	printf("[F5] Modificar Registro\n");
	gotoxy(3,8);
	printf("[F6] Eliminar Registro\n");
	gotoxy(3,9);
	printf("ESC. Salir\n");
	gotoxy(3,10);
	printf("Seleccione una opcion: ");
	
	opc1=getch();
	
	if(opc1==0)
	{
		opc1 = getch();
	}
	else if(opc1!=27)
	{
		opc1=-1;
	}
	return opc1;
	
}

bool crear()
{
	int validacion;// Variable
	
	memset(nombreArchivo,0,sizeof(nombreArchivo));
	
	system("cls");//Limpia pantalla 
	system ("color 02");

	 do
     {
     	 gotoxy(13,1);
         printf("Ingrese un nombre para crear o vincular un archivo: ");
         
         scanf("%s",nombreArchivo);
         
         validacion=validarNombre(nombreArchivo);//Se manda a llamar la funcion para validar 
         
		 system("cls");
		
     }while(validacion==0);
	

	
		strcat(nombreArchivo,".bin");//indicamos en que tipo de archivo queremos crear
	
		pf=fopen(nombreArchivo,"a");//abre flujo para crearlo
	
		if(pf==NULL)//comprobar
		{
			
		perror("Error...");
		
		Sleep(3000);
		
		exit(0);
		
		}

		fclose(pf);
	
		return true;

}

int validarNombre(char nombreArchivo[])
{
    int i;
    
    for(i=0 ; i<strlen(nombreArchivo); i++)
    
    {
    	//Validamos que acepte solo letras ya sean mayusculas o minusculas y que acepte guion bajo     
        if(!(isalpha(nombreArchivo[i]) || nombreArchivo[i]==95))
        
        {
           Beep(500,200);//Pusimos el beep, para evitar que saliera un mensaje de error
            return 0;
        }
    }
     return 1;
}

void alta()
{
	//declaracion de variavles locales
	char cadedad[5];
	int validar, limitetel,limitedad, edadval;
	char *aux;
	char opc='\0';
		
	do
	
	{
		system("cls");
		
		system ("color 02");
		
		gotoxy(13,1);
		printf("ALTA DE REGISTRO\n");
		
		limpieza();//para ahorrar lineas se utiliza la funcion limpieza que limpia toda la struct
		
		int nc = num_contactos();
		
		aux = generar_id(nc);
		
		strcpy(practica.id,aux);
	
		do
		
		{
			fflush(stdin);
			gotoxy(3,3);
            printf("Ingrese su Nombre: ");
         
            scanf("%[^\n]",practica.nombre);//se podia utilizar gets pero decidimos hacerlo de esta manera para que aceptara espacios dentro de la cadena en caso de que tenga 2 nombres
            
			fflush(stdin);
            
		    validar=validarNom(practica.nombre);//Se manda a llamar la funcion para validar 
 
		    system("cls");
	
     	}while(validar==0);
	
		do
		
		{
		
		  gotoxy(3,3);
		  
          printf("Ingrese su Apellido Paterno: ");
         
          scanf("%[^\n]",practica.ap);
          
     	  fflush(stdin);
     	  
		  validar=validarap(practica.ap);//Se manda a llamar la funcion para validar 
         
		  system("cls");
		
     	}while(validar==0);
	
		do
		
		{
		
		  gotoxy(3,3);
		  
          printf("Ingrese su Apellido Materno: ");
         
          scanf("%[^\n]",practica.am);
          
 		  fflush(stdin);  
		     
		  validar=validaram(practica.am);//Se manda a llamar la funcion para validar 
		  
		  system("cls");
		
     	}while(validar==0);
	
		do
		
		{
			do
			
			{
				gotoxy(3,3);
				
				printf("Ingrese su Telefono: ");
				
        		scanf("%s",practica.tel);
        		
        		system("cls");
        		
        		limitetel=strlen(practica.tel);
        		
			}while(limitetel!=10);
    
		     validar=validartel(practica.tel);//Se manda a llamar la funcion para validar 
	
		     system("cls");
		
     	}while(validar==0);
     	     	
		do
		
		{
     		do
			 
			 {
     				gotoxy(3,3);
     				
     				printf("Ingresa tu Edad: ");
     				
     				scanf("%s",cadedad);
     				
     				system("cls");
     			
     				limitedad=strlen(cadedad);
     			
			 }while(limitedad!=2);//limite de edad

     		  validar=validaredad(cadedad);//aqui valido la cadena local
     		   
				system("cls");
		
		 }while(validar==0);
		 
		 practica.edad=atoi(cadedad);//aqui mi cadena se transforma de caracteres a valor entero
     	
		do
		
		{
		  fflush(stdin);
		  
		  system("cls");
		  
		  gotoxy(3,3);
		  
		  printf("Ingrese su correo: ");
		  
		  scanf("%s",practica.correo);
		  
     	  fflush(stdin);
     	  
		if(!regex_match(practica.correo,validarc))
		 
		 {
			Beep(500,200);
		 }
		 
	}while(!regex_match(practica.correo,validarc));
	
	practica.ban=62;
	
	pf=fopen(nombreArchivo,"ab");//abre el flujo
	
	if(pf==NULL)//comprueba si hay error
	{
		perror("Error..");
		Sleep(3000);
		exit(0);
	}
	
	fwrite(&practica,sizeof(practica),1,pf);
	
	fprintf(pf,"\r\n");
	
	fclose(pf);//cierro el flujo
	
	printf("Deseas agregar otro registro S/N");
		
		opc=YN();//igualmente para ahorrar lineas se crea un char donde se llama una funcion para las cadenas
		
	}while(opc=='s'|| opc=='S');
	
}

void mostrar()
{
	system("cls");
	 
	system ("color 02");
			
	pf=fopen(nombreArchivo,"rb");
	
	if(pf==NULL)
	{
		perror("ERROR AL ABRIR FICHERO...");
		Sleep(3000);
		exit(0);	
	}
	
	do
	 //inicio del ciclo para leer los registros
	{
		limpieza();
		
		fread(&practica,sizeof(practica),1,pf);
		
		fgetc(pf);
		fgetc(pf);
		
		if(practica.ban==62 && !feof(pf))
		
		{
		
			printf("C�digo: %s\n",practica.id);
			
			printf("Nombre: %s\n",practica.nombre);
			
			printf("Apellido Paterno: %s\n",practica.ap);
			
			printf("Apellido Materno: %s\n",practica.am);
			
			printf("Edad: %d\n",practica.edad);
			
			printf("Tel�fono: %s\n",practica.tel);
			
			printf("Correo: %s\n\n",practica.correo);
		}
		
	}while(!feof(pf)); //mientras no se encuentre el cararcter del final del archivo 
	
	system("pause");
	fclose(pf);  //cerrar flujo 
	
}

void consulta()
{
	//veclarar varibles locales
	char consulta[50];
	int conregistro=0; 
	
	pf=fopen(nombreArchivo,"rb");
	
	if(pf==NULL)
	{
		perror("Error al abrir fichero...");
		Sleep(3000);
		exit(0);
	}
	 
	  system("cls");
	  system ("color 02");
		
	  memset(consulta,0,sizeof(consulta));
	
	  gotoxy(13,1);
	
	  printf("Ingrese el Apellido Paterno a Consultar: ");
	  gets(consulta);
		
//inicio del ciclo para leer los registros
	do
	
	{
				
		fread(&practica,sizeof(practica),1,pf);
		
		fgetc(pf);
		fgetc(pf);
		//impresion de la informacion de cada registro
		if(strcmpi(consulta,practica.ap)==0 && !feof(pf))
		{
			
			printf("C�digo: %s\n",practica.id);
			
			printf("Nombre: %s\n",practica.nombre);
			
			printf("Apellido Paterno: %s\n",practica.ap);
			
			printf("Apellido Materno: %s\n",practica.am);
			
			cout<<"Edad: "<<practica.edad<<endl;
			
			printf("Tel�fono: %s\n",practica.tel);
						
			printf("Correo: %s\n\n",practica.correo);
			
			conregistro++;
		}	
					
	}while(!feof(pf)); //mientras no se encuentre el caracter de final de archivo
	
		if(conregistro==0)
		
		{
		printf("No hay coincidencias...\n");
		}
	
		system("pause");
	
		fclose(pf); //cerrar flujo
	
}//fin de consulta

void editar()
{
	//variables locales
	char cadedad[5];
	int limitetel,limitedad, edadval, validar, limitel;
	char edicion[50], *aux, opc; 
	int conregistro;

	
	pf=fopen(nombreArchivo,"rb");
	
	pc=fopen("auxiliar.bin","ab");
	
	if(pf==NULL || pc == NULL)
	
	{
		perror("ERROR EN EL FICHERO...");
		Sleep(3000);
		exit(0);
	}
	
		system("cls");
		
		system ("color 02");
		
		memset(edicion,0,sizeof(edicion));
		
		gotoxy(13,1);
		
		printf("Ingrese el Apellido Paterno a Editar: ");
		gets(edicion);
		
		do
		
		{
			
		 fread(&practica,sizeof(practica),1,pf);
		 fgetc(pf);
		 fgetc(pf);
		
		if(strcmpi(edicion,practica.ap)==0 && !feof(pf))
		
		{
			
			printf("C�digo: %s\n",practica.id);
			
			printf("Nombre: %s\n",practica.nombre);
			
			printf("Apellido Paterno: %s\n",practica.ap);
			
			printf("Apellido Materno: %s\n",practica.am);
			
			cout<<"Edad: "<<practica.edad<<endl;
			
			printf("Tel�fono: %s\n",practica.tel);
						
			printf("Correo: %s\n\n",practica.correo);
			conregistro++;
			
			cout<<"Quieres editar este registro [S/N]"<<endl;
			
			opc=YN();
			
			system("cls");
	
			if(opc == 's'|| opc =='S')
			
			{
	
				char o;
				
				do
				
				{
						system("cls");
						cout<<"Menu de edicion..."<<endl;
						cout<<"1.- Nombre"<<endl;
						cout<<"2.- Apellido Paterno"<<endl;
						cout<<"3.-Apellido Materno"<<endl;
						cout<<"4.-Telefono"<<endl;
						cout<<"5.-Correo"<<endl;
						cout<<"6.-edad"<<endl;
						cout<<"ESC salir"<<endl;
						o=getch();
						
				switch(o)
				
					{
								
					case 49:
					 	
						    do
						    
							{
									
							 fflush(stdin);
							
        					 printf("Ingrese su Nombre: ");
        					
         					 scanf("%[^\n]",practica.nombre);
							 //se podia utilizar gets pero decidimos hacerlo de esta manera para que aceptara espacios dentro de la cadena en caso de que tenga 2 nombres
         					 fflush(stdin);
         					
							 validar=validarNom(practica.nombre);
							//Se manda a llamar la funcion para validar 
						     system("cls");
							
							}while(validar==0);
								
							 cout<<endl<<"CAMPO EDITADO"<<endl;
							 Sleep(1000);
							 break;
								
					case 50:
							do
							
							{
								
         						printf("Ingrese su Apellido Paterno: ");
         						
        						scanf("%[^\n]",practica.ap);
        						
     							fflush(stdin);
     							
								validar=validarap(practica.ap);
								//Se manda a llamar la funcion para validar 
         						system("cls");
         						
     						}while(validar==0);
									
							 cout<<endl<<"CAMPO EDITADO"<<endl;
							 Sleep(1000);
							 break;
								
					case 51:
							do
							
							{
								
         						printf("Ingrese su Apellido Materno: ");
								 	 
         						scanf("%[^\n]",practica.am);
         						
 		 						fflush(stdin);
								      
								validar=validaram(practica.am);
								//Se manda a llamar la funcion para validar 
         						system("cls");
		
     						}while(validar==0);
									
							 cout<<endl<<"CAMPO EDITADO"<<endl;
							 Sleep(1000);
							 break;
								
					case 52:
							do
							{
								do
								{
													
								  printf("Ingrese su Telefono: ");
								  
								  scanf("%s",practica.tel);
								  
								  system("cls");
								  
								  limitetel=strlen(practica.tel);
										        		
								}while(limitetel!=10);
										    
								validar=validartel(practica.tel);//Se manda a llamar la funcion para validar 
											
								system("cls");
												
							}while(validar==0);
							
							 cout<<endl<<"CAMPO EDITADO"<<endl;
							 Sleep(1000);
							 break;
								
					case 53:
							do
							
							{
									fflush(stdin);
									
									system("cls");
											
									printf("Ingrese su correo: ");
									
									scanf("%s",practica.correo);
									
								    fflush(stdin);
								    
								if(!regex_match(practica.correo,validarc))
								{
									Beep(500,200);
								}
								
							}while(!regex_match(practica.correo,validarc));
								
							 cout<<endl<<"CAMPO EDITADO"<<endl;
							 Sleep(1000);
							 break;
								
					case 54:
							do
							{
							  do
							  {
					     				
					     		printf("Ingresa tu Edad: ");
					     		
					     		scanf("%s",cadedad);
					     		
					     		system("cls");
					     	
					     		limitedad=strlen(cadedad);
     			
			 				  }while(limitedad!=2);//limite de edad
			 				  
     							validar=validaredad(cadedad);//aqui valido la cadena local
     							system("cls");

		 					}while(validar==0);
		 
							 practica.edad=atoi(cadedad);//aqui mi cadena se transforma de caracteres a valor entero
							 cout<<endl<<"CAMPO EDITADO"<<endl;
							 Sleep(1000);
							 break;
												
					case 27:
							cout<<endl<<"campo editado"<<endl;
							Sleep(1000);
							
							break;
							
							default:
								Beep(500,500);
								break;	
						}//final del swtich de edicion
						
					}while(o!=27);//fin del switch para editar
	
			}//si el resultado fue si entonces hara las modificaciones en este switch
			
		}//if para preguntar si es el registro que se quiere editar	
		
		if(practica.ban==62 && !feof(pf))
		{	
				fwrite(&practica,sizeof(practica),1,pc);
				fprintf(pc,"\r\n");	
		}	
			
		
	}while(!feof(pf));//para todo los registros que el usuario desee editar
	
		if(conregistro==0)
		{
		printf("No hay coincidencias...\n");
	    }
	    
		 system("pause");
		 fwrite(&practica,sizeof(practica),1,pf);
		 fprintf(pf,"\r\n");
	
	fclose(pf); //cerrar flujo
	fclose(pc);		
	
	remove(nombreArchivo);
	rename("auxiliar.bin",nombreArchivo);
	
}

void eliminar()
{
	//Se detecto un peque�o error al momento de que se elimina el primer registro
	// el programa  tomara  el segundo registro como el primero pero se quedara el codigo que tenia antes 
	char editar[50], *aux, opc;
	int conregistros=0;
	bool eliminado=false;//bandera para la indicacion de la elimincacion

	pf=fopen(nombreArchivo,"rb");
	pc=fopen("auxiliar.bin","ab");
	
	if(pf==NULL || pc == NULL)//compara y verifica si no hya errores
	{
		perror("ERROR EN EL FICHERO...");
		Sleep(3000);
		exit(0);
	}
		
		
		system("cls");
		
		system ("color 02");
		
		memset(editar,0,sizeof(editar));
		
		gotoxy(13,1);
		
		printf("Ingrese el Apellido Paterno a Eliminar: ");
		gets(editar);
		
		do
		{
		  eliminado = false;
		  
		  fread(&practica,sizeof(practica),1,pf);
		  
		  fgetc(pf);
		  fgetc(pf);
		
		if(strcmpi(editar,practica.ap)==0 && !feof(pf))//pregunta si es el registro correcto
		{
			
			printf("C�digo: %s\n",practica.id);
			
			printf("Nombre: %s\n",practica.nombre);
			
			printf("Apellido Paterno: %s\n",practica.ap);
			
			printf("Apellido Materno: %s\n",practica.am);
			
			cout<<"Edad: "<<practica.edad<<endl;
			
			printf("Tel�fono: %s\n",practica.tel);
						
			printf("Correo: %s\n\n",practica.correo);
			
			conregistros++;//contador de registro
			
			cout<<"Quieres eliminar este registro [S/N]"<<endl;//pregunta si es el registro a eliminar
			
			opc=YN();
			
			system("cls");
			//system("pause");
			if(opc == 's' || opc == 'S')
			{
				cout<<"REGISTRO ELIMINADO"<<endl;
				Sleep(3000);
				eliminado=true;	
			}//si el resultado es si lo elimina
			
		}//if para preguntar si es el registro que se quiere eliminar
	
				if(!feof(pf) && eliminado ==false)
				{//el if tiene que ir al final de la prgunta si es el registro correcto, aqui lee otra vez el archivo o los registros sin tomar en encuata el eliminado que es el caso de cuando la bandera se puso en true aqui lee la que no se han eliminado
				fwrite(&practica,sizeof(practica),1,pc);
				
				fprintf(pc,"\r\n");//
		    	}
		    	
	}while(!feof(pf));//para todo los registros que el usuario desee editar
	
		if(conregistros == 0)
		{
		printf("No hay coincidencias...\n");
	    }
	    
		system("pause");

	
	fclose(pf); //cerrar flujo
	fclose(pc);		
	
	remove(nombreArchivo);
	rename("auxiliar.bin",nombreArchivo);
	
}
	
void limpieza()
{
	memset(&practica,0,sizeof(practica));	
}

char YN() //Funcion para ahorranos lineas de codigo S/N
{
	char opc;
	do{
		opc=getch();
		if(opc!='n' && opc!='N' && opc!='s' && opc!= 'S')
		{
			Beep(500,200);
		}
		
	}while(opc!='n' && opc!='N' && opc!='s' && opc!= 'S');
	
	return opc;
}

int num_contactos()
{
	
	int contactos=0;
	
	pf=fopen(nombreArchivo,"rb");
	
	fseek(pf,0,2);
	
		if(pf==NULL)
		{
			perror("No se puede abrir el archivo");
			exit(1);
		}
		
		else
		{//calculo de los contactos
		
		int tamArchivo = ftell(pf);//tama�o de archivo gracias al puntero
		
		int tamRegistro = sizeof(practica)+2;//tama�odel registro una vez obtenido el tama�o del archivo, +2 son espacios para el salto de linea y retorno de carro osea \n\r
		
		contactos=(tamArchivo/tamRegistro);	
		
		}
		
		fclose(pf);
		
		return contactos+1;
		
}

//generar id automatico
char *generar_id(int contactos)
{
	char cadena[5], cadena1[5];
	int longuitud=0; //la longuitud de la cadena
	char cero[2]={'P','\0'},cero1[3]={'P','0','\0'},cero2[4]={'P','0','0','\0'};
	
	
	
	memset(cadena,0,sizeof(cadena));
	
	memset(cadena1,0,sizeof(cadena1));
	
	itoa(contactos,cadena,10);
	
	longuitud=strlen(cadena);//mide cadena
	
	//a�ade 2 ceros a a la cadena
	if(longuitud==1)
	{
		strcat(cadena1,cero2);
		strcat(cadena1,cadena);	
	}
	
	//a�ade 1 cero a la cadena
	else if(longuitud==2)
	{
		strcat(cadena1,cero1);
		strcat(cadena1,cadena);	
	}
	
	else if(longuitud==3)
	{
		strcat(cadena1,cero);
		strcat(cadena1,cadena);
	}
	
	return cadena1;
	
}

int validarNom(char nombre[])
{
    int i;
    for(i=0 ; i<strlen(nombre); i++)
    {
    	//Validamos que acepte solo letras ya sean mayusculas o minusculas y que acepte guion bajo     
         if(!(isalpha(nombre[i]) || nombre[i]==32))
        {
           Beep(500,200);//Pusimos el beep, para evitar que saliera un mensaje de error  
            return 0;
        }
    }
    return 1;
}


int validarap(char ap[])
{
    int i;
    for(i=0 ; i<strlen(ap); i++)
    {
    	//Validamos que acepte solo letras ya sean mayusculas o minusculas y que acepte guion bajo     
         if(!(isalpha(ap[i]) || ap[i]==32))
        {
           Beep(500,200);//Pusimos el beep, para evitar que saliera un mensaje de error 
            return 0;
        }
    }
    return 1;
}


int validaram(char am[])
{
    int i;
    for(i=0 ; i<strlen(am); i++)
    {
    	//Validamos que acepte solo letras ya sean mayusculas o minusculas y que acepte guion bajo     
         if(!(isalpha(am[i]) || practica.ap[i]==32))
        {
           Beep(500,200);//Pusimos el beep, para evitar que saliera un mensaje de error 
            return 0;
        }
    }
    return 1;
}


int validartel(char tel[])
{
	
    int i;
    for(i=0 ; i<strlen(tel); i++)
    {
    	//Validamos que acepte solo letras ya sean mayusculas o minusculas y que acepte guion bajo     
         if(!(isdigit(tel[i])))
        {
           Beep(500,200);//Pusimos el beep, para evitar que saliera un mensaje de error 
            return 0;
        }
    }
    return 1;
}

int validaredad(char edad[])
{
	
    int i;
    for(i=0 ; i<strlen(edad); i++)
    {
    	//Validamos que acepte solo letras ya sean mayusculas o minusculas y que acepte guion bajo     
         if(!(isdigit(edad[i])))
        {
           Beep(500,200);//Pusimos el beep, para evitar que saliera un mensaje de error 
            return 0;
        }
    }
    return 1;
}
