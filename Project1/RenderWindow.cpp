#include "WindowContainer.h"


bool RenderWindow::Initialize(WindowContainer* pWindowContainer,
    HINSTANCE hInstance, std::string window_title,
    std::string window_class, int width, int height)
{
    this->hinstance = hInstance;
    this->width = width;
    this->height = height;

    this->window_title = window_title;
    this->window_title_wide = StringConverter::StringToWide(this->window_title);
    this->window_class = window_class;
    this->window_class_wide = StringConverter::StringToWide(this->window_class);

    this->RegisterWindowClass();

    this->handle = CreateWindowEx(
        0,
        this->window_class_wide.c_str(),
        this->window_title_wide.c_str(),
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        0,
        0,
        this->width,
        this->height,
        NULL,
        NULL,
        this->hinstance,
        pWindowContainer //param to create window
    );

    if (this->handle == NULL)
    {
        ErrorLogger::Log(GetLastError(),
            "CreateWindowEx Failed for window: " + this->window_title);
        return false;
    }

    ShowWindow(this->handle, SW_SHOW);
    SetForegroundWindow(this->handle);
    SetFocus(this->handle);

    return true;
}


RenderWindow::~RenderWindow()
{
    if (this->handle != NULL)
    {
        UnregisterClass(this->window_class_wide.c_str(), this->hinstance);
        DestroyWindow(handle);
    }
}


LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg,
    WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        //All other messages
    case WM_CLOSE:
    {
        DestroyWindow(hwnd);
        return 0;
    }
    default:
    {
        //retrieve ptr to window class
        WindowContainer* const pWindow =
            reinterpret_cast<WindowContainer*>(
                GetWindowLongPtr(hwnd, GWLP_USERDATA));

        //forward message to window class handler
        return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
    }
    }
}


//l and w param - just additional data to the message
LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg,
    WPARAM wParam, LPARAM lParam) 
{
    switch (uMsg)
    {
    case WM_NCCREATE: //when a window is first created
    {
        const CREATESTRUCTW* const pCreate =
            reinterpret_cast<CREATESTRUCTW*>(lParam);

        WindowContainer* pWindow =
            reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);

        if (pWindow == nullptr) //sanity check ahaha
        {
            ErrorLogger::Log("Critical Error: Pointer to window container \
is null during WM_NCCREATE.");
            exit(-1);
        }

        //Sets the user data associated with the window
        SetWindowLongPtr(hwnd, GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pWindow));

        //Sets a new address for the window procedure
        SetWindowLongPtr(hwnd, GWLP_WNDPROC,
            reinterpret_cast<LONG_PTR>(HandleMsgRedirect));

        return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


void RenderWindow::RegisterWindowClass()
{
    WNDCLASSEX wc; //our window class
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = HandleMessageSetup;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;

    wc.hInstance = this->hinstance;
    wc.hIcon = NULL;
    wc.hIconSm = NULL;

    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = this->window_class_wide.c_str();
    wc.cbSize = sizeof(WNDCLASSEX);

    RegisterClassEx(&wc);
}


bool RenderWindow::ProcessMessages()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (PeekMessage(&msg,
        this->handle, //window for which we are checking msgs
        0, //minimum filter msg value
        0, //maximum one
        PM_REMOVE)) //remove msd after capturing it via PeekMessage
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); //dispatch msg to our Window Proc for this window
    }

    //check if the window was closed
    if (msg.message == WM_NULL)
    {
        if (!IsWindow(this->handle))
        {
            this->handle = NULL;
            UnregisterClass(this->window_class_wide.c_str(), this->hinstance);
            //DestroyWindow(handle); happens automatically
            return false;
        }
    }

    return true;
}


HWND RenderWindow::GetHWND() const
{
    return this->handle;
}
