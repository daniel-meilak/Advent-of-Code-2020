## Day 20

How can something so simple sounding turn out to be so devious? I've implemented function for rotating and flipping matrices in both directions. This was probably a terrible idea as I'm sure there are plenty of beautiful library functions to do this for me. I'm relatively happy with the method I devised for creating the full picture from a random starting piece; by creating a row of the starting piece and then working on the columns off of the finished line.

I thought part two would not be too much trouble after my implementation of part one as piece should have been rotated to the correct position form the beginning however there were several mistakes in the algorithm which reoriented the pieces and I could not create the full picture correctly. Eventually this was solved by rewriting a significant amount of the code. 

To find the monsters I filled vectors mid, top and bot with the positions of the monster '#'s. By checking all picture lines for these positions it was a relatively trivial exercise to find and replace the '#' with 'O'

