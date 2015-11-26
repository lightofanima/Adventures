/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include <GL/glew.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include <stdexcept>
#include <memory>
#include "mainshader.h"
#include "camera.h"
#include "cursor.h"
#include "vertex.h"
#include "canvas.h"
#pragma comment(lib, "C:\\Users\\light\\Documents\\glew-1.13.0\\lib\\Debug\\Win32\\glew32d.lib")

class Canvas;
class Cursor;



//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public OpenGLAppComponent
{
public:

	MainShader mMainShader;
	Canvas mCanvas;
	math::vec2i mLastMousePosition;
	math::vec2 mNormalisedMousePosition;
	Cursor mCursor;
	bool mLeftMousePressed, mRightMousePressed;

	struct
	{
		Vertex2D quad[6];
		GLuint VBO;
	} mQuad;


    //==============================================================================
    MainContentComponent()
    {
        setSize (800, 600);
    }

    ~MainContentComponent()
    {
        shutdownOpenGL();
    }

    void initialise() override
    {
		GLenum status = glewInit();
		if (status != GLEW_OK)
			throw std::runtime_error("Unable to initialise glew");

		mLeftMousePressed = false;
		mRightMousePressed = false;

		glClearColor(0, 0, 0, 1);
		mMainShader.load("shaders/main.vert", "shaders/main.frag");
		initialiseQuad();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void shutdown() override
    {
    }


	void beginDraw()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBindBuffer(GL_ARRAY_BUFFER, mQuad.VBO);
		mMainShader.set();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), NULL);
		glActiveTexture(GL_TEXTURE0);
	}


	void endDraw()
	{
		int error = glGetError();
		std::ostringstream stream;
		stream << error;
		if (error != 0)
			Error(stream.str());
	}


    void render() override
    {
        OpenGLHelpers::clear (Colours::black);
		beginDraw();
		mCanvas.draw(mMainShader);
		mCursor.draw(mCanvas.mCamera.matrix(), mMainShader);

		endDraw();
    }

	void mouseDown(const MouseEvent &e) override
	{
		mLeftMousePressed = e.mods.isLeftButtonDown();
		mRightMousePressed = e.mods.isRightButtonDown();
	}

	void mouseUp(const MouseEvent& e) override
	{
		mLeftMousePressed = e.mods.isLeftButtonDown();
		mRightMousePressed = e.mods.isRightButtonDown();
	}

	void mouseDrag(const MouseEvent& e) override
	{
		math::vec2i position = math::vec2i(e.x, e.y);
		math::vec2 delta = math::vec2(position.x, position.y) -
			math::vec2(mLastMousePosition.x, mLastMousePosition.y);

		//This is not wrong. The second part accounts for aspect ratio ^.^
		delta /= this->getBounds().getWidth() / 2.f;

		if (mRightMousePressed) //panning has priority.
		{
			mCanvas.pan(delta.x, delta.y);
		}
		else if (mLeftMousePressed)
		{
			mCanvas.applyBrush(mCursor.globalPos());
		}

		mLastMousePosition = math::vec2i(e.x, e.y);
		mNormalisedMousePosition = math::vec2(((float)mLastMousePosition.x / this->getBounds().getWidth() - 0.5f) * 2,
			((float)mLastMousePosition.y / this->getBounds().getHeight() - 0.5f)*-2);
		mCursor.globalPos(mNormalisedMousePosition, mCanvas.mCamera.matrix());
	}

	int mouseWheelMove(const MouseEvent &e, float wheelIncrementX, float wheelIncrementY) override
	{
		mCanvas.zoom(wheelIncrementY / 2000.f);
		return 0;
	}

    void paint (Graphics& g) override
    {
        // You can add your component specific drawing code here!
        // This will draw over the top of the openGL background.
		
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
		Rectangle<int> bounds = getBounds();

		mCanvas.resizeViewport(bounds.getWidth(), bounds.getHeight());
		glViewport(0, 0, bounds.getWidth(), bounds.getHeight());
    }

	void initialiseQuad()
	{
		mQuad.quad[0] = Vertex2D(-1.f, -1.f, 0.f, 0.f);
		mQuad.quad[1] = Vertex2D(1.f, -1.f, 1.f, 0.f);
		mQuad.quad[2] = Vertex2D(-1.f, 1.f, 0.f, 1.f);
		mQuad.quad[3] = Vertex2D(-1.f, 1.f, 0.f, 1.f),
			mQuad.quad[4] = Vertex2D(1.f, -1.f, 1.f, 0.f);
		mQuad.quad[5] = Vertex2D(1.f, 1.f, 1.f, 1.f);
		mQuad.VBO = ~0u;

		glGenBuffers(1, &mQuad.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, mQuad.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * 6, mQuad.quad, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), NULL);
	}


private:
    //==============================================================================

    // private member variables



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED