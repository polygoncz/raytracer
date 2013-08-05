#include "imagebuffer.h"

#include <wx/wxprec.h>

#ifndef WX_PREC
#include <wx/wx.h>
#endif
#include <wx/dcbuffer.h>

#include "core/core.h"
#include "core/scene.h"
#include "core/renderer.h"
#include "renderers/raytracer.h"

/************************************************************************/
/* ImageBufferApp                                                       */
/************************************************************************/

BEGIN_EVENT_TABLE(ImageBufferApp, wxApp) END_EVENT_TABLE()

IMPLEMENT_APP(ImageBufferApp)

bool ImageBufferApp::OnInit()
{
	wxInitAllImageHandlers();

	frame = new MainFrame(wxPoint(200, 200), wxSize(700, 500));
	frame->Center();
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

int ImageBufferApp::OnExit()
{
	return 0;
}

void ImageBufferApp::SetStatusText(const wxString& test, int number)
{
	frame->SetStatusText(test, number);
}

/************************************************************************/
/* MainFrame                                                            */
/************************************************************************/

BEGIN_EVENT_TABLE(MainFrame, wxFrame) EVT_MENU(ID_MENU_RENDER_START, MainFrame::OnRenderStart)
EVT_MENU(ID_MENU_RENDER_PAUSE, MainFrame::OnRenderPaused)
EVT_MENU(ID_MENU_RENDER_RESUME, MainFrame::OnRenderResume)
EVT_MENU(ID_MENU_FILE_SAVE, MainFrame::OnSaveFile)
EVT_MENU(ID_MENU_FILE_OPEN, MainFrame::OnOpenFile)
EVT_MENU(ID_MENU_QUIT, MainFrame::OnQuit)
EVT_COMMAND(ID_RENDER_COMPLETED, wxEVT_RENDER, MainFrame::OnRenderCompleted)
EVT_KEY_DOWN(MainFrame::KeyShortcuts)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxPoint& pos, const wxSize& size)
		: wxFrame((wxFrame *) NULL, -1, "Raytracer Image Buffer", pos, size)
{
	wxMenu* menuFile = new wxMenu;

	menuFile->Append(ID_MENU_FILE_OPEN, "&Open...");
	menuFile->Append(ID_MENU_FILE_SAVE, "&Save...");
	menuFile->AppendSeparator();
	menuFile->Append(ID_MENU_QUIT, "&Quit");

	menuFile->Enable(menuFile->FindItem("&Save..."), false);

	wxMenu* menuRender = new wxMenu;
	menuRender->Append(ID_MENU_RENDER_START, "&Start");
	menuRender->Append(ID_MENU_RENDER_PAUSE, "&Pause");
	menuRender->Append(ID_MENU_RENDER_RESUME, "&Resume");

	menuRender->Enable(menuRender->FindItem("&Start"), true);
	menuRender->Enable(menuRender->FindItem("&Pause"), false);
	menuRender->Enable(menuRender->FindItem("&Resume"), false);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuRender, "&Render");

	SetMenuBar(menuBar);

	canvas = new RenderCanvas(this);

	CreateStatusBar();
	SetStatusText("Ready");
	wxStatusBar* statusBar = GetStatusBar();
	int widths[] =
	{ 150, 300 };
	statusBar->SetFieldsCount(2, widths);
}

void MainFrame::KeyShortcuts(wxKeyEvent& evt)
{
	if (evt.GetModifiers() == wxMOD_CONTROL)
	{
		switch (evt.GetKeyCode())
		{
		case 'r':
			this->RenderStart();
			break;
		}
	}
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void MainFrame::OnSaveFile(wxCommandEvent& event)
{
	wxString caption = "Save File";

	wxString wildcard = "BMP files (*.bmp)|*.bmp|"
			"PNG files (*.png)|*.png|"
			"JPEG files (*.jpg)|*.jpg|"
			"TIFF files (*.tiff)|*.tiff";

	wxString defaultDir = wxEmptyString;
	wxString defaultFileName = "render.bmp";

	wxFileDialog dialog(this, caption, defaultDir, defaultFileName, wildcard,
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	dialog.SetPath(filePath);

	if (dialog.ShowModal() == wxID_OK)
	{
		filePath = dialog.GetPath();

		wxImage img = canvas->GetImage();
		img.SaveFile(filePath);
	}
}

void MainFrame::OnOpenFile(wxCommandEvent& event)
{
	wxString caption = "Choose a File";

	wxString wildcard = "BMP files (*.bmp)|*.bmp|"
			"PNG files (*.png)|*.png|"
			"JPEG files (*.jpg)|*.jpg|"
			"TIFF files (*.tiff)|*.tiff";

	wxString defaultDir = wxEmptyString;
	wxString defaultFileName = wxEmptyString;

	wxFileDialog dialog(this, caption, defaultDir, defaultFileName, wildcard,
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	dialog.SetPath(filePath);

	if (dialog.ShowModal() == wxID_OK)
	{
		filePath = dialog.GetPath();

		wxImage* img = new wxImage();
		img->LoadFile(filePath);

		if (!img->IsOk())
		{
			delete img;
			wxMessageBox("Could not load file.");
		}
		else
		{
			canvas->SetImage(*img);
			wxMenu* menuFile = GetMenuBar()->GetMenu(0);
			menuFile->Enable(menuFile->FindItem("&Save..."), true);
		}
	}
}

void MainFrame::OnRenderStart(wxCommandEvent& event)
{
	this->RenderStart();
}

void MainFrame::RenderStart()
{
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(menu->FindItem("&Start"), false);
	menu->Enable(menu->FindItem("&Pause"), true);
	menu->Enable(menu->FindItem("&Resume"), false);

	canvas->renderStart();

	wxMenu* menuFile = GetMenuBar()->GetMenu(0);
	menuFile->Enable(ID_MENU_FILE_OPEN, false);
	menuFile->Enable(ID_MENU_FILE_SAVE, true);
}

void MainFrame::OnRenderCompleted(wxCommandEvent& event)
{
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(ID_MENU_RENDER_START, true);
	menu->Enable(ID_MENU_RENDER_PAUSE, false);
	menu->Enable(ID_MENU_RENDER_RESUME, false);

	wxMenu* menuFile = GetMenuBar()->GetMenu(0);
	menuFile->Enable(ID_MENU_FILE_OPEN, true);

	wxGetApp().SetStatusText("Rendering complete");
}

void MainFrame::OnRenderPaused(wxCommandEvent& event)
{
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(ID_MENU_RENDER_START, false);
	menu->Enable(ID_MENU_RENDER_PAUSE, false);
	menu->Enable(ID_MENU_RENDER_RESUME, true);

	canvas->renderPause();

	wxGetApp().SetStatusText("Rendering paused");
}

void MainFrame::OnRenderResume(wxCommandEvent& event)
{
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(ID_MENU_RENDER_START, false);
	menu->Enable(ID_MENU_RENDER_PAUSE, false);
	menu->Enable(ID_MENU_RENDER_RESUME, true);

	canvas->renderResume();

	wxGetApp().SetStatusText("Rendering...");
}

/************************************************************************/
/* Render Canvas                                                        */
/************************************************************************/

RenderCanvas::RenderCanvas(wxWindow* parent)
		: wxScrolledWindow(parent), m_image(NULL), scene(NULL), thread(NULL), timer(
		NULL), updateTimer(this, ID_RENDER_UPDATE)
{
	SetOwnBackgroundColour(wxColor(143, 144, 150));
}

RenderCanvas::~RenderCanvas(void)
{
	if (m_image != NULL) delete m_image;

	if (scene != NULL) delete scene;

	if (thread != NULL) delete thread;

	if (timer != NULL) delete timer;
}

void RenderCanvas::SetImage(wxImage& image)
{
	if (m_image != NULL) delete m_image;

	m_image = new wxBitmap(image);

	SetScrollbars(10, 10, (int) (m_image->GetWidth() / 10.0f),
			(int) (m_image->GetHeight() / 10.0f), 0, 0, true);

	Refresh();
}

wxImage RenderCanvas::GetImage()
{
	if (m_image != NULL) return m_image->ConvertToImage();

	return wxImage();
}

void RenderCanvas::OnDraw(wxDC& dc)
{
	if (m_image != NULL && m_image->IsOk()) wxBufferedDC bdc(&dc, *m_image);
}

void RenderCanvas::OnRenderCompleted(wxCommandEvent& event)
{
	thread = NULL;

	if (scene != NULL)
	{
		delete scene;
		scene = NULL;
	}

	if (timer != NULL)
	{
		long interval = timer->Time();

		wxTimeSpan timeElapsed(0, 0, 0, interval);
		wxString timeString = timeElapsed.Format("Elapsed time: %H:%M:%S:%l");
		wxGetApp().SetStatusText(timeString, 1);

		delete timer;
		timer = NULL;
	}
}

void RenderCanvas::OnNewPixel(wxCommandEvent& event)
{
	wxClientDC cdc(this);
	DoPrepareDC(cdc);
	wxBufferedDC bufferedDC(&cdc, *m_image);

	std::vector<RenderPixel*> *pixelsUpdate =
			(std::vector<RenderPixel*> *) event.GetClientData();

	for (std::vector<RenderPixel*>::iterator itr = pixelsUpdate->begin();
			itr != pixelsUpdate->end(); itr++)
	{
		RenderPixel* pixel = *itr;

		wxPen pen(wxColor(pixel->r, pixel->g, pixel->b));
		bufferedDC.SetPen(pen);
		bufferedDC.DrawPoint(pixel->x, pixel->y);

		pixelsRendered++;
		delete pixel;
	}

	pixelsUpdate->clear();
	delete pixelsUpdate;
}

void RenderCanvas::renderPause(void)
{
	if (thread != NULL) thread->Pause();

	updateTimer.Stop();

	if (timer != NULL) timer->Pause();
}

void RenderCanvas::renderResume(void)
{
	if (thread != NULL) thread->Resume();

	updateTimer.Start();

	if (timer != NULL) timer->Resume();
}

void RenderCanvas::OnTimerUpdate(wxTimerEvent& event)
{
	if (timer == NULL) return;

	//procenta
	float completed = (float) pixelsRendered / (float) pixelsToRender;
	wxString progressString = wxString::Format("Rendering...%d%%",
			(int) (completed * 100));
	wxGetApp().SetStatusText(progressString, 0);

	long interval = timer->Time();

	wxTimeSpan timeElapsed(0, 0, 0, interval);

	//zbyva
	float remaining = 1.0f - completed;
	long msecRemain = (long) (((double) interval / (completed * 100)) * 100
			* remaining);
	wxTimeSpan timeRemaining(0, 0, 0, msecRemain);

	wxString timeRemainString = timeRemaining.Format(" / ETA %H:%M:%S");
	wxString timeString = timeElapsed.Format("Elapsed time: %H:%M:%S");

	if (msecRemain >= 0)
	{
		wxGetApp().SetStatusText(timeString + timeRemainString, 1);
	}
	else
	{
		wxGetApp().SetStatusText(timeString, 1);
	}
}

void RenderCanvas::renderStart(void)
{
	wxGetApp().SetStatusText("Building...");
	scene = new Scene();
	scene->Build();

	renderer = new Raytracer(scene, thread);
	wxGetApp().SetStatusText("Rendering...");

	pixelsRendered = 0;
	pixelsToRender = scene->film->width * scene->film->height;

	wxBitmap bitmap(scene->film->width, scene->film->height, -1);
	wxMemoryDC dc;
	dc.SelectObject(bitmap);
	dc.SetBackground(*wxGREY_BRUSH);
	dc.Clear();

	dc.SelectObject(wxNullBitmap);

	wxImage temp = bitmap.ConvertToImage();
	SetImage(temp);

	updateTimer.Start(250);

	timer = new wxStopWatch();

	thread = new RenderThread(this, renderer);
	thread->Create();
	renderer->SetPixelArea(thread);
	thread->SetPriority(20);
	thread->Run();
}

/************************************************************************/
/* RenderPixel                                                          */
/************************************************************************/

RenderPixel::RenderPixel(int _x, int _y, int _r, int _g, int _b)
		: x(_x), y(_y), r(_r), g(_g), b(_b)
{
}

/************************************************************************/
/* RenderThread                                                         */
/************************************************************************/

DEFINE_EVENT_TYPE(wxEVT_RENDER)

BEGIN_EVENT_TABLE(RenderCanvas, wxScrolledWindow) EVT_COMMAND(ID_RENDER_NEWPIXEL, wxEVT_RENDER, RenderCanvas::OnNewPixel)
EVT_COMMAND(ID_RENDER_COMPLETED, wxEVT_RENDER, RenderCanvas::OnRenderCompleted)
EVT_TIMER(ID_RENDER_UPDATE, RenderCanvas::OnTimerUpdate)
END_EVENT_TABLE()

void RenderThread::setPixel(int x, int y, int r, int g, int b)
{
	pixels.push_back(new RenderPixel(x, y, r, g, b));

	if (timer->Time() - lastUpdateTime > 40) NotifyCanvas();

	TestDestroy();
}

void RenderThread::NotifyCanvas()
{
	lastUpdateTime = timer->Time();

	std::vector<RenderPixel*> *pixelsUpdate = new std::vector<RenderPixel*>(
			pixels);
	pixels.clear();

	wxCommandEvent event(wxEVT_RENDER, ID_RENDER_NEWPIXEL);
	event.SetClientData(pixelsUpdate);
	canvas->GetEventHandler()->AddPendingEvent(event);
}

void RenderThread::OnExit()
{
	NotifyCanvas();

	wxCommandEvent event(wxEVT_RENDER, ID_RENDER_COMPLETED);
	canvas->GetEventHandler()->AddPendingEvent(event);
	canvas->GetParent()->GetEventHandler()->AddPendingEvent(event);
}

void* RenderThread::Entry()
{
	lastUpdateTime = 0;
	timer = new wxStopWatch();

	renderer->Render();

	return NULL;
}
