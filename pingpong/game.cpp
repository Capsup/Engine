#include "game.h"

GLint vColorValue;
GLint mvpMatrix;
GLuint FlatShader;

game::game()
{

}

game::game( HDC hdc )
{
	Camera = camera();
	m_hdc = hdc;
	
	TCHAR buffer[ MAX_PATH ];

	GetCurrentDirectory( MAX_PATH, buffer );

	sGlobalPath = tools::WStringToString( buffer );

	FlatShader = sm.LoadFromFile( sGlobalPath+"/content/shaders/flat/FlatShader.fp", sGlobalPath+"/content/shaders/flat/FlatShader.vp" );

	vColorValue = glGetUniformLocation( FlatShader, "vColorValue" );
	mvpMatrix = glGetUniformLocation( FlatShader, "mvpMatrix" );
}


game::~game(void)
{
}

void game::Update( float dt )
{
	KeyEvent event;
	while( keyboard.GetNextEvent( event ).type != KeyEventNone )
	{
		//Left arrow
		if( event.type == KeyEventRelease && event.iKeyCode == 37 )
		{
			//g.camera.m_m4LookAt = glm::translate( g.camera.m_m4LookAt, glm::vec3( 0, 0, 1 ) );
			//g.camera.MoveForward( -1.f );
			//g.camera.Apply();
			Camera.AddYaw( -40.f );
		}

		//Up Arrow
		if( event.type == KeyEventRelease && event.iKeyCode == 38 )
		{
			Camera.AddPitch( -40.f );
		}

		//Right Arrow
		if( event.type == KeyEventRelease && event.iKeyCode == 39 )
		{
			Camera.AddYaw( 40.f );
		}

		//Down Arrow
		if( event.type == KeyEventRelease && event.iKeyCode == 40 )
		{
			Camera.AddPitch( 40.f );
		}
	}

	glm::vec2 cursorpos = mouse.GetMousePos();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
		
	Camera.AddYaw( ( cursorpos.x - (viewport[2] / 2) ) * 40.f * dt );
	//g.camera.AddPitch( ( -cursorpos.y - (viewport[3] / 2) ) / 10000 );

	mouse.SetMousePos( glm::vec2( viewport[2] / 2, viewport[3] / 2 ) );

	Camera.Apply();
}

void game::Render() 
{
	glViewport(0, 0, 800,600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor( 0, 0, 0, 0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );	
	glLoadIdentity();
	

	GLfloat vColor[] = { 0.1f, 0.1f, 1.f, 1.0f };

	glm::mat4 mvp = glm::perspective( 45.0f, 800.f / 600.f, 1.f, 1000.f ) * Camera.GetLookAt() * glm::mat4(1.f);

	glUseProgram( FlatShader );
		glUniform4fv(vColorValue, 1, vColor);
		glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE, glm::value_ptr( mvp ) );
		glBegin (GL_QUAD_STRIP);
			glColor3f(  1, 0, 0 );
			glVertex3f( 0, 1, 0 );

			glColor3f(  0, 1, 0 );
			glVertex3f( 1, 1, 0 );

			glColor3f(  0, 0, 1 );
			glVertex3f( 0, 0, 0 );

			glColor3f(  1, 1, 1 );
			glVertex3f( 1, 0, 0 );
		glEnd();
		glBegin( GL_QUAD_STRIP);
			glColor3f(  1, 0, 0 );
			glVertex3f( 0, -1, 0 );

			glColor3f(  0, 1, 0 );
			glVertex3f( -1, -1, 0 );

			glColor3f(  0, 0, 1 );
			glVertex3f( 0, 0, 0 );

			glColor3f(  1, 1, 1 );
			glVertex3f( -1, 0, 0 );
		glEnd();
	glUseProgram( 0 );

	SwapBuffers(m_hdc);

}

		/*



		}*/