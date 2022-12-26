#pragma once

#include <cassert>

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#include <AppKit/AppKit.hpp>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include "renderer.h"

class MyMTKViewDelegate : public MTK::ViewDelegate {
public:
  MyMTKViewDelegate(MTL::Device *pDevice);
  virtual ~MyMTKViewDelegate() override;
  virtual void drawInMTKView(MTK::View *pView) override;

private:
  Renderer *_pRenderer;
};

MyMTKViewDelegate::MyMTKViewDelegate(MTL::Device *pDevice)
    : MTK::ViewDelegate(), _pRenderer(new Renderer(pDevice)) {}

MyMTKViewDelegate::~MyMTKViewDelegate() { delete _pRenderer; }

void MyMTKViewDelegate::drawInMTKView(MTK::View *pView) {
  _pRenderer->draw(pView);
}
