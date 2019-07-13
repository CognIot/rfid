
/* ================================================================== */
/*                                                                    */
/*   Filename.c                                                       */
/*   (c) 2012 Author                                                  */
/*                                                                    */
/*   Description                                                      */
/*                                                                    */
/* ================================================================== */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>


#include <wiringPi.h>
#include <wiringSerial.h>
#include "../libcogniot-rfid/include/CognIoT-RFID.h"


// set for GPIO Pin to use based on the jumper connection
#define GPIO_PIN 1 

int main()
{

	//int sPort = 0;		
	int *fd = calloc(1, sizeof(int));	// Pointer to serial port
	
	char *result= calloc (1, sizeof(char));
	
	int	length = 0;
	
	strcpy(result, "");
	length = strlen(result);
	
	 printf("reader build "BUILD_VERSION" (built "BUILD_DATE")\n");
	 
	
	
	if (wiringPiSetup () == -1){
		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		return 1 ;
	  }

	pinMode(GPIO_PIN,INPUT);	// GPIO_PIN  pin to identify the "CTS" 
	
	if (( *fd = serialOpen ("/dev/serial0", 9600)) < 0)  // Try to open a connection to the serial port
		{
			fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
			return 1 ;
		}
	
	printf("BEFORE CALL TO GetCmdResult\n");
	printf("==============================================\n");
	printf("Pointer 'result' in main  : %p\n", &result);
	printf("Device Response in Main() : %s\n", result);
	printf("RESPONSE LENGTH           : %d\n", length);
	printf("\n\n");
	
	WaitForCTS(fd, GPIO_PIN);
	GetCmdResult(fd, 0x7a, &result);	// Send 'z' to the PirFix
	
	length = strlen(result);

	printf("AFTER CALL TO GetCmdResult\n");
	printf("==============================================\n");
	printf("Pointer 'result' in main  : %p\n", &result);
	printf("Device Response in Main() : %s\n", result);
	printf("RESPONSE LENGTH           : %d\n", length);
	printf("\n");
	
	
	WaitForCTS(fd, GPIO_PIN);
	SetTagMode(fd, TAGMODE_c);
	
	WaitForCTS(fd, GPIO_PIN);
	GetCmdResult(fd, 0x7a, &result);	// Send 'z' to the PirFix
	
	length = strlen(result);

	printf("AFTER CALL TO GetCmdResult\n");
	printf("==============================================\n");
	printf("Pointer 'result' in main  : %p\n", &result);
	printf("Device Response in Main() : %s\n", result);
	printf("RESPONSE LENGTH           : %d\n", length);
	printf("\n");



    serialClose( *fd);
    
    free(fd);
    free(result);
    
    

	return 0;
	
}
