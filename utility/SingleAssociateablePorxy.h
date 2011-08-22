
#ifndef SINGLE_ASSOCIATEABLE_PROXY_H
#define SINGLE_ASSOCIATEABLE_PROXY_H

#include "NoCopyable.h"
#include "AssociateableProxy.h"

namespace ghost{

	namespace utility{

		template<typename PT, typename SAT>
		class SingleAssociateableProxy 
			: private NoCopyable
			, public AssociateableProxy<PT>
		{
		public:
			typedef SAT SingleAssociateType;

		private:
			SingleAssociateType* m_pAssociatedObject;

		public:
			explicit SingleAssociateableProxy(ProxiedType& obj)
				: AssociateableProxy(obj)
				, m_pAssociatedObject(0)
			{

			}
			virtual ~SingleAssociateableProxy()
			{
				DisassociateFromAll();
			}

		public:
			SingleAssociateType* GetAssociatedObject() const{return m_pAssociatedObject;}

		public: // 实现Associateable
			virtual bool AllowAssociatingWidth(Associateable* pObj) const
			{
				return 0 != dynamic_cast<SingleAssociateType*>(pObj);
			}
			virtual void DisassociateFromAll()
			{
				DisassociateFrom(m_pAssociatedObject);
			}

		protected: // 实现Associateable
			virtual bool IsAssociatedWidth(Associateable* pObj) const
			{
				return dynamic_cast<SingleAssociateType*>(pObj) == m_pAssociatedObject;
			}
			virtual void DoAssociateWith(Associateable* pObj)
			{
				m_pAssociatedObject = dynamic_cast<SingleAssociateType*>(pObj);
			}
			virtual void DoDisassociateFrom(Associateable* pObj)
			{
				m_pAssociatedObject = 0;
			}
		};


	} // namespace utility

} // namespace ghost

#endif // SINGLE_ASSOCIATEABLE_PROXY_H