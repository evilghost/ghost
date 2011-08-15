
#include "WidgetContainer.h"
#include "WidgetView.h"

namespace ghost{

	namespace widget{

		Container::Container()
			: m_pRootView(0)
		{
		}

		Container::~Container()
		{
			DisassociateFromAll();
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
				// 克隆View树
			}
			return pObj;
		}

		bool Container::AllowAssociatingWidth(Associateable* pObj) const
		{
			return 0 != dynamic_cast<View*>(pObj);
		}

		void Container::DisassociateFromAll()
		{
			DisassociateFrom(m_pRootView);
		}

		bool Container::IsAssociatedWidth(Associateable* pObj) const
		{
			return dynamic_cast<View*>(pObj) == m_pRootView;
		}

		void Container::DoAssociateWith(Associateable* pObj)
		{
			m_pRootView = dynamic_cast<View*>(pObj);
			// 对m_pRootView进行必要的初始化
		}

		void Container::DoDisassociateFrom(Associateable* pObj)
		{
			// 对m_pRootView进行必要的清除
			m_pRootView = 0;
		}

		bool Container::SetRootView(View* pView)
		{
			return AssociateWith(pView);
		}

	} // namespace widget

} // namespace ghost