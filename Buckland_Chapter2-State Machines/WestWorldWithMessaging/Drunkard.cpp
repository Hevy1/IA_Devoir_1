#include "Drunkard.h"

bool Drunkard::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Drunkard::Update()
{
  m_pStateMachine->Update();
}


// the drunkard judges if after m_iDrunkness drinks, he's enough drunk

bool Drunkard::Drunk()const
{
	if (RandInt(1, 343) < m_iDrunkness * m_iDrunkness * m_iDrunkness)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Drunkard::Print(std::string val)
{
    m_mutex->lock();

    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << std::endl;
    std::cout << val;

    m_mutex->unlock();
}

void Drunkard::PrintTelegram(std::string val)
{
    m_mutex->lock();

    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << std::endl;
    std::cout << val;

    m_mutex->unlock();
}