
#ifndef ASSOCIATEABLE_PROXY_H
#define ASSOCIATEABLE_PROXY_H

#include "Associateable.h"

namespace ghost{

	namespace utility{

		template<typename PT>
		class AssociateableProxy : public Associateable{
		public:
			typedef PT ProxiedType;

		private:
			ProxiedType& m_obj;

		public:
			explicit AssociateableProxy(ProxiedType& obj)
				: m_obj(obj)
			{

			}
			virtual ~AssociateableProxy()
			{

			}

		public:
			ProxiedType& GetProxiedObject()
			{
				return m_obj;
			}
		};

	} // namespace utility

} // namespace ghost

#endif // ASSOCIATEABLE_PROXY_H