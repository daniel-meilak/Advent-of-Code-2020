## Day 18

The problem for day 18 seemed perfect to reapply my knowledge of std::regex to. How wrong I was. 

It turns out regex in c++ is incomplete compared to what I am used to in sed for example. While I am able to use lookforwards, lookbehinds are not available meaning that I have to use string.substr after using a regex_search which seems somewhat pointless. Nonetheless, that was only the initial small hurdle. 

The main block of time spent answering this question was on figuring out what my final answer (to part 1) was wrong when all available examples from the AoC website were working. Turns out regex_match works through only the first match (and submatches) but requires effort to return the next matches, while regex_replace will replace all matches by default. A wonderful bit of inconsistency. To follow form this, it turned out to be a pain to find a match and then replace it later on after doing some arithmetic. This required creating a small function to escape the required special characters from a string.

With that all figured out, Part 1 still wouldn't work due to the usage of int rather than long or long long. Eventually this was figured out and the code fixed. 

For part 2 I came up with a simple solution to perform '+' operations first, which required a small change in the code to work. Unfortunately I could not achieve the correct answer as I made a mistake on a range for loop: "for (int num: sum)". While I had changed all digits to "1ULL" and tried to find all instances of int and change those to long long, the range for loop managed to escape me. Upon eventually finding this out I was able to get the correct answer.

I'm not sure if I will tackle future questions with std::regex instead of fully relying on string manipulation as today's problem definitely soured my relationship with this particular standard library. Nonetheless I know what to look out for now.  