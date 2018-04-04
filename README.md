# FORMICA: Foraging and Migration Cyber Architecture
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
./test <NODE_NUM> <PATH_TO_NODE_COORDINATES_TEXT_FILE> <PATH_TO_NODE_IDS_TEXT_FILE> <PATH_TO_NODE_BANDWIDTH_TEXT_FILE> <PATH_TO_NODE_DELAY_TEXT_FILE> <SIM_TIME> <MOBILE_NUM> <MODE_TS> <MODE_TD> <SERVICE_TIME> <GENERATION_TIME> <OFFLOADING_MODE> <SPEED_MOBILE_NODE> <SEED> <MIGRATION_MODE> <FAILURE_MODE> <PERC_FAILED_NODES> <THRESHOLD_MODE> <GENERATION_TRAFFIC_MODE>
```
where:

**\<NODE_NUM\>** : number of nodes in the topology

**\<PATH_TO_NODE_COORDINATES_TEXT_FILE\>** : path to the text file generated with BRITE containing the geographical coordinates of the topology nodes

**\<PATH_TO_NODE_IDS_TEXT_FILE\>** : path to the text file generated with BRITE containing how nodes are connected

**\<PATH_TO_NODE_BANDWIDTH_TEXT_FILE\>** : path to the text file generated with BRITE containing the bandwitdh of each link

**\<PATH_TO_NODE_DELAY_TEXT_FILE\>** : path to the text file generated with BRITE containing the delay of eack link

**\<SIM_TIME\>** : maximum duration of the simulation (seconds)

**\<MOBILE_NUM\>** : number of mobile device that generate tasks

**\<MODE_TS: _uniform_ | _variable_ | _constant_\>** :  the average service time value is assigned to each node according to three distributions: uniform, exponential, constant (all nodes have the same average service time) 

**\<MODE_TD: _uniform_ | _variable_ | _constant_\>** : the average generation time value is assigned to each node according to three distributions: uniform, exponential, constant (all nodes have the same average generation time) 

**\<SERVICE_TIME\>** : if <MODE_TS> == uniform -> <SERVICE_TIME> is the upper boundary of the interval \[0, <SERVICE_TIME>); if <MODE_TS> == variable -> <SERVICE_TIME> is the lambda distribution parameter (rate of events); if <MODE_TS> == constant -> <SERVICE_TIME> is the average service time value assigned to all nodes

**\<GENERATION_TIME\>** : if <MODE_TS> == uniform -> <GENERATION_TIME> is the upper boundary of the interval \[0, <GENERATION_TIME>); if <MODE_TS> == variable -> <GENERATION_TIME> is the lambda distribution parameter (rate of events); if <MODE_TS> == constant -> <GENERATION_TIME> is the average service time value assigned to all nodes

**\<OFFLOADING_MODE: _uniform_ | _variable_ | _kserver_\>** : uniform -> the vertex where tasks migrate is uniformly chosen among the active node; variable -> the vertex where tasks migrate is chosen among the more powerful active nodes (lower service time); kserver -> the vertex where tasks migrate is chosen according  to harmonic policy

**\<SPEED_MOBILE_NODE\>** : mobile node speed across the topology

**\<SEED\>** : random number used for user placement (km/h)

**\<MIGRATION_MODE: _0_ | _1_\>** : 0 -> migration cost off: when a node overcomes the threshold, its tasks ALWAYS migrate; 1 -> migration cost on: when a node overcomes the threshold, its tasks migrate only if the migration cost of the new node is better than the migration cost of the current node

**\<FAILURE_MODE: _0_ | _1_\>** : 0 -> failure off: nodes never fail; 1 -> failure on: some random nodes can fail

**\<PERC_FAILED_NODES\>** : percentage of nodes that will fail. This variable is considered only if <FAILURE_MODE> == 1

**\<THRESHOLD_MODE: _0_ | _1_\>** : 0 -> tasks never migrate; 1 -> tasks migrate when the threshold is overcome

**\<GENERATION_TRAFFIC_MODE: _uniform_ | _exponential_ | _HT_\>** : uniform -> mobile nodes generate traffic according to a uniform distribution; exponential -> mobile nodes generate traffic according to an exponential distribution; HT -> mobile nodes generate traffic according to an exponential distribution (gamma)

> *Example*
> 
> ./test 10 ./coordinates_10_1.txt ./edges_10_1.txt ./bandwidth_10_1.txt ./delay_10_1.txt 1000 5 uniform uniform 3 3 uniform 3 100 0 1 50 0 exponential

