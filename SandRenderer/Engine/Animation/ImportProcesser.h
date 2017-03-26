#ifndef IMPORT_PROCESSER_H
#define IMPORT_PROCESSER_H

namespace Sand
{
	class VScene;

	class ImportProcesser
	{
	public:
		virtual void Process( VScene& scene );
	};
}
#endif