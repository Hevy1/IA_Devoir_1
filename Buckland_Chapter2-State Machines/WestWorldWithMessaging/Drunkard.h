#ifndef DRUNKARD_H
#define DRUNKARD_H
//------------------------------------------------------------------------
//
//  Name:   Drunkard.h
//
//  Desc:   A class defining a drunkard.
//
//  Author: Jorick Célarier, Evan Weisse 2022
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>
#include <mutex>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "DrunkardOwnedStates.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

template <class entity_type> class State;
struct Telegram;


// above this value a drunkard is too drunk, but finlly not use (check : bool Drunk()const)
//const int Drunkibility = 7;


class Drunkard : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Drunkard>*  m_pStateMachine;
  
  location_type         m_Location;

  //the higher the value, the drunkier the drunkard
  int                   m_iDrunkness;

  std::mutex* m_mutex;

public:

  Drunkard(int id, std::mutex* mutex):m_Location(home),
                   m_iDrunkness(0),
                   BaseGameEntity(id)

  {
    //set up state machine
    m_pStateMachine = new StateMachine<Drunkard>(this);
    
    m_pStateMachine->SetCurrentState(HomeSweetHome::Instance());

    m_mutex = mutex;


    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE DRUNKARD */
  }

  ~Drunkard(){delete m_pStateMachine;}

  //this must be implemented
  void Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  
  StateMachine<Drunkard>* GetFSM()const{return m_pStateMachine;}


  
  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}
 
  void          DecreaseAlcohol() { m_iDrunkness -= 1; }
  void          IncreaseAlcohol() { m_iDrunkness += 1; }

  bool          Drunk()const;
  bool          Sober()const { return m_iDrunkness <= 0; }

  int           GetDrunkness() { return m_iDrunkness; }

  void          Print(std::string val);
  void          PrintTelegram(std::string val);

};



#endif
