
#include "WContainer.h"
#include "WView.h"
#include "WContainerAssociateViewProxy.h"

namespace ghost{

	namespace widget{

		Container::Container()
		{
			m_pAssociateView = new container_proxy::AssociateView(*this);
		}

		Container::~Container()
		{
			delete m_pAssociateView;
		}

		Container* Container::Clone()
		{
			return 0;
		}

		template<>
		Container* Container::Clone<Container::WITH_VIEWS>()
		{
			Container* pObj = Clone();
			if (pObj)
			{
				// ��¡View��
				// ������¡��View���Ϳ�¡��Container
			}
			return pObj;
		}

		bool Container::SetRootView(View* pView)
		{
			if (!pView)
			{
				// ȡ����view����
				m_pAssociateView->DisassociateFromAll();
				return true;
			}
			return m_pAssociateView->AssociateWith(pView->GetAssociateContainerProxy());
		}

		View* Container::GetRootView() const
		{
			return m_pAssociateView->GetRootView();
		}

	} // namespace widget

} // namespace ghost