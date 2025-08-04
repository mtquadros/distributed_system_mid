# Distributed System Module
A liteweight distributed System Middleware designed to be crash fault tolerant.

## Notes: Features until the moment,
1. It is working just with threads simulating hosts;
2. It is detecting crashed threads;
3. It shows up threads alive in a table on the screen.

## Work in progress,
1. Improve the information on the screen (i.e add the column "is alive");
2. Correct the manner the timestamp is collected;
3. Decide about a leader on group even if the actual leader crashes.

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
