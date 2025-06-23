#include <stdio.h>
#include <string.h>

#define MAX_LIBROS 10
#define DISPONIBLE "Disponible"
#define PRESTADO "Prestado"

typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[15];
} Libro;

Libro biblioteca[MAX_LIBROS];
int cantidadLibros = 0;

int buscarPorID(int id) {
    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i].id == id)
            return i;
    }
    return -1;
}

void registrarLibro() {
    if (cantidadLibros >= MAX_LIBROS) {
        printf("No se pueden agregar más libros.\n");
        return;
    }

    int id;
    printf("Ingrese ID del libro: ");
    scanf("%d", &id);
    if (buscarPorID(id) != -1) {
        printf("El ID ya existe. Debe ser único.\n");
        return;
    }

    getchar(); 
    biblioteca[cantidadLibros].id = id;
    printf("Ingrese título del libro: ");
    fgets(biblioteca[cantidadLibros].titulo, sizeof(biblioteca[cantidadLibros].titulo), stdin);
    biblioteca[cantidadLibros].titulo[strcspn(biblioteca[cantidadLibros].titulo, "\n")] = 0;

    printf("Ingrese autor del libro: ");
    fgets(biblioteca[cantidadLibros].autor, sizeof(biblioteca[cantidadLibros].autor), stdin);
    biblioteca[cantidadLibros].autor[strcspn(biblioteca[cantidadLibros].autor, "\n")] = 0;

    printf("Ingrese año de publicación: ");
    scanf("%d", &biblioteca[cantidadLibros].anio);

    strcpy(biblioteca[cantidadLibros].estado, DISPONIBLE);
    cantidadLibros++;
    printf("Libro registrado exitosamente.\n");
}

void mostrarLibros() {
    printf("\n%-5s %-30s %-20s %-6s %-12s\n", "ID", "Título", "Autor", "Año", "Estado");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < cantidadLibros; i++) {
        printf("%-5d %-30s %-20s %-6d %-12s\n", biblioteca[i].id,
               biblioteca[i].titulo, biblioteca[i].autor,
               biblioteca[i].anio, biblioteca[i].estado);
    }
}

void buscarLibro() {
    int opcion, id;
    char titulo[100];
    printf("Buscar por:\n1. ID\n2. Título\nSeleccione una opción: ");
    scanf("%d", &opcion);
    getchar(); 

    if (opcion == 1) {
        printf("Ingrese ID del libro: ");
        scanf("%d", &id);
        int  bus = buscarPorID(id);
        if (bus != -1) {
            Libro l = biblioteca[bus];
            printf("ID: %d\nTítulo: %s\nAutor: %s\nAño: %d\nEstado: %s\n", l.id, l.titulo, l.autor, l.anio, l.estado);
        } else {
            printf("Libro no encontrado.\n");
        }
    } else if (opcion == 2) {
        printf("Ingrese título del libro: ");
        fgets(titulo, sizeof(titulo), stdin);
        titulo[strcspn(titulo, "\n")] = 0;
        int encontrado = 0;
        for (int i = 0; i < cantidadLibros; i++) {
            if (strcmp(biblioteca[i].titulo, titulo) == 0) {
                Libro l = biblioteca[i];
                printf("ID: %d\nTítulo: %s\nAutor: %s\nAño: %d\nEstado: %s\n", l.id, l.titulo, l.autor, l.anio, l.estado);
                encontrado = 1;
            }
        }
        if (!encontrado) printf("Libro no encontrado.\n");
    } else {
        printf("Opción no válida.\n");
    }
}

void actualizarEstado() {
    int id;
    printf("Ingrese el ID del libro para cambiar su estado: ");
    scanf("%d", &id);
    int pos = buscarPorID(id);
    if (pos != -1) {
        if (strcmp(biblioteca[pos].estado, DISPONIBLE) == 0) {
            strcpy(biblioteca[pos].estado, PRESTADO);
        } else {
            strcpy(biblioteca[pos].estado, DISPONIBLE);
        }
        printf("Libro actualizado.\n");
    } else {
        printf("Libro no encontrado.\n");
    }
}

void eliminarLibro() {
    int id;
    printf("Ingrese el ID del libro a eliminar: ");
    scanf("%d", &id);
    int pos = buscarPorID(id);
    if (pos != -1) {
        for (int i = pos; i < cantidadLibros - 1; i++) {
            biblioteca[i] = biblioteca[i + 1];
        }
        cantidadLibros--;
        printf("Libro eliminado.\n");
    } else {
        printf("Libro no encontrado.\n");
    }
}

int main() {
    int opcion;
    do {
        printf("\nGestión de Biblioteca\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar libros\n");
        printf("3. Buscar libro\n");
        printf("4. Actualizar estado\n");
        printf("5. Eliminar libro\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: registrarLibro(); break;
            case 2: mostrarLibros(); break;
            case 3: buscarLibro(); break;
            case 4: actualizarEstado(); break;
            case 5: eliminarLibro(); break;
            case 6: printf("Salir del programa\n"); break;
            default: printf("Opción inválida.\n");
        }
    } while (opcion != 6);

    return 0;
}
