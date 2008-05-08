#ifndef CMAINFRAME_H
#define CMAINFRAME_H

class CMainFrame : public CWindow
{
public:
    static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    CMainFrame();
    bool Create(void);
    LRESULT EnableDisableCloseItem(bool bActivate);
    void IncreaseDecreaseSessionCount(bool bIncrease);
    virtual ~CMainFrame();

    // Handlers.
    //
    LRESULT OnCreate(CREATESTRUCT *pcs);
    LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

    // MDI Control
    //
    CMDIControl *m_pMDIControl;
    int          m_nChildren;
};

#endif // CMAINFRAME_H