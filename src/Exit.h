#ifndef EXIT_H
#define EXIT_H

#include "Command.h"
#include <stdlib.h>

class Exit : public Command { 

   public:
      Exit(){};
      int execute(){
         
          while(true){
             exit(0);
          }
          return 0;
      }

};

#endif

