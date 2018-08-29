#include <stdio.h>
#include <stdlib.h>
# include <string.h>
#include "Listas.h"

struct nodo *Crear_Lista(){
	 return NULL;
}

void Insertar_Principio (struct nodo **Lista, AGENDA *datos){
	struct nodo *p;
	struct nodo *aux = NULL; //Para no tener problemas con el doble puntero en struct.
	aux = *Lista;
	p=crea_nodo();
	p->info=*datos;
	p->ant=NULL;
	p->sig=NULL;
	if(*Lista==NULL){//Primer elemento de la lista..
	    *Lista =p;
	}
	 else{
		p->sig=aux;
		p->ant=aux->ant;
		aux->ant=p;
		aux=p;
		*Lista=aux;
	}
}

void Insertar_Final (struct nodo **Lista, AGENDA datos ){
	struct nodo *p,*aux;
	
	if(*Lista==NULL )
	{
		Insertar_Principio(Lista,&datos);
	}
	else
	{   aux=*Lista;
        p=crea_nodo();
        p->info=datos;
        p->sig=NULL;
        p->ant=NULL;
		for(;aux->sig!=NULL;)
            aux=aux->sig;
        p->sig=aux->sig;
        p->ant=aux;
        aux->sig=p;
	}
}

void Eliminar_Principio(struct nodo **Lista){
	int cont;
	struct nodo *p,*aux;
	p=((struct nodo *)malloc(sizeof(struct nodo)));
	cont=Cuenta_nodo(*Lista);
	if(cont == 0)
		printf("\n\nLa lista es vacía, no se pudo eliminar elemento");
	else
		if(cont==1)
			*Lista=NULL;
	else
	{
		p=*Lista;
		aux=*Lista;
		aux=aux->sig;
		aux->ant=p->ant;
		free(p);
		*Lista=aux;	
		}
	}

void Eliminar_Final(struct nodo **Lista){
	int cont;
	struct nodo *p, *aux;

	cont=Cuenta_nodo(*Lista);
	aux=*Lista;
	if(cont == 0)
		printf("\n\nLa Lista es vacía, no se pudo eliminar elemento");
	else
		if(cont==1)
			*Lista=NULL;
		else
		{
			for(;aux->sig!=NULL;){
				aux=aux->sig;
			}
			p=aux;
			aux->ant->sig=aux->sig;
			free(p);
		}
	}
 
int Buscar_Elemento(struct nodo *Lista,char *nom){	
	int x=0,ban=0,sa=0;
	if(Lista==NULL)
	{
		sa=1;
		printf("\n\nLista Vacía");
	}
	if(Lista!=NULL){
		for(;ban==0 && sa==0;)
		{
			if((strcmp(Lista->info.nombre,nom)==0)||(strcmp(Lista->info.tel,nom)==0))
				ban=1;
			if(Lista->sig==NULL)
				sa=1;
			Lista=Lista->sig;
			x++;
		}
	}
	if(ban==0)
		return 0;
	else
		return x; 
}

struct nodo *crea_nodo(){
       return ((struct nodo *)malloc(sizeof(struct nodo)));
}
	
AGENDA Imprimir_Lista(struct nodo *lista,int a){
	AGENDA imprimir;
	int i;
		for(i=0;i<=a;i++)
			if(i!=0)
				lista=lista->sig;
		strcpy(imprimir.nombre,lista->info.nombre);
		strcpy(imprimir.tel,lista->info.tel);
		strcpy(imprimir.correo,lista->info.correo);
		imprimir.dia=lista->info.dia;
		imprimir.mes=lista->info.mes;
		imprimir.anio=lista->info.anio;
		strcpy(imprimir.direccion,lista->info.direccion);
		strcpy(imprimir.foto,lista->info.foto);
	return imprimir;
}

int Cuenta_nodo(struct nodo *lista){
	int i=0;
	for(; lista!=NULL;lista=lista->sig)
		i++;
return i;
}

AGENDA Recorrido(struct nodo *Lista, int sig, int ant,int pos){
	int i;

	for(i=0;i<=pos;i++)
		if(Lista->sig!=NULL &&i!=0)
			Lista=Lista->sig;
	if(sig==1 && Lista->sig!=NULL)
				Lista=Lista->sig;
	if(ant==1 && Lista->ant!=NULL)
			Lista=Lista->ant;
	return Lista->info;
}

int verif_nulls(struct nodo *Lista,int pos){
	int i,reg=1;
	for(i=0;i<=pos;i++)
		if(i!=0 && Lista->sig!=NULL)
			Lista=Lista->sig;
	if(Lista->sig==NULL)
		reg=0;
	return reg;
}

int verif_nulla(struct nodo *Lista,int pos){
	int i,reg=1;
	for(i=0;i<pos;i++)
		if(i!=0 && Lista->ant!=NULL)
			Lista=Lista->ant;
	if(Lista->ant==NULL)
		reg=0;
	return reg;
}

void Borrar (struct nodo *Lista,int p){
	struct nodo *aux;
	aux=Lista;
	int i;
	for(i=0;i<p-1;i++)
		if(i!=0)
			aux=aux->sig;
	aux->sig=aux->sig->sig;
	aux->sig->ant=aux->sig;
}
