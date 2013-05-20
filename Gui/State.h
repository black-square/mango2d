#ifndef GuiState_h__
#define GuiState_h__

//////////////////////////////////////////////////////////////////////////

struct IWidget
{
  typedef boost::shared_ptr<IWidget> TPtr;
  typedef const TPtr &TPtrParam;

  virtual ~IWidget() {}
  virtual Rect GetRect() const = 0;
  virtual void Render() const {};
  virtual void OnLButtonDown( Point pos ) {}
  virtual void OnLButtonUp( Point pos ) {}
};
//////////////////////////////////////////////////////////////////////////

struct IGuiStateManager;
//////////////////////////////////////////////////////////////////////////

class GuiState
{
public:
  typedef boost::shared_ptr<GuiState> TPtr;
  typedef const TPtr &TPtrParam;

public:
  GuiState(): m_pManager(0) {}

  void LButtonDown( Point pos );
  void LButtonUp( Point pos );
  void KeyDown( SDLKey sym, SDLMod mod, Uint16 unicode );
  void Update( float deltaTime );
  void Render();

  IGuiStateManager *GetManager() const { ASSERT( m_pManager != 0 ); return m_pManager; }
  void SetManager( IGuiStateManager *pManager ) { m_pManager = pManager; }

protected:
  void AddWidget( IWidget::TPtrParam p ) { m_widgets.push_back(p); }

private:
  virtual void OnLButtonDown( Point pos ){}
  virtual void OnLButtonUp( Point pos ) {}
  virtual void OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode ) {}
  virtual void OnUpdate( float deltaTime ) {}
  virtual void OnRender() {}

private:
  typedef std::vector<IWidget::TPtr> TWidgets;
 
private:
  TWidgets m_widgets;
  IGuiStateManager *m_pManager;   
};
//////////////////////////////////////////////////////////////////////////

struct IGuiStateManager
{
  virtual ~IGuiStateManager() {}

  virtual void SetState( GuiState::TPtrParam p ) = 0;
  virtual void SetMainState() = 0;
};



#endif // GuiState_h__
