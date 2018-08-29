#include <stdio.h>
# define N 30
# define M 30

typedef struct {
	char nombre[M];
	char tel[N];
	char correo [N];
	int dia;
	int mes;
	int anio;
	char direccion[N];
	char foto[N];
}AGENDA;

struct nodo{
	AGENDA info;
	struct nodo *sig;
	struct nodo *ant;
};

struct nodo *Crear_Lista ();
void Insertar_Principio (struct nodo **Lista, AGENDA *datos);
void Insertar_Final(struct nodo **Lista, AGENDA datos);
AGENDA Imprimir_Lista(struct nodo *lista,int a);
struct nodo *crea_nodo();
void Eliminar_Principio(struct nodo **Lista);
int Cuenta_nodo(struct nodo *Lista);
void Eliminar_Final(struct nodo **Lista);
int Buscar_Elemento(struct nodo *Lista,char *nom);
int valor(struct nodo *Lista, int pos);
//void Imprimir_Listaguion(struct nodo *lista,int y,int x);
AGENDA Recorrido(struct nodo *Lista, int sig, int ant,int pos);
int verif_nulls(struct nodo *Lista,int pos);
int verif_nulla(struct nodo *Lista,int pos);
void Borrar (struct nodo *Lista,int p);
