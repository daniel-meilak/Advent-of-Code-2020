## Day 22

Day 22s problem (part 1) seems like an ideal place to use a list. I only ever need to access and remove the top element of each list and then insert into the bottom, which lists seem to be able to do efficiently, if I understand correctly. 

Wow that is some amount of recursion. The question does a pretty good job of explaining how I should write the code bit by bit so I didn't have to do much other than read the rules. I made a small mistake of using a global history when needed to be game specific so after fixing that the program just worked.

The first thing of note is that the program too around 15s to finish! However using any amount of optimization (other than no optimization) this speeds up to just under 4s. I'm not completely sure why but I assume the compiler is unrolling the recursive functions?

