
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
				// ��Ϊ��view������븸view�Ĺ�ϵ
			}

			void AssociateContainer::DoDisassociateFrom(Associateable* pObj)
			{
				SingleAssociateableProxy::DoDisassociateFrom(pObj);
				// ��Ϊ����view�������ع���
			}

		} // namespace view_proxy

	} // namespace widget

} // namespace ghost