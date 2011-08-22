
#include "WView.h"
#include "WContainer.h"
#include "WViewAssociateContainerProxy.h"
#include "WViewAssociateParentProxy.h"
#include "WViewAssociateChildrenProxy.h"

namespace ghost{

	namespace widget{

		View::View()
		{
			m_pAssociateContainer = new view_proxy::AssociateContainer(*this);
			m_pAssociateParent = new view_proxy::AssociateParent(*this);
			m_pAssociateChildren = new view_proxy::AssociateChildren(*this);
		}

		View::~View()
		{
			delete m_pAssociateContainer;
			delete m_pAssociateParent;
			delete m_pAssociateChildren;
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
				m_pAssociateContainer->DisassociateFromAll();
				return true;
			}
			return m_pAssociateContainer->AssociateWith(pContainer->GetAssociateViewProxy());
		}

		Container* View::GetContainer() const
		{
			return m_pAssociateContainer->GetContainer();
		}

		bool View::SetParent(View* pParent)
		{
			if (!pParent)
			{
				// 取消Parent关联
				m_pAssociateParent->DisassociateFromAll();
				return true;
			}
			return m_pAssociateParent->AssociateWith(pParent->GetAssociateChildrenProxy());
		}

		View* View::GetParent() const
		{
			return m_pAssociateParent->GetParent();
		}

	} // namespace widget

} // namespace ghost