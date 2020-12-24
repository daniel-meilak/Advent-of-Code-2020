## Day 24

Similarly to the last game of life we did during AoC 2020, this really took me back to modelling graphene in computation physics at uni, since that has a hexagonal structure and needs some thought put into how you move from one position to another since a square grid can't be used as easily.

So to solve the problem I used a 1D grid, of length=(width*heigh), where width and height are the dimensions of the 2D hexagonal grid. With this, I can translate all movements into something like "move NE -> grid`[current_pos-width-1]`", depending on the current row as in a hexagonal grid, a diagonal movement length depends on if the row is even or odd. 

Part 2 was very similar, using the same rules to check whether the neighbours are white or black, however as the system grows in size, I needed to make sure the grid was large enough to accommodate the growth. In the end this required an increase in grid size from 99`*99 to 151`*151, however this is easy to check as once the grid is large enough the answer to part 2 stops changing. 