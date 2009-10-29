#include <stdio.h>
#include "CFx.h"

CFx::CFx(FxType fxType, CFxManager* fxManager)
{
	m_fxType = fxType;
	m_enabled = false;
	m_fxManager = fxManager;
	m_callback = NULL;
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

void CFx::Reset()
{
}

void CFx::UpdateVBlank()
{
}

void CFx::UpdateHBlank()
{
}
