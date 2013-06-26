#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <vector>

class MainFrame;
class RenderCanvas;
class RenderThread;
class RenderPixel;
class Scene;

class ImageBufferApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();
    virtual void SetStatusText(const wxString& test, int number = 0);

private:
    MainFrame* frame;
    DECLARE_EVENT_TABLE()
};

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxPoint& pos, const wxSize& size);

    //Event handles
    void OnQuit(wxCommandEvent& event);
    void OnOpenFile(wxCommandEvent& event);
    void OnSaveFile(wxCommandEvent& event);
    void OnRenderStart(wxCommandEvent& event);
    void OnRenderCompleted(wxCommandEvent& event);
    void OnRenderPaused(wxCommandEvent& event);
    void OnRenderResume(wxCommandEvent& event);

private:
    RenderCanvas* canvas;
    wxString filePath;
    DECLARE_EVENT_TABLE()
};

enum
{
    ID_MENU_RENDER_START,
    ID_MENU_RENDER_PAUSE,
    ID_MENU_RENDER_RESUME,
    ID_MENU_FILE_OPEN,
    ID_MENU_FILE_SAVE,
    ID_MENU_QUIT = 100
};

class RenderCanvas : public wxScrolledWindow
{
public:
    RenderCanvas(wxWindow* parent);
    virtual ~RenderCanvas(void);

    void SetImage(wxImage& image);
    wxImage GetImage(void);

    virtual void OnDraw(wxDC& dc);
    void renderStart(void);
    void renderPause(void);
    void renderResume(void);

    void OnRenderCompleted(wxCommandEvent& event);
    void OnTimerUpdate(wxTimerEvent& event);
    void OnNewPixel(wxCommandEvent& event);

protected:
    wxBitmap* m_image;
    Scene* scene;

private:
    RenderThread* thread;
    wxStopWatch* timer;
    long pixelsRendered;
    long pixelsToRender;
    wxTimer updateTimer;

    DECLARE_EVENT_TABLE()
};

class RenderPixel
{
public:
    RenderPixel(int _x, int _y, int _r, int _g, int _b);

public:
    int x;
    int y;
    int r;
    int g;
    int b;
};

DECLARE_EVENT_TYPE(wxEVT_RENDER, -1)
#define ID_RENDER_COMPLETED 100
#define ID_RENDER_NEWPIXEL 101
#define ID_RENDER_UPDATE 102

class RenderThread : public wxThread
{
public:
    RenderThread(RenderCanvas* c, Scene* s) : wxThread(), scene(s), canvas(c) {}
    virtual void *Entry();
    virtual void OnExit();
    virtual void setPixel(int x, int y, int r, int g, int b);

private:
    void NotifyCanvas();
    Scene* scene;
    RenderCanvas* canvas;

    std::vector<RenderPixel*> pixels;
    wxStopWatch* timer;
    long lastUpdateTime;
};