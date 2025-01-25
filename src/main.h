/*
BSD 2-Clause License

Copyright (c) 2025, badcoiq
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
#pragma once
#ifndef _main_H_
#define _main_H_

#include "badcoiq.h"
#include "badcoiq/input/bqInput.h"
#include "badcoiq/gs/bqGS.h"
#include "badcoiq/gs/bqMaterial.h"
#include "badcoiq/common/bqImage.h"
#include "badcoiq/common/bqImageLoader.h"
#include "badcoiq/gs/bqTexture.h"
#include "badcoiq/scene/bqCamera.h"
#include "badcoiq/geometry/bqMeshCreator.h"
#include "badcoiq/containers/bqArray.h"
#include "badcoiq/archive/bqArchive.h"
#include "badcoiq/GUI/bqGUI.h"
#include "badcoiq/system/bqWindow.h"

class FrameworkCallback;
class WindowCallback; 
class GUIDrawTextCallback;

class Game
{
	friend class WindowCallback;

	bqString m_drawingText;

	FrameworkCallback* m_frameworkCallback = 0;
	WindowCallback* m_windowCallback = 0;
	GUIDrawTextCallback* m_textDrawCallback = 0;
	bool m_isRun = true;
	
	bqWindow* m_window = 0;

	bqGS* m_gs = 0;
	bqInputData* m_inputData = 0;
public:
	Game();
	~Game();
	BQ_PLACEMENT_ALLOCATOR(Game);

	bool Init();
	void Run();
	void Quit() { m_isRun = false; }

	bqGS* GetGS() { return m_gs; }
	bqWindow* GetWindow() { return m_window; }
	GUIDrawTextCallback* GetTextDrawCallback() { return m_textDrawCallback; }

	void OnDraw();
	
	float* m_dt = 0;

};

class FrameworkCallback : public bqFrameworkCallback
{
public:
	FrameworkCallback() {}
	virtual ~FrameworkCallback() {}
	BQ_PLACEMENT_ALLOCATOR(FrameworkCallback);
	
	virtual void OnMessage() override
	{
	}
};

class WindowCallback : public bqWindowCallback
{
public:
	WindowCallback() {}
	virtual ~WindowCallback() {}
	BQ_PLACEMENT_ALLOCATOR(WindowCallback);

	virtual void OnSizing(bqWindow* w) override 
	{
	}

	virtual void OnSize(bqWindow* w) override
	{
		Game* app = (Game*)w->GetUserData();
		if (app)
		{
			app->m_gs->OnWindowSize();
			app->m_gs->SetViewport(0, 0, (uint32_t)w->GetCurrentSize()->x, (uint32_t)w->GetCurrentSize()->y);
			app->m_gs->SetScissorRect(bqVec4f(0.f, 0.f, (float)w->GetCurrentSize()->x, (float)w->GetCurrentSize()->y));
		}
	}

	virtual void OnClose(bqWindow* w) override 
	{
		Game* app = (Game*)w->GetUserData();
		if (app)
		{
			w->SetVisible(false);
			app->Quit();
		}
	}
};

class GUIDrawTextCallback : public bqGUIDrawTextCallback
{
public:
	GUIDrawTextCallback(bqGUIFont* f):m_font(f) {}
	virtual ~GUIDrawTextCallback() {}
	BQ_PLACEMENT_ALLOCATOR(GUIDrawTextCallback);

	virtual bqGUIFont* OnFont(/*uint32_t reason,*/ char32_t c) final
	{
		return m_font;
	}
	virtual bqColor* OnColor(/*uint32_t reason, */char32_t c) final
	{
		/*switch (reason)
		{
		case bqGUIDrawTextCallback::Reason_default:
			return m_curColor;
		case bqGUIDrawTextCallback::Reason_mouseAbove:
			return &m_colorYellow;
		}*/
		return m_curColor;
	}

	bqGUIFont* m_font = 0;
	bqColor m_colorWhite = bq::ColorWhite;
	bqColor m_colorRed = bq::ColorRed;
	bqColor m_colorYellow = bq::ColorGold;
	bqColor* m_curColor = &m_colorYellow;
};


#endif
