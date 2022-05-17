#include <fstream>
#include <time.h>
#include <thread>
#include <mutex>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;
std::mutex writing;

void runBob(Miner* bob) {
    bob->Update();
}

void runElsa(MinersWife* elsa) {
    elsa->Update();
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

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);

  Dispatch->SetMutex(&writing);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Bob->Update();

    std::thread bob(runBob, Bob);
    std::thread elsa(runElsa, Elsa);

    bob.join();
    elsa.join();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete Bob;
  delete Elsa;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






