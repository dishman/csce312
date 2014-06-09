#include <iostream>
#include <cmath>
using namespace std;
int operations_count;


bool And(bool a, bool b)
{
	operations_count++;
	if(a==b&&a==true)
	{
		return true;
	}
	else
		return false;
}

//---------------------------

bool Or(bool a, bool b)
{
	operations_count++;
	if(a==true || b==true)
	{
		return true;
	}
	else
		return false;	
}

//---------------------------

bool Not(bool a)
{
	operations_count++;
	if (a==true)
	{
		return false;
	}
	else
		return true;
}

//---------------------------

void print_operations_count()
{
	cout << operations_count << " operations\n";
}

//---------------------------

void reset_operations_count()
{
	operations_count=0;	
}

//---------------------------

void bool_print(bool a)
{
	cout << a <<'\n';
}

//---------------------------

bool get_value(bool byte[],int offset)
{
	return byte[offset];
}

//---------------------------

void write_value(bool byte[], int offset, bool value)
{
	byte[offset] = value;
}

//---------------------------

void print_value(bool byte[])
{
	for(int i=7;i>=0;i--)
	{
		cout << byte[i] << " ";
	}
	cout << '\n';
}

//---------------------------

void print_value_in_decimal(bool byte[])
{
	int dec=0;
	for (int i = 0; i <= 7; ++i)
	{
		if(byte[i])
		{
			dec+=pow(2,i);
		}
	}
	cout << dec << "\n";
}

//---------------------------

bool xOr(bool a, bool b)
{
	return And(Or(a,b),Not(And(a,b)));
}

//---------------------------

bool mux(bool s,bool a,bool b)
{
	return Or(And(s,a),And(Not(s),b));
}

//---------------------------

bool sum(bool a,bool b)
{
	return xOr(a,b);
}

//---------------------------

bool sum(bool a, bool b, bool c)
{
	return xOr(xOr(a,b),c);
}

//---------------------------

bool carry_out(bool a, bool b,bool c)
{
	return Or(And(xOr(a,b),c),And(a,b));
}

//---------------------------

bool Equal(bool a, bool b)
{
	return Not(xOr(a,b));
}

//---------------------------
//   part  2
//---------------------------

bool* mux_8bit(bool output[], bool select, bool input1[], bool input2[])
{
	output[0]=mux(select,input1[0],input2[0]);
	output[1]=mux(select,input1[1],input2[1]);
	output[2]=mux(select,input1[2],input2[2]);
	output[3]=mux(select,input1[3],input2[3]);
	output[4]=mux(select,input1[4],input2[4]);
	output[5]=mux(select,input1[5],input2[5]);
	output[6]=mux(select,input1[6],input2[6]);
	output[7]=mux(select,input1[7],input2[7]);
	return output;
}

//---------------------------

bool* addu(bool output[], bool input1[], bool input2[])
{
	output[0]=sum(input1[0],input2[0],0);
	output[1]=sum(input1[1],input2[1],carry_out(input1[0],input2[0],0));
	output[2]=sum(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0)));
	output[3]=sum(input1[3],input2[3],carry_out(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0))));
	output[4]=sum(input1[4],input2[4],carry_out(input1[3],input2[3],carry_out(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0)))));
	output[5]=sum(input1[5],input2[5],carry_out(input1[4],input2[4],carry_out(input1[3],input2[3],carry_out(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0))))));
	output[6]=sum(input1[6],input2[6],carry_out(input1[5],input2[5],carry_out(input1[4],input2[4],carry_out(input1[3],input2[3],carry_out(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0)))))));
	output[7]=sum(input1[7],input2[7],carry_out(input1[6],input2[6],carry_out(input1[5],input2[5],carry_out(input1[4],input2[4],carry_out(input1[3],input2[3],carry_out(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0))))))));
	return output;
}

//---------------------------

bool* Negate(bool output[], bool input[])
{
	bool one[7],thing[7];
	one[0]=1;
	one[1]=0;
	one[2]=0;
	one[3]=0;
	one[4]=0;
	one[5]=0;
	one[6]=0;
	one[7]=0;
	thing[0]=Not(input[0]);
	thing[1]=Not(input[1]);
	thing[2]=Not(input[2]);
	thing[3]=Not(input[3]);
	thing[4]=Not(input[4]);
	thing[5]=Not(input[5]);
	thing[6]=Not(input[6]);
	thing[7]=Not(input[7]);
	addu(output,thing,one);
	return output;
}

//---------------------------

bool* subu(bool output[], bool input1[], bool input2[])
{
	bool neg[7];
	Negate(neg,input2);
	addu(output,input1,neg);
	return output;
}

//---------------------------

bool Equal_8bit(bool input1[], bool input2[])
{
	return mux(Equal(input1[0],input2[0]),mux(Equal(input1[1],input2[1]),mux(Equal(input1[2],input2[2]),mux(Equal(input1[3],input2[3]),mux(Equal(input1[4],input2[4]),mux(Equal(input1[5],input2[5]),mux(Equal(input1[6],input2[6]),mux(Equal(input1[7],input2[7]),true,false),false),false),false),false),false),false),false);
}

//---------------------------

bool lessthan_8bit(bool input1[], bool input2[])
{
	bool output1[7];
	subu(output1,input1,input2);
	return mux(Equal(input1[7],input2[7]),output1[7],input1[7]);
}

//---------------------------

bool greaterthan_8bit(bool input1[], bool input2[])
{
	bool output1[7];
	subu(output1,input2,input1);
	return mux(Equal(input1[7],input2[7]),output1[7],input2[7]);
}

//---------------------------

bool* Equal_8bit_8out(bool output[],bool input1[], bool input2[])
{
	bool out1[7],out2[7];
	out1[0]=1;
	out1[1]=1;
	out1[2]=1;
	out1[3]=1;
	out1[4]=1;
	out1[5]=1;
	out1[6]=1;
	out1[7]=1;
	out2[0]=0;
	out2[1]=0;
	out2[2]=0;
	out2[3]=0;
	out2[4]=0;
	out2[5]=0;
	out2[6]=0;
	out2[7]=0;
	return mux_8bit(output,Equal_8bit(input1,input2),out1,out2);
}

//---------------------------

bool* lessthan_8bit_8out(bool output[],bool input1[], bool input2[])
{
	bool out1[7],out2[7];
	out1[0]=1;
	out1[1]=1;
	out1[2]=1;
	out1[3]=1;
	out1[4]=1;
	out1[5]=1;
	out1[6]=1;
	out1[7]=1;
	out2[0]=0;
	out2[1]=0;
	out2[2]=0;
	out2[3]=0;
	out2[4]=0;
	out2[5]=0;
	out2[6]=0;
	out2[7]=0;
	return mux_8bit(output,lessthan_8bit(input1,input2),out1,out2);
}

//---------------------------

bool* greaterthan_8bit_8out(bool output[],bool input1[], bool input2[])
{
	bool out1[7],out2[7];
	out1[0]=1;
	out1[1]=1;
	out1[2]=1;
	out1[3]=1;
	out1[4]=1;
	out1[5]=1;
	out1[6]=1;
	out1[7]=1;
	out2[0]=0;
	out2[1]=0;
	out2[2]=0;
	out2[3]=0;
	out2[4]=0;
	out2[5]=0;
	out2[6]=0;
	out2[7]=0;
	return mux_8bit(output,greaterthan_8bit(input1,input2),out1,out2);
}

//---------------------------

bool* And_8bit(bool output[], bool input1[], bool input2[])
{
	output[0]=And(input1[0],input2[0]);
	output[1]=And(input1[1],input2[1]);
	output[2]=And(input1[2],input2[2]);
	output[3]=And(input1[3],input2[3]);
	output[4]=And(input1[4],input2[4]);
	output[5]=And(input1[5],input2[5]);
	output[6]=And(input1[6],input2[6]);
	output[7]=And(input1[7],input2[7]);
	return output;
}

//---------------------------

bool* Or_8bit(bool output[], bool input1[], bool input2[])
{
	output[0]=Or(input1[0],input2[0]);
	output[1]=Or(input1[1],input2[1]);
	output[2]=Or(input1[2],input2[2]);
	output[3]=Or(input1[3],input2[3]);
	output[4]=Or(input1[4],input2[4]);
	output[5]=Or(input1[5],input2[5]);
	output[6]=Or(input1[6],input2[6]);
	output[7]=Or(input1[7],input2[7]);
	return output;
}

//---------------------------

bool* shift_left(bool output[], bool input[])
{
	output[0] = false;
	output[1] = input[0];
	output[2] = input[1]; 
	output[3] = input[2]; 
	output[4] = input[3]; 
	output[5] = input[4]; 
	output[6] = input[5]; 
	output[7] = input[6];  
	return output;
}

//---------------------------

bool* shift_right(bool output[], bool input[])
{
	output[7] = input[7];
	output[6] = input[7];
	output[5] = input[6]; 
	output[4] = input[5]; 
	output[3] = input[4]; 
	output[2] = input[3]; 
	output[1] = input[2]; 
	output[0] = input[1];  
	return output;
}

//---------------------------



//---------------------------
