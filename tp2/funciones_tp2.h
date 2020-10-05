#ifndef __FUNCIONES_TP2
#define __FUNCIONES_TP2

#include "abb.h"
#include "hash.h"
#include "lista.h"

#define URGENTE "URGENTE"
#define REGULAR "REGULAR"

typedef struct doctor doctor_t;
typedef struct paciente paciente_t;
typedef struct especialidad especialidad_t;

/**Devuelve un doctor_t* castedo a void*, con toda la información del doctor. Devuelve NULL si falla.*/
void* constructor_doctor(char** elementos, void* extra); 

/**Devuelve un paciente_t* castedo a void*, con toda la información del paciente. Devuelve NULL si falla.*/
void* constructor_paciente(char** elementos, void* extra); 

/**
 * Encola al paciente en la especialidad dada la urgencia: si esta es URGENTE lo encola en la cola de dicha 
 * especialidad, sino lo hace en el heap de la misma. 
*/
void encolar_paciente(paciente_t* paciente, especialidad_t* especialidad, const char* urgencia);

/**Devuelve cuántos pacientes hay en espera (tanto urgentes como regulares) en dicha especialidad.*/
size_t en_espera(especialidad_t* especialidad);

/**Desencola, dentro de la especialidad del doctor que recibe, al paciente que haya entrado primero en la cola de urgencias, o si esta está vacía, desencola del heap
 * según la antiguedad. Precondición: especialidad debe ser la especialidad que tenga el doctor.*/
void atender_siguiente(doctor_t* doctor, especialidad_t* especialidad);

/**Imprime en pantalla la lista de doctores en orden alfabético, comenzando desde el doctor inicial hasta el final.
 * Si inicial o/y final son NULL, entonces se lo toma como que la lista a imprimir debe comenzar desde el inicio o/y hasta el
 * final respectivamente. Si no existe un doctor con nombre inicial o final, se toma el doctor que exista más cercano de acuerdo
 * al orden alfabético. También se imprime junto a cada doctor la cantidad de pacientes atendidos desde que inició el sistema.
*/
void informe_doctores(const char* inicial, const char* final, abb_t* doctores);

/**Devuelve el nombre de la especialdiad del doctor que recibe.*/
char* obtener_especialidad(doctor_t* doctor);

/**Devuelve un abb que todos los doctores que se pasen en la lista. Para ordenarlos se usa strcmp, o sea orden alfabético.
 * Además, se agrega al hash de especialidades todas las especialidades que se tengan entre todos los doctores. Por último, 
 * la lista se destruye.
*/
abb_t* crear_abb_doctores(lista_t* lista, hash_t* especialidades);

/**Devuelve un hash con todos los pacientes que se pasen en la lista. La lista es destruida.*/
hash_t* crear_hash_pacientes(lista_t* lista);

void destruir_especialidad(void* especialidad);

void destruir_doctor(void* doc);

void destruir_paciente(void* pac);

#endif