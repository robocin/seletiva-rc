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
├── ferramentas
│   ├── rcssmonitor
│   ├── rcssserver
│   ├── agent2d
│   ├── fedit
│   ├── librcsc
│   └── soccerwindow2
	
├── src
│   ├── chain-action
│   ├── formation-dt
│   ├── formations-keeper
│   └── formations-taker
└── README.md
```


## Rodar os times de 2D

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
