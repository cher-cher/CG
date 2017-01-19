#include "stdafx.h"
#include "Skybox.h"
#include <stdint.h>

namespace
{
const char TEXTURE_ATLAS[] = "res/galaxy/sprite.plist";
const std::pair<CubeFace, const char *> FRAME_MAPPING[] = {
    { CubeFace::Front, "sky3-front.png" },
    { CubeFace::Back, "sky5-back.png" },
    { CubeFace::Top, "sky1-top.png" },
    { CubeFace::Bottom, "sky6-down.png" },
    { CubeFace::Left, "sky2-left.png" },
    { CubeFace::Right, "sky4-right.png" },
};

// Устанавливает трансформацию так, чтобы рисование происходило
// в локальных координатах камеры, с сохранением вращения и
// масштабирования системы координат камеры.
template<class T>
void DoAtCameraPosition(T && callback)
{
    glm::mat4 modelView;
    glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(modelView));

	// Обнуляем перемещение в матрице афинного преобразования
    modelView[3][0] = 0.f;
    modelView[3][1] = 0.f;
    modelView[3][2] = 0.f;

    glPushMatrix();
    glLoadMatrixf(glm::value_ptr(modelView));
    callback();
    glPopMatrix();
}

CTexture2DLoader MakeTextureLoader()
{
    CTexture2DLoader loader;
    loader.SetWrapMode(TextureWrapMode::CLAMP_TO_EDGE);
    return loader;
}
}

CSkybox::CSkybox()
    : m_atlas(CFilesystemUtils::GetResourceAbspath(TEXTURE_ATLAS),
              MakeTextureLoader())
{
    for (const auto &pair : FRAME_MAPPING)
    {
        CFloatRect texRect = m_atlas.GetFrameRect(pair.second);
        m_cube.SetFaceTextureRect(pair.first, texRect);
    }
}

void CSkybox::Update(float dt)
{
    m_cube.Update(dt);
}

void CSkybox::Draw() const
{
    m_atlas.GetTexture().DoWhileBinded([this] {
        // Инвертируем передние и задние грани, потому что
        // на поверхность SkyBox мы всегда смотрим изнутри.
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE);
        glFrontFace(GL_CW);
        DoAtCameraPosition([this] {
            m_cube.Draw();
        });
        glFrontFace(GL_CCW);
        glDepthMask(GL_TRUE);
        glEnable(GL_LIGHTING);
    });
}
