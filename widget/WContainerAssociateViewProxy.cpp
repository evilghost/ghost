
#include "WContainerAssociateViewProxy.h"

namespace ghost{

	namespace widget{

		namespace container_proxy{

			AssociateView::AssociateView(Container& container)
				: SingleAssociateableProxy(container)
			{

			}

			AssociateView::~AssociateView()
			{
				DisassociateFromAll();
			}

			View* AssociateView::GetRootView() const
			{
				return GetAssociatedObject() ? &GetAssociatedObject()->GetProxiedObject() : (View*)0;
			}

			void AssociateView::DoAssociateWith(Associateable* pObj)
			{
				SingleAssociateableProxy::DoAssociateWith(pObj);
				// 对根View进行必要的初始化
				// 1.如果有父组件，则脱离
				View* pRootView = GetRootView();
				pRootView->SetParent(0);
			}

		} // namespace container_proxy

	} // namespace widget

} // namespace ghost