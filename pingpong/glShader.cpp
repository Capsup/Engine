#include "glShader.h"

glShader::glShader(void)
{

}


glShader::~glShader(void)
{

}

int glShader::Load( char* path )
{
	/*FILE* file;
	const GLint len = tools::GetFileLength( path );
	fopen_s( &file, path, "r" );
	if( !file )
		Err( TEXT( "fopen" ) );

	char* buffer = new char[ len + 1 ];
	if( !buffer ) 
		ErrCT( TEXT( "Memory failed to initialise." ) )
	size_t result = fread( buffer, 1, len, file );
	buffer[ len - 1 ] = 0;
	//if( result != len )
	//	Err( TEXT( "fread" ) );
	fclose( file );*/

	FILE* file;
	//MessageBoxA( NULL, path, "Pixelformat", MB_OK );

	file = fopen( path, "r" );
	if( !file )
		Err( TEXT( "fopen" ) );

	int i = 0;

	while( !feof( file ) )
	{
		fgetc( file );
		i++;
	}
	rewind( file );
	char* buffer = new char[ i ];
	size_t result = fread( buffer, 1, i, file );
	buffer[ i - 1 ] = 0;
	fclose( file );

	if( strstr( path, ".fp" ) )
		shader = glCreateShader( GL_FRAGMENT_SHADER );
	else if( strstr( path, ".vp" ) )
	{
		shader = glCreateShader( GL_VERTEX_SHADER );
	}
	else
		shader = glCreateShader( GL_GEOMETRY_SHADER );

	const char* baffer = buffer;

	//glShaderSourceARB( shader, 1, &baffer, &len );
	glShaderSourceARB( shader, 1, &baffer, &i );

	glCompileShaderARB( shader );
	GLint success;

	glGetObjectParameterivARB( shader, GL_COMPILE_STATUS, &success );
	if( !success )
	{
		GLint blen = 0;
		GLsizei slen = 0;

		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &blen );

		if( blen > 1 )
		{
			GLchar* log = (GLchar*) malloc( blen );
			char* log2 = "Compile error: ";
			glGetInfoLogARB( shader, blen, &slen, log );

			FatalAppExit( NULL, tools::DCharToError( log2, log ) );
			free( log );
		}

	}
	return 0;
}

int glShader::Load( std::string path )
{
	/*FILE* file;
	const GLint len = tools::GetFileLength( path );
	fopen_s( &file, path, "r" );
	if( !file )
		Err( TEXT( "fopen" ) );

	char* buffer = new char[ len + 1 ];
	if( !buffer ) 
		ErrCT( TEXT( "Memory failed to initialise." ) )
	size_t result = fread( buffer, 1, len, file );
	buffer[ len - 1 ] = 0;
	//if( result != len )
	//	Err( TEXT( "fread" ) );
	fclose( file );*/

	FILE* file;
	//MessageBoxA( NULL, path, "Pixelformat", MB_OK );

	file = fopen( path.c_str(), "r" );
	if( !file )
		Err( TEXT( "fopen" ) );

	int i = 0;

	while( !feof( file ) )
	{
		fgetc( file );
		i++;
	}
	rewind( file );
	char* buffer = new char[ i ];
	size_t result = fread( buffer, 1, i, file );
	buffer[ i - 1 ] = 0;
	fclose( file );

	if( strstr( path.c_str(), ".fp" ) )
		shader = glCreateShader( GL_FRAGMENT_SHADER );
	else if( strstr( path.c_str(), ".vp" ) )
	{
		shader = glCreateShader( GL_VERTEX_SHADER );
	}
	else
		shader = glCreateShader( GL_GEOMETRY_SHADER );

	const char* baffer = buffer;

	//glShaderSourceARB( shader, 1, &baffer, &len );
	glShaderSourceARB( shader, 1, &baffer, &i );

	glCompileShaderARB( shader );
	GLint success;

	glGetObjectParameterivARB( shader, GL_COMPILE_STATUS, &success );
	if( !success )
	{
		GLint blen = 0;
		GLsizei slen = 0;

		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &blen );

		if( blen > 1 )
		{
			GLchar* log = (GLchar*) malloc( blen );
			char* log2 = "Compile error: ";
			glGetInfoLogARB( shader, blen, &slen, log );

			FatalAppExit( NULL, tools::DCharToError( log2, log ) );
			free( log );
		}

	}
	return 0;
}

GLuint glShader::GetObject()
{
	return shader;
}