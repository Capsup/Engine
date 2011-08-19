#include "shadermanager.h"


shadermanager::shadermanager(void)
{
	
}


shadermanager::~shadermanager(void)
{
}

GLuint shadermanager::LoadFromFile( char* fpPath, char* vpPath )
{
	glShader fpShader;
	glShader vpShader;
	fpShader.Load( fpPath );
	vpShader.Load( vpPath );

	GLuint program = glCreateProgram();

	glAttachShader( program, fpShader.GetObject() );
	glAttachShader( program, vpShader.GetObject() );

	glLinkProgram( program );

	GLint success;

	glGetProgramiv( program, GL_LINK_STATUS, &success );

	if( !success )
	{
		GLint blen = 0;
		GLsizei slen = 0;

		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &blen );

		if( blen > 1 )
		{
			char* log = (char*) malloc( blen );
			char* log2 = "Linker error: ";
			glGetInfoLogARB( program, blen, &slen, log );

			FatalAppExit( NULL, tools::DCharToError( log2, log ) );
			free( log );
		}

	}


	return program;
}

GLuint shadermanager::LoadFromFile( std::string& fpPath, std::string& vpPath )
{
	glShader fpShader;
	glShader vpShader;
	fpShader.Load( fpPath );
	vpShader.Load( vpPath );

	GLuint program = glCreateProgram();

	glAttachShader( program, fpShader.GetObject() );
	glAttachShader( program, vpShader.GetObject() );

	glLinkProgram( program );

	GLint success;

	glGetProgramiv( program, GL_LINK_STATUS, &success );

	if( !success )
	{
		GLint blen = 0;
		GLsizei slen = 0;

		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &blen );

		if( blen > 1 )
		{
			char* log = (char*) malloc( blen );
			char* log2 = "Linker error: ";
			glGetInfoLogARB( program, blen, &slen, log );

			FatalAppExit( NULL, tools::DCharToError( log2, log ) );
			free( log );
		}

	}


	return program;
}