#ifndef FBX_IMPORTER_PROCESSER_H
#define FBX_IMPORTER_PROCESSER_H

#include "ImportProcesser.h"

namespace Sand
{
	class Geometry;

	class FbxImporterProcesser : public ImportProcesser
	{
	public:
		virtual void Process( VScene& scene );

		void SetGeometry( Geometry* pGeometry );

		Geometry* GetGeometry();

	protected:
		Geometry* m_pGeometry;
	};
}
#endif