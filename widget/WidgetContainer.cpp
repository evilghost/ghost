
#include "WidgetContainer.h"
#include "WidgetView.h"

namespace ghost{

	namespace widget{

		Container::Container()
			: m_viewAssociateable(*this)
		{
		}

		Container::~Container()
		{
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
				m_viewAssociateable.DisassociateFromAll();
				return true;
			}
			return m_viewAssociateable.AssociateWith(&pView->GetContainerAssociateableProxy());
		}

		View* Container::GetRootView() const
		{
			return m_viewAssociateable.GetRootView();
		}

	} // namespace widget

} // namespace ghost