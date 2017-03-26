#ifndef READ_WRITER_H
#define READ_WRITER_H

namespace Sand
{
	class VScene;

	void VModelReader( const char* filename );

	void VModelWriter( const char* filename , VScene& scene );
}
#endif