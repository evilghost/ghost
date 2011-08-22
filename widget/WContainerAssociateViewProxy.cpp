
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
				// �Ը�View���б�Ҫ�ĳ�ʼ��
				// 1.����и������������
				View* pRootView = GetRootView();
				pRootView->SetParent(0);
			}

		} // namespace container_proxy

	} // namespace widget

} // namespace ghost