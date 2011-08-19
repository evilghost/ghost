
#include "WidgetContainerViewAssociateableProxy.h"
#include "WidgetContainer.h"
#include "WidgetViewContainerAssociateableProxy.h"

namespace ghost{

	namespace widget{

		namespace container_proxy{

			ViewAssociateable::ViewAssociateable(Container& container)
				: AssociateableProxy(container)
				, m_pViewProxy(0)
			{

			}

			ViewAssociateable::~ViewAssociateable()
			{
				DisassociateFromAll();
			}

			View* ViewAssociateable::GetRootView() const
			{
				return m_pViewProxy ? &m_pViewProxy->GetProxiedObject() : (View*)0;
			}

			bool ViewAssociateable::AllowAssociatingWidth(Associateable* pObj) const
			{
				return 0 != dynamic_cast<view_proxy::ContainerAssociateable*>(pObj);
			}

			void ViewAssociateable::DisassociateFromAll()
			{
				DisassociateFrom(m_pViewProxy);
			}

			bool ViewAssociateable::IsAssociatedWidth(Associateable* pObj) const
			{
				return dynamic_cast<view_proxy::ContainerAssociateable*>(pObj) == m_pViewProxy;
			}

			void ViewAssociateable::DoAssociateWith(Associateable* pObj)
			{
				m_pViewProxy = dynamic_cast<view_proxy::ContainerAssociateable*>(pObj);
				// 对m_pRootView进行必要的初始化
			}

			void ViewAssociateable::DoDisassociateFrom(Associateable* pObj)
			{
				m_pViewProxy = 0;
			}

		} // namespace container_proxy

	} // namespace widget

} // namespace ghost