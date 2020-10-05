#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include "funciones_tp2.h"
#include "cola.h"
#include "strutil.h"
#include "csv.h"
#include "lista.h"
#include "hash.h"
#include "heap.h"
#include "abb.h"
#include "mensajes.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"
#define COMANDO_SALIR "SALIR"

size_t cantidad_parametros(const char **parametros)
{
  size_t resultado = 0;
  while (parametros[resultado])
  {
    resultado++;
  }
  return resultado;
}

// Devuelve true si se quiere continuar con el sistema, false en caso de que se quiera salir del mismo
bool procesar_comando(const char *comando, const char **parametros, hash_t *especialidades, abb_t *doctores, hash_t *pacientes)
{
  if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0)
  {
    if (cantidad_parametros(parametros) < 3)
    {
      printf(ENOENT_PARAMS, comando);
    }
    else if (!hash_pertenece(pacientes, parametros[0]))
    {
      printf(ENOENT_PACIENTE, parametros[0]);
    }
    else if (!hash_pertenece(especialidades, parametros[1]))
    {
      printf(ENOENT_ESPECIALIDAD, parametros[1]);
    }
    else if (strcmp(parametros[2], URGENTE) != 0 && strcmp(parametros[2], REGULAR) != 0)
    {
      printf(ENOENT_URGENCIA, parametros[2]);
    }
    else
    {
      especialidad_t *especialidad = hash_obtener(especialidades, parametros[1]);

      encolar_paciente(hash_obtener(pacientes, parametros[0]), especialidad, parametros[2]);

      printf(PACIENTE_ENCOLADO, parametros[0]);
      printf(CANT_PACIENTES_ENCOLADOS, en_espera(especialidad), parametros[1]);
    }
  }
  else if (strcmp(comando, COMANDO_ATENDER) == 0)
  {
    if (cantidad_parametros(parametros) < 1)
    {
      printf(ENOENT_PARAMS, comando);
    }
    else
    {
      doctor_t *doc = abb_obtener(doctores, parametros[0]);
      if (!doc)
      {
        printf(ENOENT_DOCTOR, parametros[0]);
      }
      else
      {
        atender_siguiente(doc, hash_obtener(especialidades, obtener_especialidad(doc)));
      }
    }
  }
  else if (strcmp(comando, COMANDO_INFORME) == 0)
  {
    if (cantidad_parametros(parametros) < 2)
    {
      printf(ENOENT_PARAMS, comando);
    }
    else
    {
      informe_doctores(parametros[0], parametros[1], doctores);
    }
  }
  else if (strcmp(comando, COMANDO_SALIR) == 0)
  {
    return false;
  }
  else
  {
    printf(ENOENT_CMD, (comando));
  }
  return true;
}

void eliminar_fin_linea(char *linea)
{
  size_t len = strlen(linea);
  if (linea[len - 1] == '\n')
  {
    linea[len - 1] = '\0';
  }
}

void procesar_entrada(hash_t *especialidades, abb_t *doctores, hash_t *pacientes)
{
  char *linea = NULL;
  size_t c = 0;
  bool cortar = false;
  while (!cortar && getline(&linea, &c, stdin) > 0)
  {
    eliminar_fin_linea(linea);
    char **campos = split(linea, ':');
    if (campos[1] == NULL)
    {
      printf(ENOENT_FORMATO, linea);
      free_strv(campos);
      continue;
    }
    char **parametros = split(campos[1], ',');
    cortar = !procesar_comando(campos[0], (const char **)parametros, especialidades, doctores, pacientes);
    free_strv(parametros);
    free_strv(campos);
  }
  free(linea);
}

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    printf(ENOENT_CANT_PARAMS);
    return 1;
  }

  // Parseo de doctores
  lista_t *lista_doctores = csv_crear_estructura(argv[1], constructor_doctor, NULL);
  if (!lista_doctores)
  {
    printf(ENOENT_ARCHIVO, "doctores");
    return 1;
  }

  // Parseo de pacientes
  lista_t *lista_pacientes = csv_crear_estructura(argv[2], constructor_paciente, NULL);
  if (!lista_pacientes)
  {
    printf(ENOENT_ARCHIVO, "pacientes");
    lista_destruir(lista_doctores, NULL);
    return 1;
  }

  // Creación de estructuras
  hash_t *especialidades = hash_crear(destruir_especialidad);
  if (!especialidades)
  {
    lista_destruir(lista_doctores, destruir_doctor);
    lista_destruir(lista_pacientes, destruir_paciente);
    return 2;
  }

  abb_t *doctores = crear_abb_doctores(lista_doctores, especialidades);
  if (!doctores)
  {
    hash_destruir(especialidades);
    lista_destruir(lista_doctores, destruir_doctor);
    lista_destruir(lista_pacientes, destruir_paciente);
    return 3;
  }

  hash_t *pacientes = crear_hash_pacientes(lista_pacientes);
  if (!pacientes)
  {
    hash_destruir(especialidades);
    abb_destruir(doctores);
    lista_destruir(lista_pacientes, destruir_paciente);
    return 4;
  }

  procesar_entrada(especialidades, doctores, pacientes);

  hash_destruir(especialidades);
  abb_destruir(doctores);
  hash_destruir(pacientes);

  return 0;
}