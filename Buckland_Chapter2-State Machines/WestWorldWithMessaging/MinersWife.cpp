#include "MinersWife.h"

bool MinersWife::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void MinersWife::Update()
{
  m_pStateMachine->Update();
}

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