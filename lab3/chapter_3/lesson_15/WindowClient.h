#pragma once
#include "libchapter3.h"
#include "Paraboloid.h"
#include "TwistValueController.h"
#include <vector>

class CWindowClient : public CAbstractWindowClient
{
public:
    CWindowClient(CWindow &window);

protected:
    // IWindowClient interface
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow() override;
    void OnKeyDown(const SDL_KeyboardEvent &) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;

private:
    void CheckOpenGLVersion();
    void SetupView(const glm::ivec2 &size);

    CParaboloid m_paraboloidObj;
    CPhongModelMaterial m_paraboloidMat;
    CCamera m_camera;
    CDirectedLightSource m_sunlight;
    CPositionLightSource m_lamp;
    CShaderProgram m_programTwist;
    CShaderProgram m_programFixed;
    bool m_programEnabled = true;
    CTwistValueController m_twistController;
};
