#ifndef GuiState_h__
#define GuiState_h__

namespace Gui {
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

struct IStateManager;
//////////////////////////////////////////////////////////////////////////

class State
{
public:
  typedef boost::shared_ptr<State> TPtr;
  typedef const TPtr &TPtrParam;

public:
  State(): m_pManager(0) {}

  void LButtonDown( Point pos );
  void LButtonUp( Point pos );
  void MouseMove( Point pos );
  void KeyDown( SDLKey sym, SDLMod mod, Uint16 unicode );
  void UpdateStep();
  void Update( float deltaTime );
  void Render( float deltaTime ) const;

  IStateManager *GetManager() const { ASSERT( m_pManager != 0 ); return m_pManager; }
  void SetManager( IStateManager *pManager ) { m_pManager = pManager; }

protected:
  void AddWidget( IWidget::TPtrParam p ) { m_widgets.push_back(p); }

private:
  virtual void OnLButtonDown( Point pos ){}
  virtual void OnLButtonUp( Point pos ) {}
  virtual void OnMouseMove( Point pos ) {}
  virtual void OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode ) {}
  virtual void OnUpdateStep() {}
  virtual void OnUpdate( float deltaTime ) {}
  virtual void OnRender( float deltaTime ) const {}
  virtual void OnRenderBelow( float deltaTime ) const {}

private:
  typedef std::vector<IWidget::TPtr> TWidgets;
 
private:
  TWidgets m_widgets;
  IStateManager *m_pManager;   
};
//////////////////////////////////////////////////////////////////////////

struct IStateManager
{
  virtual ~IStateManager() {}

  virtual void SetState( State::TPtrParam p ) = 0;
  virtual void SetMainState() = 0;
};

} //namespace Gui

#endif // GuiState_h__
