#include <cassert>

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#include <AppKit/AppKit.hpp>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#pragma region Declarations {

class Renderer {
public:
  Renderer(MTL::Device *pDevice);
  ~Renderer();
  void draw(MTK::View *pView);

private:
  MTL::Device *_pDevice;
  MTL::CommandQueue *_pCommandQueue;
};

class MyMTKViewDelegate : public MTK::ViewDelegate {
public:
  MyMTKViewDelegate(MTL::Device *pDevice);
  virtual ~MyMTKViewDelegate() override;
  virtual void drawInMTKView(MTK::View *pView) override;

private:
  Renderer *_pRenderer;
};

class MyAppDelegate : public NS::ApplicationDelegate {
public:
  ~MyAppDelegate();

  NS::Menu *createMenuBar();

  virtual void
  applicationWillFinishLaunching(NS::Notification *pNotification) override;
  virtual void
  applicationDidFinishLaunching(NS::Notification *pNotification) override;
  virtual bool applicationShouldTerminateAfterLastWindowClosed(
      NS::Application *pSender) override;

private:
  NS::Window *_pWindow;
  MTK::View *_pMtkView;
  MTL::Device *_pDevice;
  MyMTKViewDelegate *_pViewDelegate = nullptr;
};

#pragma endregion Declarations }
