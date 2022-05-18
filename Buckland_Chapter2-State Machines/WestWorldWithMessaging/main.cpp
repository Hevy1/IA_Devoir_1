#include <fstream>
#include <time.h>
#include <thread>
#include <mutex>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "Drunkard.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

// Writing variable is a mutex used to only give access of writing in the console to one thread at a time
std::mutex writing;

// Firest creating the 3 functions that will be used for the threads
void runBob(Miner* bob) {
    bob->Update();
}

void runElsa(MinersWife* elsa) {
    elsa->Update();
}

void runJoe(Drunkard* joe) {
    joe->Update();
}


int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob, &writing);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa, &writing);

  //create the drunkard
  Drunkard* Joe = new Drunkard(ent_Drunk_Joe, &writing);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Joe);

  // Giving the link to mutex to Dispatch, because it sometimes has to display messages too
  Dispatch->SetMutex(&writing);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    // Lauching the updates of the entities thrgought their own threads
    std::thread bob(runBob, Bob);
    std::thread elsa(runElsa, Elsa);
    std::thread joe(runJoe, Joe);

    // Waiting for all the threads to end
    bob.join();
    elsa.join();
    joe.join();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete Joe;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






