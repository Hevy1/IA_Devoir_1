#include "Miner.h"

bool Miner::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Miner::Update()
{
  m_iThirst += 1;
  
  m_pStateMachine->Update();
}



void Miner::AddToGoldCarried(const int val)
{
  m_iGoldCarried += val;

  if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

void Miner::AddToWealth(const int val)
{
  m_iMoneyInBank += val;

  if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

bool Miner::Thirsty()const
{
  if (m_iThirst >= ThirstLevel){return true;}

  return false;
}

bool Miner::Fatigued()const
{
  if (m_iFatigue > TirednessThreshold)
  {
    return true;
  }

  return false;
}

// Print and PrintTelegram are generic functions called each time the agents want to display a message on the console
// Those actions were standardised in order to easily add the mutex lock and unlock to the print actions

void Miner::Print(std::string val)
{
    m_mutex->lock();

    SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cout << std::endl;
    std::cout << val;

    m_mutex->unlock();
}

void Miner::PrintTelegram(std::string val)
{
    m_mutex->lock();

    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << std::endl;
    std::cout << val;

    m_mutex->unlock();
}