#include <iostream>
#include"functions.h"
using namespace std;
//int operations_count;

int main ()
{

 bool t = true,f=false,out;
 bool input1[7],input2[7],output[7];
 
 // 0 is the least significant bit
 
 input1[0]=0;
 input1[1]=1;
 input1[2]=0;
 input1[3]=0;
 input1[4]=1;
 input1[5]=0;
 input1[6]=0;
 input1[7]=0;
 
 input2[0]=1;
 input2[1]=1;
 input2[2]=1;
 input2[3]=0;
 input2[4]=0;
 input2[5]=0;
 input2[6]=0;
 input2[7]=1;
 
 
 cout << "values should be f,t" <<'\n';
 
 cout << "and ";
 out = And(t,f);
 bool_print(out);
 out = And(t,t);
 bool_print(out);
 cout << "or ";
 out = Or(f,f);
 bool_print(out);
 out = Or(t,f);
 bool_print(out);
 cout << "not ";
 out = Not(t);
 bool_print(out);
 out = Not(f);
 bool_print(out);
 cout << "xor ";
 out = xOr(t,t);
 bool_print(out);
 out = xOr(t,f);
 bool_print(out);
 cout << "mux ";
 out = mux(t,f,t);
 bool_print(out);
 out = mux(f,f,t);
 bool_print(out);
 cout << "sum small ";
 out = sum(t,t);
 bool_print(out);
 out = sum(t,f);
 bool_print(out);
 cout << "sum big ";
 out = sum(t,t,f);
 bool_print(out);
 out = sum(t,f,f);
 bool_print(out);
 cout << "carry ";
 out = carry_out(t,f,f);
 bool_print(out);
 out = carry_out(t,t,f);
 bool_print(out);
 cout << "Equal ";
 out = Equal(t,f);
 bool_print(out);
 out = Equal(f,f);
 bool_print(out);
 
 cout << "part two" << '\n' << "input1:: ";
 get_value(input1,7);
 print_value(input1);
 print_value_in_decimal(input1);
 cout << "input2:: "; 
 print_value(input2);
 print_value_in_decimal(input2);
 cout << "mux ( input one will be in the first slot and 2 in the second for the the first example of each the following functions)";
 mux_8bit(output,f,input1,input2);
 print_value(output);
 mux_8bit(output,t,input1,input2);
 print_value(output);
 cout << "addu ";
 addu(output,input1,input2);
 print_value(output);
 cout << "Negate ";
 Negate(output,input1);
 print_value(output);
 Negate(output,input2);
 print_value(output);
 cout << "subu ";
 subu(output,input1,input2);
 print_value(output);
 
 cout << "Equal_8bit ";
 out=Equal_8bit( input1,  input2);
 bool_print(out);
 
 cout << "lessthan_8bit ";
 out=lessthan_8bit( input1,  input2);
 bool_print(out);
 
 cout << "greaterthan_8bit ";
 out=greaterthan_8bit( input1,  input2);
 bool_print(out);
 
 cout << "Equal_8bit_8out ";
 Equal_8bit_8out( output, input1,  input2);
 print_value(output);
 
 cout << "lessthan_8bit_8out ";
 lessthan_8bit_8out( output, input1,  input2);
 print_value(output);
 
 
 cout << "greaterthan_8bit_8out ";
 greaterthan_8bit_8out( output, input1,  input2);
 print_value(output);
 
 cout << "And_8bit ";
 And_8bit( output,  input1,  input2);
 print_value(output);
 
 cout << "Or_8bit ";
 Or_8bit( output,  input1,  input2);
 print_value(output);
 
 cout << "shift_left ";
 shift_left( output,  input1);
 print_value(output);
 shift_left( output,  input2);
 print_value(output);
 
 cout << "shift_right ";
 shift_right( output,  input1);
 print_value(output);
 shift_right( output,  input2);
 print_value(output);
}
