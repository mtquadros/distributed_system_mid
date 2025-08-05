# Distributed System Module
A liteweight distributed System plataform

## Notes: Features until the moment,
1. It is working with threads simulating hosts;
2. All neighbors hosts connected to the same local network which run this module joing to the group by multicasting communication;
3. It is detecting crash fault of threads;
4. It shows up threads joined to the group in a table on the screen;
5. Updates the the timestamp of the last heart beat of the hosts.

## Work in progress,
1. Improve the information on the screen (i.e add the column "is alive");
2. Correct the manner the timestamp is collected;
3. Decide about a leader on group even if the actual leader crashes;
4. Migrate the implementation of threads to processes in real neighbor hosts on a local network.

## How to run it?
1. Compile the program:
   ...
   1. *cd {$project_directory}/distributed_consensus/cmake-build-debug*
   ...
   ...
   2. *cmake .. && make*
   ...
2. Open two or more terminals (terminator application helps a lot!)
3. type on each terminal: *./dsmodule* 
