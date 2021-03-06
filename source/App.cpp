/** \file App.cpp */
#include "App.h"

/** Tells C++ to invoke command-line main() function even on OS X and Win32. */
G3D_START_AT_MAIN();

int main(int argc, const char* argv[]) {
    {
        G3DSpecification g3dSpec;
        g3dSpec.audio = false;
        initGLG3D(g3dSpec);
    }

    GApp::Settings settings(argc, argv);

    // Change the window and other startup parameters by modifying the
    // settings class.  For example:
    settings.window.caption             = argv[0];

    // Set enable to catch more OpenGL errors
    // settings.window.debugContext     = true;

    // Some common resolutions:
    // settings.window.width            =  854; settings.window.height       = 480;
    // settings.window.width            = 1024; settings.window.height       = 768;
    settings.window.width               = 1280; settings.window.height       = 720;
    //settings.window.width             = 1920; settings.window.height       = 1080;
    // settings.window.width            = OSWindow::primaryDisplayWindowSize().x; settings.window.height = OSWindow::primaryDisplayWindowSize().y;
    settings.window.fullScreen          = false;
    settings.window.resizable           = ! settings.window.fullScreen;
    settings.window.framed              = ! settings.window.fullScreen;

    // Set to true for a significant performance boost if your app can't render at 60fps, or if
    // you *want* to render faster than the display.
    settings.window.asynchronous        = false;

    settings.hdrFramebuffer.depthGuardBandThickness = Vector2int16(64, 64);
    settings.hdrFramebuffer.colorGuardBandThickness = Vector2int16(0, 0);
    settings.dataDir                    = FileSystem::currentDirectory();
    settings.screenshotDirectory        = "../journal/";

    settings.renderer.deferredShading = true;
    settings.renderer.orderIndependentTransparency = false;

    return App(settings).run();
}


App::App(const GApp::Settings& settings) : GApp(settings) {
}

//Generates a scene file for a spiral staircase.
//http://bgfons.com/upload/stone_texture2399.jpg
void App::generateStaircase(){
    TextOutput text = TextOutput("scene/staircase.Scene.Any");
    String stairCode = String("{ name = \"Staircase\"; models = { ");
    text.writeSymbol( stairCode
        + "\n stairModel = ArticulatedModel::Specification { filename = \"model/cube/cube.obj\"; "
        + "\n preprocess = { setMaterial(all(), \"stone_texture.jpg\");"
        + "\n transformGeometry(all(), Matrix4::scale(2, .3, .5));};};};"
        + "\n entities = { skybox = Skybox { texture = \"cubemap/whiteroom/whiteroom-*.png\"; };" +
        + "\n sun = Light { attenuation = (0, 0, 1); bulbPower = Power3(4e+006);"
        + "\n frame = CFrame::fromXYZYPRDegrees(-15, 207, -41, -164, -77, 77);"
        + "\n shadowMapSize = Vector2int16(2048, 2048); "
        + "\n spotHalfAngleDegrees = 5; spotSquare = true; type = \"SPOT\"; };"
    );
    for (int i = 0; i < 50; ++i){
        text.writeSymbol((String) "\nstep" + (String)std::to_string(i)
            + " = VisibleEntity {"
            + " \n model = \"stairModel\";"
            + "\n frame = CFrame::fromXYZYPRDegrees(0, " + (String)std::to_string(i*.1) 
            +", 0, "
            + (String)std::to_string(i*15) + ", 0, 0); };"
        );
    }
    text.writeSymbol("\n camera = Camera { frame = CFrame::fromXYZYPRDegrees(0, 0, 5);};};};");
    text.commit();
}

//Returns the code needed to generate a stem.
String App::makeStem(float x, float z, String id){
    String stem = String("stemA_");
    stem += id
+       "= VisibleEntity {"
+"\n        model = \"stemModel\";"
+"\n        frame = CFrame::fromXYZYPRDegrees("
+   (String)std::to_string(x) + ", 0," + (String)std::to_string(z) +", 0, 0, 0);"
+"\n        };";
    return stem;
}

//Returns the code needed to generate a bloom
String App::makeBloom(float x, float z, String id){
    String flower = String("petalA_");
    flower += id
+"\n        = VisibleEntity {"
+"\n            model = \"petalModel\";"
+"\n            frame = CFrame::fromXYZYPRDegrees("
+ (String)std::to_string(x) +", 1, " + (String)std::to_string(z) +", 0, 0, 0);"
+"\n        };"

+"\n        petalB_" + id +" = VisibleEntity {"
+"\n            model = \"petalModel\";"
+"\n            frame = CFrame::fromXYZYPRDegrees("
+ (String)std::to_string(x) +", 1, " + (String)std::to_string(z) +", 45, 0, 0);"
+"\n        };"

+"\n        petalC_" + id + " = VisibleEntity {"
+"\n            model = \"petalModel\";"
+"\n            frame = CFrame::fromXYZYPRDegrees("
+ (String)std::to_string(x) +", 1, " + (String)std::to_string(z) +", 90, 0, 0);"
+"\n        };"

+"\n        petalD_" + id + " = VisibleEntity {"
+"\n            model = \"petalModel\";"
+"\n            frame = CFrame::fromXYZYPRDegrees("
+ (String)std::to_string(x) +", 1, " + (String)std::to_string(z) +", 135, 0, 0);"
+"\n         };";
        return flower;
}

//returns the code needs to generate a Puffball
String App::makePuffball(float x, float z, String id){
    String flower = String("cubeA_");
    flower += id
        + "= VisibleEntity {"
        + "\n model = \"whiteCubeModel\";"
        + "\n   frame = CFrame::fromXYZYPRDegrees(" + (String)std::to_string(x)+", 1," + (String)std::to_string(z) +", 45, 0, 0);"
        +"\n};"
        +"cubeB_" + id
        + "= VisibleEntity {"
        + "\n model = \"whiteCubeModel\";"
        + "\n   frame = CFrame::fromXYZYPRDegrees(" + (String)std::to_string(x)+", 1," + (String)std::to_string(z) +", 0, 45, 0);"
        +"\n};"
        +"cubeC_" + id
        + "= VisibleEntity {"
        + "\n model = \"whiteCubeModel\";"
        + "\n   frame = CFrame::fromXYZYPRDegrees(" + (String)std::to_string(x)+", 1," + (String)std::to_string(z) +", 0, 0, 45);"
        +"\n};";
    return flower;
}

//Generate the scene file for a field of dandelions
void App::generateFlowers(){
    TextOutput text = TextOutput("scene/pointyStars.Scene.Any");
    String starCode = String("{ name = \"pointyStars\";");
    text.writeSymbol(starCode
+"\n        models = {"
+"\n        whiteCubeModel = ArticulatedModel::Specification {"
+"\n            filename = \"model/cube/cube.obj\";"
+"\n            preprocess = {"
+"\n                setMaterial(all(), Color3(1, 1, 1));"
+"\n            };"
+"\n        };"
+"\n        petalModel = ArticulatedModel::Specification {"
+"\n            filename = \"model/cube/cube.obj\";"
+"\n            preprocess = {"
+"\n                setMaterial(all(), Color3(1, 1, 0));"
+"\n                transformGeometry(all(), Matrix4::scale(2, .3, .5));"
+"\n            };"
+"\n        };"
+"\n        stemModel = ArticulatedModel::Specification {"
+"\n            filename = \"model/cube/cube.obj\";"
+"\n            preprocess = {"
+"\n                setMaterial(all(), Color3(0, 1, 0));"
+"\n                transformGeometry(all(), Matrix4::scale(.1, 2, .1));"
+"\n            };"
+"\n        };"
+"\n        groundModel = ArticulatedModel::Specification {"
+"\n            filename = \"model/cube/cube.obj\";"
+"\n            preprocess = {"
+"\n                setMaterial(all(), Color3(0, 1, 0));"
+"\n                transformGeometry(all(), Matrix4::scale(20, .2, 20));"
+"\n            };"
+"\n        };"
+"\n    };\n"
   
    + "entities = { "
        
+ "\n        skybox = Skybox { "
+ "\n            texture = \"cubemap/whiteroom/whiteroom-*.png\"; "
+ "\n        };"
+ "\n        "
+ "\n        sun = Light { "
+ "\n            attenuation = (0, 0, 1); "
+ "\n            bulbPower = Power3(4e+005); "
+ "\n            frame = CFrame::fromXYZYPRDegrees(-15, 207, -41, -164, -77, 77);"
+ "\n            shadowMapSize = Vector2int16(2048, 2048); "
+ "\n            spotHalfAngleDegrees = 5; "
+ "\n            spotSquare = true; "
+ "\n            type = \"SPOT\"; "
+ "\n        };"
+"\n         camera = Camera {"
+"\n            frame = CFrame::fromXYZYPRDegrees(0, 0, 5);"
+"\n        };\n"
+"\n         ground0 = VisibleEntity {"
+"\n            model = \"groundModel\";"
+"\n            frame = CFrame::fromXYZYPRDegrees(0, -1, 0, 0, 0, 0);"
+"\n        };"); 
    for (int i = 0; i <= 10; i+=2){
        for (int j = 0; j <=10; j+=2){
            if((i+j)%4 == 0){
                text.writeSymbol(makePuffball(i, j, (String)std::to_string(i) + "_" + (String)std::to_string(j) +"a"));
                text.writeSymbol(makePuffball(-i, -j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"b"));
                text.writeSymbol(makePuffball(-i, j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"c"));
                text.writeSymbol(makePuffball(i, -j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"d"));
            }else{
                text.writeSymbol(makeBloom(i, j, (String)std::to_string(i) + "_" + (String)std::to_string(j) +"a"));
                text.writeSymbol(makeBloom(-i, -j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"b"));
                text.writeSymbol(makeBloom(-i, j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"c"));
                text.writeSymbol(makeBloom(i, -j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"d"));
            }
            text.writeSymbol(makeStem(i,  j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"a"));
            text.writeSymbol(makeStem(-i,  -j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"b"));
            text.writeSymbol(makeStem(-i,  j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"c"));
            text.writeSymbol(makeStem(i,  -j, (String)std::to_string(i) + "_" + (String)std::to_string(j)+"d"));
        }
    }
    
    //String puff = makePuffball(0, 0, "8_9");
    text.writeSymbol((String)"};};");
    text.commit();
}


// Called before the application loop begins.  Load data here and
// not in the constructor so that common exceptions will be
// automatically caught.
void App::onInit() {
    debugPrintf("Target frame rate = %f Hz\n", realTimeTargetDuration());
    App::generateStaircase();
    App::generateFlowers();
    GApp::onInit();
    setFrameDuration(1.0f / 120.0f);

    // Call setScene(shared_ptr<Scene>()) or setScene(MyScene::create()) to replace
    // the default scene here.
    
    showRenderingStats      = false;

    makeGUI();
    // For higher-quality screenshots:
    // developerWindow->videoRecordDialog->setScreenShotFormat("PNG");
    // developerWindow->videoRecordDialog->setCaptureGui(false);
    developerWindow->cameraControlWindow->moveTo(Point2(developerWindow->cameraControlWindow->rect().x0(), 0));
    loadScene(
        //"G3D Sponza"
        "Stars" // Load something simple
        //developerWindow->sceneEditorWindow->selectedSceneName()  // Load the first scene encountered 
        );
}


void App::makeGUI() {
    // Initialize the developer HUD
    createDeveloperHUD();

    debugWindow->setVisible(true);
    developerWindow->videoRecordDialog->setEnabled(true);

   /*GuiPane* infoPane = debugPane->addPane("Info", GuiTheme::ORNATE_PANE_STYLE);
    
    // Example of how to add debugging controls
    infoPane->addLabel("You can add GUI controls");
    infoPane->addLabel("in App::onInit().");
    infoPane->addButton("Exit", [this]() { m_endProgram = true; });
    infoPane->pack();*/

    // More examples of debugging GUI controls:
    // debugPane->addCheckBox("Use explicit checking", &explicitCheck);
    // debugPane->addTextBox("Name", &myName);
    // debugPane->addNumberBox("height", &height, "m", GuiTheme::LINEAR_SLIDER, 1.0f, 2.5f);
    // button = debugPane->addButton("Run Simulator");
    // debugPane->addButton("Generate Heightfield", [this](){ generateHeightfield(); });
    // debugPane->addButton("Generate Heightfield", [this](){ makeHeightfield(imageName, scale, "model/heightfield.off"); });

    debugWindow->pack();
    debugWindow->setRect(Rect2D::xywh(0, 0, (float)window()->width(), debugWindow->rect().height()));
}


// This default implementation is a direct copy of GApp::onGraphics3D to make it easy
// for you to modify. If you aren't changing the hardware rendering strategy, you can
// delete this override entirely.
void App::onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& allSurfaces) {

    if (!scene()) {
        if ((submitToDisplayMode() == SubmitToDisplayMode::MAXIMIZE_THROUGHPUT) && (!rd->swapBuffersAutomatically())) {
            swapBuffers();
        }
        rd->clear();
        rd->pushState(); {
            rd->setProjectionAndCameraMatrix(activeCamera()->projection(), activeCamera()->frame());
            drawDebugShapes();
        } rd->popState();
        return;
    }

    GBuffer::Specification gbufferSpec = m_gbufferSpecification;
    extendGBufferSpecification(gbufferSpec);
    m_gbuffer->setSpecification(gbufferSpec);
    m_gbuffer->resize(m_framebuffer->width(), m_framebuffer->height());
    m_gbuffer->prepare(rd, activeCamera(), 0, -(float)previousSimTimeStep(), m_settings.hdrFramebuffer.depthGuardBandThickness, m_settings.hdrFramebuffer.colorGuardBandThickness);

    m_renderer->render(rd, m_framebuffer, scene()->lightingEnvironment().ambientOcclusionSettings.enabled ? m_depthPeelFramebuffer : shared_ptr<Framebuffer>(),
        scene()->lightingEnvironment(), m_gbuffer, allSurfaces);

    // Debug visualizations and post-process effects
    rd->pushState(m_framebuffer); {
        // Call to make the App show the output of debugDraw(...)
        rd->setProjectionAndCameraMatrix(activeCamera()->projection(), activeCamera()->frame());
        drawDebugShapes();
        const shared_ptr<Entity>& selectedEntity = (notNull(developerWindow) && notNull(developerWindow->sceneEditorWindow)) ? developerWindow->sceneEditorWindow->selectedEntity() : shared_ptr<Entity>();
        scene()->visualize(rd, selectedEntity, allSurfaces, sceneVisualizationSettings(), activeCamera());

        // Post-process special effects
        m_depthOfField->apply(rd, m_framebuffer->texture(0), m_framebuffer->texture(Framebuffer::DEPTH), activeCamera(), m_settings.hdrFramebuffer.depthGuardBandThickness - m_settings.hdrFramebuffer.colorGuardBandThickness);

        m_motionBlur->apply(rd, m_framebuffer->texture(0), m_gbuffer->texture(GBuffer::Field::SS_EXPRESSIVE_MOTION),
            m_framebuffer->texture(Framebuffer::DEPTH), activeCamera(),
            m_settings.hdrFramebuffer.depthGuardBandThickness - m_settings.hdrFramebuffer.colorGuardBandThickness);
    } rd->popState();

    // We're about to render to the actual back buffer, so swap the buffers now.
    // This call also allows the screenshot and video recording to capture the
    // previous frame just before it is displayed.
    if (submitToDisplayMode() == SubmitToDisplayMode::MAXIMIZE_THROUGHPUT) {
        swapBuffers();
    }

    // Clear the entire screen (needed even though we'll render over it, since
    // AFR uses clear() to detect that the buffer is not re-used.)
    rd->clear();

    // Perform gamma correction, bloom, and SSAA, and write to the native window frame buffer
    m_film->exposeAndRender(rd, activeCamera()->filmSettings(), m_framebuffer->texture(0), settings().hdrFramebuffer.colorGuardBandThickness.x + settings().hdrFramebuffer.depthGuardBandThickness.x, settings().hdrFramebuffer.depthGuardBandThickness.x);
}


void App::onAI() {
    GApp::onAI();
    // Add non-simulation game logic and AI code here
}


void App::onNetwork() {
    GApp::onNetwork();
    // Poll net messages here
}


void App::onSimulation(RealTime rdt, SimTime sdt, SimTime idt) {
    GApp::onSimulation(rdt, sdt, idt);

    // Example GUI dynamic layout code.  Resize the debugWindow to fill
    // the screen horizontally.
    debugWindow->setRect(Rect2D::xywh(0, 0, (float)window()->width(), debugWindow->rect().height()));
}


bool App::onEvent(const GEvent& event) {
    // Handle super-class events
    if (GApp::onEvent(event)) { return true; }

    // If you need to track individual UI events, manage them here.
    // Return true if you want to prevent other parts of the system
    // from observing this specific event.
    //
    // For example,
    // if ((event.type == GEventType::GUI_ACTION) && (event.gui.control == m_button)) { ... return true; }
    // if ((event.type == GEventType::KEY_DOWN) && (event.key.keysym.sym == GKey::TAB)) { ... return true; }
    // if ((event.type == GEventType::KEY_DOWN) && (event.key.keysym.sym == 'p')) { ... return true; }

    return false;
}


void App::onUserInput(UserInput* ui) {
    GApp::onUserInput(ui);
    (void)ui;
    // Add key handling here based on the keys currently held or
    // ones that changed in the last frame.
}


void App::onPose(Array<shared_ptr<Surface> >& surface, Array<shared_ptr<Surface2D> >& surface2D) {
    GApp::onPose(surface, surface2D);

    // Append any models to the arrays that you want to later be rendered by onGraphics()
}


void App::onGraphics2D(RenderDevice* rd, Array<shared_ptr<Surface2D> >& posed2D) {
    // Render 2D objects like Widgets.  These do not receive tone mapping or gamma correction.
    Surface2D::sortAndRender(rd, posed2D);
}


void App::onCleanup() {
    // Called after the application loop ends.  Place a majority of cleanup code
    // here instead of in the constructor so that exceptions can be caught.
}
