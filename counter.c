/*
 * counter.c:
 *    Wait for Interrupt test program - ISR method
 */
                 
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
                 
// A 'key' which we can lock and unlock - values are 0 through 3
//    This is interpreted internally as a pthread_mutex by wiringPi
//    which is hiding some of that to make life simple.

#define    COUNT_KEY    0

// What wPi input are we using?

#define    BUTTON_PIN    10

// Debounce time in mS

#define    DEBOUNCE_TIME    100

// globalCounter:
//    Global variable to count interrupts
//    Should be declared volatile to make sure the compiler doesn't cache it.

static volatile int globalCounter = 0;
         
         
/*
* myInterrupt:
*********************************************************************************
*/
         
void myInterrupt (void)
{
//    piLock (COUNT_KEY) ;
    ++globalCounter;
//    piUnlock (COUNT_KEY) ;
}
         
         
/*
*********************************************************************************
* main
*********************************************************************************
*/
         
int main (void)
{
    int gotOne = 0 ;
    int myCounter = 0 ;

    wiringPiSetup () ;

    wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &myInterrupt) ;

    for (;;)
    {
        gotOne = 0 ;
        printf ("Waiting ... ") ; fflush (stdout) ;
    
        for (;;)
        {
            if (globalCounter != myCounter)
            {
                printf (" Counter: %5d\n", globalCounter ) ;
                myCounter = globalCounter ;
                ++gotOne ;
            }
            
            if (gotOne != 0)
                break ;
        }
    }

    return 0 ;
}
