#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 3

typedef struct
{
    int id;
    char nombre[21];
    int edad;
    int estado;
}edatos;

int menu();
int inicializar(edatos lista[],int tam);
int buscarlibre(edatos lista[],int tam);
int alta(edatos lista[],int tam,int* id);
int validaEntero(int entero,int min,int max);
int validatexto(char texto[],int limite);
int mostrarlista(edatos lista[],int tam);
void mostrar(edatos lista);
int buscarID(edatos lista[],int tam,int id);
int baja(edatos lista[],int tam);
int modificar(edatos lista[],int tam);
int ordenar(edatos lista[],int tam);

int main()
{
    edatos personas[TAM];
    int nextID = 1;
    char seguir = 'n';
    int flag = 0;

    inicializar(personas,TAM);
    do
        {
            switch(menu())
            {
            case 1:
                if(alta(personas,TAM,&nextID))
                    {
                       printf("\nAlta Exitosa!\n");
                       flag = 1;
                    }
                else
                    {
                        printf("\nAlta Cancelada!\n");
                    }
                break;
            case 2:
                if(modificar(personas,TAM))
                    {
                        printf("\nModificacion Exitosa!");
                    }
                else
                    {
                        printf("\nModificacion Cancelada");
                    }
                break;
            case 3:
                if(baja(personas,TAM))
                    {
                        printf("\nBaja Exitosa!");
                    }
                else
                    {
                        printf("\nBaja Cancelada");
                    }
                break;
            case 4:
                mostrarlista(personas,TAM);
                break;
            case 5:

                if(flag == 1)
                    {
                if(ordenar(personas,TAM))
                    {
                        printf("\nOrdenamiento Exitoso!");
                    }
                else
                    {
                        printf("\nOrdenamiento Cancelado");
                    }
                    }
                else
                    {
                        printf("\nPrimero de Un alta");
                    }
                break;
            case 6:
                seguir = 's';
                break;
            }
        printf("\n");
        system("pause");
        system("cls");
        }while(seguir == 'n');
    return 0;
}
int menu()
{
    int opcion;

    printf("|------------------------|\n");
    printf("|          MENU          |\n");
    printf("|------------------------|\n");
    printf("|   1)Alta Cliente       |\n");
    printf("|   2)Modificar Clientes |\n");
    printf("|   3)Baja Clientes      |\n");
    printf("|   4)Listar Clientes    |\n");
    printf("|   5)Ordenar Clientes   |\n");
    printf("|   6)Salir              |\n");
    printf("|------------------------|\n\n");
    printf("Opcion: ");
    scanf("%d",&opcion);

    while(opcion < 1 || opcion > 6)
        {
            printf("Opcion Invalida\n");
            fflush(stdin);
            printf("Opcion: ");
            scanf("%d",&opcion);
        }

    return opcion;
}
int inicializar(edatos lista[],int tam)          //incializa a todo en 1 para indicar que estan vacios
{
    int ok = 0;

    if(lista != NULL && tam > 0)
        {
            for(int i = 0; i<tam; i++)
            {
                    lista[i].estado = 1;
            }
            ok = 1;
        }
    return ok;
}
int buscarlibre(edatos lista[],int tam)       //busca al primer vector que este en 1
{
    int libre = -1;

    if(lista != NULL && tam > 0)
        {
            for(int i = 0; i<tam; i++)
                {
                    if(lista[i].estado == 1)
                        {
                            libre = i;
                            break;
                        }
                }
        }
    return libre;
}
int alta(edatos lista[],int tam,int* id)
{
    int ok = 0;
    int indice;

    if(lista != NULL && tam > 0 && id != NULL)
        {
            indice = buscarlibre(lista,tam);

            if(indice == -1)
                {
                    printf("No hay lugares");
                }
            else
                {
                    lista[indice].id = *id;

                    printf("Nombre: ");
                    fflush(stdin);
                    gets(lista[indice].nombre);
                    while(!validatexto(lista[indice].nombre,21))
                          {
                            printf("Error. Nombre demasiado largo\n");
                            printf("Nombre: ");
                            fflush(stdin);
                            gets(lista[indice].nombre);
                          }

                    printf("Edad: ");
                    fflush(stdin);
                    scanf("%d",&lista[indice].edad);
                    while(!validaEntero(lista[indice].edad,18,64))
                        {
                            printf("Error. Edad no Valida\n");
                            printf("Edad: ");
                            fflush(stdin);
                            scanf("%d",&lista[indice].edad);
                        }
                    lista[indice].estado = 0;
                    (*id)++;

                    ok = 1;
                }
        }
        return ok;
}
int buscarID(edatos lista[],int tam,int id)       //busca el id en todo el listado solo se usa en baja o modifica
{
    int indice = -1;

    if(lista != NULL && tam > 0)
        {
            for(int i = 0; i<tam; i++)
                {
                    if(!lista[i].estado && lista[i].id == id)
                        {
                            indice = i;

                            break;
                        }
                }
        }
    return indice;
}

int baja(edatos lista[],int tam)
{
    int ok = 0;
    int id;
    int indice;
    char confirmacion;

    if(lista != NULL && tam > 0)
        {
            printf("ID: ");
            scanf("%d",&id);

             indice = buscarID(lista,tam,id);

             if(indice == -1)
                {
                    printf("No existe ese ID");
                }
            else
                {
                    printf("|   ID  |   Nombre  |   Edad    |\n");
                    mostrar(lista[indice]);
                    printf("\nEsta seguro? s(si) n(no): ");
                    fflush(stdin);
                    scanf("%c",&confirmacion);

                    while(confirmacion != 's' && confirmacion != 'n')
                        {
                            printf("Opcion No valida\n");
                            printf("\nEsta seguro? s(si) n(no): ");
                            fflush(stdin);
                            scanf("%c",&confirmacion);
                        }
                    if(confirmacion == 's')
                        {
                            lista[indice].estado = 1;
                            ok = 1;
                        }
                }
        }
    return ok;
}
int modificar(edatos lista[],int tam)
{
    int ok = 0;

    int id;
    int indice;
    int opcion;

    if(lista != NULL && tam > 0)
        {
            printf("ID: ");
            scanf("%d",&id);

             indice = buscarID(lista,tam,id);

             if(indice == -1)
                {
                    printf("No existe ese ID");
                }
            else
                {
                    printf("|   ID  |   Nombre  |   Edad    |\n");
                    mostrar(lista[indice]);

                    printf("\nQue desea modificar?\n");
                    printf("1)Nombre: %s\n",lista[indice].nombre);
                    printf("2)Edad: %d\n",lista[indice].edad);
                    printf("Opcion: ");
                    fflush(stdin);
                    scanf("%d",&opcion);

                    while(opcion < 1 || opcion > 2)
                        {
                            printf("Error. Opcion Invalida\n");
                            printf("Opcion: ");
                            fflush(stdin);
                            scanf("%d",&opcion);
                        }

                    switch(opcion)
                    {
                    case 1:
                        printf("Nuevo Nombre: ");
                        fflush(stdin);
                        gets(lista[indice].nombre);
                        break;
                    case 2:
                        printf("Nueva Edad: ");
                        fflush(stdin);
                        scanf("%d",&lista[indice].edad);
                        break;
                    }
                    ok = 1;
                }
        }
    return ok;
}

int ordenar(edatos lista[],int tam)
{
    int ok = 0;
    edatos aux;
    if(lista != NULL && tam > 0)
        {

            for(int i = 0; i<tam-1; i++)
            {
                    for(int j = i+1; j<tam; j++)
                        {
                            if(lista[i].edad > lista[j].edad)
                                {
                                  aux = lista[i];
                                  lista[i] = lista[j];
                                  lista[j] = aux;
                                }
                        }
            }
            ok = 1;
        }
    return ok;
}

void mostrar(edatos lista)
{
    printf("    %d      %s        %d",lista.id,
                                      lista.nombre,
                                      lista.edad);
}
int mostrarlista(edatos lista[],int tam)
{
    int ok = 0;
    int flag = 1;
    if(lista != NULL && tam > 0)
        {
            printf("|   ID  |   Nombre  |   Edad    |\n");
            for(int i = 0; i<tam; i++){
            if(lista[i].estado != 1)
                {
                mostrar(lista[i]);
                printf("\n");
                flag = 0;
                }
            }

            if(flag)
                {
                    printf("\nNo hay datos cargados");
                }
            ok = 1;
        }
    return ok;
}
int validaEntero(int entero,int min,int max)        //terminar todo con muchos a muchos y fijarme el indice de buscar libre que no estaria andando
{
    int ok = 1;

    if(entero < min || entero > max)
    {
        ok = 0;
    }
    return ok;
}
int validatexto(char texto[],int limite)
{
    int ok = 1;
    if(texto != NULL && limite > 0)
        {
            if(limite < strlen(texto))
                {
                    ok = 0;
                }
        }
    return ok;
}
