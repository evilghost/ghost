
#include "WViewAssociateContainerProxy.h"

namespace ghost{

	namespace widget{

		namespace view_proxy{

			AssociateContainer::AssociateContainer(View& view)
				: SingleAssociateableProxy(view)
			{

			}

			AssociateContainer::~AssociateContainer()
			{
				DisassociateFromAll();
			}

			Container* AssociateContainer::GetContainer() const
			{
				return GetAssociatedObject() ? &GetAssociatedObject()->GetProxiedObject() : (Container*)0;
			}

			void AssociateContainer::DoAssociateWith(Associateable* pObj)
			{
				SingleAssociateableProxy::DoAssociateWith(pObj);
				// 成为根view，解除与父view的关系
			}

			void AssociateContainer::DoDisassociateFrom(Associateable* pObj)
			{
				SingleAssociateableProxy::DoDisassociateFrom(pObj);
				// 成为悬挂view，解除相关关联
			}

		} // namespace view_proxy

	} // namespace widget

} // namespace ghost