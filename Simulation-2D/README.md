# Simulation 2D C++

# Locais importantes
```
├── binaries
│   ├── robocin-2019-10-26.tgz
│   ├── ITAndroids_SS2D_RC2019_R3_BIN.tar.gz
│   └── titans-2019-10-25.tgz
├── logs
│   ├── robocup
│   └── rcssLogExtractor
├── robocup-soccer-simulator
│   ├── rcsslogplayer
│   ├── rcssmonitor
│   └── rcssserver
├── src
│   ├── chain-action
│   ├── formation-dt
│   ├── formations-keeper
│   └── formations-taker
└── README.md
```

# Instalar o ambiente em /robocup-soccer-simulation
O ambiente da categoria de simulação 2D é composto de três módulos principais:
- rcssserver: o servidor principal onde os jogos acontecem.
- rcssmonitor: uma ferramenta para assistir o jogo em execução.
- rcsslogplayer: um gerador de registros (logs) dos jogos.

### 1. Instalação de libs para auxiliar na build do ambiente. 
```
sudo apt-get install libaudio-dev libpng-dev libxi-dev libglib2.0-dev libfontconfig-dev libxrender-dev libtool libboost-all-dev autoconf libqt4-dev libxt-dev
```
### 2. Instalar cada um dos componentes
#### 2.1 - rcssserver
```
cd rcssserver
sudo ./bootstrap
sudo ./configure
sudo make
sudo make install
cd ..
```

#### 2.2 - rcsslogplayer
```
cd rcsslogplayer
sudo ./bootstrap
sudo ./configure
sudo make
sudo make install
cd ..
```
#### 2.3 - rcssmonitor
```
cd rcssmonitor
sudo ./bootstrap
sudo ./configure
sudo make
sudo make install
```

### 3. Configurar ambiente e compilar

```sh
$ mkdir build && cd build
$ cmake ..
$ make [-j<n_cpus>]
```

## Adicionar novas classes

1. Crie as classes no /src nome_classe.h e nome_classe.cpp 

2. Para que suas classes sejam entendidas e compiladas pelo código, é necessário fazer configurações adicionais no CMakeList.txt.
```cpp
 //Linha 31 do CMakeList.txt:
 set([arquivos]) //Inclua seus .cpp no final.
```

3. Reconfigure o ambiente em /simulation-2d-cpp/

```sh
$ mkdir build && cd build
$ cmake ..
$ make [-j<n_cpus>] // <n_cpus> =  número de threads que serão alocadas para rodar o ambiente.
```

## Rodar time

1. Primeiro inicie o server:

Ao final do jogo os logs estarão no diretório onde o servidor foi iniciado

```sh
$ rcsssserver
```

2. Conectar o monitor
```sh
$ rcssmonitor
```

3. Iniciar time 1
```sh
$ cd src
$ ./start.sh -t <NOME_TIME1>
```

3. Iniciar time 2
```sh
$ cd src
$ ./start.sh -t <NOME_TIME2>
```
## Extrair Logs
Seguir os passos em https://github.com/robocin/seletiva-rc/tree/master/Simulation-2D/logs/rcssLogExtractor .
