#ifndef DRUNKARD_OWNED_STATES_H
#define DRUNKARD_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   DrunkardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Drunkard class.
//          Note that a global state has not been implemented.
//
//  Author: Jorick Célarier, Evan Weisse 2022
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Drunkard;
struct Telegram;

//------------------------------------------------------------------------
//
//  In this state the drunkard will walk to the saloon and get drunk. If 
//  the drunkard is enough drunk, he'll change state to HomeSweetHome. If
//  a miner comes to the saloon, he'll provocate him. If he's too drunk, 
//  he'll lose the fight, if not, he'll send him home and carry on drinking.
//------------------------------------------------------------------------
class EnterSaloonAndGetDrunk : public State<Drunkard>
{
private:

	EnterSaloonAndGetDrunk() {}

	//copy ctor and assignment should be private
	EnterSaloonAndGetDrunk(const EnterSaloonAndGetDrunk&);
	EnterSaloonAndGetDrunk& operator=(const EnterSaloonAndGetDrunk&);

public:

	//this is a singleton
	static EnterSaloonAndGetDrunk* Instance();

	virtual void Enter(Drunkard* miner);

	virtual void Execute(Drunkard* miner);

	virtual void Exit(Drunkard* miner);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);

};


//------------------------------------------------------------------------
//
//  In this state the drunkard will go back home and rest in order to . If 
//  he gets sober, he'll go back to the saloon.
//------------------------------------------------------------------------
class HomeSweetHome : public State<Drunkard>
{
private:

	HomeSweetHome() {}

	//copy ctor and assignment should be private
	HomeSweetHome(const HomeSweetHome&);
	HomeSweetHome& operator=(const HomeSweetHome&);

public:

	//this is a singleton
	static HomeSweetHome* Instance();

	virtual void Enter(Drunkard* miner);

	virtual void Execute(Drunkard* miner);

	virtual void Exit(Drunkard* miner);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);

};


//------------------------------------------------------------------------
//
//  In this state the drunkard will be sent to the hospital. After resting,
//  he'll go back to the saloon.
//------------------------------------------------------------------------
class GoToHospital : public State<Drunkard>
{
private:

	GoToHospital() {}

	//copy ctor and assignment should be private
	GoToHospital(const GoToHospital&);
	GoToHospital& operator=(const GoToHospital&);

public:

	//this is a singleton
	static GoToHospital* Instance();

	virtual void Enter(Drunkard* miner);

	virtual void Execute(Drunkard* miner);

	virtual void Exit(Drunkard* miner);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);

};


#endif