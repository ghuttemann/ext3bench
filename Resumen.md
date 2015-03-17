# Introducción #

Se presenta en esta página un resumen de lo más resaltante a tener en cuenta en nuestro proyecto.


# Métricas para la evaluación del sistema #

  1. **BLs:** Cantidad de bytes leídos por segundo.
  1. **BEs:** Cantidad de bytes escritos por segundo.
  1. **LL:**  Latencia de lectura.
  1. **LE:**  Latencia de escritura.
  1. **tCD:**  Tiempo de creación de directorios.
  1. **tBD:**  Tiempo de borrado de directorios.
  1. **PF:**  Porcentaje de fragmentación del sistema de archivos.

# Parámetros a variar #

  1. **Tamaño del Bloque (pTB):** tiene influencia fundamentalmente en las lecturas. Cómo no se puede variar online, se probará con el valor máximo (4Kb) y con el valor mínimo (1Kb)
  1. **Nivel de journaling (pNJ):** Influye sobre todos en las escrituras. Se trata del nivel con el que las transacciones del filesystem serán protegidas para la recuperación, a través del archivo de journal.
```
     tune2fs: # tune2fs -O has_journal -o journal_data /dev/hdXY
```
  1. **Sync Interval (pSI):** intervalo de tiempo entre cada sincronización del journal con los archivos reales. Se puede cambiar al montar el sistema de archivos utilizando -o commit=Nsec.  A mayores valores de tiempo, se mejora el rendimiento porque se reduce la sobrecarga de operaciones del sistema de archivos, sin embargo, se pierde en confiabilidad ante fallos del sistema. Influye en operaciones de escritura
  1. **Eliminar la actualización del access time (pAT):** influye en lecturas. Consiste en la actualización de este atributo ante cada acceso al archivo.
```
Se puede manipular editando /etc/fstab con lo siguiente: 
    /dev/hda1 / ext3 defaults, errors=remount-ro, noatime, auto, rw, dev, exec, suid, nouser, data=writeback 0 1
```

# Operaciones Básicas #

> _Operaciones_ ------- _Abreviatura_ ------- _Responsable_ ------- _Estado_

  1. Crear Archivo.      **(CA)**             ghuttemann         semi-terminado
  1. Leer Archivo.       **(LA)**             ghuttemann
    1. Secuencialmente.
    1. Aleatoriamente.
  1. Escribir Archivo.   **(EA)**             ghuttemann
    1. Secuencialmente.
    1. Aleatoriamente.
  1. Borrar Archivo.     **(BA)**             cparra
  1. Crear Directorio.   **(CD)**             cparra
  1. Borrar Directorio.  **(BD)**             cparra

> _**Obs:**_ Todas las operaciones básicas, deben ser implementadas en **_primitivas.c_**

# Operaciones considerando las cargas (OPCx) #

  1. **c1000A:** Crear 1000 archivos para pruebas de re-lectura.
  1. **l1000A:** Leer secuencialmente los 1000 archivos creados.
  1. **rl1000A:** Releer secuencialmente los 1000 archivos creados.
  1. **c2000A2m:** Crear 2000 archivos de 2 MB para accesos secuenciales y escrituras
  1. **re2000A2m:** Reescribir aleatoriamente en los 2000 archivos.
  1. **lNSeq:** Leer los N archivos creados anteriormente, de forma secuencial.
  1. **lNAleat:** Leer los N archivos creados anteriormente, de forma aleatoria.
  1. **cNDirs:** Crear 100000 directorios.
  1. **bNDirs:** Borrar los 10000 directorios.
  1. **c1000Avac:** Crear 1000 archivos vacíos.<sup>1</sup>
  1. **e1000A600b:** Escribir 600 bytes en cada archivo (repetir 1000 veces).<sup>1</sup>
  1. **t1000Amitad:** Truncar cada archivo a la mitad de su longitud.<sup>1</sup>
  1. **a1000A600b:** Agregar 600 bytes en cada archivo (repetir 1000 veces).<sup>1</sup>

> <sup>1</sup> Esta operación se realizará aparte exclusivamente para medir la fragmentación.

> _**Observación:**_ Los códigos asociados a cada uno de los elementos de más arriba, fueron asignados para su fácil asociación en los cuadros y explicaciones posteriores.

# Relaciones de las operaciones con las Métricas y Parámetros #

La siguiente tabla resume todas nuestras operaciones, y su relación con los parámetros y métricas que se quieren medir.

También se aclara por cada Operación, el responsble de implementarla y probarla antes de incluir en el programa principal de evaluación.

| **Operaciones** | **Operaciones Básicas** | **Métricas** | **Parámetros** | **Grupo Param.**  | **Responsable** | **Mix de Impl.**  |
|:----------------|:-------------------------|:--------------|:----------------|:------------------|:----------------|:------------------|
| c1000A      | CA, EA  | BEs, LE  | pTB, pNJ, pSI | G1 | fmancia    | mLect |
| l1000A      | LA (S)  | BLs, LL  | pTB, pAT      | G2 | fmancia    | mLect |
| rl1000A     | LA (S)  | BLs, LL  | pTB, pAT      | G2 | fmancia    | mLect |
| c2000A2m    | CA, EA  | BEs, LE  | pTB, pNJ, pSI | G1 | mrodas     | mEscr |
| re2000A2m   | EA (A)  | BEs, LE  | pTB, pNJ, pSI | G1 | mrodas     | mEscr |
| lNSeq       | LA (S)  | BLs, LL  | pTB, pAT      | G2 | cparra     | mLect2|
| lNAleat     | LA (A)  | BLs, LL  | pTB, pAT      | G2 | cparra     | mLect2|
| cNDirs      | CD      | tCD      | pTB, pNJ, pSI | G1 | cparra     | mDirs |
| bNDirs      | BD      | tBD      | pTB, pNJ, pSI | G2 | cparra     | mDirs |
| c1000Avac   | --      | PF       | pTB           | G3 | ghuttemann | mFrag |
| e1000A600b  | --      | PF       | pTB           | G3 | ghuttemann | mFrag |
| t1000Amitad | --      | PF       | pTB           | G3 | ghuttemann | mFrag |
| a1000A600b  | --      | PF       | pTB           | G3 | ghuttemann | mFrag |

  * “A” significa aleatorio.
  * “S” significa secuencial.
  * "Gn" son los grupos según los parámetros que influyen. Cada G incluye el mismo grupo de parámetros, y al mismo tiempo, incluye solo operaciones de lectura, escritura o la parte para fragmentación.
  * En las últimas operaciones no se consideran operaciones básicas ya que lo que se quiere inducir es solamente el aumento de la fragmentación y no otras métricas.
  * Los "Mixs" de implementación, permiten agrupar las operaciones que vamos a implementar según lo que en general se está probando en ese Mix. Así tenemos:
    1. _**mLect:**_ 1<sup>ra</sup> Mezcla de operaciones de lectura.
    1. _**mEscr:**_ Mezcla de operaciones de escritura.
    1. _**mLect2:**_ 2<sup>da</sup> Mezcla de operaciones de lectura.
    1. _**mDirs:**_ Mezcla de operaciones sobre Directorios.
    1. _**mFrag:**_ Mezcla de operaciones para probar fragmentación.

# Plan de implementación #

  1. Completar la implementación de **_primitivas.c:_** Contiene la implementación adecuada para realizar las operaciones básicas
  1. Completar la implementación de **_operaciones.c:_** donde estarán todas las operaciones de carga.

> _**Obs:**_ Para no generar conflictos, tanto primitivas como operaciones se podría modularizar para que cada quien edite la operación en un .c distinto y todo se incluya en el consolidado mediante archivos .h