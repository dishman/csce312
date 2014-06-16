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

bool* adds(bool output[], bool input1[], bool input2[])
{
	//try   // i am asuuming i can use this type of instruction(along with an if) since there are no ways(at least that i know) to make jump or branch functions without gotos(which i don't know how to use properly and safely)
	//{
		//cout <<input1[2] << input1[1] << input1[0]<<'\n';
		if(Equal(carry_out(input1[6],input2[6],carry_out(input1[5],input2[5],carry_out(input1[4],input2[4],carry_out(input1[3],input2[3],carry_out(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0))))))),carry_out(input1[7],input2[7],carry_out(input1[6],input2[6],carry_out(input1[5],input2[5],carry_out(input1[4],input2[4],carry_out(input1[3],input2[3],carry_out(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0))))))))))
		{
			addu(output,input1,input2);
			//cout << input1[0]<<'\n';
			return output;
		}
		else
		{
			throw 3;
		}
	//}
	//catch(int e)
	//{
		cout << "overflow";
	//}
}

//---------------------------

bool* subs(bool output[], bool input1[], bool input2[])
{
	//try   // i am asuuming i can use this type of instruction(along with an if) since there are no ways(at least that i know) to make jump or branch functions without gotos(which i don't know how to use properly and safely)
	//{
		//cout << input1[0]<<'\n';
		bool neg[7];
		Negate(neg,input2);
		input2=neg;
		if(Equal(carry_out(input1[6],input2[6],carry_out(input1[5],input2[5],carry_out(input1[4],input2[4],carry_out(input1[3],input2[3],carry_out(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0))))))),carry_out(input1[7],input2[7],carry_out(input1[6],input2[6],carry_out(input1[5],input2[5],carry_out(input1[4],input2[4],carry_out(input1[3],input2[3],carry_out(input1[2],input2[2],carry_out(input1[1],input2[1],carry_out(input1[0],input2[0],0))))))))))
		{
			addu(output,input1,input2);
			//cout << input1[0]<<'\n';
			return output;
		}
		else
		{
			throw 4;
		}
	//}
	//catch(int e)
	//{
		cout << "overflow";
	//}
}

//---------------------------

bool* multu(bool output[],bool input1[],bool input2[]) // the problem does not tell for output size, so i am assuming it is 8 bits just like the rest of the functions. If this is not the case(for this and other similer functions) please further clearify the problems so that the proper results may be acheived.
{
	bool waist[7],waist2[7],waist3[7],waist4[7],waist5[7],waist6[7],waist7[7],waist8[7],waist9[7];
	bool waist10[7],waist11[7],waist12[7],waist13[7],waist14[7],waist15[7],waist16[7],waist17[7],waist18[7],waist19[7],waist20[7],waist21[7],waist22[7];
	output[0]=0;
	output[1]=0;
	output[2]=0;
	output[3]=0;
	output[4]=0;
	output[5]=0;
	output[6]=0;
	output[7]=0;
	output=mux_8bit(waist,input1[0],addu(waist2,output,input2),output);
	//print_value(output);
	input2=shift_left(waist3,input2);
	//print_value(input2);
	
	output=mux_8bit(waist4,input1[1],addu(waist5,output,input2),output); // the error is here......but....
	//print_value(output);
	input2=shift_left(waist6,input2);
	//print_value(input2);
	
	output=mux_8bit(waist7,input1[2],addu(waist8,output,input2),output);
	//print_value(output);
	input2=shift_left(waist9,input2);
	
	output=mux_8bit(waist10,input1[3],addu(waist11,output,input2),output);
	//print_value(output);
	input2=shift_left(waist,input2);
	
	output=mux_8bit(waist12,input1[4],addu(waist13,output,input2),output);
	//print_value(output);
	input2=shift_left(waist14,input2);
	
	output=mux_8bit(waist15,input1[5],addu(waist16,output,input2),output);
	//print_value(output);
	input2=shift_left(waist17,input2);
	
	output=mux_8bit(waist18,input1[6],addu(waist19,output,input2),output);
	//print_value(output);
	input2=shift_left(waist20,input2);
	
	output=mux_8bit(waist21,input1[7],addu(waist22,output,input2),output);
	print_value(output);
	
	return output;
}
//---------------------------

bool* multu(bool output[],bool input1[],bool input2[]) // the problem does not tell for output size, so i am assuming it is 8 bits just like the rest of the functions. If this is not the case(for this and other similer functions) please further clearify the problems so that the proper results may be acheived.
{
	bool waist[7],waist2[7],waist3[7],waist4[7],waist5[7],waist6[7],waist7[7],waist8[7],waist9[7];
	bool waist10[7],waist11[7],waist12[7],waist13[7],waist14[7],waist15[7],waist16[7],waist17[7],waist18[7],waist19[7],waist20[7],waist21[7],waist22[7];
	output[0]=0;
	output[1]=0;
	output[2]=0;
	output[3]=0;
	output[4]=0;
	output[5]=0;
	output[6]=0;
	output[7]=0;
	output=mux_8bit(waist,input1[0],add(waist2,output,input2),output);
	//print_value(output);
	input2=shift_left(waist3,input2);
	//print_value(input2);
	
	output=mux_8bit(waist4,input1[1],add(waist5,output,input2),output); // the error is here......but....
	//print_value(output);
	input2=shift_left(waist6,input2);
	//print_value(input2);
	
	output=mux_8bit(waist7,input1[2],add(waist8,output,input2),output);
	//print_value(output);
	input2=shift_left(waist9,input2);
	
	output=mux_8bit(waist10,input1[3],add(waist11,output,input2),output);
	//print_value(output);
	input2=shift_left(waist,input2);
	
	output=mux_8bit(waist12,input1[4],add(waist13,output,input2),output);
	//print_value(output);
	input2=shift_left(waist14,input2);
	
	output=mux_8bit(waist15,input1[5],add(waist16,output,input2),output);
	//print_value(output);
	input2=shift_left(waist17,input2);
	
	output=mux_8bit(waist18,input1[6],add(waist19,output,input2),output);
	//print_value(output);
	input2=shift_left(waist20,input2);
	
	output=mux_8bit(waist21,input1[7],add(waist22,output,input2),output);
	print_value(output);
	
	return output;
}
//---------------------------

bool* divu(bool output[],bool input1[],bool input2[]) // takes four bit numbers
{
	bool rem[7];
	bool one[7];
	one[0]=1;
	one[1]=0;
	one[2]=0;
	one[3]=0;
	one[4]=0;
	one[5]=0;
	one[6]=0;
	one[7]=0;
	output[0]=0;
	output[1]=0;
	output[2]=0;
	output[3]=0;
	output[4]=0;
	output[5]=0;
	output[6]=0;
	output[7]=0;;
	shift_right(input2,input2);
	shift_right(input2,input2);
	shift_right(input2,input2);
	shift_right(input2,input2);
	subu(rem,input1,input2);
	shift_left(output,output);
	mux_8bit(output,rem[7],addu(rem,input1,input2),addu(output,output,one));

	subu(rem,input1,input2);
	shift_left(output,output);
	mux_8bit(output,rem[7],addu(rem,input1,input2),addu(output,output,one));

	subu(rem,input1,input2);
	shift_left(output,output);
	mux_8bit(output,rem[7],addu(rem,input1,input2),addu(output,output,one));

	subu(rem,input1,input2);
	shift_left(output,output);
	mux_8bit(output,rem[7],addu(rem,input1,input2),addu(output,output,one));

	return output;
}

//---------------------------

bool* divs(bool output[],bool input1[],bool input2[]) // takes four bit numbers
{
	output[0]=0;
	output[1]=0;
	output[2]=0;
	output[3]=0;
	output[4]=0;
	output[5]=0;
	output[6]=0;
	output[7]=0;
	bool neg1[7];
	neg1[0]=0;
	neg1[1]=0;
	neg1[2]=0;
	neg1[3]=0;
	neg1[4]=0;
	neg1[5]=0;
	neg1[6]=0;
	neg1[7]=0;
	bool neg2[7];
	neg2[0]=0;
	neg2[1]=0;
	neg2[2]=0;
	neg2[3]=0;
	neg2[4]=0;
	neg2[5]=0;
	neg2[6]=0;
	neg2[7]=0;
	bool zero[7];
	zero[0]=0;
	zero[1]=0;
	zero[2]=0;
	zero[3]=0;
	zero[4]=0;
	zero[5]=0;
	zero[6]=0;
	zero[7]=0;
	mux_8bit(input1,input1[7],Negate(neg1,input1),input1);
	mux_8bit(input2,input2[7],Negate(neg2,input2),input2);
	mux_8bit(output,Equal_8bit(neg1,neg2),divu(output,input1,input2),Negate(output,divu(output,input1,input2)));

	return output;
}

//---------------------------

bool* alu(bool output[],bool sl[],bool input1[],bool input2[])
{
	bool output1[7],output2[7],output3[7],output4[7],output5[7],output6[7],output7[7],output8[7],output9[7],output10[7],output11[7],output12[7],output13[7],output14[7],output15[7];
	bool Add[7];
	bool waist[7];
	bool* ad,*bill;
	ad=adds(waist,input1,input2);
	//cout << ad[4];
	Add[0]=0;
	Add[1]=0;
	Add[2]=0;
	Add[3]=0;
	Add[4]=0;
	Add[5]=0;
	Add[6]=0;
	Add[7]=0;
	bool Sub[7];
	bool* su;
	su=subs(waist,input1,input2);
	Sub[0]=1;
	Sub[1]=0;
	Sub[2]=0;
	Sub[3]=0;
	Sub[4]=0;
	Sub[5]=0;
	Sub[6]=0;
	Sub[7]=0;
	bool neg[7];
	neg[0]=0;
	neg[1]=1;
	neg[2]=0;
	neg[3]=0;
	neg[4]=0;
	neg[5]=0;
	neg[6]=0;
	neg[7]=0;
	bool eq[7];
	eq[0]=1;
	eq[1]=1;
	eq[2]=0;
	eq[3]=0;
	eq[4]=0;
	eq[5]=0;
	eq[6]=0;
	eq[7]=0;
	bool lt[7];
	lt[0]=0;
	lt[1]=0;
	lt[2]=1;
	lt[3]=0;
	lt[4]=0;
	lt[5]=0;
	lt[6]=0;
	lt[7]=0;
	bool gt[7];
	gt[0]=1;
	gt[1]=0;
	gt[2]=1;
	gt[3]=0;
	gt[4]=0;
	gt[5]=0;
	gt[6]=0;
	gt[7]=0;
	bool aNd[7];
	aNd[0]=0;
	aNd[1]=1;
	aNd[2]=1;
	aNd[3]=0;
	aNd[4]=0;
	aNd[5]=0;
	aNd[6]=0;
	aNd[7]=0;
	bool oR[7];
	oR[0]=1;
	oR[1]=1;
	oR[2]=1;
	oR[3]=0;
	oR[4]=0;
	oR[5]=0;
	oR[6]=0;
	oR[7]=0;
	bool sll[7];
	sll[0]=0;
	sll[1]=0;
	sll[2]=0;
	sll[3]=1;
	sll[4]=0;
	sll[5]=0;
	sll[6]=0;
	sll[7]=0;
	bool srl[7];
	srl[0]=1;
	srl[1]=0;
	srl[2]=0;
	srl[3]=1;
	srl[4]=0;
	srl[5]=0;
	srl[6]=0;
	srl[7]=0;
	bool Multu[7];
	Multu[0]=0;
	Multu[1]=1;
	Multu[2]=0;
	Multu[3]=1;
	Multu[4]=0;
	Multu[5]=0;
	Multu[6]=0;
	Multu[7]=0;
	bool Mult[7];
	Mult[0]=1;
	Mult[1]=1;
	Mult[2]=0;
	Mult[3]=1;
	Mult[4]=0;
	Mult[5]=0;
	Mult[6]=0;
	Mult[7]=0;
	bool Divu[7];
	Divu[0]=0;
	Divu[1]=0;
	Divu[2]=1;
	Divu[3]=1;
	Divu[4]=0;
	Divu[5]=0;
	Divu[6]=0;
	Divu[7]=0;
	bool Div[7];
	Div[0]=1;
	Div[1]=0;
	Div[2]=1;
	Div[3]=1;
	Div[4]=0;
	Div[5]=0;
	Div[6]=0;
	Div[7]=0;
	bool Addu[7];
	Addu[0]=0;
	Addu[1]=0;
	Addu[2]=0;
	Addu[3]=0;
	Addu[4]=1;
	Addu[5]=0;
	Addu[6]=0;
	Addu[7]=0;
	bool Subu[7];
	Subu[0]=1;
	Subu[1]=0;
	Subu[2]=0;
	Subu[3]=0;
	Subu[4]=1;
	Subu[5]=0;
	Subu[6]=0;
	Subu[7]=0;
	
	//cout << input1[0]<<'\n';
	
	mux_8bit(output,Equal_8bit(sl,Add),adds(waist,input1,input2),mux_8bit(output1,Equal_8bit(sl,Sub),subs(waist,input1,input2),
	mux_8bit(output,Equal_8bit(sl,neg),Negate(output2,input1),
	mux_8bit(output,Equal_8bit(sl,eq),Equal_8bit_8out(output3,input1,input2),
	mux_8bit(output,Equal_8bit(sl,lt),lessthan_8bit_8out(output4,input1,input2),
	mux_8bit(output,Equal_8bit(sl,gt),greaterthan_8bit_8out(output5,input1,input2),
	mux_8bit(output,Equal_8bit(sl,aNd),And_8bit(output6,input1,input2),
	mux_8bit(output,Equal_8bit(sl,oR),Or_8bit(output7,input1,input2),
	mux_8bit(output,Equal_8bit(sl,sll),shift_left(output8,input1),
	mux_8bit(output,Equal_8bit(sl,srl),shift_right(output9,input1),
	//mux_8bit(output,Equal_8bit(sl,Multu),multu(output10,input1,input2),
	//mux_8bit(output,Equal_8bit(sl,Mult),mult(output11,input1,input2),
	//mux_8bit(output,Equal_8bit(sl,Divu),divu(output12,input1,input2),
	//mux_8bit(output,Equal_8bit(sl,Div),divs(output13,input1,input2),
	mux_8bit(output,Equal_8bit(sl,Addu),addu(output14,input1,input2),
	mux_8bit(output,Equal_8bit(sl,Subu),subu(output15,input1,input2),Addu))))))))))));/*))))))))))))))));*/
	
	//cout << output[0] << output[1] << output[2] << output[3] << output[4] << output[5] <<'\n';
	
	return output;
}
