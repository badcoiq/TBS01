/*
BSD 2-Clause License

Copyright (c) 2024, badcoiq
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "main.h"

BQ_LINK_LIBRARY("badcoiq");

int main(int argc, char* argv[])
{
	Game game;
	if (game.Init())
		game.Run();

	return EXIT_SUCCESS;
}

void WindowCallback::OnSize(bqWindow* w)
{
	Game* app = (Game*)w->GetUserData();
	if (app)
	{
		app->m_gs->OnWindowSize();
		app->m_gs->SetViewport(0, 0, (uint32_t)w->GetCurrentSize()->x, (uint32_t)w->GetCurrentSize()->y);
		app->m_gs->SetScissorRect(bqVec4f(0.f, 0.f, (float)w->GetCurrentSize()->x, (float)w->GetCurrentSize()->y));
	}
}

void WindowCallback::OnClose(bqWindow* w)
{
	Game* app = (Game*)w->GetUserData();
	if (app)
	{
		w->SetVisible(false);
		app->Quit();
	}
}

Game::Game()
{
}

Game::~Game()
{
}


bool Game::Init()
{
	bqFramework::Start(&m_frameworkCallback);
	m_dt = bqFramework::GetDeltaTime();
	m_windowCallback.SetUserData(this);
	m_window = bqFramework::CreateSystemWindow(&m_windowCallback);
	if (m_window && bqFramework::GetGSNum())
	{
		m_window->SetPositionAndSize(10, 10, 800, 600);
		m_window->SetVisible(true);
		m_window->SetUserData(this);
	}
	else
	{
		APP_PRINT_ERROR;
		return false;
	}

	m_gs = bqFramework::CreateGS(bqFramework::GetGSUID(0));
	if (!m_gs)
	{
		APP_PRINT_ERROR;
		return false;
	}

	if (!m_gs->Init(m_window, 0))
	{
		APP_PRINT_ERROR;
		return false;
	}

	return true;
}

void Game::Run()
{
	while (m_run)
	{
		bqFramework::Update();
	}
}

void Game::OnDraw()
{
}

