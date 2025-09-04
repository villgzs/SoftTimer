#include "SoftTimer.h"

  // TimerType is micros() or millis() 
  // ~~ Example: 
  // SoftTimer T1(&millis);
  // SoftTimer T2(&micros);
  
  // Constructor
  // Timer is in stop state at the start
  SoftTimer::SoftTimer( unsigned long (*TimerType)() ) {
    TimerIs = TimerType; 
    TimerStop();  
  }

  // Timer start for a period 
  // Timer ellapsed moment at now+period
  // - Checking the actual state with TimerRun()
  void SoftTimer::TimerStart( unsigned long interval ) {
    CurrentTime = TimerIs() ;
    StartTime = CurrentTime;
    Timerinterval = interval; 
    done = false;     
  }

  // Timer start for a period ( period will begin from the last end moment )
  // It is useful if you want precise average periods. Restart if it have just ellapsed.
  // - Checking the actual state with TimerRun()
  void SoftTimer::TimerReStart( unsigned long interval ) {
    CurrentTime = TimerIs();
    StartTime += Timerinterval;
    Timerinterval = interval; 
    done = false;     
  }

  void SoftTimer::TimerStop( void ) {
    CurrentTime = TimerIs();
    StartTime = CurrentTime;
    Timerinterval = 0;      
    done = true; // ??? true or false is better ??? 
    // -> TimerRun() gives false - OK

  }

  bool SoftTimer::TimerRun( void ) {

    CurrentTime = TimerIs();
    done = done || ( (CurrentTime-StartTime) >= Timerinterval );

    return( !done );
  }     

   bool SoftTimer::TimerDone( void ) {

    bool justdone;

    CurrentTime = TimerIs();
    justdone = !done &&  ( (CurrentTime-StartTime) >= Timerinterval );
    done = done || justdone ;

    return( justdone );
  }

  bool SoftTimer::TimerEllapsed( void ) {

    // return( (done != (TimerIs() - StartTime) >= Timerinterval ) ); orig - till 2025-09SEP03
    return( done != ( (TimerIs() - StartTime) >= Timerinterval ) );
    // checking .... brace position
  }  

  void SoftTimer::TimerSync( unsigned long SyncValue ) {
    CurrentTime = SyncValue ;
    StartTime = CurrentTime;
    Timerinterval = 0;      
    done = true; // ??? true or false is better ???
  }
