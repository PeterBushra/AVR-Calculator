#include "Calc_Funcs.h"
#include "math.h"
#define NumOfDigit 20
uint8_t DigitCounter = 0,SignNum_F = 0,Flag;
sint32 Digit[NumOfDigit];
double Final_arr[NumOfDigit]={0};
double Result = 0 , data = 0;
static sint8 contcatnate_counter=0;

void ResetData(){
	LCD_write_cmd_char(0x01,0);
	LCD_write_cmd_char(0x80,0);
	data = 0 ;
	DigitCounter = 0 ;
	Result = 0;
	contcatnate_counter=0;
	Flag = Start;
}
void GetData()
{
	data = KeyPad_read();
	if (data)//data!=0xff
	{
		if(data == '=')
		{
			
			Digit[DigitCounter]= data ; //Store '='
			LCD_write_cmd_char(Digit[DigitCounter],1);
			DigitCounter++;
			Digit[DigitCounter]= 63 ; // Store 63 .. To Count Untill Reach To 63
			Flag = Analyze;			//	Go To Analyze Function
			return;
		}
		else if (IsOp(data) )
		{
			if(data == '-') // To Handle many '-' Such  (5---2)
			{
				if(SignNum_F == false)
				{SignNum_F=true;}
				else if(SignNum_F == true)
				{SignNum_F=false;}
				LCD_write_cmd_char('-',1);
				_delay_ms(250);
			}
			else
			{
				Digit[DigitCounter]= data ; //Store Any Op Except '-'
				LCD_write_cmd_char(Digit[DigitCounter],1);
				DigitCounter++;
				_delay_ms(250);
			}
		}
		else if (data == 'C')
		{
			Flag = Reset; // If Press "ON"  > Reset
			return;
		}
		else if (data=='0') // To Handling '0' .. To Store & appear On Screen
		{
			Digit[DigitCounter]= (data-48) ;
			LCD_write_cmd_char('0',1);
			DigitCounter++;
			_delay_ms(250);
		}
		else
		{
			if (SignNum_F)
			{
				Digit[DigitCounter]='-'; //Store '-'
				DigitCounter++;
				data=-data;			   	// If '-' Is Pressed .. The Number After It Will be Negative
				SignNum_F=false;		 //Get Flag To False Again
				Digit[DigitCounter]=data;//Store Number After '-'
				LCD_write_number(-Digit[DigitCounter]);
				DigitCounter++;
				_delay_ms(250);
			}
			else
			{
				Digit[DigitCounter]=data; //Store Num;
				LCD_write_number(Digit[DigitCounter]);
				DigitCounter++;
				_delay_ms(250);
			}
		}
		
		
	}
	
}
void Analysis()
{
	uint8_t  Final_arr_counter = 0 ,index =0 , \
	Nums_before_Operand =0 ;
	
	if( IsOp(Digit[0]) && ((Digit[0]!= '-') || (Digit[0]!=Nums))  ) // Get Error If Enter   ex: *2= Or /7=
	{
		Errors((uint8_t*)"Invalid Input");
		Flag = Reset;
		return;
	}
	
	while(Digit[index] != 63) //Get Error If Enter ex: *\41 ;
	{
		if(IsOp(Digit[index])&&IsOp(Digit[index+1])){
			Errors((uint8_t*)"Syntax Error");
		}
		
		if ((Digit[index]=='/')&&(Digit[index+1]==0)) //if Divided  Over Zerooo Get Math Error
		{
			Errors((uint8_t*)"Math Error");
		}
		
		index++;
	}
	
	index=0;
	while(Digit[index] != 63)//Count Numbers Before Each Operand And contcatnate It .. Ex: {1,3,4,'+',8,9,'='} Will Be {134,'+',89,'='}
	{
		if(!IsOp(Digit[index]))
		{
			Nums_before_Operand++; // Count Numbers ;
			
		}
		
		else if (IsOp(Digit[index])) // If Find Opeartion
		{
			if(Nums_before_Operand > 0) // Check If There is Nums Before Operand
			{
				Final_arr[Final_arr_counter]=contcatnate(Nums_before_Operand); // Send Numbers Of Digits Berfore Operand To contcatnate;
				Final_arr_counter++;
				Nums_before_Operand = 0; //Return To Zero
			}
			
			Final_arr[Final_arr_counter]=Digit[index];//Store Operand Form Array Called Digit[] To Final_arr[]
			Final_arr_counter++;
			
		}
		index++;
	}
	
	
	Flag = calculate;  // Go To Calculation Func.
	
	
}
void Calculation()
{	sint8 i =0  ;
	while(Final_arr[i] != '=')
	{
		if (Final_arr[i]=='-')//Delete All '-' In Array Bcoz I Assume It In a Number ;
		{
			delete_node(i);
			continue;
		}
		i++;
	}
	i=0;
	while(Final_arr[i] != '=')
	{
		if (Final_arr[i]=='*') // Calculate All Multiply Operations As First And Edit The Array With New Value And Delete '*'
		{
			Final_arr[i-1]=Final_arr[i-1]*Final_arr[i+1]; //ex: {5,'*',6,'='} Will Be >> {30,'*',6,'='}
			delete_node(i);		//delete '*' From Array
			delete_node(i);		//delete "6"  From Array
			//Final_Arr Came {30,'='};
			i=0;
		}
		i++;
	}
	i=0;
	while(Final_arr[i] != '=')
	{
		if (Final_arr[i]== '/')// Calculate All Division Operations As Second And Edit The Array With New Value And Delete '/'
		{
			Final_arr[i-1]=Final_arr[i-1]/Final_arr[i+1];
			delete_node(i);//delete '/' From Array
			delete_node(i);//delete 'digit' From Array
			i=0;
		}
		i++;
	}
	i=0;
	while(Final_arr[i] != '=')
	{
		if (Final_arr[i]=='+')//// Calculate All Add Operations As 3rd And Edit The Array With New Value And Delete '+'
		{
			Final_arr[i-1]=Final_arr[i-1]+Final_arr[i+1];
			delete_node(i);//delete '+' From Array
			delete_node(i);//delete 'Digit' From Array
			i=0;
		}
		i++;
	}
	i=0;
	
	while(Final_arr[i] != '=')//Finally Summing Up All Digits In Array
	{
		Result+=Final_arr[i];
		i++;
	}
	
	
	Flag = Display; // Go TO Display ^_^
	return;
	
	
}
void DisplayResult()
{													//LET RESULT = -65.124;
	uint32_t integer = fabs(Result);			//integer = |Result| = 65  ? Bocz Integer DataType
	double temp = fabs(Result);					//temp = 65.124				? Bcoz Double DataType Support Float Num
	
	
	temp=temp-integer;		// 65.124 - 65 = .124
	temp*=10000;			// .124*10000= 12400; // Zero On Right Doesn't Problem After '.'
	if(Result==0) // To Handle Zero Appearing
	{
		LCD_write_cmd_char(0xc0,0);
		LCD_write_cmd_char('0',1);
		
	}
	else if (Result<0) // To Handle '-' Appearing ON SCR
	{LCD_write_cmd_char(0xc0,0);
		LCD_write_cmd_char('-',1);//Print '-'
		Result=-Result; //-65 Will 65 To Appear :)
		LCD_write_number(Result); //Appeared ^_^
		
	}
	else
	{
		LCD_write_cmd_char(0xc0,0);
		LCD_write_number(Result);
	}
	if(temp>0) // Bcoz If There isn't Float Num .. Not Print Float Point .
	{
		LCD_write_cmd_char('.',1);//Print Point Float
	temp==0?LCD_write_cmd_char('0',1):LCD_write_number(temp);} //Print Temp ex:12400  As I Assumed
	while(data != 'C'){data=KeyPad_read();} //Pause Until  Press 'C'
	Flag = Reset; // Reset All
}
void Errors(uint8_t* txt )
{
	LCD_write_cmd_char(0x01,0);
	LCD_write_txt(txt);
	
	while(data != 'C'){data=KeyPad_read();}
	Flag = Reset;
	
}
sint32 contcatnate(uint8_t pow){//Pow Is Nums Of Digit
	sint32 *temp=Digit; //Copy Array To Temp Array
	uint8_t i ,z  ;
	sint8 y=0 ,SignFlag=1;
	sint32 sum =0;
	pow--;

	z=contcatnate_counter;
	if (temp[contcatnate_counter] < 0) // If Number Is Negative
	{
		temp[contcatnate_counter]*=-1; // Convert It To Positive
		SignFlag=-1;					// And Set Flag
	}
	while(pow > 0)
	{	//if {1,3,5}; >> Will Be 100,30,5 And Summing up All To Be 135 ^_^
	
	for (i=0;i<pow;i++) // This Loop To Multiply On Place In .. 1*100 , 3*10 , 5*1
	{
		
		temp[contcatnate_counter]=(temp[contcatnate_counter])*10;
	}
	contcatnate_counter++;
	pow--;
	
}
y=contcatnate_counter;
while (y>=z) //TO Assume All That I Assumed Above
{
	sum+=temp[y];
	y--;
}
contcatnate_counter+=2; //Jump To New Place In Array To Recive New "Pow" , And Re This Func.
return sum*SignFlag;	// If The SignFlag Is Set Above Will Be Return Negative Value

}
void delete_node(uint8_t node)
{
	uint8_t temp = (node + 1) ;
	while(Final_arr[(node-1)] != '=')
	{
		Final_arr[node]=Final_arr[temp];
		node++;
		temp++;
	}
	
}
