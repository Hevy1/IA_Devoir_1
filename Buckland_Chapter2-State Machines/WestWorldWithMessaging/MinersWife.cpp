#include "MinersWife.h"

bool MinersWife::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void MinersWife::Update()
{
  m_pStateMachine->Update();
}

// Print and PrintTelegram are generic functions called each time the agents want to display a message on the console
// Those actions were standardised in order to easily add the mutex lock and unlock to the print actions

void MinersWife::Print(std::string val)
{
    m_mutex->lock();

    SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout << std::endl;
    std::cout << val;

    m_mutex->unlock();
}

void MinersWife::PrintTelegram(std::string val)
{
    m_mutex->lock();

    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << std::endl;
    std::cout << val;

    m_mutex->unlock();
}