#include "CFx.h"

CFx::CFx(FxType fxType, CFxManager* fxManager)
{
	m_fxType = fxType;
	m_enabled = false;
	m_fxManager = fxManager;
}

CFx::~CFx()
{
}

void CFx::Initialize()
{
}

void CFx::Shutdown()
{
}

void CFx::UpdateVBlank()
{
}

void CFx::UpdateHBlank()
{
}
