#ifndef EXPORT_PROCESSER_H
#define EXPORT_PROCESSER_H

namespace Sand
{
	class VScene;

	class ExportProcesser
	{
	public:
		virtual void Process( VScene& scene );
	};
}
#endif