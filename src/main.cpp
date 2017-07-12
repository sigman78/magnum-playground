#include <Corrade/Corrade.h>
#include <Corrade/Containers/ArrayView.h>
#include <Corrade/Utility/Directory.h>

#include <Magnum/Buffer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Context.h>
#include <Magnum/Texture.h>
#include <Magnum/TextureFormat.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Version.h>

#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>

#include <Magnum/Shader.h>
#include <Magnum/AbstractShaderProgram.h>

#include <Corrade/PluginManager/Manager.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>

#include "configure.h"

using namespace Corrade;
using namespace Magnum;

static const char VERT_SRC[] =
"layout(location = 0) in vec4 position; \n"
"layout(location = 1) in vec2 textureCoordinates; \n"
"out vec2 interpolatedTextureCoordinates; \n"
"void main() { \n"
"interpolatedTextureCoordinates = textureCoordinates; \n"
"gl_Position = position;"
"} \n";

static const char FRAG_SRC[] =
"uniform vec3 color = vec3(1.0, 1.0, 1.0); \n"
"uniform sampler2D textureData; \n"
"in vec2 interpolatedTextureCoordinates; \n"
"out vec4 fragmentColor; \n"
"void main() { \n"
"fragmentColor.rgb = color*texture(textureData, interpolatedTextureCoordinates).rgb; \n"
"fragmentColor.a = 1.0; \n"
"}\n";

class TriShader : public AbstractShaderProgram
{
	static const Int TextureLayer = 0;
	Int colorUniform;

public:
	typedef Attribute<0, Vector2> Position;
	typedef Attribute<1, Vector2> TexCoord;

	explicit TriShader() {
		MAGNUM_ASSERT_VERSION_SUPPORTED(Version::GL330);

		Shader vert{ Version::GL330, Shader::Type::Vertex };
		Shader frag{ Version::GL330, Shader::Type::Fragment };

		vert.addSource(VERT_SRC);
		frag.addSource(FRAG_SRC);

		CORRADE_INTERNAL_ASSERT_OUTPUT(Shader::compile({ vert, frag }));
		attachShaders({ vert, frag });
		CORRADE_INTERNAL_ASSERT_OUTPUT(link());
		colorUniform = uniformLocation("color");

		setUniform(uniformLocation("textureData"), TextureLayer);
	}

	TriShader& setColor(const Color3& color) {
		setUniform(colorUniform, color);
		return *this;
	}

	TriShader& setTexture(Texture2D& texture) {
		texture.bind(TextureLayer);
		return *this;
	}
};

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
    TriShader shader;
	Texture2D texture;
};

Application::Application(const Arguments& args)
: Platform::Application{args, Configuration{}.setTitle("Draw Triangle")}
{
    // set the renderer state
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::enable(Renderer::Feature::FaceCulling);

	// build tri : format must match shader decl 
	struct TriVertex {
		Vector2 position;
		Vector2 textureCoords;
	};

	static const TriVertex vertices[]{
		{ { -0.5f, -0.5f },{ 0.0f, 0.0f } },
		{ { 0.5f, -0.5f },{ 1.0f, 0.0f } },
		{ { 0.0f,  0.5f },{ 0.5f, 1.0f } } 
	};

	static const UnsignedInt indices[]{ 0, 1, 2 };

    // compose vertex buffer data
    vbuf.setData(vertices, BufferUsage::StaticDraw);
    ibuf.setData(indices, BufferUsage::StaticDraw);

    // build a mesh
	mesh.setPrimitive(MeshPrimitive::Triangles)
		.setCount(3)
		.addVertexBuffer(vbuf, 0, TriShader::Position{}, TriShader::TexCoord{})
		.setIndexBuffer(ibuf, 0, Mesh::IndexType::UnsignedInt, 0, 2);

	// load texture
	PluginManager::Manager<Trade::AbstractImporter> manager{ MAGNUM_PLUGINS_IMPORTER_DIR };
	std::unique_ptr<Trade::AbstractImporter> importer = manager.loadAndInstantiate("AnyImageImporter");
	if (!importer) std::exit(1);

	auto exePath = Utility::Directory::path(Utility::Directory::executableLocation());
	auto imagePath = Utility::Directory::join(exePath, "assets/uv_map.tga");
	if (!importer->openFile(imagePath))
		std::exit(2);

	std::optional<Trade::ImageData2D> image = importer->image2D(0);
	CORRADE_INTERNAL_ASSERT(image);
	texture.setWrapping(Sampler::Wrapping::ClampToEdge)
		.setMagnificationFilter(Sampler::Filter::Linear)
		.setMinificationFilter(Sampler::Filter::Linear)
		.setStorage(1, TextureFormat::RGB8, image->size())
		.setSubImage(0, {}, *image);
}

void Application::drawEvent() {
    Renderer::setClearColor(Color4::blue());
    defaultFramebuffer.clear(FramebufferClear::Color | FramebufferClear::Depth);

    // set uniforms
	shader.setColor({ 1.0f, 0.75f, 0.8f })
		.setTexture(texture);

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

