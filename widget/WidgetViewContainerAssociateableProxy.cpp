
#include "WidgetViewContainerAssociateableProxy.h"
#include "WidgetView.h"
#include "WidgetContainerViewAssociateableProxy.h"

namespace ghost{

	namespace widget{

		namespace view_proxy{

			ContainerAssociateable::ContainerAssociateable(View& view)
				: AssociateableProxy(view)
				, m_pContainerProxy(0)
			{

			}

			ContainerAssociateable::~ContainerAssociateable()
			{
				DisassociateFromAll();
			}

			Container* ContainerAssociateable::GetContainer() const
			{
				return m_pContainerProxy ? &m_pContainerProxy->GetProxiedObject() : (Container*)0;
			}


			bool ContainerAssociateable::AllowAssociatingWidth(Associateable* pObj) const
			{
				return 0 != dynamic_cast<container_proxy::ViewAssociateable*>(pObj);
			}

			void ContainerAssociateable::DisassociateFromAll()
			{
				DisassociateFrom(m_pContainerProxy);
			}

			bool ContainerAssociateable::IsAssociatedWidth(Associateable* pObj) const
			{
				return dynamic_cast<container_proxy::ViewAssociateable*>(pObj) == m_pContainerProxy;
			}

			void ContainerAssociateable::DoAssociateWith(Associateable* pObj)
			{
				m_pContainerProxy = dynamic_cast<container_proxy::ViewAssociateable*>(pObj);
				// 成为根view，解除与父view的关系
			}

			void ContainerAssociateable::DoDisassociateFrom(Associateable* pObj)
			{
				m_pContainerProxy = 0;
				// 成为悬挂view，解除相关关联
			}

		} // namespace view_proxy

	} // namespace widget

} // namespace ghost