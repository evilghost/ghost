
#include "WidgetView.h"
#include "WidgetContainer.h"

namespace ghost{

	namespace widget{

		View::View() 
			: m_containerAssociateable(*this)
		{
		}

		View::~View()
		{
		}

		View* View::Clone()
		{
			return 0;
		}

		template<>
		View* View::Clone<View::WITH_CHILDREN>()
		{
			View* pObj = Clone();
			if (pObj)
			{
				// ��¡��View
				// ���ÿ�¡����View�ĸ�viewΪ��¡��View
			}
			return pObj;
		}

		bool View::SetContainer(Container* pContainer)
		{
			if (!pContainer)
			{
				// ȡ��Container����
				m_containerAssociateable.DisassociateFromAll();
				return true;
			}
			return m_containerAssociateable.AssociateWith(&pContainer->GetViewAssociateableProxy());
		}

		Container* View::GetContainer() const
		{
			return m_containerAssociateable.GetContainer();
		}

	} // namespace widget

} // namespace ghost