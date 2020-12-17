## Day 17

Day 17 was a fun one. Reminding me a lot of some problems I had to answer in physics programming practicles in university, minus the requirement to parallelise the simulation which admittedly was the most annoying part of the whole process.

I vaguely remember that there are some quite beautiful methods of simulating these types of systems that vastly increase computation time. I think they worked by simulating the system at a lower resulution and then increasing up to the required max. Not sure if that works for this problem due to the propagation mechanics being quantized rather than continuous such as in heat dissipation. 

Hence I answered the question by looping over a simulated system over and over, a for loop for each dimension. Due to neighbour access requirements, I made the system one step larger (a border) and initialized these cells as inactive so that they would not affect anything but allow me to generalise (no edge requirements). To save on computation time, as the propagation can only occur one cell further at a time, I reduced the initial simulation to the core + 1 outer shell, and added a shell as the symulation cycled. 

Part 1 was not particularly difficult to code up, aside from the high chance of making a mistake when writing up so maby nested loops with similar indexing etc. In addition after solving part one, I decided to generalise the code to accept any initial input size. This way I could test the AoC examples without changing anything in the code.

Part 2 was a trivial change in the code, adding an extra index to all variables and adjusing a few functions. The main difficulty was making sure I know how to write out the initialization line for a 4D vector!