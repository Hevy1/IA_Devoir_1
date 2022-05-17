#include "DrunkardOwnedStates.h"
#include "fsm/State.h"
#include "Drunkard.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//------------------------------------------------------------------------methods for EnterSaloonAndGetDrunk
EnterSaloonAndGetDrunk* EnterSaloonAndGetDrunk::Instance()
{
    static EnterSaloonAndGetDrunk instance;

    return &instance;
}


void EnterSaloonAndGetDrunk::Enter(Drunkard* pDrunkard)
{
    //if the Drunkard is not already located at the saloon, he must
    //change location to the saloon
    if (pDrunkard->Location() != saloon)
    {
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "It's time to get drunk !";

        pDrunkard->ChangeLocation(saloon);
    }
}


void EnterSaloonAndGetDrunk::Execute(Drunkard* pDrunkard)
{
    //Now the drunkard is at the saloon he drinks until he is too drunk.
    
    pDrunkard->IncreaseAlcohol();

    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Good soup !"; //pourquoi pas faire un switch pour qu'il dise d'autres trucs

    if (pDrunkard->Drunk())
    {
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Time to go to home !";
        pDrunkard->GetFSM()->ChangeState(HomeSweetHome::Instance());
    }
    else
    {
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Another one !";
    }

}


void EnterSaloonAndGetDrunk::Exit(Drunkard* pDrunkard)
{
    
}


bool EnterSaloonAndGetDrunk::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    // if a miner goes in the saloon, the drunkard will provocate him
    switch (msg.Msg)
    {
    case Msg_BobIsInTheSaloon:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) <<
            ": Hey you, Imma kick yo ass !";

        // if the drunkard is not enough drunk, he'll win the fight and continue to drink
        if (pDrunkard->GetDrunkness() < 3)
        {
            Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                      pDrunkard->ID(),
                                      ent_Miner_Bob,
                                      Msg_DrunkardWin,
                                      NO_ADDITIONAL_INFO);
        }
        // if the drunkard is too drunk, he'll lose and send to the hospital
        else
        {
            Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                      pDrunkard->ID(),
                                      ent_Miner_Bob,
                                      Msg_BobWin,
                                      NO_ADDITIONAL_INFO);

            pDrunkard->GetFSM()->ChangeState(GoToHospital::Instance());

        }
        
    }

    return true;

    }//end switch

    return false;
}


//------------------------------------------------------------------------methods for HomeSweetHome
HomeSweetHome* HomeSweetHome::Instance()
{
    static HomeSweetHome instance;

    return &instance;
}


void HomeSweetHome::Enter(Drunkard* pDrunkard)
{
    //if the Drunkard is not already located at home, he must
    //change location to home
    if (pDrunkard->Location() != home)
    {
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Imma go to bed !";

        pDrunkard->ChangeLocation(home);
    }
}


void HomeSweetHome::Execute(Drunkard* pDrunkard)
{
    // the drunkard will decrease his drunkness.
    pDrunkard->DecreaseAlcohol();

    // 
    if (RandFloat() < 0.33 && pDrunkard->GetDrunkness()>0)
    {
        pDrunkard->DecreaseAlcohol();
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Imma gonna throw up !";

    }
    else
    {
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "ZZZZ...";
    }

    
    
    
    // when the drunkard is sober, he'll return to the saloon
    if (pDrunkard->Sober())
    {
        pDrunkard->GetFSM()->ChangeState(EnterSaloonAndGetDrunk::Instance());
    }

}


void HomeSweetHome::Exit(Drunkard* pDrunkard)
{
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
        << "I'm a lil' thirsty !";
}


bool HomeSweetHome::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}


//------------------------------------------------------------------------methods for GoToHospital
GoToHospital* GoToHospital::Instance()
{
    static GoToHospital instance;

    return &instance;
}


void GoToHospital::Enter(Drunkard* pDrunkard)
{
    //if the Drunkard is not already located at the hospital, he must
    //change location to the hospital
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    if (pDrunkard->Location() != hospital)
    {
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << " is sent to the hospital.";

        pDrunkard->ChangeLocation(hospital);
    }
}


void GoToHospital::Execute(Drunkard* pDrunkard)
{
    pDrunkard->DecreaseAlcohol();

    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << " is resting.";

    if (pDrunkard->Sober() || RandFloat() < 0.33)
    {
        pDrunkard->GetFSM()->ChangeState(EnterSaloonAndGetDrunk::Instance());

    }



}


void GoToHospital::Exit(Drunkard* pDrunkard)
{
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
        << "It's all good, I now go back to the saloon";
}


bool GoToHospital::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}