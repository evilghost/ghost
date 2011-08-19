
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
				// 克隆子View
				// 设置克隆的子View的父view为克隆的View
			}
			return pObj;
		}

		bool View::SetContainer(Container* pContainer)
		{
			if (!pContainer)
			{
				// 取消Container关联
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