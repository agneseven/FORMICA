# ForMiCa: Foraging and Migration Cyber Architecture
## Installation
### 1. Prerequisites
* [igraph](http://igraph.org/c/)
* [BRITE](https://www.cs.bu.edu/brite/)
### 2. Compile
```
g++ -g main.cpp Grafo.cpp mobility.cpp Coordinates.cpp RandomWalk.cpp mobileNode.cpp manage.cpp event_list.cpp -I/usr/local/include/igraph -L/usr/local/lib -ligraph -std=c++11 -o test
```


### 3. Run 
```
./test <NODE_NUM> <PATH_TO_NODE_COORDINATES_TEXT_FILE> <PATH_TO_NODE_IDS_TEXT_FILE> <PATH_TO_NODE_BANDWIDTH_TEXT_FILE> <PATH_TO_NODE_DELAY_TEXT_FILE> <SIM_TIME> <MOBILE_NUM> <MODE_TS> <MODETD> <SERVICE_TIME> <GENERATION_TIME> <OFFLOADING_MODE> <SPEED_MOBILE_NODE> <SEED> <MIGRATION_MODE> <FAILURE_MODE> <PERC_FAILED_NODES> <THRESHOLD_MODE> <GENERATION_TRAFFIC_MODE>
```
where:

**\<NODE_NUM\>** : number of nodes in the topology

