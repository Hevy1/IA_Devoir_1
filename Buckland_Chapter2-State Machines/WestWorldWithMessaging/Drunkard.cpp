#include "Drunkard.h"

bool Drunkard::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Drunkard::Update()
{
  SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
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

