
#include "WViewAssociateParentProxy.h"

namespace ghost{

	namespace widget{

		namespace view_proxy{

			AssociateParent::AssociateParent(View& view)
				: SingleAssociateableProxy(view)
			{

			}

			AssociateParent::~AssociateParent()
			{
				DisassociateFromAll();
			}

			View* AssociateParent::GetParent() const
			{
				return GetAssociatedObject() ? &GetAssociatedObject()->GetProxiedObject() : (View*)0;
			}

			void AssociateParent::DoDisassociateFrom(Associateable* pObj)
			{
				SingleAssociateableProxy::DoDisassociateFrom(pObj);
				// ��Ϊ����view�������ع���
			}

		} // namespace view_proxy

	} // namespace widget

} // namespace ghost