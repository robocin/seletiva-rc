# Simulation 2D C++

Para instalar o ambiente de simulação, seguir os passos em https://github.com/robocin/simulation-2d .

## Configurar ambiente e compitilar

```sh
$ mkdir build && cd build
$ cmake ..
$ make [-j<n_cpus>]
```

## Adicionar novas classes

1. Crie as classes no /src nome_classe.h e nome_classe.cpp 

2. Configure o CMakeList.txt para poder compilar as classes
```
Linha 29 do CMakeList.txt tem set([arquivos]). Inclua seus .cpp no fim.
```

3. Reconfigure o ambiente em /simulation-2d-cpp/

```sh
$ mkdir build && cd build
$ cmake ..
$ make [-j<n_cpus>]
```

## Rodar time

```sh
$ cd src
$ ./start.sh
```

## Formation Edition

[Manual](https://github.com/robocin/simulation-2d-cpp/blob/cso-newFormations-65/src/formations-robocin/FormationEdition.md)