#include <gui/password_container_app.h>

using passwordcontainer::gui::PasswordContainerApp;

void prepareSettings(PasswordContainerApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PasswordContainerApp, ci::app::RendererGl, prepareSettings);
