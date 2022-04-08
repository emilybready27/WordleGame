#include <visualizer/wordle_app.h>

using wordle::visualizer::WordleApp;

void prepareSettings(WordleApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(WordleApp, ci::app::RendererGl, prepareSettings);
