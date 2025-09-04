#ifndef SOFTTIMER_H
#define SOFTTIMER_H

class SoftTimer {

  unsigned long CurrentTime;
  unsigned long StartTime,Timerinterval;
  unsigned long (*TimerIs)() ;
  bool          done;
  
public:

  // Constructor
  // - Checking the actual state with TimerRun() or TimerDone()
  // - use ( &micros ) or ( &millis )
  SoftTimer( unsigned long (*)() ) ;

  // Timer start for a period 
  // Timer ellapsed at now+period
  // - Checking the actual state with TimerRun() or TimerDone()
  void TimerStart( unsigned long  ) ;

  // Timer start for a period ( period will begin from the last end moment )
  // It is useful if you want precise average periods. Restart if it have just ellapsed.
  // - Checking the actual state with TimerRun() or TimerDone()
  void TimerReStart( unsigned long  ) ;
  
  // Stopping the timer by moving start moment to the current time. Timer intervall will be zero after the call and done will reset.
  // - Checking the actual state with TimerRun() or TimerDone()
  void TimerStop( void ) ;

  // It checks periodically if the time period is ellapsed from the last start. Update Current time and done.
  // If gives false after the time period ellapsed at every call
  // - Other way of checking is TimerDone(). That gives true for one time after period ellapsed
  // - You can use any places of the program.
  bool TimerRun( void ) ;

  // It checks periodically if the time period is ellapsed from the last start. Update Current time and done.
  // TRUE only if it just ellapsed.
  // - Other way of checking is TimerRun() and TimerEllapsed().
  // - Using it cerfully! One time in a loop! Not more! Not working parallel with TimerRun() nor TimerEllapsed()! 
  bool TimerDone( void ) ;

  // It checks periodically if the time period is ellapsed from the last start.
  // TRUE if ellapsed. It is working parelell with TimerDone(). Other checking methods alter done bit.
  // - This function does not make modification on members variable. (Others do.)
  bool TimerEllapsed( void ) ;

  // Similar to TimerStop() - This routine moves the StartTime to a sync position. Timer will be in STOP state.
  // More timer can work parallel after this syncronisation. Use it in setup() procedure and start with ReStart();
  void TimerSync( unsigned long SyncValue ) ;
};

#endif
