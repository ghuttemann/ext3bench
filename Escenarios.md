# Introducción #

Se presenta en esta página los 4 escenarios de pruebas distintos que se evaluarán con este benchmark.

# Parámetros a variar #

  1. **Tamaño del Bloque (pTB):**

> Tiene influencia fundamentalmente en las lecturas. Cómo no se puede variar online, se probará con el valor máximo (4Kb) y con el valor mínimo (1Kb).


  1. **Nivel de journaling (pNJ):**

> Influye sobre todo en las escrituras. Se trata del nivel con el que las transacciones del filesystem serán protegidas para la recuperación, a través del archivo de journal.

> Existen tres posibles modos:
  * _Data Journal:_ Todos los datos y metadatos son confirmados al journal, antes de ser escritos en el disco.
  * _Data Ordered:_ Es el modo por defecto, solo los metadatos se guardan en el journal, pero se garantiza que todos los datos son forzados directamente al sistema de archivos, antes que los metadatos sean confirmados en el journal.
  * _Data Writeback:_ Igual que el caso anterior, solo que el orden no se preserva. Los datos pueden escribirse en el disco, antes que los metadatos sean confirmados en el journal, lo que haría que datos antiguos, puedan aparecer en los archivos después de un fallo o recuperación del journal.

> Se probarán dos modos:
  * El modo por defecto (ordered)
  * El modo optimizado (writeback)

```
   Para cambiar este parámetro, se necesita remontar el sistema de archivos: 
     # mount -t ext3 -o data=<modo> /dev/sda3 /vol01 

   También se puede cambiar el tipo de montaje por defecto:
     # tune2fs -O has_journal -o journal_data /dev/hdXY
```


  1. **Sync Interval (pSI):**

> Intervalo de tiempo entre cada sincronización del journal con los archivos reales. Se puede cambiar al montar el sistema de archivos utilizando -o commit=Nsec.

> A mayores valores de tiempo, se mejora el rendimiento porque se reduce la sobrecarga de operaciones del sistema de archivos, sin embargo, se pierde en confiabilidad ante fallos del sistema. Influye en operaciones de escritura.

```
   Al montar: 
      # mount -t ext3 -o commit=Nsec /dev/sda2 /vol02
```

  1. **Eliminar la actualización del access time (pAT):**

> Influye en lecturas. Consiste en la actualización de este atributo ante cada acceso al archivo.

```
    Se puede manipular editando /etc/fstab con lo siguiente: 
       /dev/hda1 / ext3 defaults, errors=remount-ro, noatime, auto, rw, dev, exec, suid, nouser, data=writeback 0 1

    O al montar: 
      mount -t ext3 -o noatime /dev/sda2 /vol02
```


---


# Los Escenarios #

Básicamente, tenemos 2 escenarios de pruebas, para 2 sistemas de archivos con tamaños de bloque distinto. Esto significa en total, 4 escenarios.

| _**Escenario**_|_**Tamaño de Bloque**_|_**Journal**_|_**Commit**_|_**Access time**_|
|:---------------|:----------------------|:------------|:-----------|:----------------|
| _Est4k_      | 4096 bytes         | ordered   | 5 segs   | Si            |
| _Opt4k_      | 4096 bytes         | writeback | 10 segs  | No            |
| _Est1k_      | 1024 bytes         | ordered   | 5 segs   | Si            |
| _Opt1k_      | 1024 bytes         | writeback | 10 segs  | No            |

## Particiones ##

> Se construirán para las pruebas dos particiones diferentes, de la siguiente manera:


> _**Particion 1:**_
```
     mke2fs -b 1024 -L vol01 -j

  Cómo sería la Partición: 
     [root@localhost ~]# mke2fs -b 1024 -j -L vol02 -n /dev/sda3
     mke2fs 1.40.8 (13-Mar-2008)
     Warning: 256-byte inodes not usable on older systems
     Etiqueta del sistema de ficheros=vol01
     Tipo de SO: Linux
     Tamaño del bloque=1024 (bitácora=0)
     Tamaño del fragmento=1024 (bitácora=0)
     655360 nodos i, 10482412 bloques
     524120 bloques (5.00%) reservados para el superusuario
     Primer bloque de datos=1
     Máximo de bloques del sistema de ficheros=77594624
     1280 bloque de grupos
     8192 bloques por grupo, 8192 fragmentos por grupo
     512 nodos i por grupo
     Respaldo del superbloque guardado en los bloques: 
             8193, 24577, 40961, 57345, 73729, 204801, 221185, 401409, 663553, 
             1024001, 1990657, 2809857, 5120001, 5971969
```

> _**Particion 2:**_
```
     mke2fs -b 4096 -L vol02 -j

  Cómo sería la partición: 
     [root@localhost ~]# mke2fs -b 4096 -L vol02 -j -n /dev/sda2
     mke2fs 1.40.8 (13-Mar-2008)
     Warning: 256-byte inodes not usable on older systems
     Etiqueta del sistema de ficheros=vol02
     Tipo de SO: Linux
     Tamaño del bloque=4096 (bitácora=2)
     Tamaño del fragmento=4096 (bitácora=2)
     655360 nodos i, 2620603 bloques
     131030 bloques (5.00%) reservados para el superusuario
     Primer bloque de datos=0
     Máximo de bloques del sistema de ficheros=2684354560
     80 bloque de grupos
     32768 bloques por grupo, 32768 fragmentos por grupo
     8192 nodos i por grupo
     Respaldo del superbloque guardado en los bloques: 
	     32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632


```

## Opciones de montado ##

> _**Configuración Estándar:**_
```
   mount -t ext3 /dev/sda2 /vol02

   Por defecto, se usan las opciones journal=ordered, commit=5. 
```

> _**Configuración Optimizada:**_
```
   mount -t ext3 -o data=writeback,commit=10,noatime /dev/sda2 /vol02
```

# Otras optimizaciones #

En los siguientes enlaces, existen análisis más completos sobre diversas optimizaciones que se pueden realizar sobre el filesystem ext3.

  * [Ext3 Filesystem Tips](http://wiki.archlinux.org/index.php/Ext3_Filesystem_Tips)
  * [Otros Tips para el tunning de Ext3](http://www.redhat.com/archives/ext3-users/2007-May/msg00009.html)

# Hardware de Prueba #

  * Memoria: 1 GB
  * Procesador: Intel (R) Pentium(R) 4 CPU 2.80GHz
  * Disco Duro: MAXTOR IDE 80GB.