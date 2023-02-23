/*
 * main.c
 *
 *  Created on: Jan 28, 2023
 *      Author: fathy
 */
/************includes ********/

#include<util/delay.h>

#include"../LIBRARY/errorState.h"
#include"../LIBRARY/stdTypes.h"
#include"../MCAL/DIO/DIO_int.h"
#include"../HAL/LCD/LCD_int.h"
#include"../HAL/KEYPAD/KEYPAD_int.h"
#include"../MCAL/GIE/GIE_int.h"
#include"../MCAL/EXTI/EXTI_int.h"
#include"../MCAL/ADC/ADC_int.h"
#include "../MCAL/TIMER0/TIMER0_int.h"
#include"../HAL/DC_MOTOR/DC_MOTOR_int.h"
#include "../MCAL/TIMER1/TIMER1_int.h"
#include "../HAL/SERVO_MOTOR/SERVO_MOTOR_int.h"
#include "../HAL/DIMMER_LAMP/DIMMER_LAMP_int.h"
#include"../HAL/RELAY/RELAY_int.h"
#include "../HAL/TEMP_SENSOR/TEMP_sENSOR_int.h"
#include "../MCAL/UART/UART_int.h"
#include"../HAL/HC05/HC05_int.h"
#include "../MCAL/IIC/IIC_int.h"
#include"../HAL/EEPROM/EEPROM_int.h"
#include "../HAL/BUTTON/BUTTON_int.h"
#include "../HAL/BUZZER/BUZZER_int.h"

/*****************Functions *****************************/
    void GetId    (u8* Copy_u8Id, u8 Copy_u8Mode);
	void GetPassword  (u8* Copy_u8Password, u8 Copy_u8Mode);
	void CheckAdmin (u8* Copy_u8Id, u8* Copy_u8Password,u8 *Copy_u8AdminState);
	void AddUser (u8* Copy_u8Id, u8* Copy_u8Password);
	void CheckUser ( u8* Copy_u8Id, u8* Copy_u8Password,u8 *Copy_u8UserState);

	void DeleteUser (u8 Copy_u8NumOfUsers, u8* Copy_u8Id);
	void DeleteAll (void);
	void SensorControl (u8* Copy_u8State);
	void DoorControl (u8* Copy_u8State);
	void LedsControl(u8* Copy_u8State,u8 Copy_u8NumOfLed);
	void DimmmerControl(u8 *Copy_u8State,u8 copy_u8Intensty);
	void AppInit(void);


	void CheckSensor(u8 Copy_u8State);
	void CheckDoor(u8 Copy_u8State);

	void CheckLeds(u8* Copy_u8State);
	void CheckDimmer(u8 Copy_u8State);
	void Reset(u8* Sensor_State, u8* Door_State, u8* Relay_State,u8* Dimmer_State);
	void Display_System(u8*Copy_state,u8 Sensor_State, u8 Door_State, u8* Relay_State,u8 Dimmer_State);


#define Admin_Mode      1
#define User_Mode       2
#define WELCOM_PAGE     0
#define CHOICE_MODE     1
#define ADMIN_LOGIN     2
#define USER_LOGIN      3
#define ADMIN_CONTROL   4
#define USER_CONTROL    5
#define NO_DATA         6

	// GLOBAL VARIABLE
	u8 STATE=WELCOM_PAGE;   // THIS variable to determine the state (user -admin-login -no data recived)
	u8 Max_Num_Users=5;

int main(){
  /**************** init***************/

	LCD_enuInit();

	KEYPAD_enuInit();
	GIE_enuEnable();
	ADC_enuInit();
	DC_MOTOR_enuInit();
	SERVO_MOTOR_enuInit();
	//DIMMER_LAMP_enuInit();
	RELAY_enuInit();
	TEMP_SENSOR_enuInit();
	HC05_enuInit();
	EEPROM_enuInit();
	BUTTON_enuInit();
	BUZZER_enuInit();
	SERVO_MOTOR_enuSetPosition(CLOSE);
	//this function for saving the admin pass and ID + user pass and ID for first time
	AppInit();
	u8 Number_Users=0;
	//get the number of users i have save it in address 90 page 0
	EEPROM_enuRead(&Number_Users,0,90);
// there are two arraies to save data on it before check is found or not
u8 Copy_ID	[4]={0};
u8 Copy_Password[4]={0};
u8 Key_Data=KEY_NOT_PRESSED;        // to store keypad key
u8 Num_Trails =0;
u8 Leds_State[5]={0};
u8 SERVO_State=CLOSE;     // to store door open or close
u8 SENSOR_State=0;    //to store sensor state
u8 Dimmer_State=0;
u8 Recieve_Date=0;
u8 Check=0;
// to store data from bluetooth
// appaliction program
	while(1){
		switch(STATE){
		case WELCOM_PAGE:
			LCD_enuClearScreen();
			LCD_enuWriteString("Welcome to Smart Home");
			HC05_enuSendString("Welcome to Smart Home\r\n");
		//_delay_ms(1500);
			STATE=CHOICE_MODE;
			break;
		case CHOICE_MODE:
			Key_Data=KEY_NOT_PRESSED;
			LCD_enuClearScreen();
			LCD_enuWriteString("1- Admin Mode");
			HC05_enuSendString("1- Admin Mode\r\n");
			LCD_enuGoToPosition(1,0);
			LCD_enuWriteString("2- User Mode");
			HC05_enuSendString("2- User Mode\r\n");

			while(Key_Data==KEY_NOT_PRESSED){
				KEYPAD_enuGetPressedKey(&Key_Data);
				if(Key_Data=='1'){
					STATE=ADMIN_LOGIN;
				}
				else if(Key_Data=='2'){
					STATE=USER_LOGIN;
				}

			}
			break;
		case USER_LOGIN:
			Num_Trails=0;
			while(Num_Trails<3){
				LCD_enuClearScreen();
				LCD_enuWriteString("Enter User Name:");
				GetId(Copy_ID,User_Mode);
				LCD_enuClearScreen();
				LCD_enuWriteString("Enter User Password:");
				GetPassword(Copy_Password,User_Mode);

				CheckUser(Copy_ID,Copy_Password,&Check);
				if(Check==1){
					STATE=USER_CONTROL;
					break;
				}
				else if(Check==0){
					Num_Trails++;
					if(Num_Trails==3){

						SERVO_MOTOR_enuSetPosition(CLOSE);
						SERVO_State=CLOSE;
						BUZZER_enuON();
						LCD_enuClearScreen();
						Key_Data=0;
					    for(;;){
					    	BUTTON_enuGetValue(&Key_Data);
					    	if(Key_Data==1){
					    		BUZZER_enuOFF();
					    		STATE=WELCOM_PAGE;
					    		break;
					    	}
					    }

					}
				}
			}



		Num_Trails=0;
		break;
		case ADMIN_LOGIN:
			LCD_enuClearScreen();
			LCD_enuWriteString("Admin Mode");
			LCD_enuGoToPosition(1,0);
			LCD_enuWriteString("Use Bluetooth");
			//HC05_enuSendString("use the Bluetooth\r\n");
			_delay_ms(1500);
			while(Num_Trails<3){
				HC05_enuSendString("Enter Admin Name\r\n");
				GetId(Copy_ID,Admin_Mode);
				HC05_enuSendString("Enter Admin Password\r\n");
				GetPassword(Copy_Password,Admin_Mode);
				Check=0;
				CheckAdmin(Copy_ID,Copy_Password,&Check);
				if(Check==1){
					STATE=ADMIN_CONTROL;
					break;
				}
				else if(Check==0){
					Num_Trails++;
					if(Num_Trails==3){
						SERVO_MOTOR_enuSetPosition(CLOSE);
						SERVO_State=CLOSE;
						BUZZER_enuON();
						u8 Button_read=0;
				        for(;;){

							BUTTON_enuGetValue(&Button_read);
					    	if(Button_read==1){
							   BUZZER_enuOFF();
							   STATE=WELCOM_PAGE;
						    	break;
											   }
								}


					}
				}
			}

			Num_Trails=0;
			break;
		case ADMIN_CONTROL:
			Recieve_Date=0;
			LCD_enuClearScreen();
			HC05_enuSendString("*******************************\r\n");
			HC05_enuSendString("1- Switch the door\r\n");
			HC05_enuSendString("2- Add New User\r\n");
			HC05_enuSendString("3- Remove User \r\n");
			HC05_enuSendString("4- switch LEDS \r\n");
			HC05_enuSendString("5- Switch DC Motor\r\n");
			HC05_enuSendString("6- control Dimmer Lamp\r\n");
			HC05_enuSendString("7- Go to User Mode \r\n");
			HC05_enuSendString("8- Reset The System\r\n");
			HC05_enuSendString("9- OK\r\n");
			HC05_enuRecieveChar(&Recieve_Date);
			HC05_enuSendString("\r\n");
			switch(Recieve_Date){
			case '1':
				DoorControl(&SERVO_State);
				break;
			case'2':

				LCD_enuClearScreen();
				LCD_enuWriteString("Use Bluetooth");
				_delay_ms(1000);
				LCD_enuClearScreen();
				LCD_enuWriteString("Enter User Name");
			    HC05_enuSendString("Enter New User Name\r\n");
				GetId(Copy_ID,Admin_Mode);
				LCD_enuClearScreen();
				//LCD_enuWriteString("Enter Password");
				HC05_enuSendString("Enter Password\r\n");
				GetPassword(Copy_Password,Admin_Mode);
				HC05_enuSendString("\r\n");
				AddUser(Copy_ID,Copy_Password);
				//STATE=ADMIN_CONTROL;
				break;
			case'3':
				// get the number of users
				EEPROM_enuRead(&Number_Users,0,90);
				LCD_enuClearScreen();
				LCD_enuWriteString("USE Bluetooth");
				//HC05_enuSendString("Use the Bluetooth\r\n");
				_delay_ms(1000);
				HC05_enuSendString("Enter The User Name Do you want to remove\r\n");
				GetId(Copy_ID,Admin_Mode);
				DeleteUser(Number_Users,Copy_ID);
				break;
			case'4':
				HC05_enuSendString("Enter the Number of the LED (1 to 5)\r\n");
				Recieve_Date=0;
				HC05_enuRecieveChar(&Recieve_Date);
				LedsControl(Leds_State,Recieve_Date);
				break;
			case'5':
				SensorControl(&SENSOR_State);
				break;
			case'6':
				HC05_enuSendString("Enter Intensity from 1 to 9   0-OFF \r\n");
				HC05_enuRecieveChar(&Recieve_Date);
				DimmmerControl(&Dimmer_State,Recieve_Date);

				break;
			case '7':
				HC05_enuSendString("System Changed to User Mode\r\n");
				STATE=USER_LOGIN;
				break;
			case '8':
				Reset(&SENSOR_State,&SERVO_State,Leds_State,&Dimmer_State);
				break;
			case'9':
				//HC05_enuSendString("System Changed to User Mode\r\n");
				 Display_System(&STATE,SENSOR_State,SERVO_State,Leds_State,Dimmer_State);
				//STATE=WELCOM_PAGE;
				break;
			default:
				break;
			}
			break;
			case USER_CONTROL:
				LCD_enuClearScreen();
				LCD_enuWriteString("1-Leds 2-AC");
				LCD_enuGoToPosition(1,0);
				LCD_enuWriteString("3-DIMMER 4-OK");
				Key_Data=KEY_NOT_PRESSED;
				while(Key_Data==KEY_NOT_PRESSED){
					KEYPAD_enuGetPressedKey(&Key_Data);
					if(Key_Data=='1'){
						LCD_enuClearScreen();
						LCD_enuWriteString("Enter Number of LED");
						LCD_enuGoToPosition(1,0);
						LCD_enuWriteString("from 1 to 5");
						u8 key_led_num=KEY_NOT_PRESSED;
						while(key_led_num==KEY_NOT_PRESSED){
							KEYPAD_enuGetPressedKey(&key_led_num);
						}
						LedsControl(Leds_State,key_led_num);
					}
					else if(Key_Data=='2'){
						SensorControl(&SENSOR_State);
					}
					else if(Key_Data=='3'){
						LCD_enuClearScreen();
						LCD_enuWriteString("Enter Intensity");
						LCD_enuGoToPosition(1,0);
						LCD_enuWriteString("1 to 9 ** 0-OFF");
						u8 key_intensty=KEY_NOT_PRESSED;
						while (key_intensty==KEY_NOT_PRESSED){
							KEYPAD_enuGetPressedKey(&key_intensty);
						}

						DimmmerControl(&Dimmer_State,key_intensty);
					}
					else if (Key_Data=='4'){
						 Display_System(&STATE,SENSOR_State,SERVO_State,Leds_State,Dimmer_State);
					}
				}
				break;
			case NO_DATA:
				LCD_enuClearScreen();
                STATE=WELCOM_PAGE;
                LCD_enuWriteString("welcome page");
                _delay_ms(1000);

				break;
			default:
				break;
	}
}
}

    void GetId(u8*Copy_u8Id, u8 Copy_u8Mode){
       u8 Num_Digit=0; u8 Key=KEY_NOT_PRESSED; u8 Data_Recived=0;
       if (Copy_u8Mode==Admin_Mode){
    	   LCD_enuClearScreen();
    	   LCD_enuWriteString("Enter User Name");
    	   LCD_enuGoToPosition(1,0);
    	   while(Num_Digit<4){
    		   HC05_enuRecieveChar(&Data_Recived);
    		   if(Data_Recived){
    			   Copy_u8Id[Num_Digit]=Data_Recived;
    			   LCD_enuWriteCharacter(Copy_u8Id[Num_Digit]);
    			   Num_Digit++;
    		   }
    	   }
    	   HC05_enuSendString("\r\n");
    	   _delay_ms(300);

       }
       else if(Copy_u8Mode==User_Mode){
    	   LCD_enuGoToPosition(1,0);

    	   while(Num_Digit<4){
    		   KEYPAD_enuGetPressedKey(&Key);

    		   if(Key!=KEY_NOT_PRESSED){
    			   Copy_u8Id[Num_Digit]=Key;
    			   LCD_enuWriteCharacter(Copy_u8Id[Num_Digit]);
    			   Num_Digit++;
    		   }
    	   }
    	   _delay_ms(300);
       }
         LCD_enuClearScreen();
    }
	void GetPassword  (u8* Copy_u8Password, u8 Copy_u8Mode){
         u8 Num_Digit=0; u8 Key=KEY_NOT_PRESSED; u8 Data_Recieved=0;
         if (Copy_u8Mode==Admin_Mode){
        	 LCD_enuClearScreen();
        	 LCD_enuWriteString("Enter PassWord");
        	 LCD_enuGoToPosition(1,0);
        	 while(Num_Digit<4){
        		 HC05_enuRecieveChar(&Data_Recieved);
        		 if(Data_Recieved){
        			 Copy_u8Password[Num_Digit]=Data_Recieved;
        			 LCD_enuWriteCharacter('*');
        			 Num_Digit++;
        		 }
        	 }
        	 _delay_ms(50);
        	 }
         else if(Copy_u8Mode==User_Mode){
        	 LCD_enuGoToPosition(1,0);
        	 while(Num_Digit<4){
        		 KEYPAD_enuGetPressedKey(&Key);
        		 if(Key!=KEY_NOT_PRESSED){
        			 Copy_u8Password[Num_Digit]=Key;
        			 LCD_enuWriteCharacter('*');
        			 Num_Digit++;
        		 }
        	 }
        	 _delay_ms(300);
         }
	}
	void CheckAdmin (u8* Copy_u8Id, u8* Copy_u8Password,u8 *Copy_u8AdminState){
        u8 Address=0; u8 Num_Digit=0; u8 Exist_UserNAme=0;  u8 Exist_Password=0;
        u8 Data=0;
		LCD_enuClearScreen();
		HC05_enuSendString("\r\n");
		while(Num_Digit<4){
			Address=91+Num_Digit;
			EEPROM_enuRead(&Data,0,Address);
			if(Data==Copy_u8Id[Num_Digit]){
				Exist_UserNAme++;
			}
			Num_Digit++;
		}
		Num_Digit=0;
		while(Num_Digit<4){
			Address=91+4+Num_Digit;
			EEPROM_enuRead(&Data,0,Address);
			if(Data==Copy_u8Password[Num_Digit]){
				Exist_Password++;
			}
			Num_Digit++;
		}
		if(Exist_Password==4&&Exist_UserNAme==4){
			LCD_enuClearScreen();
			LCD_enuWriteString("Successful Login");
			HC05_enuSendString("Successful Login\r\n");
			*Copy_u8AdminState=1;
			_delay_ms(1000);
		}
		else if(Exist_Password==4&&Exist_UserNAme!=4){
			LCD_enuClearScreen();
			LCD_enuWriteString("Invalid UserName");
			HC05_enuSendString("Invalid UserName\r\n");
			*Copy_u8AdminState=0;
			_delay_ms(200);
		}
		else if(Exist_UserNAme==4&&Exist_Password!=4){
			LCD_enuClearScreen();
			LCD_enuWriteString("Invalid Password");
			HC05_enuSendString("Invalid Password\r\n");
			*Copy_u8AdminState=0;
			_delay_ms(200);
		}
		else if(Exist_Password!=4&&Exist_UserNAme!=4){
			LCD_enuClearScreen();
			LCD_enuWriteString("Invalid UserName");
			HC05_enuSendString("Invalid UserName\r\n");
			LCD_enuGoToPosition(1,0);
			LCD_enuWriteString("Invalid Password");
			HC05_enuSendString("Invalid Password\r\n");
			*Copy_u8AdminState=0;
			_delay_ms(200);

		}
		LCD_enuClearScreen();
	}
	void AddUser (u8* Copy_u8Id, u8* Copy_u8Password){

		u8 Num_Users=0;
		EEPROM_enuRead(&Num_Users,0,90);
		if(Num_Users<Max_Num_Users){

			if(Num_Users>0){
				u8 Problem=0;
				for (u8 Counter=0;Counter<Num_Users;Counter++){

					u8 Num_Digit=0;  u8 Address=0;  u8 Exist_User=0; u8   Date=0;
					for(;Num_Digit<4;Num_Digit++){
						Address=Counter*8+Num_Digit;
						EEPROM_enuRead(&Date,0,Address);
						if(Date==Copy_u8Id[Num_Digit]){
							Exist_User++;
						}
					}
						if (Exist_User==4){
							LCD_enuClearScreen();
							LCD_enuWriteString("User Is Existed");
							HC05_enuSendString("the User is Already Existed\r\n");
							_delay_ms(1000);
							Problem++;
							break;

						}
						}
				if(!Problem){
                      LCD_enuClearScreen();
                      LCD_enuWriteString("Successful Add");
                      HC05_enuSendString("Successful Add\r\n");
                      u8 Num_Digit=0;  u8 Address=0;
                      for(;Num_Digit<4;Num_Digit++){
                    	  Address=Num_Users*8+Num_Digit;
                    	  EEPROM_enuWrite(Copy_u8Id[Num_Digit],0,Address);
                      }
                       Num_Digit=0;
                      for(;Num_Digit<4;Num_Digit++){
                    	  Address=Num_Users*8+4+Num_Digit;
                    	  EEPROM_enuWrite(Copy_u8Password[Num_Digit],0,Address);
                      }
                      Num_Users++;
                      EEPROM_enuWrite(Num_Users,0,90);
                   _delay_ms(1000);

					}
				}

			else{
				LCD_enuClearScreen();
				LCD_enuWriteString("Successful Add");
				HC05_enuSendString("Successful Add\r\n");
			//	u8 location=0;
				u8 Num_Digit=0; u8 Address=0;
				for(;Num_Digit<4;Num_Digit++){
					Address=Num_Digit;
					EEPROM_enuWrite(Copy_u8Id[Num_Digit],0,Address);
				}
				 Num_Digit=0;
				for(;Num_Digit<4;Num_Digit++){
									Address=Num_Digit+4;
									EEPROM_enuWrite(Copy_u8Password[Num_Digit],0,Address);
				}
				Num_Users++;
				EEPROM_enuWrite(Num_Users,0,90);
			//	_delay_ms(300);
			}
		}
		else{
			LCD_enuClearScreen();
			LCD_enuWriteString("System Exceed");
			LCD_enuGoToPosition(1,0);
			LCD_enuWriteString("max Num of Users");
			HC05_enuSendString("System Exceed Max Number of Users\r\n");
			_delay_ms(300);
		}
	}
	void CheckUser ( u8* Copy_u8Id, u8* Copy_u8Password,u8 *Copy_u8UserState){
		u8 Num_Users=0;
		EEPROM_enuRead(&Num_Users,0,90);
		u8 Location =0; u8 Counter=0; u8 Data=0;
		 u8 Exist_UserName=0; u8 EXist_Password=0;
		u8 Address=0;
		if(Num_Users>0){

			for(;Counter<Num_Users;Counter++){
				  Exist_UserName=0;  EXist_Password=0;
				 Location=Counter*8;
				 u8 Num_Digit=0;
				 for(;Num_Digit<4;Num_Digit++){
					Address=Location+Num_Digit;
					EEPROM_enuRead(&Data,0,Address);
					if(Data==Copy_u8Id[Num_Digit]){
						Exist_UserName++;
					}
				 }
				 Num_Digit=0;
				 for(;Num_Digit<4;Num_Digit++){
									Address=Location+Num_Digit+4;
									EEPROM_enuRead(&Data,0,Address);
									if(Data==Copy_u8Password[Num_Digit]){
										EXist_Password++;
									}
				                  }
				 if(Exist_UserName==4&&EXist_Password==4){
					 break;
				 }
				 else{
					 Exist_UserName=0;
					 EXist_Password=0;
				 }

		}
			 if(Exist_UserName==4&&EXist_Password==4){
								 LCD_enuClearScreen();
								 LCD_enuWriteString("successful Login");
								 HC05_enuSendString("successful Login\r\n");
								 *Copy_u8UserState=1;
								 _delay_ms(1000);
							 }
			 else{
				 LCD_enuClearScreen();
				 LCD_enuWriteString("Invalid UserName");
				 LCD_enuGoToPosition(1,0);
				 LCD_enuWriteString("or Password");
				 HC05_enuSendString("Invalid UserName Or Password\r\n");
				 *Copy_u8UserState=0;
				 _delay_ms(1000);
			 }
	}
		else {
			LCD_enuClearScreen();
			LCD_enuWriteString("there is no Users");
			HC05_enuSendString("There is no Users\r\n");
			*Copy_u8UserState=0;
			_delay_ms(1000);
		}
	}
	void DeleteUser (u8 Copy_u8NumOfUsers, u8* Copy_u8Id){

			if (Copy_u8NumOfUsers>0){
				u8 Counter=0; u8 Data=0; u8 Location =0; u8 Address=0; u8 Done=0;
				for(;Counter<Copy_u8NumOfUsers;Counter++){
					Location=Counter*8;
				   u8 Exist_UserName=0;
				   for(u8 Num_Digit=0;Num_Digit<4;Num_Digit++){
					   Address=Location+Num_Digit;
					   EEPROM_enuRead(&Data,0,Address);
					   if(Data==Copy_u8Id[Num_Digit]){
						   Exist_UserName++;
					   }
				   }
				   if(Exist_UserName==4){

					   Done=1;
				   }
				   if(Done==1){
					   u8 Num_Digit=0;
					   for(;Num_Digit<4;Num_Digit++){
						   Address=Location+Num_Digit;
						   u8 Next_Address=Address+8;
						   EEPROM_enuRead(&Data,0,Next_Address);
						   EEPROM_enuWrite(Data,0,Address);
					   }
					    Num_Digit=0;
					   for(;Num_Digit<4;Num_Digit++){
						   Address=Location+Num_Digit+4;
						  	u8 Next_Address=Address+8;
						    EEPROM_enuRead(&Data,0,Next_Address);
						  	EEPROM_enuWrite(Data,0,Address);
					   }
				   }
				}
				if (Done==1){
					Copy_u8NumOfUsers--;
					EEPROM_enuWrite(Copy_u8NumOfUsers,0,90);

				}
			}

		}

	void DeleteAll (void){

		  for (u16 Counter = 0; Counter <= 0xFF; Counter++)
		  {
		    EEPROM_enuWrite(0xFF, 0, Counter);
		  }

		  EEPROM_enuWrite(0, 0, 90);

	}
	void SensorControl (u8* Copy_u8State){
            if (*Copy_u8State==0){
            	u16 Temperature=0;
            	Temperature=TEMP_SENSOR_enuRead();
            	LCD_enuWritInteger(Temperature);
            	if(Temperature>28){
            		DC_MOTOR_enuSetDirection(CLOCKWISE);
            		DC_MOTOR_enuSetSpeed(100);
            		DC_MOTOR_enuStart();
            		//LCD_enuClearScreen();

            	}
            	else if(Temperature<21){
            		DC_MOTORenuStop();
            	}
            	*Copy_u8State=1;

            }
            else if(*Copy_u8State==1){
            	DC_MOTORenuStop();
            	*Copy_u8State=0;
            }
	}
	void DoorControl (u8* Copy_u8State){
		if(*Copy_u8State==CLOSE){
			LCD_enuClearScreen();
			SERVO_MOTOR_enuSetPosition(OPEN);
			LCD_enuWriteString("DOOR is OPEN");
			HC05_enuSendString("DOOR is OPEN\r\n");
			*Copy_u8State=OPEN;
			_delay_ms(1000);
		}
		else{
			LCD_enuClearScreen();
			SERVO_MOTOR_enuSetPosition(CLOSE);
			LCD_enuWriteString("DOOR is CLOSE");
			HC05_enuSendString("DOOR is Close\r\n");
			*Copy_u8State=CLOSE;
			_delay_ms(1000);
		}

	}
	void LedsControl(u8* Copy_u8State,u8 Copy_u8NumOfLed){
		LCD_enuClearScreen();
          switch(Copy_u8NumOfLed){
          case'1':
        	  RELAY_enuToggle(LED_1);
        	  if(Copy_u8State[0]==0){
        		  Copy_u8State[0]=1;
        		  LCD_enuWriteString("LED1 ON");
        		  HC05_enuSendString("LED1 ON\r\n");
        	  }
        	  else{
        		  Copy_u8State[0]=0;
        		  LCD_enuWriteString("LED1 OFF");
        		  HC05_enuSendString("LED1 OFF\r\n");
        	  }
        	  break;
        	 case'2':
        	  RELAY_enuToggle(LED_2);
        	  if(Copy_u8State[1]==0){
        	     Copy_u8State[1]=1;
       		  LCD_enuWriteString("LED2 ON");
       		  HC05_enuSendString("LED2 ON\r\n");
        	  }
        	   else{
        	     Copy_u8State[1]=0;
       		  LCD_enuWriteString("LED2 OFF");
       		  HC05_enuSendString("LED2 OFF\r\n");
        	   }
        	          	  break;
             case'3':
           	  RELAY_enuToggle(LED_3);
           	  if(Copy_u8State[2]==0){
           		  Copy_u8State[2]=1;
        		  LCD_enuWriteString("LED3 ON");
        		  HC05_enuSendString("LED3 ON\r\n");
           	  }
           	  else{
           		  Copy_u8State[2]=0;
        		  LCD_enuWriteString("LED3 OFF");
        		  HC05_enuSendString("LED3 OFF\r\n");
           	  }
           	       break;
             case'4':
           	  RELAY_enuToggle(LED_4);
           	  if(Copy_u8State[3]==0){
           		  Copy_u8State[3]=1;
        		  LCD_enuWriteString("LED4 ON");
        		  HC05_enuSendString("LED4 ON\r\n");
           	  }
           	  else{
           		  Copy_u8State[3]=0;
        		  LCD_enuWriteString("LED4 OFF");
        		  HC05_enuSendString("LED4 OFF\r\n");
           	  }
           	  break;
             case'5':
           	  RELAY_enuToggle(LED_5);
           	  if(Copy_u8State[4]==0){
           		  Copy_u8State[4]=1;
        		  LCD_enuWriteString("LED5 ON");
        		  HC05_enuSendString("LED5 ON\r\n");
           	  }
           	  else{
           		  Copy_u8State[4]=0;
        		  LCD_enuWriteString("LED5 OFF");
        		  HC05_enuSendString("LED5 OFF\r\n");
           	  }
           	  break;

          }
          _delay_ms(500);

	}
	void DimmmerControl(u8 *Copy_u8State,u8 copy_u8Intensity){
			LCD_enuClearScreen();
			//LCD_enuWritInteger(copy_u8Intensity);
	        if(copy_u8Intensity=='0'){
	        	DIMMER_LAMP_enuSetIntensity(0);
	        	*Copy_u8State=0;
	        }
	        else {
				DIMMER_LAMP_enuInit();

			u16 intensity=copy_u8Intensity;
			intensity-=48;
			intensity*=100;
			intensity/=9;

			DIMMER_LAMP_enuSetIntensity(intensity);
		    DIMMER_LAMP_enuStart();
		    LCD_enuWriteString("DIMMER is On");
		    HC05_enuSendString("DIMMER IS ON\r\n");
		    DIMMER_LAMP_enuStart();
		    _delay_ms(500);
		    *Copy_u8State=1;
			}

		}

	void AppInit(void){
      // Num OF users
		EEPROM_enuWrite(0,0,90);
	// Admin information
		EEPROM_enuWrite('1',0,91);
		EEPROM_enuWrite('1',0,92);
		EEPROM_enuWrite('2',0,93);
		EEPROM_enuWrite('2',0,94);
    //Admin Password
		EEPROM_enuWrite('1',0,95);
		EEPROM_enuWrite('2',0,96);
		EEPROM_enuWrite('3',0,97);
		EEPROM_enuWrite('4',0,98);

    // user information
		/*
	         	EEPROM_enuWrite('1',0,0);
				EEPROM_enuWrite('2',0,1);
				EEPROM_enuWrite('3',0,2);
				EEPROM_enuWrite('4',0,3);

	// user Password
				EEPROM_enuWrite('1',0,4);
				EEPROM_enuWrite('2',0,5);
			    EEPROM_enuWrite('3',0,6);
				EEPROM_enuWrite('4',0,7);
				*/

	}


	void CheckSensor(u8 Copy_u8State)
		 {
			 if(Copy_u8State==1){
		            	u16 Temperature=0;
		           Temperature=TEMP_SENSOR_enuRead();
		            	if(Temperature>28){
		            		DC_MOTOR_enuSetDirection(CLOCKWISE);
		            		DC_MOTOR_enuSetSpeed(100);
		            		DC_MOTOR_enuStart();

		            		LCD_enuWriteString(" AC ON");
		            		HC05_enuSendString("AC MOTOR ON \r\n");


		            	}
		            	else if(Temperature<21){
		            		DC_MOTORenuStop();

		            		LCD_enuWriteString("AC OFF");
		            		HC05_enuSendString("AC OFF\r\n");
		            	}


		            }
		            else {
		            	DC_MOTORenuStop();
		            	LCD_enuWriteString(" AC Of");
		            	HC05_enuSendString("AC OFF\r\n");
		            }
//_delay_ms(1000);
	}
	void CheckDoor(u8 Copy_u8State){
              if(Copy_u8State==OPEN){
            	  LCD_enuWriteString("DOOR OPEN");
            	  HC05_enuSendString("DOOR OPEN\r\n");
              }
              else{
            	  LCD_enuWriteString("DOOR CLOSE");
            	   HC05_enuSendString("DOOR CLOSE\r\n");
              }
	}

	void CheckLeds(u8* Copy_u8State){
		LCD_enuClearScreen();
		LCD_enuWriteString("L1 L2 L3 L4 L5");
		HC05_enuSendString("LED1 LED2 LED3 LED4 LED5\r\n");
		LCD_enuGoToPosition(1,0);
       for(u8 count=0;count<5;count++){
          if(Copy_u8State[count]==1){
        	  LCD_enuWriteString("ON ");
        	  HC05_enuSendString("ON   ");
          }
          else{
        	  LCD_enuWriteString("OF ");
        	  HC05_enuSendString("OFF  ");
          }
       }
       HC05_enuSendString("\r\n");
	}
	void CheckDimmer(u8 Copy_u8State){
       if(Copy_u8State==1){
    	   LCD_enuWriteString("DIMMER ON");
    	 HC05_enuSendString("DIMMER ON \r\n");

       }
       else{
    	   LCD_enuWriteString("DIMMER OFF");
    	   HC05_enuSendString("DIMMER OFF \r\n");

       }
	}
void Reset(u8* Sensor_State, u8* Door_State, u8* Relay_State,u8* Dimmer_State){
*Sensor_State=0;
*Door_State=0;
for(u8 counter=0;counter<5;counter++){
	Relay_State[counter]=0;
	RELAY_enuOF(counter+1);
}
DIMMER_LAMP_enuStop();
*Dimmer_State=0;
DC_MOTORenuStop();
SERVO_MOTOR_enuSetPosition(CLOSE);
HC05_enuSendString("Door is Close\r\n");
HC05_enuSendString("Dc Motor is Close\r\n");
HC05_enuSendString("All Leds is OFF\r\n");
HC05_enuSendString("Dimmer Lamp is OFF\r\n");
HC05_enuSendString("Reseting System\r\n");
DeleteAll();
AppInit();
	}
void Display_System(u8*Copy_state,u8 Sensor_State, u8 Door_State, u8* Relay_State,u8 Dimmer_State){
	u8 Key_Data=KEY_NOT_PRESSED;
					KEYPAD_enuGetPressedKey(&Key_Data);
					while(Key_Data==KEY_NOT_PRESSED){
	          //      LCD_enuWriteString(" long Press");
	          //      LCD_enuGoToPosition(1,0);
	          //      LCD_enuWriteString("to start");
					KEYPAD_enuGetPressedKey(&Key_Data);
					if(Key_Data!=KEY_NOT_PRESSED)
						continue;

					    LCD_enuClearScreen();
						CheckDoor(Door_State);
						KEYPAD_enuGetPressedKey(&Key_Data);
						if(Key_Data!=KEY_NOT_PRESSED)
											continue;
						LCD_enuGoToPosition(1,0);
					    CheckDimmer(Dimmer_State);
						KEYPAD_enuGetPressedKey(&Key_Data);
						if(Key_Data!=KEY_NOT_PRESSED)
											continue;
						CheckSensor(Sensor_State);

						KEYPAD_enuGetPressedKey(&Key_Data);
						if(Key_Data!=KEY_NOT_PRESSED)
											continue;
						_delay_ms(1000);
					CheckLeds(Relay_State);
						KEYPAD_enuGetPressedKey(&Key_Data);
						if(Key_Data!=KEY_NOT_PRESSED)
											continue;
						_delay_ms(1000);
						LCD_enuClearScreen();
					}

				*Copy_state=WELCOM_PAGE;


}


