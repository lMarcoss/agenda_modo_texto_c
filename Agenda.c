/*
 *Ejemplo del uso de la lista, accediendo en ella a través de un menú
 * **Datos del equipo
 Equipo Nº 1
 * 	Santiago Santiago Adrian
 * 	Marcos Santiago Leonardo 
 * Pascual Hernandez Jose Luis
 * 	Santos Sainos Hernández
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "Listas.h"
# define M 30
typedef struct{
	char tem[M];
}aux;
int leer_opciones();
int comp_cad(char c1[], char c2[]);
int compara(char c[]);
void llenado(AGENDA *datos,struct nodo *Lista);
int Validafecha(int dd,int mm,int aa);
void sobrescribe(AGENDA registro[100],FILE *nm,FILE *tl,FILE *cr,FILE *fc,FILE *cp,FILE *im,int i);
int num_tel(struct nodo *Lista,AGENDA contacto);
void Leer_archivos(struct nodo *Lista,FILE *nm,AGENDA registro[], int *tot);
void guardar_enArc(struct nodo *Lista,FILE *nm,AGENDA contacto);
void Ordenar(AGENDA registro[], int *tot);
int main(){
	AGENDA datos,contacto,registro[100];
	FILE *nm=NULL;
	char nombre[20];
	int i=0,x,tot;
	system ("clear");
	int opcion,busqueda=-1,pos=0,ant=0,sig=0,salir;
	struct nodo *Lista;
	Lista=Crear_Lista();
	Leer_archivos(Lista,nm,registro,&tot);
	//////////ordenar el registro
	Ordenar(registro,&tot);
	for(x=0;x<tot;x++){
		Insertar_Final(&Lista,registro[x]);
	}
	do{
			if(Lista!=NULL){
				contacto=Recorrido(Lista,sig,ant,pos);
				printf("\n\n\n\t\t %s",contacto.nombre);
				printf("\n\t\t %s",contacto.tel);
				printf("\n\t\t %s",contacto.correo);
				printf("\n\t\t %d/%d/%d",contacto.dia,contacto.mes,contacto.anio);
				printf("\n\t\t %s",contacto.direccion);
				printf("\n\t\t %s\n\n",contacto.foto);
			}
			opcion=leer_opciones();
			if(opcion!=7){
				switch (opcion) { 
					case 1:
						llenado(&datos,Lista);//leer datos del nuevo contacto
						Insertar_Final(&Lista,datos);
						system ("clear");
					break;
					case 2:	//elimina un elemento en la lista
							setbuf(stdin,NULL);
							printf("\n\n\nEscriba el nombre del contacto que desea eliminar: ");
							scanf("%[^\n]",nombre);
							busqueda=Buscar_Elemento(Lista,nombre);
							if(busqueda==0){
								printf("\n\n\nEl elemento buscado no existe");
							}
							else{
								if(busqueda==1)
									Eliminar_Principio(&Lista);
								else
									if(busqueda==Cuenta_nodo(Lista)){
										Eliminar_Final(&Lista);
										if(pos==busqueda)
											pos--;
										
									}
									else
										Borrar(Lista,busqueda);
									
								printf("\nContacto eliminado");
									
							}
						sleep(2);
						system ("clear");
					break;
					case 3:
					do{
						setbuf(stdin,NULL);
						printf("\n\n\nEscriba el Nombre o teléfono a buscar: ");
						scanf("%[^\n]",nombre);
						busqueda=Buscar_Elemento(Lista,nombre);
						if(busqueda==0){
							printf("\n\n\nEl elemento buscado no existe");
						}
						else{
								contacto=Imprimir_Lista(Lista,busqueda-1);
									printf("\n%s",contacto.nombre);
									printf("\n%s",contacto.tel);
									printf("\n%s",contacto.correo);
									printf("\n%d/%d/%d",contacto.dia,contacto.mes,contacto.anio);
									printf("\n%s",contacto.direccion);
									printf("\n%s\n\n==================",contacto.foto);
						}
							printf("\n\n\nEscriba un numero diferente de 0 para regresar al menu de opc: ");
							scanf("%d",&salir);
						}while(salir==0);
						system ("clear");
					break;
					case 4:if(Cuenta_nodo(Lista)!=0){
								pos--;
								if(verif_nulla(Lista,pos+1)!=0)
									pos++;
								
							}
							if(pos==-1)
								pos=0;
								
					break;
					case 5:if(Cuenta_nodo(Lista)!=0){
								pos++;
								if(verif_nulls(Lista,pos-1)==0)
									pos--;
							}
							if(Cuenta_nodo(Lista)==pos)
								pos--;
					break;
					case 6://Imprime los elementos de la lista
						do{
						if(Lista!=NULL){
							for(i=0;i<Cuenta_nodo(Lista);i++)
							{
									contacto=Imprimir_Lista(Lista,i);
									printf("\n%s",contacto.nombre);
									printf("\n%s",contacto.tel);
									printf("\n%s",contacto.correo);
									printf("\n%d/%d/%d",contacto.dia,contacto.mes,contacto.anio);
									printf("\n%s",contacto.direccion);
									printf("\n%s\n===============",contacto.foto);
							}
						}
						else
							printf("Lista vacia");
							printf("\n\n\nEscriba un numero diferente de 0 para regresar al menu de opc: ");
							scanf("%d",&salir);
						}while(salir==0);
						system ("clear");	
					break;
				}
			}
		}while(opcion!=7);
	if(Lista!=NULL){
		guardar_enArc(Lista,nm,contacto);
		
	}
	else
	{
		remove("Nombre.txt");
		remove("Telefono.txt");
		remove("Correo.txt");
		remove("Direccion.txt");
		remove("Foto.txt");
		remove("Fecha.txt");
	}
	return 0;
}
void Ordenar(AGENDA registro[], int *tot){
	AGENDA tmp;
	int i,j,x;
	x=*tot;
	
	for (i=0;i<x-1;i++){
		for (j=i+1;j<x;j++){
			if (strcmp(registro[i].nombre,registro[j].nombre)>0)
			{
				strcpy(tmp.nombre,registro[i].nombre);
				strcpy(tmp.tel,registro[i].tel);
				strcpy(tmp.correo,registro[i].correo);
				strcpy(tmp.direccion,registro[i].direccion);
				strcpy(tmp.foto,registro[i].foto);
				tmp.dia=registro[i].dia;
				tmp.mes=registro[i].mes;
				tmp.anio=registro[i].anio;
				registro[i]=registro[j];
				registro[j]=tmp;
			}
		}
	}
} 
void Leer_archivos(struct nodo *Lista,FILE *nm,AGENDA registro[], int *tot){
	int total=0;
	aux var[M],bas[M];
	int i=0,j;
	nm=fopen("Nombre.txt","r+");
	if(nm==NULL)
	{
		remove("Nombre.txt");
	}else{///////
		nm=fopen("Nombre.txt","r+");
		while(feof(nm)==0){
			total++;
			fgets(bas[i++].tem,1000,nm);
		}
		fclose(nm);
		i=0;
		*tot=total;
		nm=fopen("Nombre.txt","r+");
		while(feof(nm)==0){
			fgets(var[i].tem,1000,nm);
			i++;
			if(i==total){
				for(j=0;j<strlen(var[i-1].tem);j++){
					registro[i-1].nombre[j]=var[i-1].tem[j];
				}
			}
			else{
				for(j=0;j<strlen(var[i-1].tem)-1;j++){
					registro[i-1].nombre[j]=var[i-1].tem[j];
				}
			}
		}
		fclose(nm);
		i=0;
		nm=fopen("Telefono.txt","r+");
		while(feof(nm)==0){
			fgets(var[i].tem,1000,nm);
			i++;
			if(i==total){
				for(j=0;j<strlen(var[i-1].tem);j++){
					registro[i-1].tel[j]=var[i-1].tem[j];
				}
			}
			else{
				for(j=0;j<strlen(var[i-1].tem)-1;j++){
					registro[i-1].tel[j]=var[i-1].tem[j];
				}
			}
		}
		fclose(nm);
		i=0;
		nm=fopen("Direccion.txt","r+");
		while(feof(nm)==0){
			fgets(var[i].tem,1000,nm);
			i++;
			if(i==total){
				for(j=0;j<strlen(var[i-1].tem);j++){
					registro[i-1].direccion[j]=var[i-1].tem[j];
				}
			}
			else{
				for(j=0;j<strlen(var[i-1].tem)-1;j++){
					registro[i-1].direccion[j]=var[i-1].tem[j];
				}
			}
		}
		fclose(nm);
		i=0;
		nm=fopen("Foto.txt","r+");
		while(feof(nm)==0){
			fgets(var[i].tem,1000,nm);
			i++;
			if(i==total){
				for(j=0;j<strlen(var[i-1].tem);j++){
					registro[i-1].foto[j]=var[i-1].tem[j];
				}
			}
			else{
				for(j=0;j<strlen(var[i-1].tem)-1;j++){
					registro[i-1].foto[j]=var[i-1].tem[j];
				}
			}
		}
		fclose(nm);
		i=0;
		nm=fopen("Fecha.txt","r+");
			for(i=0;i<total;i++)
				fscanf(nm,"%d %d %d",&registro[i].dia,&registro[i].mes,&registro[i].anio);
		fclose(nm);
		i=0;
		nm=fopen("Correo.txt","r+");
		while(feof(nm)==0){
			fgets(var[i].tem,1000,nm);
			i++;
			if(i==total){
				for(j=0;j<strlen(var[i-1].tem);j++){
					registro[i-1].correo[j]=var[i-1].tem[j];
				}
			}
			else{
				for(j=0;j<strlen(var[i-1].tem)-1;j++){
					registro[i-1].correo[j]=var[i-1].tem[j];
				}
			}
		}
		fclose(nm);
		}
}
void guardar_enArc(struct nodo *Lista,FILE *nm,AGENDA contacto){
	int i;
	for(i=0;i<Cuenta_nodo(Lista);i++)
		{
				contacto=Imprimir_Lista(Lista,i);
				if(i==0)
				{
					nm=fopen("Nombre.txt","w+");
					fprintf(nm,"%s",contacto.nombre);
					fclose(nm);	
					nm=fopen("Telefono.txt","w+");
					fprintf(nm,"%s",contacto.tel);
					fclose(nm);
					nm=fopen("Correo.txt","w+");
					fprintf(nm,"%s",contacto.correo);
					fclose(nm);
					nm=fopen("Fecha.txt","w+");
					fprintf(nm,"%d %d %d",contacto.dia,contacto.mes,contacto.anio);
					fclose(nm);
					nm=fopen("Direccion.txt","w+");
					fprintf(nm,"%s",contacto.direccion);
					fclose(nm);
					nm=fopen("Foto.txt","w+");
					fprintf(nm,"%s",contacto.foto);
					fclose(nm);
				}
				else{
					nm=fopen("Nombre.txt","a+");
					fprintf(nm,"\n%s",contacto.nombre);
					fclose(nm);	
					nm=fopen("Telefono.txt","a+");
					fprintf(nm,"\n%s",contacto.tel);
					fclose(nm);
					nm=fopen("Correo.txt","a+");
					fprintf(nm,"\n%s",contacto.correo);
					fclose(nm);
					nm=fopen("Fecha.txt","a+");
					fprintf(nm,"\n%d %d %d",contacto.dia,contacto.mes,contacto.anio);
					fclose(nm);
					nm=fopen("Direccion.txt","a+");
					fprintf(nm,"\n%s",contacto.direccion);
					fclose(nm);
					nm=fopen("Foto.txt","a+");
					fprintf(nm,"\n%s",contacto.foto);
					fclose(nm);
				}
		}
}
int leer_opciones(){ 
	int opc;
	do
	{		
		printf("\n\n\n\n\tOPCIONES \n\n");
		printf("\t1\tAgregar nuevo contacto\n\n");
		printf("\t2\tEliminar un contacto\n\n");
		printf("\t3\tBuscar un contacto\n\n");
		printf("\t4\tAnterior\n\n");
		printf("\t5\tSiguiente\n\n");
		printf("\t6\tImprimir lista de contactos\n\n");
		printf("\t7\tSalir\n\n");
		printf("Escriba la Opcion(1-7): ");
		scanf ("%d",&opc);
	}while (opc<=0 && opc>7);
	system ("clear");
	return opc;
}
void llenado(AGENDA *datos,struct nodo *Lista){
	int i,si=0;
	char aux[15];
	int res,a;
	AGENDA contacto;
	int dd,mm,aa;
	int fech;
	printf("\n\n\tEscriba los datos del nuevo contacto: ");
		printf("\nNOMBRE: ");
		setbuf(stdin,NULL);
		scanf("%[^\n]",datos->nombre);
		do{
			si=0;
			res=1;
			printf("\nNÚMERO TELEFÓNICO: ");
			scanf("%s",aux);
			for(i=0;i<(strlen(aux))&&res==1;i++){
				a=isdigit(aux[i]);
				if(a==0){
					res=0;
					printf("\nerror...\n");
				}
				else{
				res=1;
				}
			}
			si=num_tel(Lista,contacto);

		}while((strlen(aux)!=10)||(res!=1)||(si!=0));
		strcpy(datos->tel,aux);
		do{
		printf("\nCORREO ELECTRÓNICO: ");
		scanf("%s",datos->correo);
		}while(compara(datos->correo)==0);
		do{
			printf("\nFECHA DE NACIMIENTO (dd/mm/aaaa): \n");
			printf("Dia: ");
			scanf("%d",&dd);
			printf("Mes: ");
			scanf("%d",&mm);
			printf("Año: ");
			scanf("%d",&aa);
			fech=Validafecha(dd,mm,aa);
		}while(fech!=1);
		datos->dia=dd;
		datos->mes=mm;
		datos->anio=aa;
		printf("\nDIRECCIÓN POSTAL: ");
		setbuf(stdin,NULL);
		scanf("%[^\n]",datos->direccion);
		setbuf(stdin,NULL);
		printf("\nDIRECCIÓN DE LA IMAGEN: ");		
		setbuf(stdin,NULL);
		scanf("%[^\n]",datos->foto);
}
int num_tel(struct nodo *Lista,AGENDA contacto){
	int cont,i,j,si=0;
	char aux[15],auxtel[15];
	for(i=0;i<Cuenta_nodo(Lista);i++){
		cont=0;
		contacto=Imprimir_Lista(Lista,i);
		strcpy(auxtel,contacto.tel);
		for(j=3;j<(strlen(aux));j++){
			if(aux[j]==auxtel[j]){
				cont++;
			}
		}
		if(cont==7)
			si++;
	}
	return si;
}
int compara(char c[]){
	int i,ret=1;
	for (i=0;i<strlen(c);i++)	
		if(c[i]==' ')
			ret=0;
	return ret;
			
}
int comp_cad(char c1[], char c2[]){
	int i, reg=1;
	
	for(i=0;c1[i]!='\0';i++)
		if(c1[i]!=c2[i])
			reg=0;
	return reg;
}
int Validafecha(int dd,int mm,int aa){
	int valor=1;
	if((mm==1)||(mm==3)||(mm==5)||(mm==7)||(mm==8)||(mm==10) || (mm==12)){
		if((dd>0)&&(dd<=31))
			valor=1;
	else
		valor=0;
	}
	else{
		if((mm==4)||(mm==6)||(mm==9)||(mm==11)){
			if((dd>0)&&(dd<=30))
				valor=1;
			else
				valor=0;
		}
		else{
			if(mm==2){
				if(((aa%4==0)&&(aa%100!=0))||(aa%400==0)){
					if((dd>0)&&(dd<=29))
						valor=1;
					else
						valor=0;
				}
				else{
					if((dd>0)&&(dd<=28))
						valor=1;
					else
						valor=0;
				}
			}
			else{
				if((mm<1)||(mm>12))
					valor=0;
			}
		}
	}
	return valor;
	}
