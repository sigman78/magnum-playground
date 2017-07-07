#include <Corrade/Corrade.h>

#include <Magnum/Buffer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/Platform/Sdl2Application.h>

#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Primitives/Cube.h>

#include <Magnum/Shaders/Phong.h>

#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/Primitives/Cube.h>

#include "configure.h"

using namespace Magnum;

class Application: public Platform::Sdl2Application
{
public:
    explicit Application(const Arguments& args);

private:
    void drawEvent() override;
    void keyPressEvent(KeyEvent& evt) override;

    Buffer vbuf;
    Buffer ibuf;
    Mesh mesh;
    Shaders::Phong shader;

    Matrix4 proj;
    Matrix4 trans;
};

Application::Application(const Arguments& args)
: Platform::Application{args, Configuration{}.setTitle("Primitive")}
{
    // set the renderer state
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::enable(Renderer::Feature::FaceCulling);

    // build mesh from prefab
    auto cube = Primitives::Cube::solid();

    // compose vertex buffer data
    vbuf.setData(MeshTools::interleave(cube.positions(0), cube.normals(0)), BufferUsage::StaticDraw);

    // compose index buffer data
    Containers::Array<char> indexData;
    Mesh::IndexType indexType;
    UnsignedInt indexStart, indexEnd;

    std::tie(indexData, indexType, indexStart, indexEnd) = MeshTools::compressIndices(cube.indices());
    ibuf.setData(indexData, BufferUsage::StaticDraw);

    // build a mesh
    mesh.setPrimitive(cube.primitive())
        .setCount(cube.indices().size())
        .addVertexBuffer(vbuf, 0, Shaders::Phong::Position{}, Shaders::Phong::Normal{})
        .setIndexBuffer(ibuf, 0, indexType, indexStart, indexEnd);

    // matrices
    trans = Matrix4::rotationX(30.0_degf)
            * Matrix4::rotationY(40.0_degf);

    proj = Matrix4::perspectiveProjection(35.0_degf, Vector2{defaultFramebuffer.viewport().size()}.aspectRatio(), 0.01f, 100.0f)
        * Matrix4::translation(Vector3::zAxis(-10.0f));
}

void Application::drawEvent() {
    Renderer::setClearColor(Color4::blue());
    defaultFramebuffer.clear(FramebufferClear::Color | FramebufferClear::Depth);

    // set uniforms
    shader.setLightPosition({7.0f, 5.0f, 2.5f})
        .setLightColor(Color3{1.0f})
        .setDiffuseColor(Color3::green())
        .setAmbientColor(Color3{0.1f, 0.2f, 0.3f})
        .setTransformationMatrix(trans)
        .setNormalMatrix(trans.rotationScaling())
        .setProjectionMatrix(proj);

    // submit mesh
    mesh.draw(shader);

    swapBuffers();
}

void Application::keyPressEvent(KeyEvent& evt) {
    if (evt.key() == KeyEvent::Key::Esc) {
        exit();
    }
}

MAGNUM_APPLICATION_MAIN(Application)

