#include "LCD.h"

void LCD_init()
{
	init_port_lcd;
	LCD_write_cmd_char( 0x02, 0);
	LCD_write_cmd_char( 0x28, 0);
	LCD_write_cmd_char( 0x01, 0);
	LCD_write_cmd_char( 0x06, 0);
	LCD_write_cmd_char( 0x80, 0);
	LCD_write_cmd_char( 0x0E, 0);
	_delay_ms(20);

	

}
void LCD_write_cmd_char(uint8_t data,uint8_t select)
{
					RS(select);
					
					D7(READBIT(data,7));
					D6(READBIT(data,6));
					D5(READBIT(data,5));
					D4(READBIT(data,4));
					EN(1);
					 _delay_ms(1);
				   	EN(0);
					_delay_ms(0);
					D7(READBIT(data,3));
					D6(READBIT(data,2));
					D5(READBIT(data,1));
					D4(READBIT(data,0));
					EN(1);
					_delay_ms(1);
					EN(0);
					_delay_ms(0);
				
	
		
	
}
void LCD_write_txt(uint8_t* txt)
{	char i=0;
	while(txt[i]!='\0')
	{
		LCD_write_cmd_char(txt[i],1);
		i++;
	}
	
		
}
void LCD_write_num(uint16_t num)
{	
	int x,y,z,k,i,j;
		if(num<10)
		LCD_write_cmd_char(num+48,1);
		else if(num<100)
		{
			x=num/10;
			y=num%10;
			LCD_write_cmd_char(x+48,1);
			LCD_write_cmd_char(y+48,1);
		}
		else if(num<1000)
		{
			x=num/100;
			y=num%100;
			z=y/10;
			k=y%10;
			LCD_write_cmd_char(x+48,1);
			LCD_write_cmd_char(z+48,1);
			LCD_write_cmd_char(k+48,1);
		}
		else if(num<10000)
		{
			x=num/1000;
			y=num%1000;
			z=y/100;
			k=y%100;
			j=k/10;
			i=k%10;
			LCD_write_cmd_char(x+48,1);
			LCD_write_cmd_char(z+48,1);
			LCD_write_cmd_char(j+48,1);
			LCD_write_cmd_char(i+48,1);
		}
		else
		LCD_write_txt("LONG NUMBER");
}

	
void LCD_write_number(uint16_t num){
int8_t i=0;
uint8_t txt[10];
while(num!=0)
{
	txt[i++]=(num%10)+48;
	num/=10;
}
i--;
while(i>=0)
{
LCD_write_cmd_char(txt[i--],1);
}
}


