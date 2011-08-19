
#ifndef ASSOCIATEABLE_PROXY_H
#define ASSOCIATEABLE_PROXY_H

#include "Associateable.h"

namespace ghost{

	namespace utility{

		template<typename T>
		class AssociateableProxy : public Associateable{
			T& m_obj;

		public:
			explicit AssociateableProxy(T& obj)
				: m_obj(obj)
			{

			}
			virtual ~AssociateableProxy()
			{

			}

		public:
			T& GetProxiedObject()
			{
				return m_obj;
			}
		};

	} // namespace utility

} // namespace ghost

#endif // ASSOCIATEABLE_PROXY_H