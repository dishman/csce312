csce312
=======

Programing assinment


to run week one:
compile on the linux server useing g++-4.7 -std=c+11 312-csce-week1.cpp
then run with./a.out to print to the screen

the main testing file is the one that is run. the functions that are used are in the functions header file

week two:

compile on the linux server useing g++-4.7 -std=c+11 week2.cpp
then run with./a.out to print to the screen

the main testing file is the one that is run. the functions that are used are in the functions header file

--for using the alu
all options are already slected in the alu, so for testing all you should have to do is change the values for input1 and input2.



week three:

the instructions for the firtual matiane are curently called from a in.txt file

the format for this file is the number of 8 bit strings followed by a new line, then 8 bit section on each line where each bit is seperated by a space.(I usede notpad++ for this file, though it shouldn't make a differance i know differant things save endline chars differantly)  the format of the instructions is the same as in the problem 8 bit instruction type, 8 bit output reg location, input reg location, input reg location.

the only way i currently have to set my regs is useing the li instruction.

there were several problems with c++ compiling and running all functions in the alu which kept me from implementing some of the functions exactly as wrriten in the problem because they would trigger inproperly since i don't have if statments. this functionality has been comminted out but still works. if there is a way around this problem i would love to know it as i spent almost 5 hours today tring to fix it.


Final:

like before this program runs using g++-4.7 -std=c+11 file_name.cpp on either the linux or comput servers

to get the proper data path program flow i was required to use a lot of ifs. i could not figure out a way to avoid this.
for some reason my divid function is still not working and is giving a constant value... i don't know wjy this is but the rest of the program is working just fine.

to run the programs just but the program one of the two program text files into the intilize function in the main. i have the first one in there for default.




