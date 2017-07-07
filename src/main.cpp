#include <Corrade/Corrade.h>
#include <Corrade/Utility/Directory.h>
#include <Corrade/Utility/Debug.h>

#include <Magnum/Math/Color.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/Platform/Sdl2Application.h>

#include "configure.h"

using namespace Magnum;

class Application: public Magnum::Platform::Sdl2Application
{
public:
    explicit Application(const Arguments& args);

private:
    void drawEvent() override;
    void keyPressEvent(KeyEvent& evt) override;
};

Application::Application(const Arguments& args)
: Magnum::Platform::Application{args, Configuration{}.setTitle("Application")}
{
    Debug() << "Sandboxed: "        << Utility::Directory::isSandboxed();
    Debug() << "Executable dir: "   << Utility::Directory::executableLocation();
    Debug() << "Home: "             << Utility::Directory::home();
    Debug() << "Tmp: "              << Utility::Directory::tmp();
}

void Application::drawEvent() {
    Magnum::Renderer::setClearColor(Magnum::Color4::magenta());
    Magnum::defaultFramebuffer.clear(Magnum::FramebufferClear::Color);

    // draw here

    swapBuffers();
}

void Application::keyPressEvent(KeyEvent& evt) {
    if (evt.key() == KeyEvent::Key::Esc) {
        exit();
    }
}

MAGNUM_APPLICATION_MAIN(Application)

