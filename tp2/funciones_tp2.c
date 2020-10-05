#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "funciones_tp2.h"
#include "cola.h"
#include "heap.h"
#include "mensajes.h"
#include "abb.h"

struct doctor
{
  char *nombre;
  char *especialidad;
  size_t cant_atendidos;
};

struct paciente
{
  char *nombre;
  size_t anio;
};

struct especialidad
{
  cola_t *urgentes;
  heap_t *no_urgentes;
  size_t en_espera;
};

typedef struct informe
{
  doctor_t **doctores;
  size_t cantidad;
} informe_t;

void encolar_paciente(paciente_t *paciente, especialidad_t *especialidad, const char *urgencia)
{
  if (strcmp(urgencia, URGENTE) == 0)
  {
    cola_encolar(especialidad->urgentes, paciente);
  }
  else
  {
    heap_encolar(especialidad->no_urgentes, paciente);
  }
  especialidad->en_espera++;
}

size_t en_espera(especialidad_t *especialidad)
{
  return especialidad->en_espera;
}

void atender_siguiente(doctor_t *doctor, especialidad_t *especialidad)
{
  paciente_t *paciente;
  if (!cola_esta_vacia(especialidad->urgentes))
  {
    paciente = cola_desencolar(especialidad->urgentes);
  }
  else if (!heap_esta_vacio(especialidad->no_urgentes))
  {
    paciente = heap_desencolar(especialidad->no_urgentes);
  }
  else
  {
    printf(SIN_PACIENTES);
    return;
  }
  doctor->cant_atendidos++;
  especialidad->en_espera--;
  printf(PACIENTE_ATENDIDO, paciente->nombre);
  printf(CANT_PACIENTES_ENCOLADOS, especialidad->en_espera, doctor->especialidad);
}

char *obtener_especialidad(doctor_t *doctor)
{
  return doctor->especialidad;
}

int cmp_anios(const void *_a, const void *_b)
{
  const paciente_t *a = _a;
  const paciente_t *b = _b;
  if (a->anio <= b->anio)
    return 1;

  return -1;
}

void agregar_especialidad(hash_t *especialidades, char *nombre)
{
  if (hash_pertenece(especialidades, nombre))
    return;

  especialidad_t *especialidad = malloc(sizeof(especialidad_t));
  if (!especialidad)
    return;

  especialidad->urgentes = cola_crear();
  if (!especialidad->urgentes)
  {
    free(especialidad);
    return;
  }

  especialidad->no_urgentes = heap_crear(cmp_anios);
  if (!especialidad->no_urgentes)
  {
    cola_destruir(especialidad->urgentes, NULL);
    free(especialidad);
    return;
  }
  especialidad->en_espera = 0;
  hash_guardar(especialidades, nombre, especialidad);
}

bool guardar_doctor(const char *nombre, void *_doctor, void *extra) // Función visitar
{
  doctor_t *doctor = _doctor;
  informe_t *informe = extra;

  informe->doctores[informe->cantidad] = doctor;
  informe->cantidad++;

  return true;
}

void imprimir_informe(informe_t *informe)
{
  printf(DOCTORES_SISTEMA, informe->cantidad);
  doctor_t *doctor;
  for (size_t i = 0; i < informe->cantidad; i++)
  {
    doctor = informe->doctores[i];
    printf(INFORME_DOCTOR, i + 1, doctor->nombre, doctor->especialidad, doctor->cant_atendidos);
  }
}

void informe_doctores(const char *inicial, const char *final, abb_t *doctores)
{
  informe_t *informe = malloc(sizeof(informe_t));
  if (!informe)
    return;

  informe->cantidad = 0;
  informe->doctores = malloc(sizeof(doctor_t *) * abb_cantidad(doctores));

  if (!informe->doctores)
  {
    free(informe);
    return;
  }

  abb_por_rangos(doctores, guardar_doctor, informe, inicial, final);
  imprimir_informe(informe);

  free(informe->doctores);
  free(informe);
}

void *constructor_doctor(char **elementos, void *extra)
{
  doctor_t *doctor = malloc(sizeof(doctor_t));

  if (!doctor)
    return NULL;

  doctor->nombre = strdup(elementos[0]);
  doctor->especialidad = strdup(elementos[1]);
  doctor->cant_atendidos = 0;

  return doctor;
}

void *constructor_paciente(char **elementos, void *extra)
{
  char *resto;
  long anio = strtol(elementos[1], &resto, 10); // Aprovechamos la capacidad validativa de strtol

  if (resto == elementos[1] || *resto != '\0')
  {
    printf(ENOENT_ANIO, elementos[1]);
    return NULL;
  }

  paciente_t *paciente = malloc(sizeof(paciente_t));

  if (!paciente)
    return NULL;

  paciente->nombre = strdup(elementos[0]);
  paciente->anio = (size_t)anio;

  return paciente;
}

abb_t *crear_abb_doctores(lista_t *lista, hash_t *especialidades)
{
  abb_t *doctores = abb_crear(strcmp, destruir_doctor);

  if (!doctores)
    return NULL;

  doctor_t *actual;
  while (!lista_esta_vacia(lista))
  {
    actual = lista_borrar_primero(lista);
    abb_guardar(doctores, actual->nombre, actual);
    agregar_especialidad(especialidades, actual->especialidad);
  }
  lista_destruir(lista, NULL);
  return doctores;
}

hash_t *crear_hash_pacientes(lista_t *lista)
{
  hash_t *pacientes = hash_crear(destruir_paciente);

  if (!pacientes)
    return NULL;

  paciente_t *actual;
  while (!lista_esta_vacia(lista))
  {
    actual = lista_borrar_primero(lista);
    hash_guardar(pacientes, actual->nombre, actual);
  }
  lista_destruir(lista, NULL);
  return pacientes;
}

void destruir_especialidad(void *esp)
{
  especialidad_t *especialidad = esp;
  cola_destruir(especialidad->urgentes, NULL);
  heap_destruir(especialidad->no_urgentes, NULL);
  free(especialidad);
}

void destruir_doctor(void *doc)
{
  doctor_t *doctor = doc;
  free(doctor->nombre);
  free(doctor->especialidad);
  free(doctor);
}

void destruir_paciente(void *pac)
{
  paciente_t *paciente = pac;
  free(paciente->nombre);
  free(paciente);
}