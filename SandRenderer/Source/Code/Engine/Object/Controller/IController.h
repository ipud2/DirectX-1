#ifndef IController_h
#define IController_h

namespace Sand
{
	template < typename T > 
	class IController
	{
	public:
		IController();
		~IController();

		virtual void Update( float time ) = 0;

		void SetEntity( T* pEntity );
		T* GetEntity();

	protected:
		T* m_pEntity;
	};

	/*
		赋予对象层级关联的能力 
	*/
	template<typename T>
	class ControllerPack
	{
	public:
		ControllerPack( T* host ) : m_pHost( host )
		{

		}

		virtual ~ControllerPack()
		{

		}

		void Attach( IController<T>* pController )
		{
			if( pController )
			{
				pController->SetEntity( m_pHost );
				m_vControllers.push_back( pController );
			}
		}

		IController<T>* Get( int index )
		{
			if( index >= m_vControllers.size() )
			{
				return nullptr;
			}

			return m_vControllers[index];
		}

		void Update( float time )
		{
			for( auto pController : m_vControllers )
			{
				pController->Update( time );
			}
		}

	protected:
		T* m_pHost;
		std::vector<IController<T>*> m_vControllers;
	};

#include "IController.inl"
};

#endif