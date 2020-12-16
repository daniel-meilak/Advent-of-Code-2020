## Day 16

For day 16 the input is somewhat complex as it is made up of several different components. While I could take the trouble to split and work on each part individually within C++, I thought this was unecessary and ended up dividing the input beforehand into 3 components: the rule list, my ticket and the other tickets. The tickets can be easily parsed using my read_input function in utility.cpp, while the rules will require more delicacy. 

While I could go through the rules using string.find and substrings, today I decided to try using std::regex. 'day16_no_regex' does contain an implentation without regex' as I was stubborn. It is quite clean looking anyway.  

Also I got a little lazy today and after figuring out which columns applys to which rule, I ended up figuring out the answer to part 2 by hand as a small puzzle!